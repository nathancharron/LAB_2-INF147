#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>



typedef struct {
	int posx, posy;
	double rad;
	double dist;
	int position;
} t_point;

#define PI 3.14159265358979323846

double distance(t_point* pA, t_point* pB);
double prod_vectoriel(t_point* p0, t_point* p1, t_point* p2);
double coord_polaire(t_point* pA, t_point* pB, t_point* href);
int alea(int min, int max);
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy);
int occurence(int tab[], int taille, int celuila);
int trouver_pt_minimal(const t_point tab_pts[], int taille);
t_point placer_pt_reference(t_point tab_pts[], int pos_min);

int main(void)
{

	







	system("pause");
	return EXIT_SUCCESS;
}

double distance(t_point* pA, t_point* pB) {

	double differenceX = pB->posx - pA->posx;
	double differenceY = pB->posy - pA->posy;

	double dist = sqrt(((differenceX) * (differenceX)) + ((differenceY) * (differenceY)));

	return dist;
}

double prod_vectoriel(t_point* p0, t_point* p1, t_point* p2) {

	double vecteurA = p2->posx - p0->posx;
	double vecteurB = p1->posx - p0->posx;
	double vecteurC = p2->posy - p0->posy;
	double vecteurD = p1->posy - p0->posy;

	return vecteurA * vecteurD - vecteurB * vecteurC;

}

double coord_polaire(t_point* pA, t_point* pB, t_point* h_ref) {

	double dist = distance(pA, pB);

	double angle = asin((pB->posy - pA->posy) / dist);

	double produit = prod_vectoriel(pA, h_ref, pB);
    
	if (produit < 0.0) {
		return (2 * (PI/2 - angle));
	}
	
}

int alea(int min, int max) {    //retourne un entier aléatoire dans [min, max]
	return (rand() % (max - min + 1) + min);
}

int occurence(t_point tab[],int taille, int posy) {

	for (int i = 0; i < taille; i++) {

		if (tab[i].posy == posy) {
			return 1;
		}

	}

	return 0;

}

void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy) {

	for (int i = 0; i < taille; i++) {
		tab_pts[i].posx = alea(1, maxx);

		do {
			tab_pts[i].posy = alea(1, maxy);
		} while (occurence(tab_pts, i, tab_pts[i].posy));
	}


}

int trouver_pt_minimal(const t_point tab_pts[], int taille) {

	int indiceMin = 0;

	for (int i = 1; i < taille; i++) {


		if (tab_pts[i].posy < tab_pts[indiceMin].posy) {
			indiceMin = i;
		}
		else if (tab_pts[i].posy == tab_pts[indiceMin].posy && tab_pts[i].posx < tab_pts[indiceMin].posx) {
			indiceMin = i;
		}

	}

	return indiceMin;

}

t_point placer_pt_reference(t_point tab_pts[], int pos_min) {

	t_point temp = tab_pts[0];
	tab_pts[0] = tab_pts[pos_min];
	tab_pts[pos_min] = temp;

	t_point pointRef = { tab_pts[0].posx, 800 };

	return pointRef;
}
