/**********************************************************************************************/
/* INF147 - TP1 : Calcul de l'enveloppe convexe                                               */
/* Auteur : Nathan Charron-Galarneau et Gregory Osorio Rivera                                 */
/* Date : Automne 2026                                                                        */
/*                                                                                            */
/* Ce programme permet de déterminer l'enveloppe convexe d'un ensemble de points à l'aide de  */
/* l'algorithme de Graham. Les points peuvent être générés aléatoirement ou lus à partir d'un */
/* fichier texte.                                                                             */
/*                                                                                            */
/* Le programme permet également d'afficher graphiquement l'enveloppe convexe et d'effectuer  */
/* des simulations pour calculer le nombre moyen de points formant celle-ci.                  */
/**********************************************************************************************/

#include "tab_points.h"
#include "affichage.h"
#include "winbgim.h"
#include "pileslib.h"
#include "interactions.h"
#include <windows.h>

/**********************************************************************************************/
/*                                 DECLARATIONS DES FONCTIONS                                 */
/**********************************************************************************************/

/*********************************** AFFICHER_PTS_EN_ORDRE ************************************/
/* Cette fonction affiche les points du tableau selon leur ordre polaire. Le mode 0 affiche   */
/* les points avec leurs lignes polaires, tandis que le mode 1 affiche uniquement les points. */
/* RETOUR: Aucun (void).                                                                      */
/**********************************************************************************************/
void afficher_pts_en_ordre(t_point tab_pts[], int taille, int mode);

/************************************** ALGO_GRAHAM_SCAN **************************************/
/* Cette fonction détermine les points formant l'enveloppe convexe à l'aide de l'algorithme   */
/* de Graham et d'une pile de points. Le paramètre mode permet d'activer ou non l'affichage   */
/* graphique.                                                                                 */
/* RETOUR: Le nombre de points formant l'enveloppe convexe.                                   */
/**********************************************************************************************/
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile* pile_Graham, int mode);

/************************************ AFFI_RESULTAT_GRAHAM ************************************/
/* Cette fonction affiche les numéros des points de l'enveloppe convexe dans la console et    */
/* dessine les segments reliant ces points. La pile est vidée au fur et à mesure de           */
/* l'affichage.                                                                               */
/* RETOUR: Aucun (void).                                                                      */
/**********************************************************************************************/
void affi_resultat_graham(t_pile* pile_Graham);

/************************************* SIMULATION_MOYENNE *************************************/
/* Cette fonction effectue un nombre donné de simulations du parcours de Graham avec des      */
/* points générés aléatoirement. Elle calcule ensuite la moyenne du nombre de points formant  */
/* l'enveloppe convexe.                                                                       */
/* RETOUR: Le nombre moyen de points de l'enveloppe convexe (double).                         */
/**********************************************************************************************/
double simulation_moyenne(int nb_pts, int nb_tests);


/**********************************************************************************************/
/*                                 DEFINITIONS DES FONCTIONS                                  */
/**********************************************************************************************/

int main(void)
{

	t_point* tab_pts = NULL; // Tableau dynamique contenant les points
	t_point h_ref;           // Point de référence pour le calcul des angles polaires
	int pos_pt_min; //position du point minimal dans le tableau
	int mode; //Mode choisi par l'utilisateur
	int nb_pts; // Nombre de points à traiter

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
		FILE* fichier = choisir_fichier();
		//On lit le fichier
		tab_pts = lire_points(fichier, &nb_pts);

	}

	// Si on choisi simulation on a va écrire les moyennes dans un fichier
	else if (mode == MODE_SIMULATION) {
		// Ouvrir le fichier en mode W
		FILE* f_log = fopen("excel", "w"); // Fichier contenant les moyennes des simulations
		assert(f_log);

		// Faire une simualtion de 5 à 200 points avec des pas de 5
		for (int i = 5; i <= 200; i += 5)
		{
			double moyenne = simulation_moyenne(i, 10000); // Moyenne des points de l'enveloppe

			printf("%d %.2f\n", i, moyenne);
			fprintf(f_log, "%d %lf\n", i, moyenne);
		}
		// Fermer le fichier
		fclose(f_log);

		return EXIT_SUCCESS;
	}


	//Trouver le point ayant la position minimale
	pos_pt_min = trouver_pt_minimal(tab_pts, nb_pts);

	//Placer le point de reference a partir du pt minimal
	h_ref = placer_pt_reference(tab_pts, pos_pt_min);

	// Calculer les coordonnées polaires des points
	calcul_coord_polaires(tab_pts, nb_pts, &h_ref);

	//Trier les points selon leurs angles polaires
	trier_pts(tab_pts, nb_pts);

	/*Initialiser le mode graphique et afficher les points avec
	leurs lignes et numeros*/
	mode_graphique();
	afficher_pts_en_ordre(tab_pts, nb_pts, 0);
	pause_ecran();

	//Nettoyer l'écran des affichages graphiques
	nettoyer_ecran();

	//Affiche les points en tri sans les lignes
	afficher_pts_en_ordre(tab_pts, nb_pts, 1);

	//Initialise la pile pour l'algorithme de Graham
	t_pile pile_Graham; // Pile contenant les points de l'enveloppe convexe
	pile_Graham = initpile(nb_pts);

	//lancer l'algorithme de Graham avec l'affichage
	algo_Graham_scan(tab_pts, nb_pts, &pile_Graham, 1);

	//On affiche les resultat de l'algorithme de Graham
	affi_resultat_graham(&pile_Graham);

	//Mettre programme en pause pour visualiser le resultat
	pause_ecran();

	//Libérer la mémoire
	free(tab_pts);

	system("pause");

	return EXIT_SUCCESS;
}


