#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;

void atualizar(struct noBstAvl* no);
struct noBstAvl* balancear(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no);


struct avl {
    struct noBstAvl* raiz;
    int tam;
};

struct noBstAvl {
    int val;
    int altura;
    int balanco;
    struct noBstAvl* esq;
    struct noBstAvl* dir;
};

/**
 * Funcao que aloca uma nova arvore avl.
 **/
struct avl* alocarAvl() {
    struct avl* novaAvl = (struct avl*)malloc(sizeof(struct avl));
    novaAvl->tam = NULL;
    novaAvl->raiz = NULL;
    return novaAvl;
}

/**
 * Funcao que aloca um novo noBstAvl, e
 * ajusta os ponteiros esq e dir para NULL,
 * e variáveis altura e balanco para 0.
 **/
struct noBstAvl* alocarNovoNo(int valor) {
    struct noBstAvl* no = (struct noBstAvl*)malloc(sizeof(struct noBstAvl));
        no->val = valor;
        no->esq = NULL;
        no->dir = NULL;
        no->altura = 0;
        no->balanco = 0;
    return no;
}

/**
 * Funcao que rotaciona uma arvore para a
 * direita e retorna a nova raiz.
 **/


struct noBstAvl* rotacaoDireita(struct noBstAvl* arvore) {
    struct noBstAvl* noEsq = arvore->esq;
    arvore->esq = noEsq->dir;
    noEsq->dir = arvore;
    atualizar(arvore);
    atualizar(noEsq);
    return noEsq;
}

/**
 * Funcao que rotaciona uma arvore para a
 * esquerda e retorna a nova raiz.
 **/


struct noBstAvl* rotacaoEsquerda(struct noBstAvl* arvore) {
    struct noBstAvl* noDir = arvore->dir;
    arvore->dir = noDir->esq;
    noDir->esq = arvore;
    atualizar(arvore);
    atualizar(noDir);
    return noDir;
}

/**
 * Funcao que recebe a raiz de uma bstAvl, e
 * insere um novo valor nela.
 * Raiz é passada por referência (ponteiro de ponteiro).
 * Lembrar de atualizar altura e fator de balanco dos nós
 * antecessores do nó inserido, bem como balanceá-los caso
 * seja necessário.
 * Dica: reutilizar a função de inserir de BST, e lembrar
 * de como usar inteligentemente a recursão para conseguir
 * atualizar e balancear os nós antecessores.
 **/


void inserirNo(struct noBstAvl* raiz, struct noBstAvl* no) {
    //CASOS PARA ESQUERDA

    if (raiz->esq == NULL && no->val < raiz->val) {
        raiz->esq = no;
    }
    else if (raiz->esq != NULL && no->val < raiz->val) {
        inserirNo(raiz->esq, no);
    }

    //CASOS PARA DIREITA

    if (raiz->dir == NULL && no->val >= raiz->val) {
        raiz->dir = no;
    }
    
    else if (raiz->dir != NULL && no->val >= raiz->val) {
        inserirNo(raiz->dir, no);
    }
    atualizar(raiz);
    balancear(raiz);
}

/**
 * Funcao fachada para insercao, similar a funcao de
 * insercao na BST.
 * Lembrar de incrementar tamanho.
 **/


