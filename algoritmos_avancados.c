#include <stdio.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10 // tamanho da tabela hash

// --- Estrutura que representa uma sala da mansão ---
struct NoSala
{
    char nome[50];           // nome do cômodo
    char pista[100];         // pista associada ao cômodo
    struct NoSala *esquerda; // caminho à esquerda
    struct NoSala *direita;  // caminho à direita
};

// --- Estrutura que representa um nó da árvore BST de pistas ---
struct NoPista
{
    char pista[100];
    struct NoPista *esquerda;
    struct NoPista *direita;
};

// --- Estrutura da Tabela Hash (pista -> suspeito) ---
struct ParPistaSuspeito
{
    char pista[100];
    char suspeito[50];
    struct ParPistaSuspeito *prox;
};

// --- Função hash simples (soma dos caracteres) ---
int hash(char *pista)
{
    int soma = 0;
    for (int i = 0; pista[i] != '\0'; i++)
        soma += pista[i];
    return soma % TAM_HASH;
}

// --- Inserir associação pista-suspeito na tabela hash ---
void inserirHash(struct ParPistaSuspeito *tabela[], char *pista, char *suspeito)
{
    int indice = hash(pista);
    struct ParPistaSuspeito *novo = (struct ParPistaSuspeito *)malloc(sizeof(struct ParPistaSuspeito));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabela[indice];
    tabela[indice] = novo;
}

// --- Buscar suspeito associado a uma pista ---
char *buscarSuspeito(struct ParPistaSuspeito *tabela[], char *pista)
{
    int indice = hash(pista);
    struct ParPistaSuspeito *atual = tabela[indice];
    while (atual != NULL)
    {
        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;
        atual = atual->prox;
    }
    return NULL;
}

