#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"
#include "router.h"
#include "connection.h"

//STRUCT AREA
struct router {
    char * name;
    char * carrier;
    Connect * cnt;
    Router * Next;
};

typedef struct routlist {
    Router * first;
    Router * last;
}RoutList;

//END OF STRUCT AREA
//STATIC FUNCTIONS AREA
static char * adjustString(char * name){
    char * space = (char *)malloc(strlen(name)*sizeof(char)+1);
    strcpy(space, name);
    return space;
}

static Router * findPreviousRouter(Router * r, Router * rw) {
    while(r != NULL && r->Next != rw) {
        r = r->Next;
    }
    return r;
}

static int isFirst(Router * r, Router * rw) {
    Router * temp = findPreviousRouter(r, rw);
    if(temp == NULL && rw->Next != NULL) return 1;
    else return 0;
}

static int isMiddle(Router * r, Router * rw) {
    Router * temp = findPreviousRouter(r, rw);
    if(temp != NULL && rw->Next != NULL) return 1;
    else return 0;
}

static int isLast(Router * r, Router * rw) {
    Router * temp = findPreviousRouter(r, rw);
    if(temp != NULL && rw->Next == NULL) return 1;
    else return 0;
}
//END OF STATIC FUNCTIONS AREA
RoutList * inicializeRouters() {
    RoutList * list = (RoutList *)malloc(sizeof(RoutList));
    list->first = NULL;
    list->last = NULL;
    return list;
}

Router * findRouter(RoutList * rlist, char * name) {
    Router * aux = rlist->first;
    while(aux != NULL && strcmp(aux->name, name)){
        aux = aux->Next;
    }
    return rlist;
}

void registerRouter(RoutList * rlist, char * n, char * o) {
    Router * newRouter = (Router *)malloc(sizeof(Router));
    newRouter->name = adjustString(n);
    newRouter->carrier = adjustString(o);
    newRouter->cnt = NULL;
    
    if(rlist->first == NULL) { //If router list is empty
        newRouter->Next = NULL;
        rlist->last = rlist->first = newRouter;
    } else { //If router list has elements
        newRouter->Next = rlist->first;
        rlist->first = newRouter;
    }
}

void removeRouter(RoutList * rlist, char * rn) {
    Router * wanted = findRouter(rlist, rn);
    Router * before = findPreviousRouter(rlist, wanted);
    if(before == NULL) { //First
        rlist->first = wanted->Next;
    }
    else if(wanted->Next == NULL) { //Last
        rlist->last = NULL;
    }
    else { //Middle
        before->Next = wanted->Next;
    }
    //free connects
}

void carrierFrequency(Router * rlist, char * carrier){
    int i = 0;
    while(rlist != NULL){
        if(!strcmp(rlist->carrier,carrier))
            i++;
        rlist = rlist->Next;
    }
    i ? printf("There are %d routers from '%s'.\n", i, carrier) :
    printf("There are no routers from '%s'.\n", carrier);
}

void printRouters(Router * r) {
    while(r != NULL){
        printf("name: %s\n", r->name);
        printf("carrier: %s\n\n", r->carrier);
        r = r->Next;
    }
}

char * routerName(Router * r) {
    if(r != NULL) return r->name;
    else return NULL;
}

Router * decimateRouters(Router * r) {
    Router * temp;
    while(r != NULL) {
        temp = r->Next;
        removeRouter(r, r->name);
        r = temp;
    }
    return NULL;
}

Router * webConnectRouters(Router * rlist, char * rn1, char * rn2) {
    Router * temp = findRouter(rlist, rn1);
    temp->cnt = webConnectRouterLL(temp->cnt, rlist, rn2);
    Router * temp1 = findRouter(rlist, rn2);
    temp1->cnt = webConnectRouterLL(temp1->cnt, rlist, rn1);
    return rlist;
}

Router * webDisconnectRouters(Router * rlist, char * rn1, char * rn2) {
    Router * temp1 = findRouter(rlist, rn1);
    Router * temp2 = findRouter(rlist, rn2);
    temp1->cnt = destroyConnection(temp1->cnt, rn2);
    temp2->cnt = destroyConnection(temp2->cnt, rn1);
    return rlist;
}

void PrintRouterConnections(Router * r) {
    while(r != NULL) {
        printf("\n--Connected to %s:\n", routerName(r));
        printConnections(r->cnt);
        r = r->Next;
    }
}
