/** 
 * Descrição: Funções auxiliares para o sistema de gestão de vacinas
 * Autora: Carolina Matias (ist1114295)
*/

#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "base.h"
#include "estruturas.h"



/**
 * @brief Compara duas datas.
 * 
 * @param data_a Primeira data.
 * @param data_b Segunda data.
 * @return -1 se a primeira data for menor, 0 se forem iguais, 1 se maior.
 */
int compara_data(Data data_a, Data data_b);



/**
 * @brief Verifica se a data é válida e não anterior à data atual do sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param data Data a ser validada.
 * @param idioma_pt Inteiro que indica o idioma (1 para PT, 0 para EN).
 * @return 0 se a data for válida, -1 se não for.
 */
int eh_data_valida(Sistema *sistema, Data data, int idioma_pt);



/**
 * @brief Verifica se o nome de uma vacina é válido.
 * 
 * @param nome Ponteiro para o nome da vacina.
 * @return 0 se o nome for válido, -1 se não for.
 */
int eh_nomeVacina_valido(char *nome);



/**
 * @brief Verifica se o lote de uma vacina é válido.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param lote Ponteiro para o lote da vacina.
 * @param idioma_pt Inteiro que indica o idioma (1 para PT, 0 para EN).
 * @return 0 se o lote for válido, -1 se não for.
 */
int eh_lote_valido(Sistema *sistema, char *lote, int idioma_pt);



/**
 * @brief Adiciona uma vacina ao sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param nome_vacina Ponteiro para o nome da vacina.
 * @param lote Ponteiro para o lote.
 * @param validade Data de validade.
 * @param doses Número de doses.
 */
void aux_adiciona_vacina(Sistema *sistema,char *nome_vacina,char *lote,
    Data validade,int doses);



/**
 * @brief Ordena vacinas por data de validade e, em caso de empate, por lote.
 * 
 * @param lst Lista de vacinas.
 * @param esq Índice da esquerda.
 * @param dir Índice da direita.
 * @param meio Índice do meio.
 */
void aux_merge_vac(Vacina lst[],int esq,int dir,int meio);

/**
 * @brief Implementa o algoritmo de ordenação merge sort para vacinas.
 * 
 * @param lst Lista de vacinas.
 * @param esq Índice da esquerda.
 * @param dir Índice da direita.
 */
void mergeSort_vac(Vacina lst[],int esq,int dir);



/**
 * @brief Imprime a lista de vacinas.
 * 
 * @param vacina Vacina a ser impressa.
 */
void imprime_lista_vacinas(Vacina vacina);



/**
 * @brief Adiciona vacinas ao sistema a partir de uma string de entrada.
 * 
 * @param nomes_vacinas Matriz para armazenar os nomes das vacinas.
 * @param input String de entrada.
 * @return Número de vacinas adicionadas.
 */
int aux_lista_vacinas(char nomes_vacinas[MAX_LOTES][MAX_NOME_VACINA],
    char *input);



/**
 * @brief Verifica se uma vacina existe no sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param nomes_vacinas Matriz com os nomes das vacinas.
 * @param nmr_nomes Número de nomes.
 * @param idioma_pt Inteiro que indica o idioma (1 para PT, 0 para EN).
 */
void aux_processa_vac(Sistema *sistema,
    char nomes_vacinas[MAX_LOTES][MAX_NOME_VACINA],int nmr_nomes,
    int idioma_pt);



/**
 * @brief Verifica se um utente já foi vacinado com uma vacina.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param nome_utente Nome do utente.
 * @param nome_vacina Nome da vacina.
 * @return 1 se o utente já foi vacinado, 0 caso contrário.
 */
int eh_vacinado(Sistema *sistema, char *nome_utente, char *nome_vacina);



/**
 * @brief Processa o nome do utente e da vacina a partir de uma string.
 * 
 * @param input String de entrada.
 * @param nome_utente Ponteiro para o nome do utente.
 * @param nome_vacina Ponteiro para o nome da vacina.
 */
