/*
    Descrição: Definições de constantes e estruturas para o sistema de 
    gestão de vacinas
    Autora: Carolina Matias (ist1114295)
*/

#ifndef BASE_H
#define BASE_H

#define MAX_LOTES 1000 
#define MAX_NOME_LOTE 20 + 1
#define MAX_NOME_VACINA 50 + 1
#define MAX_CARACTERES 65535 + 1

/**Definição dos erros em inglês*/
#define NOMEMORY_EN "no memory"
#define TOOMANYVAC_EN "too many vaccines"
#define INVNAME_EN "invalid name"
#define INVDATE_EN "invalid date"
#define INVBATCH_EN	"invalid batch"
#define INVQUANTITY_EN "invalid quantity"
#define DUPEBATCH_EN "duplicate batch number"
#define NOVACCINE_EN "no such vaccine"
#define NOSTOCK_EN "no stock"
#define VACCINATED_EN "already vaccinated"
#define NOBATCH_EN "no such batch"
#define NOUSER_EN "no such user"

/**Definição dos erros em português*/
#define NOMEMORY_PT "sem memória"
#define TOOMANYVAC_PT "demasiadas vacinas"
#define INVNAME_PT "nome inválido"
#define INVDATE_PT "data inválida"
#define INVBATCH_PT "lote inválido"
#define INVQUANTITY_PT "quantidade inválida"
#define DUPEBATCH_PT "número de lote duplicado"
#define NOVACCINE_PT "vacina inexistente"
#define NOSTOCK_PT "esgotado"
#define VACCINATED_PT "já vacinado"	
#define NOBATCH_PT "lote inexistente"
#define NOUSER_PT "utente inexistente"


#endif 