void inserir(struct avl* avl, int val) {
    struct noBstAvl* no = alocarNovoNo(val);
    if (avl->raiz == NULL) {
        avl->raiz = alocarNovoNo(val);
    }
    else {
        inserirNo(avl->raiz, no);     
    }
    avl->tam++;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e atualiza sua altura
 * e fator de balanço.
 * Lembre que a altura das sub-árvores direita e esquerda
 * não vão mudar, por isso a implementação não é tão complicada.
 **/


void atualizar(struct noBstAvl* no) {
    
    int alturaEsq = 0, alturaDir = 0;

    if (no->esq == NULL) {
        alturaEsq = -1;
    }
    else {
        alturaEsq = no->esq->altura;
    }
    if (no->dir == NULL) {
        alturaDir = -1;
    }
    else {
        alturaDir = no->dir->altura;
    }
    if (no->altura == 0) {
        no->balanco = 0;
    }
    else {
        no->balanco = alturaDir - alturaEsq;
    }
    if (alturaDir > alturaEsq) {
        no->altura = alturaDir + 1;
    }
    else {
        no->altura = alturaEsq + 1;
    }
    
}

/**
 * Funcao que recebe a raiz de uma bstAvl e identifica em qual caso
 * ela se encaixa para executar os procedimentos de balanceamento
 * corretos:
 *      - Caso 1: esquerda-esquerda e esquerda-cheio
 *      - Caso 2: esquerda-direita
 *      - Caso 3: direita-direita e direita-cheio
 *      - Caso 4: direita-esquerda
 * Lembrar que quando há balanceamento temos uma nova raiz
 * que deve ser retornada para a função que chama o balanceamento.
 * Dica: usar fator de balanço do nó e de uma de suas sub-árvores
 * para descobrir qual é o caso.
 **/


struct noBstAvl* balancear(struct noBstAvl* no) {

    if (no->balanco == -2) {
        if (no->esq->balanco <= 0) {
            no = rebalancearEsqEsq(no);
        }
        else {
            no = rebalancearEsqDir(no);
        }
    }
    
    if (no->balanco == 2) {
        if (no->dir->balanco >= 0) {
            no = rebalancearDirDir(no);
        }
        else {
            no = rebalancearDirEsq(no);
        }
    }
    return no;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 1.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/


struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no) {
    no = rotacaoDireita(no);
    return no;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 2.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/


struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no) {
    no->esq = rotacaoEsquerda(no->esq);
    no = rotacaoDireita(no);
    return no;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 3.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/


struct noBstAvl* rebalancearDirDir(struct noBstAvl* no) {
    no = rotacaoEsquerda(no);
    return no;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 4.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/


struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no) {
    no->dir = rotacaoDireita(no->dir);
    no = rotacaoEsquerda(no);
    return no;
}

/**
 * Funcao que retorna o maior valor de uma árvore AVL.
 * Mesma implementação da BST.
 **/
int max(struct noBstAvl* raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    else if (raiz->dir != NULL) {
        return max(raiz->dir);
    }

    return raiz->val;
}

/**
 * Funcao que retorna o menor valor de uma árvore AVL.
 * Mesma implementação da BST.
 **/
int min(struct noBstAvl* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    else if (raiz->esq != NULL) {
        return min(raiz->esq);
    }

    return raiz->val;
}


/**
 * Funcao que recebe a raiz de uma árvore AVL, e
 * remove o nó que contem o valor passado como
 * argumento.
 * Lembrar de atualizar altura e fator de balanco dos nós
 * antecessores do nó removido, bem como balanceá-los caso
 * seja necessário.
 * Dica: reutilizar a função de remover de BST, e lembrar
 * de como usar inteligentemente a recursão para conseguir
 * atualizar e balancear os nós antecessores.
 **/
struct noBstAvl* removerNo(struct noBstAvl* raiz, int val) {
    if (raiz == NULL) {
        return NULL;
    }
    if (val < raiz->val) {
        raiz->esq = removerNo(raiz->esq, val);
        raiz = balancear(raiz);
        atualizar(raiz);
    }
    else if (val > raiz->val) {
        raiz->dir = removerNo(raiz->dir, val);
        raiz = balancear(raiz);
        atualizar(raiz);
    }
    else {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        else if (raiz->esq == NULL || raiz->dir == NULL) {
            struct noBstAvl* auxRemocao;
            if (raiz->esq == NULL) {
                auxRemocao = raiz->dir;
            }
            else {
                auxRemocao = raiz->esq;
            }
            free(raiz);
            return auxRemocao;
        }
        else {
            int auxRemocao;
            auxRemocao = min(raiz->dir);
            raiz->val = auxRemocao;
            raiz->dir = removerNo(raiz->dir, auxRemocao);
        }
    }
    raiz = balancear(raiz);
    atualizar(raiz);
    return raiz;
}

/**
 * Funcao fachada para remocao, similar a funcao de
 * remocao na BST.
 * Lembrar de decrementar tamanho.
 **/
void remover(struct avl* avl, int val) { 
    if (avl->raiz != NULL) {
        struct noBstAvl* remove = removerNo(avl->raiz, val);
        if (remove != NULL) {
            avl->raiz = remove;
            avl->tam--;
        }
    }
}

void imprimir(queue<struct noBstAvl*> nosImpressao);

/**
* Função que imprime a árvore.
* Pode ser útil para depuração.
**/
void imprimir(struct noBstAvl* raiz) {
    queue<struct noBstAvl*> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBstAvl*> nosImpressao) {

    queue<struct noBstAvl*> nosImpressaoProxNivel;

    while (!nosImpressao.empty()) {
        struct noBstAvl* noImpressao = nosImpressao.front();
        //add filhos na fila
        if (noImpressao != NULL) {
            if (noImpressao->esq != NULL)
                nosImpressaoProxNivel.push(noImpressao->esq);
            else
                nosImpressaoProxNivel.push(NULL);
            if (noImpressao->dir != NULL)
                nosImpressaoProxNivel.push(noImpressao->dir);
            else
                nosImpressaoProxNivel.push(NULL);
        }
        nosImpressao.pop();

        if (noImpressao != NULL) {
            cout << to_string(noImpressao->val) << " | ";
        }
        else {
            cout << "N | ";
        }
    }
    cout << endl << endl;
    if (!nosImpressaoProxNivel.empty())
        imprimir(nosImpressaoProxNivel);
}
