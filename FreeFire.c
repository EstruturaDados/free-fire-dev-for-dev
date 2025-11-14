// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// --- 1. Bibliotecas ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- 2. Constantes e Estruturas ---

#define MAX_ITENS 10
#define MAX_NOME 50

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
struct Item
{
    char nome[MAX_NOME];
    char tipo[MAX_NOME];
    int quantidade;
    int prioridade;
};

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
enum CriterioOrdenacao
{
    NOME,
    TIPO,
    PRIORIDADE
};

// --- 3. Variáveis Globais ---

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
struct Item mochila[MAX_ITENS];
int numItens = 0;
bool estaOrdenadoPorNome = false;
long long comparacoesOrdenacao = 0;

// --- 4. Protótipos de Funções ---
void limparBuffer();
void limparTela();
void pausarSistema();
void exibirMenu();
int obterOpcao();
void adicionarItem();
void removerItem();
void listarItens();
void buscarSequencial();
void menuOrdenacao();
void ordenarItens(enum CriterioOrdenacao criterio);
void buscarBinaria();


// --- 5. Função Principal (main) ---
int main()
{
    int opcao = 0;

    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. (NOVO) Buscar Item (Sequencial) - (Mantido do Nível Aventureiro)
    // 5. (NOVO) Ordenar os itens por critério (nome, tipo, prioridade)
    // 6. (NOVO) Realizar busca binária por nome
    // 0. Sair
    do
    {
        limparTela();
        exibirMenu();
        opcao = obterOpcao();

        // A estrutura switch trata cada opção chamando a função correspondente.
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
        case 4:
            printf("### 4. Buscar Item (Sequencial) ###\n\n");
            buscarSequencial();
            break;
        case 5:
            printf("### 5. Ordenar Mochila ###\n\n");
            menuOrdenacao();
            break;
        case 6:
            printf("### 6. Buscar Item (Binaria) ###\n\n");
            buscarBinaria();
            break;
        case 0:
            printf("\nSaindo da ilha... Ate a proxima, sobrevivente!\n");
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

    // A ordenação e busca binária exigem que os dados estejam bem organizados.
    return 0;
}

// --- 6. Funções de Utilidade ---

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.
// (Implementação real usa comandos do sistema para melhor efeito)
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

// --- 7. Funções de Menu e Interface ---

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu()
{
    printf("========================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA (v. Mestre)\n");
    printf("========================================\n");
    printf("Itens na mochila: %d / %d\n", numItens, MAX_ITENS);
    printf("Ordenada por nome? %s\n", estaOrdenadoPorNome ? "Sim" : "Nao");
    printf("----------------------------------------\n");
    printf(" [1] Adicionar Item\n");
    printf(" [2] Remover Item\n");
    printf(" [3] Listar Itens\n");
    printf(" [4] Buscar Item (Sequencial)\n");
    printf(" [5] Ordenar Mochila\n");
    printf(" [6] Buscar Item (Binaria por Nome)\n");
    printf(" [0] Sair do Programa\n");
    printf("----------------------------------------\n");
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

// --- 8. Funções de Gerenciamento de Itens ---

// inserirItem(): (Nomeado como adicionarItem para consistência)
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
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

    printf("Prioridade (1-5, onde 5 e max): ");
    while (scanf("%d", &novoItem->prioridade) != 1 || novoItem->prioridade < 1 || novoItem->prioridade > 5)
    {
        limparBuffer();
        printf("Valor invalido. Digite uma prioridade entre 1 e 5: ");
    }
    limparBuffer();

    numItens++;
    estaOrdenadoPorNome = false;

    printf("\nSucesso: Item '%s' (x%d) adicionado a mochila!\n", novoItem->nome, novoItem->quantidade);
}

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
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
        estaOrdenadoPorNome = false;
        printf("\nSucesso: Item '%s' removido da mochila.\n", nomeParaRemover);
    }
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens()
{
    if (numItens == 0)
    {
        printf("A mochila esta vazia. Hora de procurar loot!\n");
        return;
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("| %-25s | %-20s | %-10s | %-10s |\n", "NOME", "TIPO", "QTD.", "PRIORIDADE");
    printf("================================================================================\n");

    for (int i = 0; i < numItens; i++)
    {
        printf("| %-25s | %-20s | %-10d | %-10d |\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
    printf("--------------------------------------------------------------------------------\n");
}

// --- 9. Funções de Busca e Ordenação (Nível Mestre) ---

// menuDeOrdenacao(): (Nomeado como menuOrdenacao para consistência)
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() (ordenarItens) com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuOrdenacao()
{
    if (numItens < 2)
    {
        printf("Nao ha itens suficientes para ordenar.\n");
        return;
    }

    printf("Escolha o criterio de ordenacao (usando Insertion Sort):\n");
    printf(" [1] Por Nome (A-Z)\n");
    printf(" [2] Por Tipo (A-Z)\n");
    printf(" [3] Por Prioridade (Maior primeiro, 5 -> 1)\n");
    printf(" [0] Cancelar\n");

    int opcao = obterOpcao();

    switch (opcao)
    {
    case 1:
        ordenarItens(NOME);
        break;
    case 2:
        ordenarItens(TIPO);
        break;
    case 3:
        ordenarItens(PRIORIDADE);
        break;
    case 0:
        printf("Ordenacao cancelada.\n");
        break;
    default:
        printf("Opcao de ordenacao invalida.\n");
        break;
    }
}

// insertionSort(): (Nomeado como ordenarItens para consistência)
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
void ordenarItens(enum CriterioOrdenacao criterio)
{
    comparacoesOrdenacao = 0;
    estaOrdenadoPorNome = false;

    for (int i = 1; i < numItens; i++)
    {
        struct Item chave = mochila[i];
        int j = i - 1;
        bool mover = false;

        while (j >= 0)
        {
            comparacoesOrdenacao++;
            mover = false;

            switch (criterio)
            {
            case NOME:
                if (strcmp(mochila[j].nome, chave.nome) > 0)
                    mover = true;
                break;
            case TIPO:
                if (strcmp(mochila[j].tipo, chave.tipo) > 0)
                    mover = true;
                break;
            case PRIORIDADE:
                if (mochila[j].prioridade < chave.prioridade)
                    mover = true;
                break;
            }

            if (mover)
            {
                mochila[j + 1] = mochila[j];
                j--;
            }
            else
            {
                break;
            }
        }
        mochila[j + 1] = chave;
    }

    if (criterio == NOME)
    {
        estaOrdenadoPorNome = true;
        printf("\nSucesso: Mochila ordenada por NOME.\n");
    }
    else if (criterio == TIPO)
    {
        printf("\nSucesso: Mochila ordenada por TIPO.\n");
    }
    else
    {
        printf("\nSucesso: Mochila ordenada por PRIORIDADE (maior primeiro).\n");
    }

    printf("Analise de Desempenho (Insertion Sort): %lld comparacoes realizadas.\n", comparacoesOrdenacao);
    listarItens();
}

// (Função de Busca Sequencial mantida do Nível Aventureiro)
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
    nomeParaBuscar[strcspn(nomeParaBuscar, "\n")] = 0;

    bool encontrado = false;
    int comparacoes = 0;

    for (int i = 0; i < numItens; i++)
    {
        comparacoes++;
        if (strcmp(mochila[i].nome, nomeParaBuscar) == 0)
        {
            printf("\n--- Item Encontrado (Busca Sequencial)! ---\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Qtd.: %d\n", mochila[i].quantidade);
            printf("Prio: %d\n", mochila[i].prioridade);
            printf("-------------------------------------------\n");
            printf("(Encontrado em %d comparacoes)\n", comparacoes);

            encontrado = true;
            break;
        }
    }
    if (!encontrado)
    {
        printf("\nErro: Item '%s' nao foi encontrado na mochila.\n", nomeParaBuscar);
        printf("(Busca sequencial realizou %d comparacoes)\n", comparacoes);
    }
}


// buscaBinariaPorNome(): (Nomeado como buscarBinaria para consistência)
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscarBinaria()
{
    if (!estaOrdenadoPorNome)
    {
        printf("\n### ATENCAO! ###\n");
        printf("A Busca Binaria so funciona se a mochila estiver ordenada por NOME.\n");
        printf("Por favor, use a Opcao 5 (Ordenar Mochila -> Por Nome) primeiro.\n");
        return;
    }

    if (numItens == 0)
    {
        printf("A mochila esta vazia.\n");
        return;
    }

    char nomeParaBuscar[MAX_NOME];
    printf("Nome do item a buscar (Busca Binaria): ");
    fgets(nomeParaBuscar, MAX_NOME, stdin);
    nomeParaBuscar[strcspn(nomeParaBuscar, "\n")] = 0;

    int inicio = 0;
    int fim = numItens - 1;
    bool encontrado = false;
    int comparacoes = 0;

    while (inicio <= fim)
    {
        comparacoes++;
        int meio = inicio + (fim - inicio) / 2;
        int cmp = strcmp(nomeParaBuscar, mochila[meio].nome);

        if (cmp == 0)
        {
            printf("\n--- Item Encontrado (Busca Binaria)! ---\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Qtd.: %d\n", mochila[meio].quantidade);
            printf("Prio: %d\n", mochila[meio].prioridade);
            printf("-------------------------------------------\n");
            printf("(Encontrado em %d comparacoes)\n", comparacoes);

            encontrado = true;
            break;
        }
        else if (cmp < 0)
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    if (!encontrado)
    {
        printf("\nErro: Item '%s' nao foi encontrado na mochila.\n", nomeParaBuscar);
        printf("(Busca binaria realizou %d comparacoes)\n", comparacoes);
    }
}