/*
 * ---------------------------------------------------------------------
 * Desafio Código da Ilha – Edição Free Fire (NÍVEL AVENTUREIRO)
 * Linguagem: C
 *
 * Funcionalidades:
 * 1. Adicionar itens (Nome, Tipo, Quantidade)
 * 2. Remover itens (por Nome)
 * 3. Listar itens
 * 4. Buscar item por nome (Busca Sequencial)
 * ---------------------------------------------------------------------
 */

// --- 1. Bibliotecas ---
#include <stdio.h>   // Para entrada e saída (printf, scanf)
#include <stdlib.h>  // Para funções utilitárias (system, exit)
#include <string.h>  // Para manipulação de strings (strcmp, strcpy)
#include <stdbool.h> // NOVO! Para usar o tipo 'bool' (true, false)

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
struct Item mochila[MAX_ITENS];
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

// (Nível Aventureiro)
void buscarSequencial();

// --- 5. Função Principal (main) ---
int main()
{
    int opcao = 0;

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
        
        // Case para a busca sequencial
        case 4:
            printf("### 4. Buscar Item (Sequencial) ###\n\n");
            buscarSequencial();
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

// --- 6. Implementação das Funções de Utilidade ---

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausarSistema()
{
    printf("\nPressione Enter para continuar...");
    limparBuffer();
    getchar();
}

/**
 * @brief Exibe o menu principal de opções.
 */
void exibirMenu()
{
    printf("=========================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA (v. Aventureiro)\n");
    printf("=========================================\n");
    printf("Itens na mochila: %d / %d\n", numItens, MAX_ITENS);
    printf("-----------------------------------------\n");
    printf(" [1] Adicionar Item\n");
    printf(" [2] Remover Item\n");
    printf(" [3] Listar Itens\n");
    printf(" [4] Buscar Item (Sequencial)\n");
    printf(" [0] Sair do Programa\n");
    printf("-----------------------------------------\n");
}

int obterOpcao()
{
    int opcao = -1;
    printf("Escolha sua acao: ");
    if (scanf("%d", &opcao) != 1)
    {
        opcao = -1;
    }
    limparBuffer();
    return opcao;
}

// --- 7. Funções do Nível Novato ---

void adicionarItem()
{
    if (numItens >= MAX_ITENS)
    {
        printf("Erro: A mochila esta cheia! (Max: %d itens)\n", MAX_ITENS);
        return;
    }
    struct Item *novoItem = &mochila[numItens];

    printf("Nome do item: ");
    fgets(novoItem->nome, MAX_NOME, stdin);
    novoItem->nome[strcspn(novoItem->nome, "\n")] = 0;

    printf("Tipo do item (ex: Arma, Municao, Cura): ");
    fgets(novoItem->tipo, MAX_NOME, stdin);
    novoItem->tipo[strcspn(novoItem->tipo, "\n")] = 0;

    printf("Quantidade: ");
    while (scanf("%d", &novoItem->quantidade) != 1 || novoItem->quantidade <= 0)
    {
        limparBuffer();
        printf("Valor invalido. Digite uma quantidade positiva: ");
    }
    limparBuffer();

    numItens++;
    printf("\nSucesso: Item '%s' (x%d) adicionado a mochila!\n", novoItem->nome, novoItem->quantidade);
}

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
    nomeParaRemover[strcspn(nomeParaRemover, "\n")] = 0;

    int indiceEncontrado = -1;

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
        for (int i = indiceEncontrado; i < numItens - 1; i++)
        {
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        printf("\nSucesso: Item '%s' removido da mochila.\n", nomeParaRemover);
    }
}

void listarItens()
{
    if (numItens == 0)
    {
        printf("A mochila esta vazia. Hora de procurar loot!\n");
        return;
    }
    printf("-----------------------------------------------------------------\n");
    printf("| %-25s | %-20s | %-10s |\n", "NOME", "TIPO", "QTD.");
    printf("=================================================================\n");
    for (int i = 0; i < numItens; i++)
    {
        printf("| %-25s | %-20s | %-10d |\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("-----------------------------------------------------------------\n");
}

// --- 8. Função do Nível Aventureiro ---

/**
 * @brief (NÍVEL AVENTUREIRO) Busca um item pelo nome (Busca Sequencial).
 */
void buscarSequencial()
{
    if (numItens == 0)
    {
        printf("A mochila esta vazia.\n");
        return;
    }

    char nomeParaBuscar[MAX_NOME];
    printf("Nome do item a buscar: ");
    fgets(nomeParaBuscar, MAX_NOME, stdin);
    nomeParaBuscar[strcspn(nomeParaBuscar, "\n")] = 0; // Remove o \n

    // Flag para controlar se o item foi achado
    bool encontrado = false;
    int comparacoes = 0;

    // Loop sequencial (do início ao fim)
    for (int i = 0; i < numItens; i++)
    {
        comparacoes++; // Conta cada comparação
        
        // strcmp retorna 0 se as strings forem iguais
        if (strcmp(mochila[i].nome, nomeParaBuscar) == 0)
        {
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Qtd.: %d\n", mochila[i].quantidade);
            printf("------------------------\n");
            printf("(Encontrado em %d comparacoes)\n", comparacoes);

            encontrado = true;
            break; // Para o loop assim que encontrar
        }
    }

    // Se o loop terminar e a flag for falsa, não achou
    if (!encontrado)
    {
        printf("\nErro: Item '%s' nao foi encontrado na mochila.\n", nomeParaBuscar);
        printf("(Busca sequencial realizou %d comparacoes)\n", comparacoes);
    }
}