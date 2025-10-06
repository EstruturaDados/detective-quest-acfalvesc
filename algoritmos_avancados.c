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

// --- Estrutura que representa uma sala (nó da árvore binária) ---
struct No
{
    char valor[50];           // nome do cômodo
    struct No *esquerda;      // caminho à esquerda
    struct No *direita;       // caminho à direita
};

// --- Função criarSala(): cria dinamicamente uma sala com o nome informado ---
struct No *criarSala(char *valor)
{
    struct No *novo = (struct No *)malloc(sizeof(struct No));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// --- Função para percorrer em pré-ordem (usada apenas para depuração, se desejar) ---
void preOrdem(struct No *raiz)
{
    if (raiz != NULL)
    {
        printf("%s ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

// --- Função liberar(): libera memória da árvore ---
void liberar(struct No *raiz)
{
    if (raiz != NULL)
    {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

// --- Função explorarSalas(): navegação interativa do jogador ---
void explorarSalas(struct No *raiz)
{
    struct No *atual = raiz;
    char escolha;

    printf("\nVocê está no %s.\n", atual->valor);

    // Loop até chegar a um nó sem filhos (nó-folha)
    while (1)
    {
        if (atual->esquerda == NULL && atual->direita == NULL)
        {
            printf("\nVocê chegou ao fim do caminho, não há mais portas.\n");
            printf("Você está em: %s.\n", atual->valor);
            break;
        }

        printf("\nVocê está em: %s\n", atual->valor);
        printf("Caminhos disponíveis:\n");
        if (atual->esquerda != NULL)
            printf("  [e] Esquerda -> %s\n", atual->esquerda->valor);
        if (atual->direita != NULL)
            printf("  [d] Direita  -> %s\n", atual->direita->valor);

        printf("Escolha um caminho (e/d): ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E')
        {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Não há caminho à esquerda!\n");
        }
        else if (escolha == 'd' || escolha == 'D')
        {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Não há caminho à direita!\n");
        }
        else
        {
            printf("Escolha inválida! Use apenas 'e' ou 'd'.\n");
        }
    }
}

// --- Função principal: monta o mapa e inicia a exploração ---
int main()
{
    // Criação automática do mapa da mansão (árvore binária)
    struct No *raiz = criarSala("Hall de entrada");
    raiz->esquerda = criarSala("Sala de estar");
    raiz->direita = criarSala("Biblioteca");
    raiz->esquerda->esquerda = criarSala("Cozinha");
    raiz->esquerda->direita = criarSala("Sala de jantar");
    raiz->direita->esquerda = criarSala("Escritório");
    raiz->direita->direita = criarSala("Jardim");

    printf("=== Mapa da Mansão Criado com Sucesso ===\n");
    printf("Você começará sua exploração pelo Hall de entrada.\n");

    explorarSalas(raiz);

    liberar(raiz);
    printf("\nMemória liberada. Fim da exploração.\n");

    return 0;
}