void aux_aplica_dose(char *input, char **nome_utente,char *nome_vacina, 
    int idioma_pt);



/**
 * @brief Verifica se o nome da vacina está no sistema e se há doses válidas.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param nome_vacina Nome da vacina.
 * @return Índice do lote encontrado, -1 se não for encontrado.
 */
int aux_encontra_lote(Sistema *sistema, char *nome_vacina);



/**
 * @brief Adiciona uma inoculação ao sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param nome_utente Nome do utente.
 * @param nome_vacina Nome da vacina.
 * @param lote_encontrado Índice do lote encontrado.
 */
void aux_adiciona_inoculacao(Sistema *sistema, char *nome_utente,
    char *nome_vacina,int lote_encontrado);



/**
 * @brief Extrai o nome do utente de uma string de entrada.
 * 
 * @param input String de entrada.
 * @param nome_utente Ponteiro para o nome do utente.
 */
void aux_lista_aplicacoes(char *input,char *nome_utente);



/**
 * @brief Ordena inoculações por data ou por ordem alfabética do lote.
 * 
 * @param lst Lista de inoculações.
 * @param esq Índice da esquerda.
 * @param dir Índice da direita.
 * @param meio Índice do meio.
 */
void aux_merge_api(Inoculacao lst[],int esq,int dir,int meio);

/**
 * @brief Implementa o algoritmo de ordenação merge sort para inoculações.
 * 
 * @param lst Lista de inoculações.
 * @param esq Índice da esquerda.
 * @param dir Índice da direita.
 */
void mergeSort_api(Inoculacao lst[],int esq,int dir);



/**
 * @brief Conta o número de doses aplicadas de um lote.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param lote Nome do lote.
 * @return Número de doses aplicadas.
 */
int aux_doses_aplicadas(Sistema *sistema,char *lote);



/**
 * @brief Remove um lote específico do sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param lote Nome do lote.
 * @return 1 se o lote foi removido, 0 caso contrário.
 */
int aux_remove_lote(Sistema *sistema,char *lote);



/**
 * @brief Verifica se o utente ou lote existem no sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param arg String de entrada.
 * @param identificador Inteiro que indica se é utente (1) ou lote (2).
 * @return 1 se existir, 0 caso contrário.
 */
int aux_verifica_UtenteELote(Sistema *sistema, char *arg, int identificador);



/**
 * @brief Remove todas as inoculações de um utente em uma data específica.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param nome_utente Nome do utente.
 * @param data Data específica.
 * @return Número de inoculações removidas.
 */
int aux_remove_inoculacoes_utente_data(Sistema *sistema,char *nome_utente,
    Data *data);



/**
 * @brief Remove todas as inoculações de um utente.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param nome_utente Nome do utente.
 * @return Número de inoculações removidas.
 */
int aux_remove_inoculacoes_utente(Sistema *sistema, char *nome_utente);



/**
 * @brief Remove uma inoculação específica de um utente.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param nome_utente Nome do utente.
 * @param lote Nome do lote.
 * @param data Data da inoculação.
 * @return Número de inoculações removidas.
 */
int aux_remove_inoculacao_especifica(Sistema *sistema,char *nome_utente,
    char*lote,Data *data);


    
/**
 * @brief Imprime erro caso o lote não exista no sistema.
 * 
 * @param sistema Ponteiro para o sistema.
 * @param lote Nome do lote.
 * @param entrada Inteiro que indica se é utente ou lote.
 * @param idioma_pt Inteiro que indica o idioma (1 para PT, 0 para EN).
 * @return 0 se o lote existir, -1 caso contrário.
 */
int erro_nobatch(Sistema *sistema, char *lote, int entrada, int idioma_pt);



/**
 * @brief Valida o idioma do sistema.
 * 
 * @param num Número de argumentos.
 * @param args Matriz de argumentos.
 * @return 1 se o idioma for PT, 0 se for EN.
 */
int idioma(int num, char *args[]);

#endif