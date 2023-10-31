#include<stdio.h>
#include<stdlib.h>

 struct Data {
    int code;
    char city[100];
    char street[100];
    char neighborhood[100];
    char postalCode[10]; 
    char streetType[20];
};

typedef struct Data dataCep;


typedef struct _node{
    dataCep data;
    struct _node  *pai;
    struct _node * esq;
    struct _node * dir;
    int h;
}tnode;

int maior(int a, int b) {
    return (a > b) ? a : b;
}
int altura(tnode * arv){
    int ret = -1;
    if (arv != NULL){
        ret = arv->h;
    }
    return ret;
}
void avl_cria(tnode ** parv){
    *parv = NULL;
}

void RD(tnode **pparv, tnode **pai){
    tnode * y;
    tnode * x;
    tnode * a;
    tnode * b;
    tnode * c;

    y = *pparv;
    y->pai= *pai;
    x = y->esq;
    x->pai=y;
    a = x->esq;
    a->pai=x;
    b = x->dir;
    b->pai=x;
    c = y->dir;
    c->pai=y;

    y->dir = c;
    y->esq = b;
    y->pai=x;
    b->pai=y;
    x->esq = a;
    x->dir = y;
    *pparv = x;
    x->pai=*pai;

    y->h = maior(altura(b),altura(c)) +1;
    x->h = maior(altura(y),altura(a)) +1;
}
void RE(tnode **pparv, tnode ** pai){
    tnode * y;
    tnode * x;
    tnode * a;
    tnode * b;
    tnode * c;

    x = *pparv;
    x->pai=*pai;
    y = x->dir;
    y->pai=x;
    a = x->esq;
    a->pai=x;
    b = y->esq;
    b->pai=y;
    c = y->dir;
    c->pai=y;

    x->esq = a;
    x->dir = b;
    x->pai=y;
    y->esq = x;
    y->dir = c;
    *pparv = y;
    y->pai=*pai;
    x->h = maior(altura(a),altura(b)) +1;
    y->h = maior(altura(x),altura(c)) +1;

}
void avl_rebalancear(tnode ** parv,tnode **pai){
    int fb; 
    int fbf;
    tnode * filho;

    fb = altura((*parv)->esq) - altura((*parv)->dir);
    if (fb == 2){
        filho = (*parv)->esq;
        fbf   = altura(filho->esq) - altura(filho->dir);
        if (fbf == -1) /*-->  <--<--*/
            RE(&(*parv)->esq,parv);
        RD(parv,pai);
    }else if (fb == -2){
        filho = (*parv)->dir;
        fbf   = altura(filho->esq) - altura(filho->dir);
        if (fbf == 1)
            RD(&(*parv)->dir,parv);
        RE(parv,pai);
    }

}

void avl_insere(tnode ** parv,tnode **pai, dataCep data){
    if (*parv == NULL){
        *parv = malloc(sizeof(tnode));
        (*parv)->data = data;
        (*parv)->pai=*pai;
        (*parv)->esq = NULL;
        (*parv)->dir = NULL;
        (*parv)->h   = 0;
    }else if (data.postalCode < (*parv)->data.postalCode){
        avl_insere(&(*parv)->esq,parv, data);
    }else{
        avl_insere(&(*parv)->dir,parv, data);
    }
    (*parv)->h = max(altura((*parv)->esq),altura((*parv)->dir)) + 1;
    avl_rebalancear(parv,pai);

}
 tnode ** minimo( tnode** parv) {
     tnode** x = *parv;
    while ((*x)->esq != NULL) {
        x = (*x)->esq;
    }
    return x;
}

//sucessor de nó sem filho a direita

tnode **Sucessor(tnode **parv){
    if((*parv)->dir!=NULL)
        return minimo(&(*parv)->dir);

    tnode *filho= *parv;
    tnode *pai= filho->dir;

    while(pai!=NULL && pai->dir==filho){
        filho=pai;
        pai=pai->pai;
    }
    return pai;

}
tnode **buscaNode(tnode **parv, int valor){
    tnode ** ret;
    if (*parv == NULL){
        ret = NULL;
    }else if (valor == (*parv)->data.postalCode){
        ret = parv;
    }else if (valor < (*parv)->data.postalCode){
        ret = arvoreb_busca(&(*parv)->esq,valor);
    }else{
        ret = arvoreb_busca(&(*parv)->dir,valor);
    }

    return ret;
   
}

tnode ** busca_intervalo(tnode **parv, int inicio, int fim){


    tnode **percorre=buscaNode(parv,inicio)    ;
    while((*percorre)->data.postalCode<=fim){
            sucessor(percorre);
            

    }






   
}




int main(void){

    tnode *parv;
    tnode *pai;


    FILE *arquivo;
    arquivo = fopen("data.csv", "r"); 

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return 1;
    }

    char line[1024]; 

    while (fgets(line, sizeof(line), arquivo) != NULL) {

        dataCep data;
    if (sscanf(line, "%19[^,],%49[^,],%49[^,],%49[^,],%9[^,],%19[^,],", data.code, data.city, data.street, data.neighborhood, data.postalCode, data.streetType) == 6) {

        avl_insere(&parv, &pai,data);

       }
   
}

}