// --- Liberar memória da tabela hash ---
void liberarHash(struct ParPistaSuspeito *tabela[])
{
    for (int i = 0; i < TAM_HASH; i++)
    {
        struct ParPistaSuspeito *atual = tabela[i];
        while (atual != NULL)
        {
            struct ParPistaSuspeito *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}

// --- Criação das salas e pistas ---
struct NoSala *criarSala(char *nome, char *pista)
{
    struct NoSala *novo = (struct NoSala *)malloc(sizeof(struct NoSala));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// --- Criar nó da árvore de pistas ---
struct NoPista *criarNoPista(char *pista)
{
    struct NoPista *novo = (struct NoPista *)malloc(sizeof(struct NoPista));
    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// --- Inserir pista na BST ---
struct NoPista *inserirPista(struct NoPista *raiz, char *pista)
{
    if (raiz == NULL)
        return criarNoPista(pista);

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

// --- Exibir pistas em ordem alfabética ---
void exibirPistasEmOrdem(struct NoPista *raiz)
{
    if (raiz != NULL)
    {
        exibirPistasEmOrdem(raiz->esquerda);
        printf("• %s\n", raiz->pista);
        exibirPistasEmOrdem(raiz->direita);
    }
}

// --- Liberar memória ---
void liberarPistas(struct NoPista *raiz)
{
    if (raiz != NULL)
    {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}
void liberarSalas(struct NoSala *raiz)
{
    if (raiz != NULL)
    {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

// --- Exploração interativa da mansão ---
void explorarSalas(struct NoSala *raiz, struct NoPista **arvorePistas, struct ParPistaSuspeito *tabela[])
{
    struct NoSala *atual = raiz;
    char escolha;

    printf("\nVocê está no %s.\n", atual->nome);

    // mapa rápido de suspeitos associados às pistas
    if (strlen(atual->pista) > 0)
    {
        printf("Você encontrou uma pista: \"%s\"\n", atual->pista);
        *arvorePistas = inserirPista(*arvorePistas, atual->pista);
    }

    while (1)
    {
        printf("\nVocê está em: %s\n", atual->nome);
        if (atual->esquerda == NULL && atual->direita == NULL)
        {
            printf("Você chegou ao fim do caminho. Não há mais portas.\n");
            break;
        }

        printf("Caminhos disponíveis:\n");
        if (atual->esquerda != NULL)
            printf("  [e] Esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita != NULL)
            printf("  [d] Direita  -> %s\n", atual->direita->nome);
        printf("  [s] Sair da mansão\n");

        printf("Escolha um caminho (e/d/s): ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E')
        {
            if (atual->esquerda != NULL)
            {
                atual = atual->esquerda;
                printf("\nVocê entrou em: %s\n", atual->nome);
                if (strlen(atual->pista) > 0)
                {
                    printf("Você encontrou uma pista: \"%s\"\n", atual->pista);
                    *arvorePistas = inserirPista(*arvorePistas, atual->pista);
                }
            }
            else
                printf("Não há caminho à esquerda!\n");
        }
        else if (escolha == 'd' || escolha == 'D')
        {
            if (atual->direita != NULL)
            {
                atual = atual->direita;
                printf("\nVocê entrou em: %s\n", atual->nome);
                if (strlen(atual->pista) > 0)
                {
                    printf("Você encontrou uma pista: \"%s\"\n", atual->pista);
                    *arvorePistas = inserirPista(*arvorePistas, atual->pista);
                }
            }
            else
                printf("Não há caminho à direita!\n");
        }
        else if (escolha == 's' || escolha == 'S')
        {
            printf("\nVocê decidiu sair da mansão.\n");
            break;
        }
        else
        {
            printf("Escolha inválida! Use apenas 'e', 'd' ou 's'.\n");
        }
    }
}

// --- Contar quantas pistas ligam a um suspeito ---
int contarPistasSuspeito(struct NoPista *raiz, struct ParPistaSuspeito *tabela[], char *suspeito)
{
    if (raiz == NULL)
        return 0;

    int contador = 0;
    char *resp = buscarSuspeito(tabela, raiz->pista);
    if (resp != NULL && strcmp(resp, suspeito) == 0)
        contador++;

    contador += contarPistasSuspeito(raiz->esquerda, tabela, suspeito);
    contador += contarPistasSuspeito(raiz->direita, tabela, suspeito);

    return contador;
}

// --- Programa principal ---
int main()
{
    // Tabela hash de pistas e suspeitos
    struct ParPistaSuspeito *tabela[TAM_HASH] = {NULL};

    // Associações pista -> suspeito
    inserirHash(tabela, "Pegadas suspeitas no tapete", "Sr. Black");
    inserirHash(tabela, "Um copo quebrado", "Sra. White");
    inserirHash(tabela, "Um livro fora do lugar", "Professor Plum");
    inserirHash(tabela, "Uma faca suja", "Coronel Mustard");
    inserirHash(tabela, "Um guardanapo com uma inicial", "Srta. Scarlet");
    inserirHash(tabela, "Uma carta rasgada", "Professor Plum");
    inserirHash(tabela, "Pegadas na terra molhada", "Sr. Black");

    // Construção da mansão
    struct NoSala *raiz = criarSala("Hall de Entrada", "Pegadas suspeitas no tapete");
    raiz->esquerda = criarSala("Sala de Estar", "Um copo quebrado");
    raiz->direita = criarSala("Biblioteca", "Um livro fora do lugar");
    raiz->esquerda->esquerda = criarSala("Cozinha", "Uma faca suja");
    raiz->esquerda->direita = criarSala("Sala de Jantar", "Um guardanapo com uma inicial");
    raiz->direita->esquerda = criarSala("Escritório", "Uma carta rasgada");
    raiz->direita->direita = criarSala("Jardim", "Pegadas na terra molhada");

    // Árvore BST de pistas coletadas
    struct NoPista *pistas = NULL;

    printf("=== Mapa da Mansão Criado ===\n");
    printf("Você começará sua exploração pelo Hall de Entrada.\n");

    explorarSalas(raiz, &pistas, tabela);

    printf("\n=== Pistas Coletadas ===\n");
    if (pistas == NULL)
        printf("Nenhuma pista foi encontrada.\n");
    else
        exibirPistasEmOrdem(pistas);

    // --- Fase de acusação ---
    char acusado[50];
    printf("\nQuem você acredita ser o culpado? ");
    scanf(" %[^\n]", acusado);

    int total = contarPistasSuspeito(pistas, tabela, acusado);

    printf("\nAnalisando suas pistas...\n");
    if (total >= 2)
        printf("Você acertou! Há %d pistas que indicam %s como o culpado!\n", total, acusado);
    else if (total == 1)
        printf("Há apenas uma pista ligando %s ao crime. Pode ser coincidência...\n", acusado);
    else
        printf("Nenhuma pista liga %s ao crime. Acusação incorreta!\n", acusado);

    // Liberação de memória
    liberarSalas(raiz);
    liberarPistas(pistas);
    liberarHash(tabela);

    printf("\nMemória liberada. Fim da investigação.\n");

    return 0;
}
