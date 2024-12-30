/* caisse.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "shm_op.c"
#include "shm_const.h"

/******************************************************************************/
/*
 * Nouveau fichier pour gérer les caisses inspirée de entree.c
 * A modifier
 */
/******************************************************************************/

extern void attente_aleatoire(unsigned int delais);
extern int P(int semid);
extern int V(int semid);

void achat_places(int *mem, int semid) {
    P(semid);

    int nb_places = (random() % 7) + 1; // Nombre de places aléatoire entre 1 et 7

    if (*mem >= nb_places) {
        *mem -= nb_places;
        printf("Caisse: %d places achetées, %d restantes.\n", nb_places, *mem);
    } else {
        printf("Caisse: Demande de %d places refusée, seulement %d disponibles.\n", nb_places, *mem);
    }

    V(semid);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <shmid> <semid>\n", argv[0]);
        return 1;
    }

    int shmid = atoi(argv[1]);
    int semid = atoi(argv[2]);
    int *mem = attacher_segment_memoire(NULL, &shmid);

    srandom(time(NULL) ^ (getpid() << 16)); // Initialisation du générateur aléatoire

    while (1) {
        attente_aleatoire(3);

        if (*mem == 0) {
            printf("Caisse: Plus de places disponibles. Fermeture.\n");
            break;
        }

        achat_places(mem, semid);
    }

    return 0;
}
