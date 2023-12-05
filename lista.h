#ifndef LISTA_H
#define LISTA_H
#define TAMANHO_NOME 100

typedef struct dados_pessoas dados_pessoas;
struct dados_pessoas
{
  int id;
  char nome[TAMANHO_NOME];
  dados_pessoas *proximo;
};
extern dados_pessoas *lista_pessoas;

// funcoes utilizadas no gerador
void inserir_ordenado(int novo_id, char *novo_nome);
void liberar_lista();
// funcoes utilizadas no editor
void salvar_arquivo_binario(const char *arquivo_binario);
void inserir_ordenado(int novo_id, char *novo_nome);

// funcoes utilizadas no exportador
void exportarBinarioParaTexto(const char *nomeArquivoBinario, const char *nomeArquivoTexto);

#endif