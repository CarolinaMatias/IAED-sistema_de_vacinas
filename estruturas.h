/** 
 * Descrição: Estruturas para o sistema de gestão de vacinas
 * Autora: Carolina Matias (ist1114295)
*/

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "base.h"



/**
 * @brief Define estrutura para a data
*/
typedef struct{
    int dia,mes,ano;/**Dia, mês e ano de uma data*/
}Data;



/**
 * @brief Define estrutura para a vacina
*/
typedef struct{
    char nome[MAX_NOME_VACINA];/**Array que armazena o nome da vacina*/
    char lote[MAX_NOME_LOTE];/**Array que armazena o nome do lote*/
    Data validade;/**Data de validade do lote*/
    int doses;/**Número de doses disponíveis no lote*/
    int administrados;/**Número de doses já administradas*/
}Vacina;



/**
 * @brief Define estrutura para a inoculacao
*/
typedef struct{
    char *utente;/**Nome de utente alocado dinamicamente*/
    char nome[MAX_NOME_VACINA];/**Nome da vacina administrada*/
    char lote[MAX_NOME_LOTE];/**Array que armazena o nome do lote administrado*/
    Data data_vac;/**Data de vacinação*/
}Inoculacao;



/**
 * @brief Define estrutura para o sistema de vacinas
*/
typedef struct{
    Vacina vacinas[MAX_LOTES]; /**Array que armazena as vacinas*/
    Inoculacao *inoculacoes; /**Ponteiro para as inoculações*/
    int n_vacinas; /**Número de vacinas do sistema*/
    int n_inoculacoes; /**Número de inoculações do sistema*/
    Data data_atual; /**Data atual do sistema*/
}Sistema;

#endif