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


