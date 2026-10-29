#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

typedef struct {
	int posx, posy;
	double rad;
	double dist;
	int position;
} t_point;

#define PI 3.14159265358979323846
#define TAILLE 20 //détermine le nombre de points

double distance(t_point* pA, t_point* pB);
double prod_vectoriel(t_point* p0, t_point* p1, t_point* p2);
double coord_polaire(t_point* pA, t_point* pB, t_point* href);
int alea(int min, int max);
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy);
int occurence(t_point tab[], int taille, int celuila);
int trouver_pt_minimal(const t_point tab_pts[], int taille);
t_point placer_pt_reference(t_point tab_pts[], int pos_min);
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref);
void trier_pts(t_point tab_pts[], int taille);