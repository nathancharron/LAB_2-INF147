#include "tab_points.h"
#include "affichage.h"
#include "winbgim.h"
#include "pileslib.h"
#include "interactions.h"
#include <windows.h>

void afficher_pts_en_ordre(t_point tab_pts[], int taille, int mode);
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile* pile_Graham, int mode);
void affi_resultat_graham(t_pile* pile_Graham);
double simulation_moyenne(int nb_pts, int nb_tests);

int main(void)
{

	t_point *tab_pts = NULL;
	t_point h_ref;
	int pos_pt_min; //position du point minimal dans le tableau
	int mode; //Mode choisi par l'utilisateur
	int nb_pts;

	FILE* f_log;

	srand(time(NULL)); //initialise le générateur “rand()” 

	mode = demander_mode();

	//Si on choisi ce mode (1), on a 20 pts
	if (mode == MODE_ALEA) {
		nb_pts = TAILLE;

		//On defini tab_pts comme tableau dynamique
		tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
		assert(tab_pts);

		init_tab_alea(tab_pts, nb_pts, 1400, 800);
	}
	//Sinon le nb_pts depend de celui du fichier
	else if (mode == MODE_FICHIER) {

		//On choisi le fichier
		FILE*fichier = choisir_fichier();
		//On lit le fichier
		tab_pts = lire_points(fichier, &nb_pts);

	}
	else if(mode == MODE_SIMULATION){

		f_log = fopen("excel", "w");
		assert(f_log);

		for (int i = 5; i <= 200; i += 5)
		{
			double moyenne = simulation_moyenne(i, 10000);

			printf("%d %.2f\n", i, moyenne);
			fprintf(f_log, "%d %lf\n", i, moyenne);
		}

		fclose(f_log);

		return EXIT_SUCCESS;
	}

	
	//Trouver le point ayant la position minimale
	pos_pt_min = trouver_pt_minimal(tab_pts, nb_pts);

	//Placer le point de reference a partir du pt minimal
	h_ref = placer_pt_reference(tab_pts, pos_pt_min);
	
	calcul_coord_polaires(tab_pts, nb_pts, &h_ref);

	//Trier les points selon leurs angles polaires
	trier_pts(tab_pts, nb_pts);

	/*Initialiser le mode graphique et afficher les points avec
	leurs lignes et numeros*/
	mode_graphique();
	afficher_pts_en_ordre(tab_pts, nb_pts,0);
	pause_ecran();


	nettoyer_ecran();

	//Affiche les points en tri sans les lignes
	afficher_pts_en_ordre(tab_pts, nb_pts, 1);

	//Initialise la pile pour l'algorithme de Graham
	t_pile pile_Graham;
	pile_Graham = initpile(nb_pts);

	algo_Graham_scan(tab_pts, nb_pts, &pile_Graham, 1);
	
	//On affiche les resultat de l'algorithme de Graham
	affi_resultat_graham(&pile_Graham);

	//Mettre programme en pause pour visualiser le resultat
	pause_ecran();

	free(tab_pts);

	system("pause");
	return EXIT_SUCCESS;
}

void afficher_pts_en_ordre(t_point tab_pts[], int taille, int mode)
{
	// Mode 0 : afficher les points et tracer les lignes entre le premier point et les autres
	if (mode == 0)
	{
	for (int i = 0; i < taille; i++)
	{
		tab_pts[i].position = i;
		// Dessiner le point avec son numéro correspondant
		dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);
		// Tracer une ligne entre le premier point et le point courant
		dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[i].posx, tab_pts[i].posy);
	}
	}
	// Mode 1 : afficher uniquement les points, sans tracer de lignes
	if (mode == 1)
	{
		for (int i = 0; i < taille; i++)
		{
			tab_pts[i].position = i;
			// Dessiner le point avec son numéro correspondant
			dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);
		}
	}
}

int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile* pile_Graham, int mode_aff) {

	//Empiler le point - minimal p0 dans la pile_Graham.
	push(pile_Graham, tab_pts[0]);
	// Empiler le point p1 dans la pile_Graham.
	push(pile_Graham, tab_pts[1]);
	//Empiler le point p2 dans la pile_Graham(ces 3 points forment le premier segment).
	push(pile_Graham, tab_pts[2]);

	if (mode_aff == 1) 
	{
	//Affichage : dessiner une ligne de p0 à p1 et de p1 à p2, suivi d’un délai - écran(eg. 300 msec.).
	dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[1].posx, tab_pts[1].posy);
	dessiner_lig(tab_pts[1].posx, tab_pts[1].posy, tab_pts[2].posx, tab_pts[2].posy);
	Sleep(300);
	}

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
			if (mode_aff == 1)
			{
				//- Affichage : effacer la ligne qui relie les points pA – pB, suivi d’un petit délai - écran.
				effacer_lig(pA.posx, pA.posy, pB.posx, pB.posy);
				Sleep(100);
				//- Fin Si
			}
		}
		
		
		else 
		{ 
			break; 
		}
		

		//- Tant Que : le segment pA – pB – pi  est un virage vers la droite.
	}
			//- Empiler le point suivant pi dans la pile_Graham.
			push(pile_Graham, pi);
			if (mode_aff == 1)
			{
				//- Affichage : dessiner une ligne de pB à pi, suivi d’un délai - écran
				dessiner_lig(pB.posx, pB.posy, pi.posx, pi.posy);
			}
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

double simulation_moyenne(int nb_pts, int nb_tests) 
{
	t_pile pile_Graham;       //la pile-solution de l’enveloppe
	t_point* tab_pts = NULL;  //le tableau dynamique des points
	t_point h_ref = { 0 };    //le point de référence horizontal
	int p_min;                //la position du point-minimal p0
	int nb_pts_tot = 0;       //le nb. total de points-enveloppe


	tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
	assert(tab_pts);

	for(int i = 0; i<nb_tests; i++)
	{
		pile_Graham = initpile(nb_pts);

		init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);

		p_min = trouver_pt_minimal(tab_pts, nb_pts);

		h_ref = placer_pt_reference(tab_pts, p_min);

		calcul_coord_polaires(tab_pts, nb_pts, &h_ref);

		trier_pts(tab_pts, nb_pts);

		nb_pts_tot += algo_Graham_scan(tab_pts, nb_pts, &pile_Graham, 0);

		liberer_pile(&pile_Graham);
	}

	free(tab_pts);

	return (double)nb_pts_tot / nb_tests;
}

