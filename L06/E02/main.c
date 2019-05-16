#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNGHSTRINGA 50

typedef struct{
    int giorno;
    int mese;
    int anno;
}data;

typedef struct{
    char codice[LUNGHSTRINGA];
    char nome[LUNGHSTRINGA];
    char cognome[LUNGHSTRINGA];
    data dataNascita;
    char via[LUNGHSTRINGA];
    char citta[LUNGHSTRINGA];
    int cap;
}Item;

typedef struct node{
    Item val;
    struct node *next;
}node_t,*link;

typedef enum{
    r_leggiTastiera, r_leggiFile, r_ricerca, r_cancellaCodice, r_cancellaDate, r_stampa, r_fine
}codiceComando;

void leggiFile(link* head);
void stampaItem(Item anag);
int dataMaggiore(data data1, data data2);
codiceComando leggiComando();
link SortListIns(link h, Item val);
link newNode(Item val, link next);
void selezionaDati(link* head, codiceComando comando);
void stampaLista(link head);
void leggiTastiera(link* head);
void ricerca(link head);
void cancellaCodice(link *head);
link ricercaPerData(link head, data data1, data data2);
link ricercaPerCodice(link head, char codice[]);
link cancellaCodiceR(link head, char codice[]);
void cancellaDate(link *head);

void stampaFile(link head);

int main() {

    link head = NULL;

    codiceComando comando= r_leggiTastiera;

    while(comando != r_fine){
        comando = leggiComando();

        selezionaDati(&head,comando);
    }

    return 0;
}

void selezionaDati(link* head, codiceComando comando) {

    switch(comando){
        case r_leggiTastiera:
            leggiTastiera(head);//Passaggio per referenza(in caso di cambio head)
            stampaLista(*head);//Passaggio per valore(non devo cambiare il valore di head)
            break;
        case r_leggiFile:
            leggiFile(head);
            stampaLista(*head);
            break;
        case r_ricerca:
            ricerca(*head);
            break;
        case r_cancellaCodice:
            cancellaCodice(head);
            break;
        case r_cancellaDate:
            cancellaDate(head);
            break;
        case r_stampa:
            stampaLista(*head);
            stampaFile(*head);
            break;
    }
}

void stampaFile(link head) {
    char nomeFile[30];

    //Controllo lista vuota
    if(head == NULL){
        printf("Lista vuota");
        exit(-1);
    }

    printf("Inserire nome file su cui vuoi salvare i dati: ");
    scanf("%s",nomeFile);

    FILE* fp = fopen(nomeFile,"w");
    if(fp == NULL){
        printf("Errore apertura file");
        exit(-1);
    }

    //Stampa lista su file
    link x;
    for(x = head; x!= NULL; x=x->next){
        fprintf(fp,"%s ",x->val.codice);
        fprintf(fp,"%s ",x->val.nome);
        fprintf(fp,"%s ",x->val.cognome);
        fprintf(fp,"%d/",x->val.dataNascita.giorno);
        fprintf(fp,"%d/",x->val.dataNascita.mese);
        fprintf(fp,"%d ",x->val.dataNascita.anno);
        fprintf(fp,"%s ",x->val.via);
        fprintf(fp,"%s ",x->val.citta);
        fprintf(fp,"%d ",x->val.cap);
        fprintf(fp,"\n");
    }

    fclose(fp);
}


void cancellaDate(link *head) {
    link link_supporto;
    data data1;
    data data2;

    printf("Inserire prima data(DD/MM/YYYY): ");
    scanf("%d/%d/%d", &data1.giorno,&data1.mese,&data1.anno);
    printf("Inserire seconda data(DD/MM/YYYY): ");
    scanf("%d/%d/%d", &data2.giorno,&data2.mese,&data2.anno);

    link_supporto = ricercaPerData(*head,data1,data2);

    while(link_supporto != NULL){
        //Prima di cancellarlo effettivamento lo stampo
        printf("Cancellata anagrafica:");
        stampaItem(link_supporto->val);
        *head = cancellaCodiceR(*head,link_supporto->val.codice);

        link_supporto = ricercaPerData(*head,data1,data2);
    }

}

void cancellaCodice(link *head){
    link link_supporto;
    char codice[LUNGHSTRINGA];

    printf("Inserire codice: ");
    scanf("%s", codice);

    link_supporto = ricercaPerCodice(*head,codice);

    if(link_supporto != NULL){
        *head = cancellaCodiceR(*head,codice);
        printf("Cancellata anagrafica:");
        stampaItem(link_supporto->val);
    }
    else
        printf("Anagrafica non trovata\n");

}

