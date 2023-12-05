#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define TAMANHO_NOME 100

// Função para abrir um arquivo binário em modo de leitura
void abrir_Arquivo_Binario(const char *nome_Arquivo_Binario, FILE **arquivo_Binario)
{
    // Tenta abrir o arquivo binário em modo de leitura binária ("rb")
    *arquivo_Binario = fopen(nome_Arquivo_Binario, "rb");
    // Verifica se houve erro na abertura do arquivo
    if (*arquivo_Binario == NULL)
    {
        perror("Erro ao abrir o arquivo binário");
        exit(1);
    }
}

// Função para exportar dados de um arquivo binário para um arquivo de texto
void exportar_Binario_Para_Texto(FILE *arquivo_Binario, const char *nome_Arquivo_Texto)
{
    // Abre um arquivo de texto em modo de escrita ("w")
    FILE *arquivo_Texto = fopen(nome_Arquivo_Texto, "w");
    // Verifica se houve erro na abertura do arquivo de texto
    if (arquivo_Texto == NULL)
    {
        perror("Erro ao abrir o arquivo de texto");
        // Fecha o arquivo binário antes de encerrar o programa
        fclose(arquivo_Binario);
        exit(1);
    }

    // Estrutura para armazenar dados de uma pessoa
    dados_pessoas pessoa;

    // Lê os dados do arquivo binário e escreve no arquivo de texto
    while (fread(&pessoa, sizeof(dados_pessoas), 1, arquivo_Binario) == 1)
    {
        fprintf(arquivo_Texto, "%d %s\n", pessoa.id, pessoa.nome);
    }

    // Fecha o arquivo de texto após a escrita
    fclose(arquivo_Texto);
}

// Função principal do programa
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

    // Mensagem informativa sobre o processo de abertura do arquivo binário
    printf("Abrindo arquivo binário %s ...\n", arquivo_entrada);

    // Chama a função para abrir o arquivo binário
    FILE *arquivo_Binario;
    abrir_Arquivo_Binario(arquivo_entrada, &arquivo_Binario);

    // Mensagem informativa sobre o processo de exportação
    printf("Exportando conteúdo para o arquivo de texto %s ...\n", arquivo_saida);

    // Chama a função para exportar os dados do arquivo binário para o arquivo de texto
    exportar_Binario_Para_Texto(arquivo_Binario, arquivo_saida);

    // Fecha o arquivo binário após a exportação
    fclose(arquivo_Binario);

    // Retorna 0 indicando sucesso na execução do programa
    return 0;
}
/*
gcc -o Exportador  exportador.c Lista.o
./exportador dadosEDITADOS.bin dadosFINAIS.txt
*/
