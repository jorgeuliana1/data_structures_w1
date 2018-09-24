#include <stdlib.h>
#include <stdio.h>
#include "router.h"
#include "terminal.h"
#include "connection.h"
//STATIC FUNCTIONS AREA


//END OF STATIC FUNCTIONS
void printRouterAndTerminal(Router * r, Terminal * t) {
    if(r != NULL)
        printRouters(r);
    if(t != NULL)
        printTerminals(t);
}

void linkRouterToTerminal(char * rname, Router * rlist, char * tname, Terminal * tlist) {
    Terminal * t = findTerminal(tlist, tname);
    Router * r = findRouter(rlist, rname);
    if(r != NULL && t != NULL) //t->r = r;
        plugRouter(t, r);
    else printf("\nError: NOT FOUND\n\n");
}

Router * destroyRouter(Router * r, Terminal * t, char * rn) {
    t = disconnectRouter(t, rn);
    r = removeRouter(r, rn);
}

int enviadados (char * n1, char * n2, Terminal * tlist, Router * rlist){
    Terminal * t1 = findTerminal(tlist, n1);
    Terminal * t2 = findTerminal(tlist, n2);
    Router * r1 = t1->r; //find router by terminal
    Router * r2 = t1->r; //find router by terminal
     
    //check every connect list in rlist until find the router from the other router i guess im not sure anymore
}
