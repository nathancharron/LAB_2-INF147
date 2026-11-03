#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pileslib.h"
//procédure pour initialiser une pile, la pile sera vide
t_pile initpile(int taille)
{
	t_pile pile;
	pile.points = (t_point*)malloc(taille * sizeof(t_point));
	assert(pile.points);

	pile.taille = taille;
	pile.sommet = -1;

	return pile;
}

void liberer_pile(t_pile* pile)
{
	free(pile->points);
	pile->taille = 0;
	pile->sommet = -1;
	pile->points = NULL;

}

int get_nb_element(const t_pile* pile)
{
	return pile->sommet + 1;
}

int get_sommet(const t_pile* pile, t_point* point)
{
	if(pile->sommet == -1){
		return 0;
	}

	*point = pile->points[pile->sommet];

	return 1;
	
}

int get_suiv_sommet(const t_pile* pile, t_point* point) 
{
	if (pile->sommet <=0) {
		return 0;
	}

	*point = pile->points[pile->sommet-1];

	return 1;


}

//fonction pour vérifier si une pile est pleine
int pleine(const t_pile* pile)
{
	return (pile->sommet == pile->taille - 1);
}
//fonction pour vérifier si une pile est vide
int vide(const t_pile* pile)
{
	return (pile->sommet == -1);
}

//procédure pour ajouter un élément de plus sur une pile
void push(t_pile* pile, t_point point)
{
	if (pleine(pile))
		printf("ERREUR!!! Débordement de pile.");
	else {
		pile->sommet++;
		pile->points[pile->sommet] = point;
	}
}

//procédure pour enlever un élément du haut d'une pile
void pop(t_pile * pile, t_point * point)
{
	if (vide(pile))
		printf("ERREUR!!! Pile vide.");
	else {
		*point = pile->points[pile->sommet];
		pile->sommet--;
	}
}
