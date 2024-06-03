#ifndef CONTOUR_H
#define CONTOUR_H

#include "types_macros.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>

// Définitions de types
typedef struct Point_ { double x, y; } Point;

typedef struct Cellule_Liste_Point_
{
  Point data;
  struct Cellule_Liste_Point_* suiv;
} Cellule_Liste_Point;

typedef struct Liste_Point_
{
  unsigned int taille;
  Cellule_Liste_Point* first;
  Cellule_Liste_Point* last;
} Liste_Point;

typedef enum { Nord, Est, Sud, Ouest } Orientation;

// Prototypes de fonctions
Cellule_Liste_Point *creer_element_liste_Point(Point v);
Liste_Point creer_liste_Point_vide();
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);
Liste_Point supprimer_liste_Point(Liste_Point L);

void trouver_pixel_depart(Image I, int* x, int* y);
void memoriser_position(int x, int y, Orientation orientation, Liste_Point *L);
void avancer(int *x, int *y, Orientation orientation);
void nouvelle_orientation(Orientation* orientation, Image I, int x, int y);
void ecrire_contours_fichier(const char *nom_fichier, Liste_Point *contours, int nombre_contours);
void calculer_et_afficher_contour(Image I, const char *contourFileName);
Liste_Point calculer_contour(Image I);
void sauvegarder_contour_eps(Image I, char *nom_fichier, int mode);
Image creer_image_masque(Image I);
// Fonction pour trouver le prochain pixel noir dans l'image masque M
int trouver_pixel_noir(Image M, int *x, int *y);
int detecter_contours(Image I, Liste_Point **contours);
#endif // CONTOUR_H
