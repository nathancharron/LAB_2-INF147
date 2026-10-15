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