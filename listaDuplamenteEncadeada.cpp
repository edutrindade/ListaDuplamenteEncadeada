#include <iostream>

using namespace std;

typedef struct TipoItem{
    int id;
    string nome;
} TipoItem;

typedef struct TipoElemento* Apontador;

typedef struct TipoElemento{ //Célula
    TipoItem item;
    struct TipoElemento *prox;
    struct TipoElemento *ant;
} TipoElemento;

typedef struct TipoLista{
    Apontador primeiro;
    Apontador ultimo;
} TipoLista;

//=======================Utilizando Celula Principal============================
void CriaListaVazia(TipoLista *lista){
    lista->primeiro = new TipoElemento;
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
    lista->primeiro->ant = NULL;
}

bool VerificaListaVazia(TipoLista * lista){
    return (lista->primeiro == lista->ultimo);
}

void InsereListaPrimeiro(TipoLista *lista, TipoItem *item){
    Apontador aux;
    aux = lista->primeiro->prox;
    lista->primeiro->prox = new TipoElemento;
    lista->primeiro->prox->prox = aux;
    lista->primeiro->prox->item = *item;
    // prox C -> 1 -> 2 -> 3 -> 4
    // ant  C <- 1 <- 2 <- 3 <- 4
    aux->ant = lista->primeiro->prox;
    lista->primeiro->prox->ant = lista->primeiro; // aux->ant->ant = lista->primeiro;
}

void InsereListaAposElemento(TipoLista *lista, TipoItem *item, int idEleX) {
    Apontador aux, x, itemAnterior;
    x = lista->primeiro; // Célula cabeça

    while(x->prox != NULL) { // 1
        if (x->prox->item.id == idEleX) { // 1 == 1
            itemAnterior = x->prox; // Anterior será a célula do 1
            break;
        }
        x = x->prox; // Avanço com o x na lista
    }

    aux = itemAnterior->prox; // Aux aponta pro 1
    itemAnterior->prox = new TipoElemento; // Após o 1 eu aloco memória
    itemAnterior->prox->item = *item; // Recebo o 2 após o 1
    itemAnterior->prox->prox = aux; // Aponto o aux para o 3
    aux->ant = itemAnterior->prox; // Aponto o anterior do aux (3) para o 2
    aux->ant->ant = itemAnterior; // Aponto o anterior do 2 para o 1
}

void InsereListaUltimo(TipoLista *lista, TipoItem *item) { 
    Apontador aux;
    aux = lista->ultimo;
    lista->ultimo->prox = new TipoElemento;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->item = *item;
    lista->ultimo->prox = NULL;
    lista->ultimo->ant = aux;
}

void RemoveListaPrimeiro(TipoLista *lista, TipoItem *item){
    Apontador aux;
    
    if (VerificaListaVazia(lista)){
        return ;
    }
    *item = lista->primeiro->prox->item;
    aux = lista->primeiro->prox;
    lista->primeiro->prox = aux->prox;
    lista->primeiro->prox->ant = lista->primeiro; // aux->prox->ant = lista->primeiro;
    free(aux);
}

void RemoveListaUltimo(TipoLista *lista, TipoItem *item){
    Apontador aux, anterior, x;
    
    if (VerificaListaVazia(lista)) {
        return ;
    }
 
    x = lista->primeiro;
    while(x != NULL){
        if (x->prox == lista->ultimo){
            anterior = x;
        break;
        }
        x = x->prox;
    }
 
    aux = lista->ultimo;
    lista->ultimo = anterior;
    *item = aux->item;
    lista->ultimo->prox = NULL;
    free(aux);
}

void RemoveElementoXbyId(TipoLista *lista, TipoItem *item, int idEle){
    Apontador aux, anterior, x;
    
    if (VerificaListaVazia(lista)){
        return;
    }
    
    x = lista->primeiro;
    
    while (x != NULL){
        if (x->prox->item.id == idEle){
            anterior = x;
            break;
        }
        x = x->prox;
    }
    aux = anterior->prox;
    anterior->prox = aux->prox;
    *item = aux->item;
    free(aux);
}

void ImprimeLista(TipoLista *lista){
    Apontador x;
    
    x = lista->primeiro->prox;
    
    while (x != NULL){
        cout << x->item.id << " ";
        cout << x->item.nome << " ";
        x = x->prox; /* próxima célula */
    }
}

int main (){
    TipoLista lista;
    Apontador x;
    TipoItem item;
    
    item.id = 1;
    item.nome = "Xulambs";
    
    CriaListaVazia(&lista);
    InsereListaPrimeiro(&lista, &item);
    ImprimeLista(&lista);

    return 0;
}