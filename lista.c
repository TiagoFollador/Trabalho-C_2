#include "lista.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaração da lista global
dados_pessoas *lista_pessoas = NULL;

// Função para inserir uma pessoa ordenadamente na lista
void inserir_ordenado(int novo_id, char *novo_nome)
{
    // Aloca memória para uma nova pessoa
    dados_pessoas *nova_pessoa = (dados_pessoas *)malloc(sizeof(dados_pessoas));
    if (nova_pessoa == NULL)
    {
        // Exibe uma mensagem de erro em caso de falha na alocação de memória e encerra o programa
        puts("Erro na alocação de memória");
        exit(1);
    }

    // Preenche os dados da nova pessoa
    nova_pessoa->id = novo_id;
    strcpy(nova_pessoa->nome, novo_nome);

    // Inicializa ponteiros para percorrer a lista
    dados_pessoas *no_atual = NULL;
    dados_pessoas *proximo_no = lista_pessoas;

    // Variável para controle da busca na lista
    bool procurando = true;
    // Percorre a lista até encontrar a posição correta para a nova pessoa
    while (proximo_no && procurando)
    {
        if (novo_id <= proximo_no->id)
            procurando = false;
        else
        {
            no_atual = proximo_no;
            proximo_no = proximo_no->proximo;
        }
    }

    // Insere a nova pessoa no início da lista ou no meio/final
    if (no_atual == NULL)
    {
        nova_pessoa->proximo = lista_pessoas;
        lista_pessoas = nova_pessoa; // insere no início
    }
    else
    {
        no_atual->proximo = nova_pessoa;
        nova_pessoa->proximo = proximo_no;
    }
}

// Função para liberar a memória ocupada pela lista
void liberar_lista()
{
    dados_pessoas *proxima_pessoa = lista_pessoas;
    while (proxima_pessoa)
    {
        dados_pessoas *atual = proxima_pessoa;
        proxima_pessoa = proxima_pessoa->proximo;
        free(atual);
    }
    lista_pessoas = NULL; // Atualiza o ponteiro da lista após liberar a memória
}

// Função para salvar a lista em um arquivo binário
void salvar_arquivo_binario(const char *arquivo_binario)
{
    // Abre o arquivo binário para escrita
    FILE *dadosBIN = fopen(arquivo_binario, "wb");
    if (dadosBIN == NULL)
    {
        // Exibe uma mensagem de erro em caso de falha na abertura do arquivo e encerra o programa
        puts("Erro na abertura do arquivo");
        exit(1);
    }

    // Escreve cada pessoa da lista no arquivo binário
    dados_pessoas *pessoa = lista_pessoas;
    while (pessoa)
    {
        fwrite(pessoa, sizeof(dados_pessoas), 1, dadosBIN);
        pessoa = pessoa->proximo;
    }

    // Fecha o arquivo após concluir a escrita
    fclose(dadosBIN);
}
/*
gcc -c -o Lista.o Lista.c

*/