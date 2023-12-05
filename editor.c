#include "lista.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a lista global de pessoas
extern dados_pessoas *lista_pessoas;

// Função para exibir as opções do editor
int vizualizar_opcoes(int *opcao)
{
    printf("\nQual operacao deseja realizar? \n[1] Imprimir a lista de pessoas \n[2] Inserir um dado de pessoa \n[3] Excluir uma pessoa \n[4] Pesquisar uma pessoa por ID \n[5] Salvar o arquivo e continuar utilizando \n[6] Salvar o arquivo e sair \n>>>");
    scanf("%d", opcao);
    return *opcao;
}

// Função para abrir um arquivo binário e alocar os dados na lista
void abir_binario_alocar_dados(const char *nome_arquivo_binario)
{
    int id;
    char nome[TAMANHO_NOME];
    dados_pessoas *pessoa = (dados_pessoas *)malloc(sizeof(dados_pessoas));

    FILE *arquivo_binario = fopen(nome_arquivo_binario, "rb");
    if (arquivo_binario == NULL)
    {
        perror("Erro ao abrir o arquivo binário");
        exit(1);
    }
    while (fread(pessoa, sizeof(dados_pessoas), 1, arquivo_binario) == 1)
    {
        inserir_ordenado(pessoa->id, pessoa->nome);
    }
    fclose(arquivo_binario);
}

// Função para imprimir a lista de pessoas
void imprimir_lista()
{
    dados_pessoas *pessoa = lista_pessoas;
    while (pessoa)
    {
        printf("ID: %3d NOME: %s \n", pessoa->id, pessoa->nome);
        pessoa = pessoa->proximo;
    }
}

// Função para inserir uma pessoa na lista de forma ordenada
void inserir_pessoa_na_lista()
{
    int id;
    char nome[TAMANHO_NOME];
    int tentar_outro_ID = 0;
    bool retornar_menu = false;
    dados_pessoas *pessoa = lista_pessoas;

    printf("\ninsira o id: ");
    scanf("%d", &id);
    getchar();
    puts("Utilize _ no lugar dos espacos");
    printf("insira o nome: ");
    fgets(nome, TAMANHO_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    while (pessoa)
    {
        if (pessoa->id == id)
        {
            while (tentar_outro_ID != 1 && tentar_outro_ID != 2)
            {
                printf("\nParece que o ID: %2d ja existe, ele pertence a %s. \nDeseja retornar ao menu ou deseja inserir um novo ID? \n [1] Retornar ao menu [2] Inserir novo ID \n>>>", id, pessoa->nome);
                scanf("%d", &tentar_outro_ID);
                if (tentar_outro_ID == 1)
                {
                    retornar_menu = true;
                }
                else if (tentar_outro_ID == 2)
                {
                    pessoa = lista_pessoas;
                    printf("\ninsira o id:");
                    scanf("%d", &id);
                }
            }
        }

        pessoa = pessoa->proximo;
    }
    if (!retornar_menu)
    {
        inserir_ordenado(id, nome);
        printf("Pessoa inserida com sucesso.\n ID: %2d NOME: %s", id, nome);
    }
    else
    {
        puts("Retornando ao menu");
    }
}

// Função para deletar pessoas da lista
void deletar_pessoas_da_lista()
{
    int id;
    bool ID_nao_localizado = false;
    dados_pessoas *no_atual = NULL;
    dados_pessoas *no_seguinte = lista_pessoas;

    imprimir_lista();

    printf("Digite qual ID deseja excluir \n>>>");
    scanf("%d", &id);

    while (no_seguinte && id != no_seguinte->id)
    {
        no_atual = no_seguinte;
        no_seguinte = no_seguinte->proximo;
    }
    if (no_seguinte == NULL)
    {
        printf("Nao foi encontrado o ID: %2d.\n", id);
        ID_nao_localizado = true;
    }
    if (!ID_nao_localizado)
    {
        if (no_atual == NULL)
        {
            lista_pessoas = no_seguinte->proximo; // Remove do início da lista
        }
        else
        {
            no_atual->proximo = no_seguinte->proximo; // Remove no meio ou final da lista
        }
        free(no_seguinte);
        printf("Pessoa com o ID: %2d foi deletada com sucesso.", id);
    }
}

// Função para buscar uma pessoa na lista pelo ID
dados_pessoas *buscar_pessoa_por_ID(dados_pessoas *pessoa, int id)
{
    if (pessoa == NULL)
    {
        return NULL;
    }
    if (pessoa->id == id)
    {
        return pessoa;
    }
    return buscar_pessoa_por_ID(pessoa->proximo, id);
}

// Função para realizar a pesquisa por ID
void pesquisa_por_id()
{
    int id;
    dados_pessoas *pessoas = lista_pessoas;
    printf("Digite o ID que deseja buscar: \n>>>");
    scanf("%d", &id);
    pessoas = buscar_pessoa_por_ID(lista_pessoas, id);
    if (pessoas == NULL)
    {
        printf("Pessoa não localizada, parece que o ID: %2d não foi inserido ainda", id);
    }
    else
    {
        printf("Foram localizadas essas informações: \nID: %2d NOME: %s", pessoas->id, pessoas->nome);
    }
}

// Função principal do editor
void editor(const char *nome_arquivo_bin_entrada, const char *nome_arquivo_bin_saida)
{
    // Variáveis locais
    int opcoes = 0;                  // Armazena a opção escolhida pelo usuário
    bool controle_editor = true;     // Controla a execução do loop principal
    abir_binario_alocar_dados(nome_arquivo_bin_entrada); // Abre o arquivo binário e aloca os dados na lista

    // Loop principal do editor
    while (controle_editor)
    {
        // Exibe as opções e obtém a escolha do usuário
        vizualizar_opcoes(&opcoes);

        // Estrutura de switch para lidar com as diferentes opções
        switch (opcoes)
        {
        case 1:
            imprimir_lista(); // Imprime a lista de pessoas
            break;
        case 2:
            inserir_pessoa_na_lista(); // Insere uma nova pessoa na lista
            break;
        case 3:
            deletar_pessoas_da_lista(); // Deleta uma pessoa da lista
            break;
        case 4:
            pesquisa_por_id(); // Realiza a pesquisa de uma pessoa por ID
            break;
        case 5:
            salvar_arquivo_binario(nome_arquivo_bin_saida); // Salva o arquivo binário
            puts("Arquivo salvo com sucesso");
            break;
        case 6:
            salvar_arquivo_binario(nome_arquivo_bin_saida); // Salva o arquivo binário
            controle_editor = false; // Encerra o loop principal
            liberar_lista(); // Libera a memória alocada para a lista
            puts("Arquivo salvo com sucesso e encerrando programa");
            break;
        default:
            puts("Nao temos essa opcao!!!"); 
            break;
        }
    }
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

    // Mensagem informativa sobre o processo de edição e salvamento
    printf("Editando o conteúdo de %s e salvando em %s ...\n",
           arquivo_entrada, arquivo_saida);

    // Chama a função principal do editor
    editor(arquivo_entrada, arquivo_saida);

    // Retorna 0 indicando sucesso na execução do programa
    return 0;
}
/*
gcc -o Editor  editor.c Lista.o
./Editor dadosBIN.bin dadosEDITADOS.bin
*/