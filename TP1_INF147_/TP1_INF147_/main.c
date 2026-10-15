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

double distance(t_point* pA, t_point* pB);
double prod_vectoriel(t_point* p0, t_point* p1, t_point* p2);

int main(void)
{

	







	system("pause");
	return EXIT_SUCCESS;
}

double distance(t_point* pA, t_point* pB) {

	double differenceX = pB->posx - pA->posx;
	double differenceY = pB->posy - pA->posy;

	distance = sqrt(((differenceX) * (differenceX)) - ((differenceY) * (differenceY)));

	return distance;
}

double prod_vectoriel(t_point* p0, t_point* p1, t_point* p2) {

	double vecteurA = p1->posx - p0->posx;
	double vecteurB = p2->posx - p0->posx;
	double vecteurC = p1->posy - p0->posy;
	double vecteurD = p2->posy - p0->posy;

	return vecteurA * vecteurD - vecteurB * vecteurC;

}