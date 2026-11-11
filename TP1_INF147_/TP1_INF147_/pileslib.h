
/************************************************************************/
/* INF147 - TP1 : Calcul de l'enveloppe convexe                         */
/* Auteur : Nathan Charron-Galarneau et Gregory Osorio Rivera           */
/* Date : Automne 2026                                                  */
/*                                                                      */
/* Ce module contient les fonctions pour initialiser                    */
/* et libérer une pile, ajouter ou retirer des points,                  */
/* ainsi que consulter les éléments au sommet.                          */
/************************************************************************/

#pragma once
#include "tab_points.h"

/************************************************************************/
/*                    DEFINITION DU TYPE PILE                           */
/************************************************************************/

typedef struct {
    t_point* points;    //Tableau dynamique des points de la pile.    
    int taille;         // Capacité maximale de la pile.                
    int sommet;         //Indice du sommet                           
} t_pile;

/************************************************************************/
/*                    DECLARATIONS DES FONCTIONS                        */
/************************************************************************/

/***************************** INITPILE *********************************/
/* Cette fonction initialise une pile vide en allouant un tableau       */
/* dynamique pouvant contenir le nombre de points donné par taille.     */
/* RETOUR: La pile initialisée avec un sommet égal à -1.                */
/************************************************************************/
t_pile initpile(int taille);

/*************************** LIBERER_PILE *******************************/
/* Cette fonction libère la mémoire allouée au tableau dynamique de     */
/* la pile et remet ses champs à leur état initial.                     */
/* RETOUR: Aucun (void).                                                */
/************************************************************************/
void liberer_pile(t_pile* pile);

/************************** GET_NB_ELEMENT ******************************/
/* Cette fonction détermine le nombre d'éléments actuellement           */
/* présents dans la pile.                                               */
/* RETOUR: Le nombre de points contenus dans la pile.                   */
/************************************************************************/
int get_nb_element(const t_pile* pile);

/**************************** GET_SOMMET ********************************/
/* Cette fonction récupère une copie du point au sommet de la pile      */
/* dans le paramètre points, sans modifier la pile.                     */
/* RETOUR: 1 si la récupération réussit, 0 si la pile est vide.         */
/************************************************************************/
int get_sommet(const t_pile* pile, t_point* points);

/************************* GET_SUIV_SOMMET ******************************/
/* Cette fonction récupère une copie du point situé immédiatement       */
/* sous le sommet de la pile.                                           */
/* RETOUR: 1 si la récupération réussit, 0 si la pile contient          */
/* moins de deux éléments.                                              */
/************************************************************************/
int get_suiv_sommet(const t_pile* pile, t_point* point);

/****************************** PLEINE **********************************/
/* Cette fonction vérifie si la pile a atteint sa capacité maximale.    */
/* RETOUR: 1 si la pile est pleine, 0 sinon.                            */
/************************************************************************/
int pleine(const t_pile*);

/******************************** VIDE **********************************/
/* Cette fonction vérifie si la pile ne contient aucun élément.         */
/* RETOUR: 1 si la pile est vide, 0 sinon.                              */
/************************************************************************/
int vide(const t_pile*);

/******************************** PUSH **********************************/
/* Cette fonction ajoute un point au sommet de la pile si celle-ci      */
/* n'est pas pleine.                                                    */
/* RETOUR: Aucun (void).                                                */
/************************************************************************/
void push(t_pile*, t_point);

/******************************** POP ***********************************/
/* Cette fonction retire le point au sommet de la pile et en transmet   */
/* une copie par pointeur, si la pile n'est pas vide.                   */
/* RETOUR: Aucun (void).                                                */
/************************************************************************/
void pop(t_pile*, t_point*);
