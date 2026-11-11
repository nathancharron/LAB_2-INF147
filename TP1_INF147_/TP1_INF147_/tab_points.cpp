
/**************************************************************************************************************/
/* INF147 - TP1 : Calcul de l'enveloppe convexe                                                               */
/* Auteur : Nathan Charron-Galarneau et Gregory Osorio Rivera                                                 */
/* Date : Automne 2026                                                                                        */
/*                                                                                                            */
/* Ce module contient les fonctions permettant de manipuler un tableau de points. Il permet de calculer la    */
/* distance entre deux points, le produit vectoriel et les coordonnées polaires.                              */
/*                                                                                                            */
/* Il permet également de générer des points aléatoires, de trouver le point minimal et de trier les points   */
/* selon leurs angles polaires afin de préparer le calcul de l'enveloppe convexe.                             */
/**************************************************************************************************************/

#include "tab_points.h"

/**************************************************************************************************************/
//On calcule la distance entre deux points
double distance(t_point* pA, t_point* pB) {

	double differenceX = pB->posx - pA->posx;
	double differenceY = pB->posy - pA->posy;

	double dist = sqrt(((differenceX) * (differenceX)) + ((differenceY) * (differenceY)));

	return dist;
}

/**************************************************************************************************************/
//On calcule le produit vectoriel a l'aide de 3 points
double prod_vectoriel(t_point* p0, t_point* p1, t_point* p2) {

	double vecteurA = p2->posx - p0->posx;
	double vecteurB = p1->posx - p0->posx;
	double vecteurC = p2->posy - p0->posy;
	double vecteurD = p1->posy - p0->posy;

	return vecteurA * vecteurD - vecteurB * vecteurC;

}

/**************************************************************************************************************/
//Calcule la l'angle polaire et la retourne des points A et B
double coord_polaire(t_point* pA, t_point* pB, t_point* h_ref) {

	double dist = distance(pA, pB);

	double angle = asin((pB->posy - pA->posy) / dist);

	double produit = prod_vectoriel(pA, h_ref, pB);

	if (produit > 0.0) {
		/*Si le produit vectoriel est plus grand
		que 0, l'angle est aigu*/
		return angle;
	}
	else if (produit < 0.0) {
		/*Si le produit vectoriel est negatif
		on retourne son angle equivalent*/
		return angle + (2 * (PI / 2 - angle));
	}
	else {
		/*Si le produit vectoriel vaut 0,
		l'angle vaut a 90 (en rad)*/
		return PI / 2;
	}

}

/**************************************************************************************************************/
static int alea(int min, int max) {    //retourne un entier aléatoire dans [min, max]
	return (rand() % (max - min + 1) + min);
}

/**************************************************************************************************************/
//Fonction qui determine si un nombre revient plusieurs fois
int occurence(t_point tab[], int taille, int posy) {

	for (int i = 0; i < taille; i++) {

		if (tab[i].posy == posy) {
			return 1;
		}

	}

	return 0;

}

/**************************************************************************************************************/
//Initialise tout les points du tableau aleatoirement
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy) {

	for (int i = 0; i < taille; i++) {
		tab_pts[i].posx = alea(1, maxx);

		/*Verifie si 2 points on le meme posy*/
		do {
			tab_pts[i].posy = alea(1, maxy);
		} while (occurence(tab_pts, i, tab_pts[i].posy));
	}

}

/**************************************************************************************************************/
//Permet de trouver le point avec le posy le plus petit
int trouver_pt_minimal(const t_point tab_pts[], int taille) {

	int indiceMin = 0;

	for (int i = 1; i < taille; i++) {

		if (tab_pts[i].posy < tab_pts[indiceMin].posy) {
			indiceMin = i;
		}
		else if (tab_pts[i].posy == tab_pts[indiceMin].posy && tab_pts[i].posx < tab_pts[indiceMin].posx) {
			indiceMin = i;/*Si deux points ont le meme posy, on choisi
							lui avec le posx le plus petit*/
		}

	}

	return indiceMin;

}

/**************************************************************************************************************/
/*Avec le pt_minimal, on permute le[0]
du tableau pour avoir le pt de reference*/
t_point placer_pt_reference(t_point tab_pts[], int pos_min) {

	//On cree des variables temporaraires
	t_point temp = tab_pts[0];
	tab_pts[0] = tab_pts[pos_min];
	tab_pts[pos_min] = temp;

	//On defini le pt de reference
	t_point pointRef = { tab_pts[0].posx, 800 };

	return pointRef;
}

/**************************************************************************************************************/
//On calcule les coord. polaires de chacun des points
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref) {

	for (int i = 1; i < taille; i++) {

		tab_pts[i].rad = coord_polaire(&tab_pts[0], &tab_pts[i], ref);

		tab_pts[i].dist = distance(&tab_pts[0], &tab_pts[i]);

	}
}

/**************************************************************************************************************/
//Tri les points (ordre croissant) par rapport a leur angle polaire
void trier_pts(t_point tab_pts[], int taille) {


	for (int i = 1; i < taille; i++) {

		for (int j = i + 1; j < taille; j++) {

			t_point temp = tab_pts[j];

			/*Si egalite entre deux points, celui avec la plus
			courte distance est place devant*/
			if ((tab_pts[i].rad > tab_pts[j].rad) ||
				(tab_pts[i].rad == tab_pts[j].rad && tab_pts[i].dist > tab_pts[j].dist)) {


				tab_pts[j] = tab_pts[i];
				tab_pts[i] = temp;

			}

		}

	}

}
