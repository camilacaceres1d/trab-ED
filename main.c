#include<stdio.h>
#include<stdlib.h>


int max(int a, int b){
    return a>b?a:b;
}

typedef struct Data {
    int code;
    char city[100];
    char street[100];
    char neighborhood[100];
    char postalCode[10]; 
    char streetType[20];
}date;

typedef struct _node{
    date data;
    struct _node * esq;
    struct _node * dir;
    int h;
}tnode;

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

void RD(tnode **pparv){
    tnode * y;
    tnode * x;
    tnode * a;
    tnode * b;
    tnode * c;

    y = *pparv;
    x = y->esq;
    a = x->esq;
    b = x->dir;
    c = y->dir;

    y->dir = c;
    y->esq = b;
    x->esq = a;
    x->dir = y;
    *pparv = x;
    y->h = max(altura(b),altura(c)) +1;
    x->h = max(altura(y),altura(a)) +1;
}
void RE(tnode **pparv){
    tnode * y;
    tnode * x;
    tnode * a;
    tnode * b;
    tnode * c;

    x = *pparv;
    y = x->dir;
    a = x->esq;
    b = y->esq;
    c = y->dir;

    x->esq = a;
    x->dir = b;
    y->esq = x;
    y->dir = c;
    *pparv = y;
    x->h = max(altura(a),altura(b)) +1;
    y->h = max(altura(x),altura(c)) +1;

}
void avl_rebalancear(tnode ** parv){
    int fb; 
    int fbf;
    tnode * filho;

    fb = altura((*parv)->esq) - altura((*parv)->dir);
    if (fb == 2){
        filho = (*parv)->esq;
        fbf   = altura(filho->esq) - altura(filho->dir);
        if (fbf == -1) /*-->  <--<--*/
            RE(&(*parv)->esq);
        RD(parv);
    }else if (fb == -2){
        filho = (*parv)->dir;
        fbf   = altura(filho->esq) - altura(filho->dir);
        if (fbf == 1)
            RD(&(*parv)->dir);
        RE(parv);
    }

}
void insert(tnode ** parv,date data.code, date data.city, date data.street, date data.neighbordhood, ){
    if (*parv == NULL){
        *parv = malloc(sizeof(tnode));
        (*parv)->reg = reg;
        (*parv)->esq = NULL;
        (*parv)->dir = NULL;
        (*parv)->h   = 0;
    }else if (reg < (*parv)->reg){
        avl_insere(&(*parv)->esq,reg);
    }else{
        avl_insere(&(*parv)->dir,reg);
    }
    (*parv)->h = max(altura((*parv)->esq),altura((*parv)->dir)) + 1;
    avl_rebalancear(parv);

}



int main(void){

    FILE *arquivo;
    arquivo = fopen("seuarquivo.csv", "r"); // Substitua "seuarquivo.csv" pelo nome do seu arquivo CSV.

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char line[1024]; 

    while (fgets(line, sizeof(line), arquivo) != NULL) {

        date data;
    if (sscanf(line, "%19[^,],%49[^,],%49[^,],%49[^,],%9[^,],%19[^,],", data.code, data.city, data.street, data.neighborhood, data.postalcode, data.streeType) == 6) {

        insert(root, data);

       }
   
}
