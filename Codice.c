#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 512

typedef struct Node {
    int data;
    int AUTO[N];
    int max;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct list {
    int data;
    int tappe;
    int visitato;
    struct list* precedente;
    struct list* next;
}list;


struct list* createNodeList(int data);
void freeList(struct list* head);
struct Node* findPredecessor(struct Node* root, struct Node* node);
struct Node* findMaxNode(struct Node* node);

void pianificadritto(struct Node * start,struct Node * finish,struct Node * root);
void pianificareverse(struct Node * start,struct Node * finish,struct Node * root);
struct Node* aggiungistazione(int distanza,int AUTONOMIA[N],Node* root);
struct Node* demoliscistazione(int distanza, Node* root);
struct Node* aggiungiauto(int distanza,int autonomia,Node* root);
struct Node*rottamaauto(int distanza,int autonomia,Node* root);
void pianificapercorso(int partenza, int arrivo,Node* root);
Node* delete(Node* root, int data);
Node* searchNode(Node* root, int data);
Node* insert(Node* root, int data);
Node* findMinNode(Node* root);
Node* createNode(int data);
struct Node* Next(struct Node* root, struct Node* node);
void freeBST(struct Node* root);

int main(){
    FILE *fp;
    char comando[5000];
    int i,distanza=0,numero_auto=0,partenza=0,arrivo=0,autonomia=0,controllo=0;
    int AUTONOMIA[N];
    struct Node* root=NULL;

    fp=stdin;
    if(fp) {
        while (fgets(comando, sizeof(comando), fp) != NULL) {
                char* parola = strtok(comando, " ");
                if (strcmp(comando, "aggiungi-stazione") == 0) {
                    parola = strtok(NULL, " ");
                    distanza= atoi(parola);
                    parola = strtok(NULL, " ");
                    numero_auto = atoi(parola);
                    for (i = 0; i < numero_auto; i++) { //creo parco auto appena creo stazione
                        parola = strtok(NULL, " ");
                        controllo = atoi(parola);
                        AUTONOMIA[i] = controllo;
                    }
                    for (i = numero_auto; i < N; i++) { //inizializzo tutto il parco auto a -1
                        AUTONOMIA[i] = -1;
                    }
                    root = aggiungistazione(distanza, AUTONOMIA, root);
                }
                if (strcmp(comando, "demolisci-stazione") == 0) {
                    parola = strtok(NULL, " ");
                    distanza = atoi(parola);
                    root = demoliscistazione(distanza, root);
                }
                if (strcmp(comando, "aggiungi-auto") == 0) {
                    parola = strtok(NULL, " ");
                    distanza = atoi(parola);
                    parola = strtok(NULL, " ");
                    autonomia = atoi(parola);
                    root = aggiungiauto(distanza, autonomia, root);
                }
                if (strcmp(comando, "rottama-auto") == 0) {
                    parola = strtok(NULL, " ");
                    distanza = atoi(parola);
                    parola = strtok(NULL, " ");
                    autonomia = atoi(parola);
                    root = rottamaauto(distanza, autonomia, root);
                }
                if (strcmp(comando, "pianifica-percorso") == 0) {
                    parola = strtok(NULL, " ");
                    partenza = atoi(parola);
                    parola = strtok(NULL, " ");
                    arrivo = atoi(parola);
                    pianificapercorso(partenza, arrivo, root);
                }
                printf("\n");
        }
        freeBST(root);
        fclose(fp);
    }
    else{
        printf("Errore di apertura del file\n");
    }
    return 0;
}

void pianificapercorso(int partenza, int arrivo,Node* root) {
    struct Node *start, *finish;
    start = searchNode(root, partenza);
    finish = searchNode(root, arrivo);
    if (start== NULL || finish == NULL) {
        printf("nessun percorso\n");
    } else {
        if (partenza < arrivo) {
            pianificadritto(start, finish, root);
        }
        if (arrivo < partenza) {
            pianificareverse(start, finish, root);
        }
    }
}

void pianificadritto(struct Node * start,struct Node * finish,struct Node * root) {
    struct Node *next;
    struct list *coda = NULL, *tmp = NULL, *tmp1 = NULL, *head = NULL, *prec = NULL;
    int tappe = 0,stampa[50],i=0;
    next = Next(root, start);
    if (next != NULL) {
        coda = createNodeList(start->data);
        head = coda;
        head->precedente=NULL;
        while (next->data <= finish->data && next != NULL) {
            tappe++;
            if(i==-1){
                prec=tmp;
            }else {
                prec = coda;
            }
            i=0;
            while (next->data <= finish->data && next != NULL) {
                if ((next->data - start->data) <= start->max) {
                    tmp1 = createNodeList(next->data);
                    coda->next = tmp1;
                    coda = coda->next;
                    coda->tappe = tappe;
                    coda->precedente = prec;
                } else {
                    break;
                }
                next = Next(root, next);
                if (next == NULL || next->data > finish->data) {
                    break;
                }
            }
            if (coda->data != finish->data) {
                if(coda->visitato==1){
                    tmp=head;
                    if(start->data == head->data){
                        break;
                    }
                    while(tmp->next->data != start->data){
                        tmp=tmp->next;
                    }
                    if(tmp->data == head->data){
                        break;
                    }
                    start= searchNode(root,tmp->data);
                    tmp->visitato=1;
                    tappe=tmp->tappe;
                    i=-1;
                }else {
                    start = searchNode(root, coda->data);
                    next = Next(root, start);
                    coda->visitato = 1;
                    if (next == NULL || next->data > finish->data) {
                        break;
                    }
                }
            } else {
                break;
            }
        }

        if(coda->data==finish->data){
            tmp1 = head;
            tmp1 = tmp1->next;
            if (tmp1 != NULL) {
                while (tmp1->visitato == 1) {
                    tmp1 = tmp1->next;
                }
                if (tmp1 != NULL) {
                    tappe = tmp1->tappe;
                    tmp1->visitato = 1;
                    start = searchNode(root, tmp1->data);
                    tmp = tmp1->next;
                    if (tmp != NULL) {
                        while (tmp->data <= finish->data && tmp != NULL) {
                            tappe++;
                            prec = tmp1;
                            while (tmp->data <= finish->data && tmp != NULL) {
                                if ((tmp->data - start->data)<= start->max) {
                                    if (tappe < tmp->tappe || (tappe == tmp->tappe && start->data < tmp->precedente->data)) {
                                        tmp->tappe = tappe;
                                        tmp->precedente = prec;
                                    }
                                } else {
                                    break;
                                }
                                if (tmp->next == NULL || tmp->next->data > finish->data) {
                                    break;
                                }
                                tmp = tmp->next;
                                if(tmp==NULL){
                                    break;
                                }
                            }
                            while (tmp1->visitato == 1) {
                                tmp1 = tmp1->next;
                            }
                            if (tmp1 != NULL) {
                                tappe = tmp1->tappe;
                                tmp1->visitato = 1;
                                start = searchNode(root, tmp1->data);
                                tmp = tmp1->next;
                                if(tmp==NULL){
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    }
                }
                tmp1 = NULL;
                next = NULL;
                prec = NULL;
                tmp = NULL;
                i=0;
                while (coda != NULL) {
                    stampa[i]=coda->data;
                    coda = coda->precedente;
                    i++;
                }
                i--;
                while(i>=0){
                    printf("%d",stampa[i]);
                    if(i!=0){
                        printf(" ");
                    }
                    i--;
                }
                if (head != NULL) {
                    freeList(coda);
                }
                head = NULL;
                coda=NULL;
            }
        } else {
            printf("nessun percorso");
        }
    }else{
        printf("nessun percorso");
    }
}

void pianificareverse(struct Node * start,struct Node * finish,struct Node * root) {
    struct Node *pre;
    struct list *coda = NULL, *tmp = NULL, *tmp1 = NULL, *head = NULL, *prec = NULL;
    int tappe = 0,stampa[100],i=0;
    pre = findPredecessor(root, start);
    if (pre != NULL) {
        coda = createNodeList(start->data);
        head = coda;
        head->precedente=NULL;
        while (pre->data >= finish->data && pre != NULL) {
            tappe++;
            if (i == -1) {
                prec = tmp;
            } else {
                prec = coda;
            }
            i = 0;
            while (pre->data >= finish->data && pre != NULL) {
                if ((start->data - pre->data) <= start->max) {
                    tmp1 = createNodeList(pre->data);
                    coda->next = tmp1;
                    coda = coda->next;
                    coda->tappe = tappe;
                    coda->precedente = prec;
                } else {
                    break;
                }
                pre = findPredecessor(root, pre);
                if (pre == NULL || pre->data < finish->data) {
                    break;
                }
            }
            if (coda->data != finish->data) {
                if (coda->visitato == 1) {
                    tmp = head;
                    tmp=head;
                    if(start->data == head->data){
                        break;
                    }
                    while (tmp->next->data != start->data) {
                        tmp = tmp->next;
                    }
                    if (tmp->data == head->data) {
                        break;
                    }
                    start = searchNode(root, tmp->data);
                    tmp->visitato = 1;
                    tappe = tmp->tappe;
                    i = -1;
                } else {
                    start = searchNode(root, coda->data);
                    pre = findPredecessor(root, start);
                    coda->visitato = 1;
                    if (pre == NULL || pre->data < finish->data) {
                        break;
                    }
                }
            } else {
                break;
            }
        }

        if (coda->data == finish->data) {
            tmp1 = head;
            tmp1 = tmp1->next;
            if (tmp1 != NULL) {
                while (tmp1->visitato == 1) {
                    tmp1 = tmp1->next;
                }
                if (tmp1 != NULL) {
                    tappe = tmp1->tappe;
                    tmp1->visitato = 1;
                    start = searchNode(root, tmp1->data);
                    tmp = tmp1->next;
                    if (tmp != NULL) {
                        while (tmp->data >= finish->data && tmp != NULL) {
                            tappe++;
                            prec = tmp1;
                            while (tmp->data >= finish->data && tmp != NULL) {
                                if ((start->data - tmp->data) <= start->max) {
                                    if (tappe < tmp->tappe || (tappe == tmp->tappe && start->data < tmp->precedente->data)) {
                                        tmp->tappe = tappe;
                                        tmp->precedente = prec;
                                    }
                                } else {
                                    break;
                                }
                                if (tmp->next == NULL || tmp->next->data < finish->data) {
                                    break;
                                }
                                tmp = tmp->next;
                                if(tmp==NULL){
                                    break;
                                }
                            }
                            while (tmp1->visitato == 1) {
                                tmp1 = tmp1->next;
                            }
                            if (tmp1 != NULL) {
                                tappe = tmp1->tappe;
                                tmp1->visitato = 1;
                                start = searchNode(root, tmp1->data);
                                tmp = tmp1->next;
                                if(tmp==NULL){
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    }
                }
                tmp1 = NULL;
                pre = NULL;
                prec = NULL;
                tmp = NULL;
                i=0;
                while (coda != NULL) {
                    stampa[i]=coda->data;
                    coda = coda->precedente;
                    i++;
                }
                i--;
                while(i>=0){
                    printf("%d",stampa[i]);
                    if(i!=0){
                        printf(" ");
                    }
                    i--;
                }
                if (head != NULL) {
                    freeList(coda);
                }
                head = NULL;
                coda=NULL;
            }
        } else {
            printf("nessun percorso");
        }
    }else{
        printf("nessun percorso");
    }
}



struct Node* aggiungistazione(int distanza, int AUTONOMIA[N],Node* root) {
    struct Node* nodo;
    int i;
    if(root==NULL || searchNode(root,distanza)==NULL) {
        root=insert(root, distanza);
        nodo=searchNode(root,distanza);
        nodo->max=-1;
        for (i = 0; i < N; i++) {
            nodo->AUTO[i] = AUTONOMIA[i];
            if(AUTONOMIA[i] > nodo->max){
                nodo->max=AUTONOMIA[i];
            }
        }
        printf("aggiunta");
    }
    else{
        printf("non aggiunta");
    }
    return root;
}


struct Node* demoliscistazione(int distanza,Node* root){
    if(searchNode(root,distanza)!=NULL) {
        root=delete(root, distanza);
        printf("demolita");
    }
    else {
        printf("non demolita");
    }
    return root;
}

struct Node* aggiungiauto(int distanza,int autonomia,Node* root) {
    struct Node *nodo;
    int i, flag = 0;
    nodo = searchNode(root, distanza);
    if (nodo != NULL) {
        if(autonomia > nodo->max){
            nodo->max=autonomia;
        }
        for (i = 0; i < N && flag == 0; i++) {
            if (nodo->AUTO[i] == -1) {
                nodo->AUTO[i] = autonomia;
                flag = 1;
            }
        }
        printf("aggiunta");
    }
    else{
        printf("non aggiunta");
    }
    return root;
}


struct Node* rottamaauto(int distanza,int autonomia,Node* root) {
    struct Node *nodo;
    int i, flag = 0;
    nodo = searchNode(root, distanza);
    if (nodo != NULL) {
        for (i = 0; i < N && flag == 0; i++) {
            if (nodo->AUTO[i] == autonomia) {
                nodo->AUTO[i] = -1;
                flag = 1;
                if(nodo->max == autonomia){
                    nodo->max=-1;
                    for(i=0;i<N;i++){
                        if(nodo->AUTO[i]>nodo->max){
                            nodo->max=nodo->AUTO[i];
                        }
                    }
                }
            }
        }
    }
    else{
        printf("non rottamata");
    }
    if(nodo!=NULL){
        if(flag==1){
            printf("rottamata");
        }
        else {
            printf("non rottamata");
        }
    }
    return root;
}


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

struct Node* findMinNode(struct Node* root) {
    if (root == NULL || root->left == NULL) {
        return root;
    }
    return findMinNode(root->left);
}


struct Node* searchNode(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return searchNode(root->left, data);
    } else {
        return searchNode(root->right, data);
    }
}


struct list* createNodeList(int data) {
    struct list* newNode = (struct list*)malloc(sizeof(struct list));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


void freeList(struct list* head) {
    struct list* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

struct Node* findPredecessor(struct Node* root, struct Node* node) {
    if (root == NULL || node == NULL) {
        return NULL;
    }
    if (node->left != NULL) {
        return findMaxNode(node->left);
    } else {
        struct Node* predecessor = NULL;
        struct Node* current = root;

        while (current != NULL) {
            if (current->data > node->data) {
                current = current->left;
            } else if (current->data < node->data) {
                predecessor = current;
                current = current->right;
            } else {
                break;
            }
        }
        return predecessor;
    }
}


struct Node* findMaxNode(struct Node* node) {
    if (node == NULL) {
        return NULL;
    }
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

void freeBST(struct Node* root) {
    if (root == NULL) {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

struct Node* Next(struct Node* root, struct Node* node) {
    struct Node*tmp=root;
    if (node->right != NULL) {
        return findMinNode(node->right);
    }
    struct Node* successor = NULL;
    while (tmp != NULL) {
        if (node->data < tmp->data) {
            successor = tmp;
            tmp = tmp->left;
        } else if (node->data > tmp->data) {
            tmp = tmp->right;
        } else {
            break;
        }
    }
    return successor;
}

struct Node* delete(struct Node* root, int data) {
    int i;
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            for(i=0;i<N;i++) {
                temp->AUTO[i] = root->right->AUTO[i];
            }
            temp->max=root->right->max;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            for(i=0;i<N;i++) {
                temp->AUTO[i] = root->left->AUTO[i];
            }
            temp->max=root->left->max;
            free(root);
            return temp;
        }
        struct Node* temp = findMinNode(root->right);
        root->data = temp->data;
        for(i=0;i<N;i++) {
            root->AUTO[i] = temp->AUTO[i];
        }
        root->max=temp->max;
        root->right = delete(root->right, temp->data);
    }
    return root;
}


















