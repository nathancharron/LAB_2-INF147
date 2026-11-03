#pragma once

#include "tab_points.h"

typedef struct {
	t_point *points;
	int taille;
	int sommet;
} t_pile;

//procédure pour initialiser une pile, la pile sera vide après un appel
//de cette procédure. Peut aussi être utilisée pour vider une pile.
t_pile initpile(int taille);

void liberer_pile(t_pile* pile);

int get_nb_element(const t_pile* pile);

int get_sommet(const t_pile* pile, t_point* points);

int get_suiv_sommet(const t_pile* pile, t_point* point);

//fonction pour vérifier si une pile est pleine
int pleine(const t_pile*);

//fonction pour vérifier si une pile est vide
int vide(const t_pile*);

//procédure pour ajouter un élément de plus sur une pile
void push(t_pile*, t_point);

//procédure pour enlever un élément du haut d'une pile
void pop(t_pile*, t_point*);
