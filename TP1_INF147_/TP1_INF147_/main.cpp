#include "tab_points.h"
#include "affichage.h"
#include "winbgim.h"
#include "pileslib.h"
#include "interactions.h"
#include <windows.h>

void afficher_pts_en_ordre(t_point tab_pts[], int taille, int mode);
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile* pile_Graham);
void affi_resultat_graham(t_pile* pile_Graham);

int main(void)
{

	t_point *tab_pts = NULL;
	t_point h_ref;
	int pos_pt_min; //position du point minimal dans le tableau
	int mode;
	int nb_pts;

	srand(time(NULL)); //initialise le générateur “rand()” 

	

	mode = demander_mode();

	if (mode == MODE_ALEA) {
		nb_pts = TAILLE;

		tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
		assert(tab_pts);

		init_tab_alea(tab_pts, nb_pts, 1400, 800);
	}
	else if (mode == MODE_FICHIER) {

		FILE*fichier = choisir_fichier();

		tab_pts = lire_points(fichier, &nb_pts);

	}

	

	pos_pt_min = trouver_pt_minimal(tab_pts, nb_pts);

	h_ref = placer_pt_reference(tab_pts, pos_pt_min);
	
	calcul_coord_polaires(tab_pts, nb_pts, &h_ref);

	trier_pts(tab_pts, nb_pts);

	mode_graphique();
	afficher_pts_en_ordre(tab_pts, nb_pts,0);
	pause_ecran();

	nettoyer_ecran();

	afficher_pts_en_ordre(tab_pts, nb_pts, 1);

	t_pile pile_Graham;

	pile_Graham = initpile(nb_pts);

	algo_Graham_scan(tab_pts, nb_pts, &pile_Graham);
	
	affi_resultat_graham(&pile_Graham);

	pause_ecran();

	free(tab_pts);

	system("pause");
	return EXIT_SUCCESS;
}

void afficher_pts_en_ordre(t_point tab_pts[], int taille, int mode)
{
	if (mode == 0)
	{
	for (int i = 0; i < taille; i++)
	{
		tab_pts[i].position = i;
		dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);
		dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[i].posx, tab_pts[i].posy);
	}
	}
	if (mode == 1)
	{
		for (int i = 0; i < taille; i++)
		{
			tab_pts[i].position = i;
			dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);
		}
	}
}

int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile* pile_Graham) {

	//Empiler le point - minimal p0 dans la pile_Graham.
	push(pile_Graham, tab_pts[0]);
	// Empiler le point p1 dans la pile_Graham.
	push(pile_Graham, tab_pts[1]);
	//Empiler le point p2 dans la pile_Graham(ces 3 points forment le premier segment).
	push(pile_Graham, tab_pts[2]);

	//Affichage : dessiner une ligne de p0 à p1 et de p1 à p2, suivi d’un délai - écran(eg. 300 msec.).
	dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[1].posx, tab_pts[1].posy);
	dessiner_lig(tab_pts[1].posx, tab_pts[1].posy, tab_pts[2].posx, tab_pts[2].posy);
	Sleep(300);

	t_point pB;
	t_point pA;
	// Pour i = tous les points de p3 à pNB - 1 :
	for (int i = 3; i < nb_pts; i++)
	{
		t_point pi;
		pi = tab_pts[i];
		//-Répéter :
		while (get_nb_element(pile_Graham) >= 2) {

		//-Récupérer une copie du point - sommet de la pile  pB
		get_sommet(pile_Graham, &pB);
		//- Récupérer une copie du point suivant du sommet de la pile  pA
		get_suiv_sommet(pile_Graham, &pA);
		//- Si(le segment pA – pB – pi est un virage vers la droite) :
		if (prod_vectoriel(&pA, &pB, &pi) > 0)
		{
			//-Dépiler le point sommet(pB) de la pile_Graham(ce point n’est pas dans l’enveloppe).
			pop(pile_Graham, &pB);
			//- Affichage : effacer la ligne qui relie les points pA – pB, suivi d’un petit délai - écran.
			effacer_lig(pA.posx, pA.posy, pB.posx, pB.posy);
			Sleep(100);
			//- Fin Si
		}
		
		
		else 
		{ 
			break; 
		}
		

		//- Tant Que : le segment pA – pB – pi  est un virage vers la droite.
	}
			//- Empiler le point suivant pi dans la pile_Graham.
			push(pile_Graham, pi);
			//- Affichage : dessiner une ligne de pB à pi, suivi d’un délai - écran
			dessiner_lig(pB.posx, pB.posy, pi.posx, pi.posy);
	
		//- Fin Pour
	}
		//- Retourner le nombre d’éléments dans la pile_Graham.
	return get_nb_element(pile_Graham);
}

void affi_resultat_graham(t_pile* pile_Graham) {

	printf("Les %d points-contour sont:",(pile_Graham->sommet)+1);

	t_point pt_fin;
	t_point p0;
	t_point p1;

	pop(pile_Graham, &p0);

	pt_fin = p0;

	printf("\n%d", pt_fin.position);

	while (!vide(pile_Graham)) {

		pop(pile_Graham, &p1);

		printf(" -> %d",p1.position);

		dessiner_lig(
			p0.posx, p0.posy,
			p1.posx, p1.posy);

		p0 = p1;

	}
	
	dessiner_lig(
		p0.posx, p0.posy,
		pt_fin.posx, pt_fin.posy);

	printf(" -> %d\n", pt_fin.position);

}