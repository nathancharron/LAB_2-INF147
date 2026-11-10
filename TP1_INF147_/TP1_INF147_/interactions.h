#pragma once
#include "tab_points.h"

int demander_mode(void);
FILE* choisir_fichier(void);
t_point* lire_points(FILE* fichier, int* nb_points);