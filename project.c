/* iaed25 - ist1114295 - project */
/** 
 * Descrição: Sistema de gestão de vacinas
 * Autora: Carolina Matias (ist1114295)
*/

#include "base.h"
#include "auxiliares.h"
#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



/*Inicializa a estrutura com a data inicial do sistema*/
Sistema sistema={.data_atual={1,1,2025}};

/**
 * @brief Comando 'c': Adiciona um lote de vacina ao sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param input Ponteiro para o input do utilizador.
 * @param idioma_pt Inteiro que irá definir o idioma (1 para PT, 0 para EN).
 */
void adiciona_lote(Sistema *sistema, char *input, int idioma_pt){
    char lote[MAX_NOME_LOTE],nome_vacina[MAX_CARACTERES];

    int dia,mes,ano,
    doses,n_vacinas=sistema->n_vacinas;

    int entrada=sscanf(input,"%s %d-%d-%d %d %s",lote,&dia,&mes,&ano,
        &doses,nome_vacina);
    Data validade={dia,mes,ano};

    if (entrada!=6||eh_nomeVacina_valido(nome_vacina)<0){
        puts(idioma_pt?INVNAME_PT:INVNAME_EN);
        return;
    }
    if (n_vacinas>=MAX_LOTES){
        puts(idioma_pt?TOOMANYVAC_PT:TOOMANYVAC_EN);
        return;
    }
    if(eh_lote_valido(sistema,lote,idioma_pt)<0||
    eh_data_valida(sistema,validade,idioma_pt)<0){
        return;
    }
    if (doses<1){
        puts(idioma_pt?INVQUANTITY_PT:INVQUANTITY_EN);
        return;
    }
    aux_adiciona_vacina(sistema,nome_vacina,lote,validade,doses);
}



/**
 * @brief Comando 'l': Lista os lotes de vacinas do sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param input Ponteiro para o input do utilizador.
 * @param idioma_pt Inteiro que irá definir o idioma (1 para PT, 0 para EN).
 */
void lista_vacinas(Sistema *sistema,char *input, int idioma_pt){
    char nomes_vacinas[MAX_LOTES][MAX_NOME_VACINA];
    int nmr_vacinas=sistema->n_vacinas;
    
    /*armazena o número de nomes de vacinas*/
    int nmr_nomes=aux_lista_vacinas(nomes_vacinas,input); 

    /*Organizar as vacinas por ordem cronológica de data ou por
    ordem alfabética do lote caso tenham a mesma data*/
    mergeSort_vac(sistema->vacinas,0,nmr_vacinas-1); 
 
    if (nmr_nomes>0){
        aux_processa_vac(sistema,nomes_vacinas,nmr_nomes,idioma_pt);
    }else{
        for (int i=0;i<nmr_vacinas;++i){
            imprime_lista_vacinas(sistema->vacinas[i]);
        }
    }
}



/**
 * @brief Comando 'a': Aplica uma vacina a um utente.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param input Ponteiro para o input do utilizador.
 * @param idioma_pt Inteiro que irá definir o idioma (1 para PT, 0 para EN).
 */
void aplica_dose(Sistema *sistema,char *input,int idioma_pt){ 
    char *nome_utente=NULL,
    nome_vacina[MAX_NOME_VACINA]; 
    
    /*vai tirar o nome do utente e da vacina*/
    aux_aplica_dose(input,&nome_utente,nome_vacina,idioma_pt);

    if (eh_vacinado(sistema,nome_utente,nome_vacina)){
        puts(idioma_pt?VACCINATED_PT:VACCINATED_EN);
        free(nome_utente);
        return;
    }
    /*armazena o índice do lote que da vacina a aplicar*/
    int lote_encontrado=aux_encontra_lote(sistema,nome_vacina);

    if (lote_encontrado==-1){
        puts(idioma_pt?NOSTOCK_PT:NOSTOCK_EN);
        free(nome_utente);
        return;
    }
    
    /*Adiciona ao sistema a aplicação da vacina ao utente*/
    aux_adiciona_inoculacao(sistema,nome_utente,nome_vacina,lote_encontrado);
    
    free(nome_utente);
   
}



/**
 * @brief Comando 'r':Retira a disponibilidade de um lote de vacinas do 
 *          sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param lote Ponteiro para o nome do lote.
 * @param idioma_pt Inteiro que irá definir o idioma (1 para PT, 0 para EN).
 */
void remove_lote(Sistema *sistema, char *lote, int idioma_pt){
    int nmr_vacinas=sistema->n_vacinas,
    doses_aplicadas=aux_doses_aplicadas(sistema,lote);
    char lote_aux[MAX_NOME_LOTE];
    sscanf(lote,"%s",lote_aux);
    
    for (int i=0;i<nmr_vacinas;++i){
        if (doses_aplicadas>0 && strcmp(sistema->vacinas[i].lote,lote)==0){
            sistema->vacinas[i].doses=0;
            sistema->vacinas[i].administrados=doses_aplicadas;
            printf("%d\n",doses_aplicadas);
            return;
        }
        if (doses_aplicadas==0 && 
            strcmp(sistema->vacinas[i].lote,lote_aux)==0){
            aux_remove_lote(sistema,lote_aux);
            printf("%d\n",doses_aplicadas);
            return;
        }
    }
    printf("%s: %s\n",lote_aux,idioma_pt?NOBATCH_PT:NOBATCH_EN);
}
    


/**
 * @brief Comando 'd': Apaga o registo de aplicações da vacina do sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param input Ponteiro para o input do utilizador.
 * @param idioma_pt Inteiro que irá definir o idioma (1 para PT, 0 para EN).
 */