/***********************************************************************************************/
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


/**********************************************************************************************/
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile* pile_Graham, int mode_aff)
{
	// Empiler les trois premiers points pour former le premier segment
	push(pile_Graham, tab_pts[0]);
	push(pile_Graham, tab_pts[1]);
	push(pile_Graham, tab_pts[2]);

	// Afficher les deux premiers segments si le mode graphique est activé
	if (mode_aff == 1)
	{
		dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[1].posx, tab_pts[1].posy);
		dessiner_lig(tab_pts[1].posx, tab_pts[1].posy, tab_pts[2].posx, tab_pts[2].posy);
		Sleep(300);
	}

	t_point pB; // Point au sommet de la pile
	t_point pA; // Point situé sous le sommet de la pile

	// Parcourir les points restants pour construire l'enveloppe
	for (int i = 3; i < nb_pts; i++)
	{
		t_point pi; // Nouveau point à analyser
		pi = tab_pts[i];

		// Retirer les points formant un virage vers la droite
		// jusqu'à obtenir un virage valide ou avoir moins de 2 points
		while (get_nb_element(pile_Graham) >= 2)
		{
			// Récupérer les deux points au sommet de la pile
			get_sommet(pile_Graham, &pB);
			get_suiv_sommet(pile_Graham, &pA);

			// Vérifier si le segment pA - pB - pi forme un virage vers la droite
			if (prod_vectoriel(&pA, &pB, &pi) > 0)
			{
				// Retirer le point qui ne fait pas partie de l'enveloppe
				pop(pile_Graham, &pB);

				if (mode_aff == 1)
				{
					// Effacer le segment entre pA et pB
					effacer_lig(pA.posx, pA.posy, pB.posx, pB.posy);
					delai_ecran(100);
				}
			}
			else
			{
				// Arrêter de retirer des points lorsque le virage est valide
				break;
			}
		}

		// Récupérer le dernier point conservé dans l'enveloppe
		get_sommet(pile_Graham, &pB);

		// Ajouter le nouveau point à l'enveloppe
		push(pile_Graham, pi);

		// Afficher le nouveau segment si le mode graphique est activé
		if (mode_aff == 1)
		{
			dessiner_lig(pB.posx, pB.posy, pi.posx, pi.posy);
			delai_ecran(100);
		}
	}

	// Retourner le nombre de points formant l'enveloppe convexe
	return get_nb_element(pile_Graham);
}



/***********************************************************************************************/
void affi_resultat_graham(t_pile* pile_Graham) {

	// Afficher le nombre de points formant l'enveloppe convexe
	printf("Les %d points-contour sont:", (pile_Graham->sommet) + 1);

	t_point pt_fin; // Dernier point de l'enveloppe, conservé pour la fin
	t_point p0;     // Point de départ du segment à dessiner
	t_point p1;     // Point suivant du segment à dessiner

	// Récupérer le point au sommet de la pile
	pop(pile_Graham, &p0);

	// Conserver une copie pour fermer l'enveloppe à la fin
	pt_fin = p0;

	printf("\n%d", pt_fin.position);

	// Parcourir la pile jusqu'à ce qu'elle soit vide
	while (!vide(pile_Graham)) {

		// Récupérer le prochain point de l'enveloppe
		pop(pile_Graham, &p1);

		// Afficher le numéro du point
		printf(" -> %d", p1.position);

		// Dessiner le segment entre les deux points
		dessiner_lig(p0.posx, p0.posy, p1.posx, p1.posy);

		// Le point suivant devient le départ du prochain segment
		p0 = p1;

	}

	// Fermer l'enveloppe en reliant le dernier point au premier
	dessiner_lig(p0.posx, p0.posy, pt_fin.posx, pt_fin.posy);

	// Afficher le numéro du point de fermeture
	printf(" -> %d\n", pt_fin.position);

}



/************************************************************************************************/
double simulation_moyenne(int nb_pts, int nb_tests)
{
	t_pile pile_Graham;       // Pile contenant les points de l'enveloppe
	t_point* tab_pts = NULL;  // Tableau dynamique des points
	t_point h_ref = { 0 };    // Point de référence pour les angles polaires
	int p_min;                // Position du point minimal
	int nb_pts_tot = 0;       // Nombre total de points des enveloppes

	// Allouer la mémoire pour le tableau dynamique de points
	tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
	assert(tab_pts);

	// Répéter l'algorithme de Graham pour le nombre d'essais demandé
	for (int i = 0; i < nb_tests; i++)
	{
		// Initialiser une nouvelle pile pour chaque simulation
		pile_Graham = initpile(nb_pts);

		// Générer aléatoirement les points
		init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);

		// Trouver le point minimal
		p_min = trouver_pt_minimal(tab_pts, nb_pts);

		// Placer le point minimal en première position et obtenir h_ref
		h_ref = placer_pt_reference(tab_pts, p_min);

		// Calculer les coordonnées polaires des points
		calcul_coord_polaires(tab_pts, nb_pts, &h_ref);

		// Trier les points selon leurs angles polaires
		trier_pts(tab_pts, nb_pts);

		// Calculer l'enveloppe et ajouter son nombre de points au total
		nb_pts_tot += algo_Graham_scan(tab_pts, nb_pts, &pile_Graham, 0);

		// Libérer la mémoire de la pile avant le prochain essai
		liberer_pile(&pile_Graham);
	}

	// Libérer la mémoire du tableau de points
	free(tab_pts);

	// Retourner la moyenne de points par enveloppe
	return (double)nb_pts_tot / nb_tests;
}