#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

extern dados_pessoas *lista_pessoas;

// Função responsável por gerar dados a partir de um arquivo de texto e salvar em um arquivo binário
void gerador(const char *nome_arquivo_txt, const char *arquivo_binario)
{
    // Abre o arquivo de texto para leitura
    FILE *arquivo = fopen(nome_arquivo_txt, "r");
    if (arquivo == NULL)
    {
        // Exibe uma mensagem de erro em caso de falha na abertura do arquivo e encerra o programa
        puts("Erro na abertura do arquivo");
        exit(1);
    }

    int id;
    char nome[TAMANHO_NOME];

    // Lê dados do arquivo de texto e insere ordenadamente na lista
    while (fscanf(arquivo, "%d %s", &id, nome) != EOF)
    {
        inserir_ordenado(id, nome);
    }

    // Fecha o arquivo de texto após a leitura
    fclose(arquivo);

    // Salva os dados da lista no arquivo binário
    salvar_arquivo_binario(arquivo_binario);

    // Libera a memória ocupada pela lista
    liberar_lista();
}

int main(int argc, char *argv[])
{
    // Verifica se o número de argumentos é correto
    if (argc != 3)
    {
        // Exibe uma mensagem de erro e a forma correta de uso do programa
        puts("ERRO: número incorreto de argumentos!");
        puts("Uso: copiar <arquivo-entrada> <arquivo-saida>");
        exit(1);
    }

    // Obtém os nomes dos arquivos de entrada e saída a partir dos argumentos
    char *arquivo_entrada = argv[1];
    char *arquivo_saida = argv[2];

    // Mensagem informativa sobre o processo de geração
    printf("Gerando conteúdo de %s para %s ...\n", arquivo_entrada, arquivo_saida);

    // Chama a função gerador para processar os arquivos
    gerador(arquivo_entrada, arquivo_saida);
}
/*
gcc -o Gerador  gerador.c Lista.o
./Gerador dados.txt dadosBIN.bin
*/