#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ATTENTE_MAX 7
#define ACHAT_MAX 7

void attente_aleatoire(unsigned int delais) {

/* Initialisation du désordre */
srandom(time(NULL) % delais);

/* Attente */
sleep((unsigned int)(random() % ATTENTE_MAX));

}

int place_aleatoire() {
    /* Initialisation du désordre */
    srandom(time(NULL));
    return ((unsigned int)(random() % ACHAT_MAX + 1));
}
