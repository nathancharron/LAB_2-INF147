#include "tab_points.h"
#include "affichage.h"
#include "winbgim.h"

void afficher_pts_en_ordre(t_point tab_pts[], int taille);


int main(void)
{

	t_point *tab_pts = NULL;
	t_point h_ref;
	int pos_pt_min; //position du point minimal dans le tableau

	srand(time(NULL)); //initialise le générateur “rand()” 

	tab_pts = (t_point*)malloc(TAILLE * sizeof(t_point));
	assert(tab_pts);

	init_tab_alea(tab_pts,TAILLE ,1400, 800);

	pos_pt_min = trouver_pt_minimal(tab_pts, TAILLE);

	h_ref = placer_pt_reference(tab_pts, pos_pt_min);

	calcul_coord_polaires(tab_pts, TAILLE, &h_ref);

	trier_pts(tab_pts, TAILLE);

	mode_graphique();
	afficher_pts_en_ordre(tab_pts, TAILLE);
	pause_ecran();

	free(tab_pts);

	system("pause");
	return EXIT_SUCCESS;
}

void afficher_pts_en_ordre(t_point tab_pts[], int taille)
{
	for (int i = 0; i < taille; i++)
	{
		tab_pts[i].position = i;
		dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);
		dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[i].posx, tab_pts[i].posy);
	}
}