void apaga_registos(Sistema *sistema, char *input, int idioma_pt) {
    Data data; 
    char nome_utente[MAX_CARACTERES]= "", lote[MAX_NOME_LOTE]= "";
    int entrada,removidas,dias[]={31,28,31,30,31,30,31,31,30,31,30,31};
        entrada=sscanf(input,"%s %d-%d-%d %s",nome_utente,&data.dia,&data.mes,
        &data.ano,lote);
    if (!aux_verifica_UtenteELote(sistema,nome_utente,1)){
        printf("%s: %s\n",nome_utente,idioma_pt?NOUSER_PT:NOUSER_EN);return;
    }
    if (entrada>=2){
        if (data.mes<1||data.mes>12||data.dia<1||data.dia>dias[data.mes-1]
        ||compara_data(data,sistema->data_atual)>0){
            printf("%s\n",idioma_pt?INVDATE_PT:INVDATE_EN);return;
        }
    }
    if (erro_nobatch(sistema,lote,entrada,idioma_pt)==1){return;
    }
    if (entrada==4){
        removidas=aux_remove_inoculacoes_utente_data(sistema,nome_utente,
            &data);
    } else if (entrada==5){
        removidas=aux_remove_inoculacao_especifica(sistema,nome_utente,lote, 
            &data);
    } else{
        removidas=aux_remove_inoculacoes_utente(sistema,nome_utente);
    }
    printf("%d\n",removidas);
}
 


/**
 * @brief Comando 'u': Lista as aplicações de vacinas do sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param input Ponteiro para o input do utilizador.
 * @param idioma_pt Inteiro que irá definir o idioma (1 para PT, 0 para EN).
 */
void lista_aplicacoes(Sistema *sistema,char *input,int idioma_pt){
    char nome_utente[MAX_CARACTERES]="";
    int nmr_inoculacoes=sistema->n_inoculacoes;
    int existe_utente=0;

    /*processa o nome do utente do input*/
    aux_lista_aplicacoes(input,nome_utente);
    /*Organiza a lista por ordem cronológica de aplicação*/
    mergeSort_api(sistema->inoculacoes,0,nmr_inoculacoes-1);

    for (int i=0;i<nmr_inoculacoes;++i){ 
        if (strlen(nome_utente)==0||
            strcmp(sistema->inoculacoes[i].utente,nome_utente)==0){
            printf("%s %s %02d-%02d-%04d\n",sistema->inoculacoes[i].utente,
            sistema->inoculacoes[i].lote,
            sistema->inoculacoes[i].data_vac.dia,
            sistema->inoculacoes[i].data_vac.mes,
            sistema->inoculacoes[i].data_vac.ano);
            existe_utente=1;
        }
    }
    if (!existe_utente){
        printf("%s: %s\n",nome_utente,idioma_pt?NOUSER_PT:NOUSER_EN);
    }
}



/**
 * @brief Comando 't': Avança a data do sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param input Ponteiro para o input do utilizador.
 * @param idioma_pt Inteiro que irá definir o idioma (1 para PT, 0 para EN).
 */
void avanca_data(Sistema *sistema, char *input, int idioma_pt){
    Data data;
    int entrada;

    if (input[0]=='\n'){
        printf("%02d-%02d-%04d\n",sistema->data_atual.dia,
            sistema->data_atual.mes,sistema->data_atual.ano);
        return;
    }

    entrada=sscanf(input,"%d-%d-%d",&data.dia,&data.mes,&data.ano);

    if (entrada!=3){
        puts(idioma_pt?INVDATE_PT:INVDATE_EN);
        return;
    }
    if (eh_data_valida(sistema,data,idioma_pt)<0){
        return;
    }
    /*Atualiza a data do sistema*/
    sistema->data_atual.dia=data.dia;
    sistema->data_atual.mes=data.mes;
    sistema->data_atual.ano=data.ano;
    printf("%02d-%02d-%04d\n",data.dia,data.mes,data.ano);
}



/**
 * @brief Função principal onde todos os comandos são processados.
 * 
 * @param num Inteiro que indica o número de argumentos.
 * @param args Matriz de argumentos.
 * 
 * @return Retorna 0 se o programa correr sem erros.
 */
int main(int num,char *args[]){
    Sistema sistema={.n_vacinas=0,.n_inoculacoes=0,.data_atual={1,1,2025}};
    sistema.inoculacoes=malloc(MAX_LOTES *sizeof(Inoculacao));

    char escolha,input[MAX_CARACTERES];
    int idioma_pt=idioma(num,args);
    while ((escolha=getchar())!='q'){
        fgets(input,sizeof(input),stdin);
        switch (escolha){
            case 'c':adiciona_lote(&sistema,input,idioma_pt);break;
            case 'l':lista_vacinas(&sistema,input,idioma_pt);break;
            case 'a':aplica_dose(&sistema,input,idioma_pt);break;
            case 'r':remove_lote(&sistema,input,idioma_pt);break;
            case 'd':apaga_registos(&sistema,input,idioma_pt);break;
            case 'u':lista_aplicacoes(&sistema,input,idioma_pt);break;
            case 't':avanca_data(&sistema,input,idioma_pt);break;
        }
    }
    for (int i=0;i<sistema.n_inoculacoes;++i){
        if (sistema.inoculacoes[i].utente!=NULL) {
            free(sistema.inoculacoes[i].utente);
        }
    }
    free(sistema.inoculacoes);
    return 0;
}


