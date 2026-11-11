#include "interactions.h"

//Demandera a l'utilisateur le mode. Retourne 1 ou 2
int demander_mode(void) {

	int valide;

	printf("Choisir le mode d'excecution : \n"
		"1: Mode aleatoire (20 pts.)\n"
		"2: Mode Fichier Texte\n"
		"3: Mode Moyenne simulation\n"
		"-->");

	

	//On redemande tant qu'on n'insere pas 1,2 ou 3
	while (scanf("%d", &valide) != 1 || (valide != 1 && valide != 2 && valide!=3)) {

		FFLUSH();

		printf("Choisir le mode d'excecution : \n"
			"1: Mode aleatoire (20 pts.)\n"
			"2: Mode Fichier Texte\n"
			"3: Mode Moyenne simulation\n"
			"--> ");	

	}

	return valide;

}

//Demande a l'utilisateur le fichier voulu. Retourne le nom du fichier
FILE* choisir_fichier(void) {

	char nom_fich[100];

	printf("Quelle est le nom du fichier? ");

	scanf("%99s", nom_fich);

	FILE* fich_txt = fopen(nom_fich, "r");
	
	//On relance tant qu'on ne trouve pas un fichier valide
	while (fich_txt == NULL) {
		printf("Erreur. Veuillez entrer le nom du fichier ");

		scanf("%99s", nom_fich);

		fich_txt = fopen(nom_fich, "r");

	}

	return fich_txt;
}

/*Permet de lire les points dans un fichier donnee et retourner un tableau
dynamique avec ces points*/
t_point* lire_points(FILE* fichier, int* nb_points) {

	/*Doit seulement lire un seul nombre pour le nombre de point
	et il doit etre au dessus de 0*/
	if (fscanf(fichier, "%d", nb_points) != 1 || *nb_points <= 0) {
		fclose(fichier);
		return NULL;
	}
	

	t_point* tab_dyn_pts = (t_point*)malloc(*nb_points * sizeof(t_point));

	//On quitte si l'allocation ne marche pas
	if (tab_dyn_pts == NULL) {
		fclose(fichier);
		return NULL;
	}

	for (int i = 0; i < *nb_points; i++) {
		
		tab_dyn_pts[i].position = -1; //On met leur position a -1

		/*On lit la position x et y de chaque points*/
		fscanf(fichier, "%d", &tab_dyn_pts[i].posx);
		fscanf(fichier, "%d", &tab_dyn_pts[i].posy);

	}

	fclose(fichier);

	return tab_dyn_pts;

}