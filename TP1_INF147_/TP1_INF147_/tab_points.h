
/**************************************************************************************************************/
/* INF147 - TP1 : Calcul de l'enveloppe convexe                                                               */
/* Auteur : Nathan Charron-Galarneau et Gregory Osorio Rivera                                                 */
/* Date : Automne 2026                                                                                        */
/*                                                                                                            */
/* Ce module contient la définition du type t_point et les déclarations des fonctions permettant de           */
/* manipuler un tableau de points. Il permet de calculer la distance entre deux points, le produit vectoriel  */
/* et les coordonnées polaires.                                                                               */
/*                                                                                                            */
/* Il permet également de générer des points aléatoires, de trouver le point minimal et de trier les points   */
/* selon leurs angles polaires afin de préparer le calcul de l'enveloppe convexe.                             */
/**************************************************************************************************************/

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>

/**************************************************************************************************************/
/*                                      DEFINITION DES TYPES ET MACROS                                        */
/**************************************************************************************************************/


typedef struct {
    int posx, posy;  // Coordonnées X et Y du point
    double rad;      // Angle polaire du point en radians
    double dist;     // Distance par rapport au point minimal
    int position;    // Position du point dans le tableau trié
} t_point;

#define PI 3.14159265358979323846  // Valeur de pi
#define TAILLE 20                   // Nombre de points en mode aléatoire
#define MODE_ALEA 1                 // Mode de génération aléatoire
#define MODE_FICHIER 2              // Mode de lecture d'un fichier texte
#define MODE_SIMULATION 3           // Mode de simulation des moyennes
#define FFLUSH() while (getchar() != '\n')

/**************************************************************************************************************/
/*                                        DECLARATIONS DES FONCTIONS                                          */
/**************************************************************************************************************/

/********************************************* DISTANCE *******************************************************/
/* Cette fonction calcule la distance entre deux points à partir de leurs coordonnées X et Y.                 */
/* RETOUR: La distance entre les deux points (double).                                                        */
/**************************************************************************************************************/
double distance(t_point* pA, t_point* pB);

/****************************************** PROD_VECTORIEL ****************************************************/
/* Cette fonction calcule le produit vectoriel de deux vecteurs formés à partir de trois points.              */
/* RETOUR: La valeur du produit vectoriel (double).                                                           */
/**************************************************************************************************************/
double prod_vectoriel(t_point* p0, t_point* p1, t_point* p2);

/******************************************* COORD_POLAIRE ****************************************************/
/* Cette fonction calcule l'angle polaire entre les points pA et pB en utilisant un point de référence.       */
/* Le produit vectoriel permet de déterminer si l'angle est aigu ou obtus.                                    */
/* RETOUR: L'angle polaire calculé en radians (double).                                                       */
/**************************************************************************************************************/
double coord_polaire(t_point* pA, t_point* pB, t_point* href);

/************************************************ ALEA ********************************************************/
/* Cette fonction génère un nombre entier aléatoire compris entre les valeurs min et max.                     */
/* RETOUR: Le nombre entier généré aléatoirement (int).                                                       */
/**************************************************************************************************************/
int alea(int min, int max);

/******************************************* INIT_TAB_ALEA ****************************************************/
/* Cette fonction initialise les coordonnées des points du tableau avec des valeurs aléatoires.               */
/* Les coordonnées X sont comprises entre 1 et maxx et les Y entre 1 et maxy.                                 */
/* RETOUR: Aucun (void).                                                                                      */
/**************************************************************************************************************/
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy);

/********************************************* OCURENCE *******************************************************/
/* Cette fonction vérifie si une coordonnée Y est déjà présente parmi les points du tableau.                  */
/* RETOUR: 1 si la coordonnée est déjà présente, 0 sinon.                                                     */
/**************************************************************************************************************/
int occurence(t_point tab[], int taille, int celuila);

/***************************************** TROUVER_PT_MINIMAL *************************************************/
/* Cette fonction trouve le point ayant la plus petite coordonnée Y dans le tableau.                          */
/* RETOUR: L'indice du point minimal dans le tableau (int).                                                   */
/**************************************************************************************************************/
int trouver_pt_minimal(const t_point tab_pts[], int taille);

/**************************************** PLACER_PT_REFERENCE *************************************************/
/* Cette fonction permute le point minimal avec le premier point du tableau et crée un point de référence     */
/* ayant la même coordonnée X que le point minimal et une coordonnée Y de 800.                                 */
/* RETOUR: Le point de référence créé (t_point).                                                              */
/**************************************************************************************************************/
t_point placer_pt_reference(t_point tab_pts[], int pos_min);

/**************************************** CALCUL_COORD_POLAIRES ***********************************************/
/* Cette fonction calcule l'angle polaire et la distance de chaque point par rapport au point minimal.        */
/* RETOUR: Aucun (void).                                                                                      */
/**************************************************************************************************************/
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref);

/********************************************* TRIER_PTS ******************************************************/
/* Cette fonction trie les points selon leurs angles polaires, du plus petit au plus grand			          */
/* RETOUR: Aucun (void).                                                                                      */
/**************************************************************************************************************/
void trier_pts(t_point tab_pts[], int taille);