link cancellaCodiceR(link head, char codice[]) {
    link x, p;
    if (head == NULL)
        return NULL;
    for (x=head, p=NULL; x!=NULL; p=x, x=x->next) {
        if (!strcmp(x->val.codice,codice)) {
            if (x==head)
                head = x->next;
            else
                p->next = x->next;
            free(x);
            break;
        }
    }
    return head;
}


void ricerca(link head){
    link link_supporto;
    char codice[LUNGHSTRINGA];

    printf("Inserire codice: ");
    scanf("%s", codice);

    link_supporto = ricercaPerCodice(head,codice);

    if(link_supporto != NULL)
        stampaItem(link_supporto->val);
    else
        printf("Anagrafica non trovata\n");
}


link ricercaPerCodice(link head, char codice[]) {

    link x;
    if(head == NULL)
        return NULL;
    for(x = head; x != NULL; x = x->next){
        if(!strcmp(x->val.codice, codice))
            return x;
    }

    return NULL;
}

link ricercaPerData(link head, data data1, data data2) {

    link x;
    if(head == NULL)
        return NULL;
    for(x = head; x != NULL; x = x->next){
        if(dataMaggiore(x->val.dataNascita,data1) && dataMaggiore(data2,x->val.dataNascita))
            return x;
    }

    return NULL;
}


void leggiTastiera(link* head) {

    //Chiedo informazioni del nuovo anagramma da tastiera
    Item anag;
    printf("Inserisci codice: ");
    scanf("%s",anag.codice);
    printf("Inserisci nome: ");
    scanf("%s",anag.nome);
    printf("Inserisci cognome: ");
    scanf("%s",anag.cognome);
    printf("Inserisci data (DD/MM/YYYY): ");
    scanf("%d/%d/%d",&anag.dataNascita.giorno,&anag.dataNascita.mese,&anag.dataNascita.anno);
    printf("Inserisci via: ");
    scanf("%s",anag.via);
    printf("Inserisci città: ");
    scanf("%s",anag.citta);
    printf("Inserisci cap: ");
    scanf("%d",&anag.cap);

    //Inserisco nuovo anagramma nella lista
    *head = SortListIns(*head,anag);
}


codiceComando leggiComando(){

    char cmd[20];
    codiceComando c = r_leggiTastiera;

    char tabella[7][20] = {"leggiTastiera","leggiFile","ricerca","cancellaCodice","cancellaDate","stampaFile","fine"};

    printf("Inserisci comando ");
    printf("( leggiTastiera | leggiFile | ricerca | cancellaCodice | cancellaDate | stampaFile | fine ): ");
    scanf("%s",cmd);

    while(c < r_fine && strcmp(cmd,tabella[c]) != 0)
        c++;

    return c;
}

void stampaLista(link head){
    link x;
    if(head == NULL)
        return;
    for (x = head; x != NULL; x = x->next) {
        stampaItem(x->val);
    }
}



void leggiFile(link* head) {

    char nomeFile[30];
    printf("Inserisci nome file: ");
    scanf("%s", nomeFile);

    FILE *fp = fopen(nomeFile, "r");

    if (fp == NULL) {
        printf("Errore apertura file");
        exit(-1);
    }

    Item anag;//Item usato come variabile di supporto

    while (fscanf(fp, "%s %s %s %d/%d/%d %s %s %d",
                  anag.codice, anag.nome, anag.cognome, &anag.dataNascita.giorno, &anag.dataNascita.mese,
                  &anag.dataNascita.anno, anag.via, anag.citta, &anag.cap) != EOF) {
        *head = SortListIns(*head, anag);
    }

    fclose(fp);
}

link SortListIns(link h, Item val) {
    link x, p;
    if (h==NULL || dataMaggiore(h->val.dataNascita,val.dataNascita))
        return newNode(val, h);
    for (x=h->next, p=h;
         x!=NULL && dataMaggiore(val.dataNascita,x->val.dataNascita);
         p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}

link newNode(Item val, link next) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

int dataMaggiore(data data1, data data2){
    if(data1.anno > data2.anno)
        return 1;
    if(data1.anno < data2.anno)
        return 0;
    if(data1.mese > data2.mese)
        return 1;
    if(data1.mese < data2.mese)
        return 0;
    if(data1.giorno > data2.giorno)
        return 1;
    if(data1.giorno < data2.giorno)
        return 0;

    return 0;//Caso date uguali
}


void stampaItem(Item anag){
    printf("%s ",anag.codice);
    printf("%s ",anag.nome);
    printf("%s ",anag.cognome);
    printf("%d/",anag.dataNascita.giorno);
    printf("%d/",anag.dataNascita.mese);
    printf("%d ",anag.dataNascita.anno);
    printf("%s ",anag.via);
    printf("%s ",anag.citta);
    printf("%d ",anag.cap);
    printf("\n");

}
