#include "tab_points.h"

int main(void)
{

	t_point tab_pts[TAILLE], h_ref;
	int pos_pt_min; //position du point minimal dans le tableau

	srand(time(NULL)); //initialise le générateur “rand()” 

	init_tab_alea(tab_pts,TAILLE ,1400, 800);

	pos_pt_min = trouver_pt_minimal(tab_pts, TAILLE);

	h_ref = placer_pt_reference(tab_pts, pos_pt_min);

	calcul_coord_polaires(tab_pts, TAILLE, &h_ref);

	trier_pts(tab_pts, TAILLE);


	system("pause");
	return EXIT_SUCCESS;
}


