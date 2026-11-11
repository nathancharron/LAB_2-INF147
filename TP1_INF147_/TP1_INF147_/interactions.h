
/**************************************************************************************************************/
/* INF147 - TP1 : Calcul de l'enveloppe convexe                                                               */
/* Auteur : Nathan Charron-Galarneau et Gregory Osorio Rivera                                                 */
/* Date : Automne 2026                                                                                        */
/*                                                                                                            */
/* Ce module contient les déclarations des fonctions permettant de choisir le mode d'exécution,				  */
/* de sélectionner un fichier texte et de lire les coordonnées des points dans un tableau dynamique.          */                                                                      
/**************************************************************************************************************/

#pragma once
#include "tab_points.h"

/**************************************************************************************************************/
/*                                        DECLARATIONS DES FONCTIONS                                          */
/**************************************************************************************************************/

/******************************************* DEMANDER_MODE ****************************************************/
/* Cette fonction affiche un menu permettant à l'utilisateur de choisir entre les trois modes d'exécution :   */
/* aléatoire, fichier texte et simulation.																	  */
/* RETOUR: Un entier (1, 2 ou 3)									                                          */
/**************************************************************************************************************/
int demander_mode(void);

/******************************************* CHOISIR_FICHIER **************************************************/
/* Cette fonction demande à l'utilisateur le nom d'un fichier texte et tente de l'ouvrir en mode lecture.     */
/* Si le fichier est introuvable, elle redemande un nom jusqu'à ce qu'un fichier valide soit ouvert.          */
/* RETOUR: Un pointeur FILE*										                                          */
/**************************************************************************************************************/
FILE* choisir_fichier(void);

/******************************************** LIRE_POINTS *****************************************************/
/* Cette fonction lit le nombre de points et leurs coordonnées dans un fichier texte. Elle alloue un tableau  */
/* dynamique pour conserver les points.																		  */
/* RETOUR: Un pointeur vers le tableau dynamique de points							                          */
/**************************************************************************************************************/
t_point* lire_points(FILE* fichier, int* nb_points);
