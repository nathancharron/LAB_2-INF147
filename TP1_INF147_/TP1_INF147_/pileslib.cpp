
/************************************************************************/
/* INF147 - TP1 : Calcul de l'enveloppe convexe                         */
/* Auteur : Nathan Charron-Galarneau                                    */
/* Date : 11 novembre 2026                                              */
/*                                                                      */
/* Ce module contient les fonctions permettant de gérer une pile       */
/* dynamique de points. Il permet d'initialiser et de libérer une pile, */
/* d'ajouter ou de retirer des points, ainsi que de consulter les       */
/* éléments au sommet de celle-ci.                                      */
/*                                                                      */
/* La pile est utilisée pour conserver les points de l'enveloppe       */
/* convexe lors du parcours de Graham.                                  */
/************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pileslib.h"

/************************************************************************/
/*                    DEFINITIONS DES FONCTIONS                         */
/************************************************************************/

/************************************************************************/
// Initialise une pile vide et alloue la mémoire nécessaire.
t_pile initpile(int taille)
{
    t_pile pile;
    pile.points = (t_point*)malloc(taille * sizeof(t_point));
    assert(pile.points);

    pile.taille = taille;
    pile.sommet = -1;

    return pile;
}

/*************************** LIBERER_PILE *******************************/
// Libère la mémoire du tableau dynamique et réinitialise la pile.
void liberer_pile(t_pile* pile)
{
    free(pile->points);
    pile->taille = 0;
    pile->sommet = -1;
    pile->points = NULL;
}

/************************************************************************/
// Calcule le nombre d'éléments à partir de l'indice du sommet.
int get_nb_element(const t_pile* pile)
{
    return pile->sommet + 1;
}

/************************************************************************/
// Copie le point au sommet si la pile n'est pas vide.
int get_sommet(const t_pile* pile, t_point* point)
{
    if (pile->sommet == -1) {
        return 0;
    }

    *point = pile->points[pile->sommet];

    return 1;
}

/************************************************************************/
// Copie le point sous le sommet si la pile contient au moins 2 éléments.
int get_suiv_sommet(const t_pile* pile, t_point* point)
{
    if (pile->sommet <= 0) {
        return 0;
    }

    *point = pile->points[pile->sommet - 1];

    return 1;
}

/************************************************************************/
// Vérifie si le sommet a atteint le dernier indice du tableau.
int pleine(const t_pile* pile)
{
    return (pile->sommet == pile->taille - 1);
}

/************************************************************************/
// Vérifie si le sommet est à -1, ce qui indique une pile vide.
int vide(const t_pile* pile)
{
    return (pile->sommet == -1);
}

/************************************************************************/
// Ajoute un point au sommet après avoir vérifié la capacité de la pile.
void push(t_pile* pile, t_point point)
{
    if (pleine(pile))
        printf("ERREUR!!! Débordement de pile.");
    else {
        pile->sommet++;
        pile->points[pile->sommet] = point;
    }
}

/************************************************************************/
// Copie le point au sommet puis décrémente son indice.
void pop(t_pile* pile, t_point* point)
{
    if (vide(pile))
        printf("ERREUR!!! Pile vide.");
    else {
        *point = pile->points[pile->sommet];
        pile->sommet--;
    }
}
