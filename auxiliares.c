/** 
 * Descrição: Funções auxiliares para o sistema de gestão de vacinas
 * Autora: Carolina Matias (ist1114295)
*/

#include "auxiliares.h"
#include "base.h"
#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



int compara_data(Data data_a, Data data_b){
    /*Se a data a for mais antiga que a data b*/
    if (data_a.ano<data_b.ano || 
        (data_a.ano==data_b.ano && data_a.mes<data_b.mes) || 
        (data_a.ano==data_b.ano && data_a.mes==data_b.mes && 
        data_a.dia<data_b.dia)){
        return -1;
    }
    /*Se a data a for igual à data b*/
    if (data_a.dia==data_b.dia && data_a.mes==data_b.mes && 
        data_a.ano==data_b.ano){
        return 0;
    }   
    /*Se a data a for mais recente que a data b*/
    return 1;
}



int eh_data_valida(Sistema *sistema, Data data, int idioma_pt){
    int dias[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (data.mes<1||data.mes>12||data.dia<1||data.dia>dias[data.mes-1]){
        printf("%s\n",idioma_pt?INVDATE_PT:INVDATE_EN);
        return -1;
    }

    /*Verifica se a data de validade não é inferior à data atual do sistema*/
    if (compara_data(sistema->data_atual,data)>0){
        printf("%s\n",idioma_pt?INVDATE_PT:INVDATE_EN);
        return -1;
    }   
    
    return 0;
}



int eh_nomeVacina_valido(char *nome){
    int len=strlen(nome);
    if (len>=MAX_NOME_VACINA){
        return -1;
    }
    for (int i=0;i<len;++i){
        if (isspace(nome[i])){
            return -1;
        }
    }
    return 0;
}



int eh_lote_valido(Sistema *sistema, char *lote,int idioma_pt){
    int len=strlen(lote);
    int nmr_vacinas=sistema->n_vacinas;
    
    /*Verifica se o lote tem o tamanho correto*/
    if (len>MAX_NOME_LOTE){
        puts(idioma_pt?INVBATCH_PT:INVBATCH_EN);
        return -1;
    }

    /*Verifica se o lote só é composto por letras de A a F ou números de 0-9*/
    for (int i= 0;i<len;++i){
        if (!((lote[i]>='A' && lote[i]<='F')||isdigit(lote[i]))){
            puts(idioma_pt?INVBATCH_PT:INVBATCH_EN);
            return -1;
        }
    }

    /*Verifica se o lote é ou não duplicado*/
    for (int i=0;i<nmr_vacinas;++i){
        if (strcmp(sistema->vacinas[i].lote,lote)==0){
            puts(idioma_pt?DUPEBATCH_PT:DUPEBATCH_EN);
            return -1;
        }
    }
    return 0;
}



void aux_adiciona_vacina(Sistema *sistema,char *nome_vacina,char *lote,
    Data validade,int doses){
    Vacina nova_vacina={.validade=validade,.doses=doses,.administrados=0}; 
    strcpy(nova_vacina.nome,nome_vacina);
    strcpy(nova_vacina.lote,lote);

    sistema->vacinas[sistema->n_vacinas++]=nova_vacina;
    printf("%s\n",lote);
}



void aux_merge_vac(Vacina lst[],int esq,int dir,int meio){
    int esquerda=meio-esq+1; 
    int direita=dir-meio;
    Vacina *E=(Vacina*)malloc(esquerda*sizeof(Vacina)); 
    Vacina *D=(Vacina*)malloc(direita*sizeof(Vacina));
    /*Copia os elementos para as sublistas*/
    for (int i=0;i<esquerda;++i){
        E[i]=lst[esq+i];
    }
    for (int i=0;i<direita;++i){
        D[i]=lst[meio+1+i];
    }
    int i=0,j=0,k=esq; 
    while (i<esquerda && j<direita){
        int compara_datas=compara_data(E[i].validade,D[j].validade);
        if (compara_datas<0||(compara_datas==0 && 
            strcmp(E[i].lote,D[j].lote)<0)){
            lst[k++]=E[i++];
        } else {
            lst[k++]=D[j++];
        }
    }
    while (i<esquerda){
        lst[k++]=E[i++];
    }
    while (j<direita){
        lst[k++]=D[j++];
    }
    free(E);
    free(D);
}

void mergeSort_vac(Vacina lst[],int esq,int dir){
    if (esq<dir){
        int meio=esq+(dir-esq)/2; 
        /*Ordena as duas metades separadamente e depois combina as 
        duas metades ordenadas*/
        mergeSort_vac(lst,esq,meio);
        mergeSort_vac(lst,meio+1,dir);
        aux_merge_vac(lst,esq,dir,meio);
    }
}



void imprime_lista_vacinas(Vacina vacina){
    printf("%s %s %02d-%02d-%04d %d %d\n",vacina.nome,vacina.lote,
    vacina.validade.dia,vacina.validade.mes,vacina.validade.ano,
    vacina.doses,vacina.administrados);
}



int aux_lista_vacinas(char nomes_vacinas[MAX_LOTES][MAX_NOME_VACINA],
    char *input){

    /*divide a string de entrada com "\n"*/
    char *ponteiro=strtok(input," \n");
    int nmr_nomes=0; 
    while (ponteiro!=NULL){
        strcpy(nomes_vacinas[nmr_nomes],ponteiro);
        nomes_vacinas[nmr_nomes][MAX_NOME_VACINA-1]='\0';
        nmr_nomes++;
        ponteiro=strtok(NULL," \n");
    }
    return nmr_nomes;
}



void aux_processa_vac(Sistema *sistema,
    char nomes_vacinas[MAX_LOTES][MAX_NOME_VACINA],int nmr_nomes,
    int idioma_pt){

    int nmr_vacinas=sistema->n_vacinas; 
    for (int j=0;j<nmr_nomes;++j){

        int vacina_encontrada=0; 
        for (int i=0;i<nmr_vacinas;++i){
            if (strcmp(sistema->vacinas[i].nome,nomes_vacinas[j])==0){
                vacina_encontrada=1;
                imprime_lista_vacinas(sistema->vacinas[i]);
            }
        }
        if (vacina_encontrada==0){
            printf("%s: %s\n",nomes_vacinas[j],
                idioma_pt?NOVACCINE_PT:NOVACCINE_EN);
        }
    }
}



int eh_vacinado(Sistema *sistema,char *nome_utente,char *nome_vacina){
    int nmr_inoculacoes=sistema->n_inoculacoes;

    for (int i=0;i<nmr_inoculacoes;++i){
        if (strcmp(sistema->inoculacoes[i].nome,nome_vacina)==0 && 
            strcmp(sistema->inoculacoes[i].utente,nome_utente)==0 &&
            compara_data(sistema->inoculacoes[i].data_vac,
                sistema->data_atual)==0){
            return 1; 
        }
    }   
    return 0;
}



void aux_aplica_dose(char *input, char **nome_utente, char *nome_vacina,
    int idioma_pt){
    char *nome=input;
    while (isspace(*nome)){nome++;  
    }
    if (*nome=='"'){ /*Se o nome do utente estiver entre aspas*/
        nome++;
        char *fim_nome=strchr(nome,'"');
        if (!fim_nome){
            *nome_utente=NULL;return;
        }
        *fim_nome='\0';
    }else{
        char *fim_nome=nome; /*Caso o nome do utente não estar entre aspas*/
        while (*fim_nome && !isspace(*fim_nome)){fim_nome++;
        }
        *fim_nome='\0';
    }
    *nome_utente=malloc(strlen(nome)+1);
    if (*nome_utente){
        /*se conseguir alocar a memória, copio o nome para o nome do utente*/
        strcpy(*nome_utente,nome);
    }else{
        *nome_utente=NULL; /*caso não consiga alocar a memória*/
        printf("%s\n",idioma_pt?NOMEMORY_PT:NOMEMORY_EN);return;
    }
    nome+=strlen(nome)+1;
    while (isspace(*nome)){ nome++; /*avança para o próximo nome*/
    }
    sscanf(nome,"%50s",nome_vacina);
}



int aux_encontra_lote(Sistema *sistema, char *nome_vacina){
    int nmr_vacinas=sistema->n_vacinas; /*Número de vacinas do sistema*/
    int lote_encontrado=-1; 
    for (int i=0;i<nmr_vacinas;++i){

        if (strcmp(sistema->vacinas[i].nome,nome_vacina)==0 && 
            sistema->vacinas[i].doses>0 &&
            compara_data(sistema->vacinas[i].validade,sistema->data_atual)>=0){

            if (lote_encontrado==-1||
                compara_data(sistema->vacinas[i].validade,
                    sistema->vacinas[lote_encontrado].validade)<0){
                    lote_encontrado=i;
            }
        }
    }
    return lote_encontrado;
}



void aux_adiciona_inoculacao(Sistema *sistema,char *nome_utente,
    char *nome_vacina, int lote_encontrado){
    int nmr_inoculacoes=sistema->n_inoculacoes;
    
    /*Cria uma inoculação nova*/
    Inoculacao nova_inoculacao;
    nova_inoculacao.utente=strdup(nome_utente);
    strcpy(nova_inoculacao.nome,nome_vacina);
    strcpy(nova_inoculacao.lote,sistema->vacinas[lote_encontrado].lote);    
    nova_inoculacao.data_vac=sistema->data_atual;
    
    /*Adiciona a inoculação ao sistema*/
    sistema->inoculacoes[nmr_inoculacoes]=nova_inoculacao;
    sistema->n_inoculacoes++;
    
    /*atualiza o sistema*/
    sistema->vacinas[lote_encontrado].doses--;
    sistema->vacinas[lote_encontrado].administrados++;

    printf("%s\n",sistema->vacinas[lote_encontrado].lote);
    
}



void aux_lista_aplicacoes(char *input,char *nome_utente){
    char *nome=input;

    while (isspace(*nome)){
        nome++;
    }

    if (*nome=='"'){
        nome++; 
        char *fim_nome=strchr(nome,'"'); 

        if (fim_nome){
            *fim_nome='\0';  
            strcpy(nome_utente,nome);
            nome_utente[MAX_CARACTERES-1]='\0'; 
        }else{
            nome_utente[0]='\0';
        }
    }else{
        sscanf(nome,"%65535s",nome_utente);
    }
}



void aux_merge_api(Inoculacao lst[],int esq,int dir,int meio){
    int esquerda=meio-esq+1;
    int direita=dir-meio;
    Inoculacao *E=(Inoculacao*)malloc(esquerda*sizeof(Inoculacao));
    Inoculacao *D=(Inoculacao*)malloc(direita*sizeof(Inoculacao));
    for (int i=0;i<esquerda;++i){
        E[i]=lst[esq+i];
    }
    for (int i=0;i<direita;++i){
        D[i]=lst[meio+1+i];
    }
    int i=0,j=0,k=esq;
    while (i<esquerda && j<direita){
        int compara_datas=compara_data(E[i].data_vac,D[j].data_vac);
        if (compara_datas<=0){
            lst[k++]=E[i++];
        } else {
            lst[k++]=D[j++];
        }
    }
    while (i<esquerda){
        lst[k++]=E[i++];
    }
    while (j<direita){
        lst[k++]=D[j++];
    }
    free(E);
    free(D);
}

void mergeSort_api(Inoculacao lst[],int esq,int dir){
    if (esq<dir){
        int meio=esq+(dir-esq)/2; /*Calcula o índice do meio*/
        mergeSort_api(lst,esq,meio);
        mergeSort_api(lst,meio+1,dir);
        aux_merge_api(lst,esq,dir,meio);
    }
}



int aux_doses_aplicadas(Sistema *sistema,char *lote){
    int nmr_inoculacoes=sistema->n_inoculacoes;
    int doses=0;

    for (int i=0;i<nmr_inoculacoes;++i){
        if (strcmp(sistema->inoculacoes[i].lote,lote)==0){
            doses++;
        }
    }
    return doses;
}



int aux_remove_lote(Sistema *sistema,char *lote){
    int nmr_vacinas=sistema->n_vacinas;
    for (int i=0;i<nmr_vacinas;++i){
        if (strcmp(sistema->vacinas[i].lote,lote)==0){
            sistema->vacinas[i]=sistema->vacinas[nmr_vacinas-1];
            sistema->n_vacinas--;
            return 1;
        }
    }
    return 0;
}



int aux_verifica_UtenteELote(Sistema *sistema, char *arg, int identificador){
    int nmr_inoculacoes=sistema->n_inoculacoes;
    int nmr_vacinas=sistema->n_vacinas;

    /*Verifica se o nome do utente existe*/
    if (identificador==1){
        for (int i=0;i<nmr_inoculacoes;++i){
            if (strcmp(sistema->inoculacoes[i].utente,arg)==0){
                return 1;
        }
    }
    /*Verifica se o lote existe*/
    }else if (identificador==2){
        for (int i=0;i<nmr_vacinas;++i){
            if (strcmp(sistema->vacinas[i].lote,arg)==0){
                return 1;
            }
        }
    
    /*Caso o nome do utente ou o lote não forem encontrados*/
    }return 0;
}


/**Remove todas as inoculações do utente daquela data*/
int aux_remove_inoculacoes_utente_data(Sistema *sistema,char *nome_utente,
    Data *data){
    int nmr_inoculacoes=sistema->n_inoculacoes; 
    int removidas=0; 

    for (int i=0;i<nmr_inoculacoes;++i){
        int remove=0;
        if (strcmp(sistema->inoculacoes[i].utente,nome_utente)==0 && 
            compara_data(sistema->inoculacoes[i].data_vac,*data)==0){
            remove=1;
        }
        if (remove==1){
            /*Liberta a memória da inoculação anterior*/
            free(sistema->inoculacoes[i].utente); 
            for (int j=i;j<nmr_inoculacoes;++j){
            /*Desloca todas as inoculações restantes para o índice anterior*/
                sistema->inoculacoes[j]=sistema->inoculacoes[j+1]; 
            }
            removidas++;
            nmr_inoculacoes--;
            i--;
        }
    }
    sistema->n_inoculacoes=nmr_inoculacoes;
    return removidas;
}


/**Remove todas as inoculações do utente*/
int aux_remove_inoculacoes_utente(Sistema *sistema, char *nome_utente){
    int nmr_inoculacoes=sistema->n_inoculacoes;
    int removidas=0;

    for (int i=0;i<nmr_inoculacoes;++i){
        int remove=0;
        if (strcmp(sistema->inoculacoes[i].utente,nome_utente)==0){
            remove=1;
        }
        if (remove==1){
            /*Liberta a memória da inoculação anterior*/
            free(sistema->inoculacoes[i].utente); 
            for (int j=i;j<nmr_inoculacoes;++j){
            /*Desloca todas as inoculações restantes para o índice anterior*/
                sistema->inoculacoes[j]=sistema->inoculacoes[j+1]; 
            }
            removidas++;
            nmr_inoculacoes--;
            i--;
        }
    }
    sistema->n_inoculacoes=nmr_inoculacoes;
    return removidas;
}


/**Remove uma inoculação específica*/
int aux_remove_inoculacao_especifica(Sistema *sistema,char *nome_utente,
    char *lote,Data *data){
    int nmr_inoculacoes=sistema->n_inoculacoes; 
    int removidas=0;

    for (int i=0;i<nmr_inoculacoes;++i){
        int remove=0; 
        if (strcmp(sistema->inoculacoes[i].utente,nome_utente)==0 && 
            strcmp(sistema->inoculacoes[i].lote,lote)==0 && 
            compara_data(sistema->inoculacoes[i].data_vac,*data)==0){
            remove=1;
            }
        if (remove==1){
            /*Se for possível remover, liberta a memória da inoculação do 
            utente anterior*/
            free(sistema->inoculacoes[i].utente); 
            for (int j=i;j<nmr_inoculacoes;++j){
            /*e desloca todas as inoculações restantes para o índice anterior*/
                sistema->inoculacoes[j]=sistema->inoculacoes[j+1]; 
            }
            removidas++;
            nmr_inoculacoes--;
            i--;
        }
    }
    sistema->n_inoculacoes=nmr_inoculacoes;
    return removidas;
}



int erro_nobatch(Sistema *sistema, char *lote, int entrada, int idioma_pt){
    if (entrada==5 && !aux_verifica_UtenteELote(sistema,lote,2)){
        printf("%s: %s\n",lote,idioma_pt?NOBATCH_PT:NOBATCH_EN);
        return 1;
    }
    return 0;
}



int idioma(int num, char *args[]){
    if (num>1){
        if (strcmp(args[1],"pt")==0){
            return 1;
        }
    }
    return 0;
}