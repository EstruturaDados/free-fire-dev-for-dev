/*
 * ---------------------------------------------------------------------
 * Desafio Código da Ilha – Edição Free Fire (NÍVEL NOVATO)
 * Linguagem: C
 *
 * Funcionalidades:
 * 1. Adicionar itens (Nome, Tipo, Quantidade)
 * 2. Remover itens (por Nome)
 * 3. Listar itens
 * 4. Menu interativo com vetor estático (MAX 10).
 * ---------------------------------------------------------------------
 */

// --- 1. Bibliotecas ---
#include <stdio.h>   // Para entrada e saída (printf, scanf)
#include <stdlib.h>  // Para funções utilitárias (system, exit)
#include <string.h>  // Para manipulação de strings (strcmp, strcpy)

// --- 2. Constantes e Estruturas ---

// Capacidade máxima da mochila
#define MAX_ITENS 10
#define MAX_NOME 50

// Estrutura para representar cada item (Nível Novato)
struct Item
{
    char nome[MAX_NOME];
    char tipo[MAX_NOME];
    int quantidade;
};

// --- 3. Variáveis Globais ---
// O 'inventário' em si é um vetor da nossa struct
struct Item mochila[MAX_ITENS];
// Controla quantos itens estão ATUALMENTE na mochila
int numItens = 0;

// --- 4. Protótipos de Funções ---
// (Utilidade)
void limparBuffer();
void limparTela();
void pausarSistema();

// (Menu)
void exibirMenu();
int obterOpcao();

// (Nível Novato)
void adicionarItem();
void removerItem();
void listarItens();

// --- 5. Função Principal (main) ---
int main()
{
    int opcao = 0;

    // Loop principal do menu (Nível Novato)
    do
    {
        limparTela();
        exibirMenu();
        opcao = obterOpcao();

        switch (opcao)
        {
        case 1:
            printf("### 1. Adicionar Item ###\n\n");
            adicionarItem();
            break;
        case 2:
            printf("### 2. Remover Item ###\n\n");
            removerItem();
            break;
        case 3:
            printf("### 3. Listar Itens ###\n\n");
            listarItens();
            break;
        case 0:
            printf("\nSaindo do programa... Ate mais!\n");
            break;
        default:
            printf("\nOpcao invalida! Pressione Enter para tentar novamente.\n");
            break;
        }

        if (opcao != 0)
        {
            pausarSistema();
        }

    } while (opcao != 0);

    return 0;
}

// --- 6. Implementação das Funções ---

/**
 * @brief Limpa o buffer de entrada (stdin).
 */
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * @brief Limpa o terminal (multiplataforma).
 */
void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Pausa a execução até o usuário pressionar Enter.
 */
void pausarSistema()
{
    printf("\nPressione Enter para continuar...");
    limparBuffer(); // Limpa qualquer entrada anterior
    getchar();      // Espera o Enter
}

/**
 * @brief Exibe o menu principal de opções.
 */
void exibirMenu()
{
    printf("======================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA (v. Novato)\n");
    printf("======================================\n");
    printf("Itens na mochila: %d / %d\n", numItens, MAX_ITENS);
    printf("--------------------------------------\n");
    printf(" [1] Adicionar Item\n");
    printf(" [2] Remover Item\n");
    printf(" [3] Listar Itens\n");
    printf(" [0] Sair do Programa\n");
    printf("--------------------------------------\n");
}

/**
 * @brief Lê e retorna a opção do usuário (um inteiro).
 */
int obterOpcao()
{
    int opcao = -1;
    printf("Escolha sua acao: ");
    if (scanf("%d", &opcao) != 1)
    {
        opcao = -1; // Define como opção inválida
    }
    limparBuffer(); // Limpa o \n ou entrada inválida
    return opcao;
}

/**
 * @brief (NÍVEL NOVATO) Adiciona um novo item à mochila.
 */
void adicionarItem()
{
    if (numItens >= MAX_ITENS)
    {
        printf("Erro: A mochila esta cheia! (Max: %d itens)\n", MAX_ITENS);
        return;
    }

    // Pega o item atual (o próximo índice livre)
    struct Item *novoItem = &mochila[numItens];

    // Leitura dos dados
    printf("Nome do item: ");
    fgets(novoItem->nome, MAX_NOME, stdin);
    novoItem->nome[strcspn(novoItem->nome, "\n")] = 0; // Remove o \n

    printf("Tipo do item (ex: Arma, Municao, Cura): ");
    fgets(novoItem->tipo, MAX_NOME, stdin);
    novoItem->tipo[strcspn(novoItem->tipo, "\n")] = 0; // Remove o \n

    printf("Quantidade: ");
    while (scanf("%d", &novoItem->quantidade) != 1 || novoItem->quantidade <= 0)
    {
        limparBuffer();
        printf("Valor invalido. Digite uma quantidade positiva: ");
    }
    limparBuffer();

    // Incrementa o contador de itens
    numItens++;

    printf("\nSucesso: Item '%s' (x%d) adicionado a mochila!\n", novoItem->nome, novoItem->quantidade);
}

/**
 * @brief (NÍVEL NOVATO) Remove um item da mochila pelo nome.
 */
void removerItem()
{
    if (numItens == 0)
    {
        printf("A mochila ja esta vazia.\n");
        return;
    }

    char nomeParaRemover[MAX_NOME];
    printf("Nome do item a remover: ");
    fgets(nomeParaRemover, MAX_NOME, stdin);
    nomeParaRemover[strcspn(nomeParaRemover, "\n")] = 0; // Remove o \n

    int indiceEncontrado = -1;

    // 1. Encontra o índice do item
    for (int i = 0; i < numItens; i++)
    {
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0)
        {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1)
    {
        printf("\nErro: Item '%s' nao encontrado na mochila.\n", nomeParaRemover);
    }
    else
    {
        // 2. "Puxa" todos os itens seguintes para a esquerda
        // (Sobrescreve o item removido)
        for (int i = indiceEncontrado; i < numItens - 1; i++)
        {
            mochila[i] = mochila[i + 1];
        }

        // 3. Decrementa o número de itens
        numItens--;

        printf("\nSucesso: Item '%s' removido da mochila.\n", nomeParaRemover);
    }
}

/**
 * @brief (NÍVEL NOVATO) Lista todos os itens da mochila em formato de tabela.
 */
void listarItens()
{
    if (numItens == 0)
    {
        printf("A mochila esta vazia. Hora de procurar loot!\n");
        return;
    }

    // Cabeçalho da tabela
    printf("-----------------------------------------------------------------\n");
    // Formatação: -25s = 25 chars para string, alinhado à esquerda
    printf("| %-25s | %-20s | %-10s |\n", "NOME", "TIPO", "QTD.");
    printf("=================================================================\n");

    // Lista os itens
    for (int i = 0; i < numItens; i++)
    {
        printf("| %-25s | %-20s | %-10d |\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("-----------------------------------------------------------------\n");
}