
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shm_const.h"
#include "shm_const.h"

/******************************************************************************/
/*
 * Correspond à parking.c
*/
/******************************************************************************/

extern int creer_initialiser_semaphore();
extern int *attacher_segment_memoire();
extern int creer_segment_memoire();

int main(int argc, char *argv[]){
    pid_t pid_affichage; /* no du processus du processus affichage */
    pid_t pid_caisse; /* no des processus  caisse */

    int code_retour_fin_caisse;
    int code_retour_fin_affichage;

    
    int nombre_places; /* Paramètre Nombre de places */
    char * nombre_places_str; /* Pour conversion du nombre_places (int) en chaine */

    char *titre_film; /* Paramètre Titre du film */

    int shmid; /* Id du segment de mémoire partagé */
    int semid; /* Id du sémaphore */

    char shmid_str[20]; /* Pour conversion du shmid (int) en chaine */
    char semid_str[20]; /* Pour conversion du semid (int) en chaine */

    int *mem; /* Adresse du segment de mémoire partagée */

    char param_gnome_terminal[80];


     if ( argc != 4 ) {
        fprintf(stderr, "Usage : %s nombre_places\n", argv[0]);
        return(3);
    }


    nombre_places_str = argv[3];
    nombre_places = atoi(nombre_places_str);


    titre_film = argv[2];

    /* Avant de créer les fils :
    * - on crée le semaphore
    * - on crée le segment de mémoire partagé
    * - on s'attache le segment de mémoire partagé
    * - on initialise le nombre de places de cinéma libres dans la shm
    */

   /* Création sémaphore */
    creer_initialiser_semaphore(CLE_SEM, &semid);
    /* Création segment de mémoire partagé */
    creer_segment_memoire(CLE_SHM, &shmid);
/*
printf("DEBUg : parking : shmid=%d\n", shmid);
*/

    /* Attachement du segment de mémoire partagée */
    mem = attacher_segment_memoire(NULL, &shmid);

    /* Initialisation du nombre de places dans la mémoire partagée */
    *mem = nombre_places;

    /* Conversion des shmid et semid (int) en chaînes pour appel programme externe */
    sprintf(shmid_str, "%d", shmid);
    sprintf(semid_str, "%d", semid);

    /* Création du fils affichage */
    pid_affichage = fork();
    if (pid_affichage == -1) {
        /* Erreur */
        perror("Erreur fork pour affichage");
        return 1;
    }

    if (pid_affichage == 0) {
        /*
        printf("Je suis le fils entree, je vais faire execl dans 10s shmid_str=%s, semid_str=%s\n", shmid_str, semid_str);
        */
        execl("affichage_cinema", "affichage_cinema", shmid_str,semid_str,nombre_places_str,titre_film, NULL);
        /* En cas d'erreur */
        perror("Erreur execl affichage"); 
        exit(1);
    }
    int nombre_caisses = atoi(argv[1]);
    /* Création des processus caisses */
    for (int i = 1; i < nombre_caisses; i++) {
        pid_t pid_caisse = fork();

        if (pid_caisse == -1) {
            perror("Erreur fork pour caisse");
            return 1;
        }
        else if(pid_caisse > 0) {
            execl("caisse", "caisse", shmid_str, semid_str, NULL);
            perror("Erreur execl caisse");
            exit(1);
        }
        // parent process
        waitpid(pid_affichage, &code_retour_fin_affichage, 0);
        waitpid(pid_caisse, &code_retour_fin_caisse, 0);
        wait(NULL);
    }
}
