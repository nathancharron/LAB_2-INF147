#include "interactions.h"

int demander_mode(void) {

	int valide;

	printf("Choisir le mode d'excecution : \n"
		"1: Mode aleatoire (20 pts.)\n"
		"2: Mode Fichier Texte\n"
		"3: Mode Moyenne simulation\n"
		"-->");

	


	while (scanf("%d", &valide) != 1 || (valide != 1 && valide != 2)) {

		FFLUSH();

		printf("Choisir le mode d'excecution : \n"
			"1: Mode aleatoire (20 pts.)\n"
			"2: Mode Fichier Texte\n"
			"3: Mode Moyenne simulation\n"
			"--> ");	

	}

	return valide;

}

FILE* choisir_fichier(void) {

	char nom_fich[100];

	printf("Quelle est le nom du fichier? ");

	scanf("%99s", nom_fich);

	FILE* fich_txt = fopen(nom_fich, "r");
	
	while (fich_txt == NULL) {
		printf("Erreur. Veuillez entrer le nom du fichier ");

		scanf("%99s", nom_fich);

		fich_txt = fopen(nom_fich, "r");

	}

	return fich_txt;
}

t_point* lire_points(FILE* fichier, int* nb_points) {


	if (fscanf(fichier, "%d", nb_points) != 1 || *nb_points <= 0) {
		fclose(fichier);
		return NULL;
	}
	

	t_point* tab_dyn_pts = (t_point*)malloc(*nb_points * sizeof(t_point));

	if (tab_dyn_pts == NULL) {
		fclose(fichier);
		return NULL;
	}

	for (int i = 0; i < *nb_points; i++) {
		
		tab_dyn_pts[i].position = -1;
		fscanf(fichier, "%d", &tab_dyn_pts[i].posx);
		fscanf(fichier, "%d", &tab_dyn_pts[i].posy);

	}

	fclose(fichier);

	return tab_dyn_pts;

}