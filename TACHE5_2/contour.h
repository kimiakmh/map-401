#ifndef CONTOUR_H
#define CONTOUR_H

#include "types_macros.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>

// Définitions de types
typedef struct Point_
{
	double x, y;
} Point;

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
	Point data;
	struct Cellule_Liste_Point_ *suiv;
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;
	Cellule_Liste_Point *first;
	Cellule_Liste_Point *last;
} Liste_Point;

typedef enum
{
	Nord,
	Est,
	Sud,
	Ouest
} Orientation;


// Prototypes de fonctions
Cellule_Liste_Point *creer_element_liste_Point(Point v);
Liste_Point creer_liste_Point_vide();
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);
Liste_Point supprimer_liste_Point(Liste_Point L);

/* Fonction pour trouver le pixel de départ du contour */
void trouver_pixel_depart(Image I, int *x, int *y);
/* Fonction pour mémoriser la position du robot */
void memoriser_position(int x, int y, Orientation orientation, Liste_Point *L);
/* Fonction pour avancer d'une unité dans la direction du contour */
void avancer(int *x, int *y, Orientation orientation);
/* Fonction pour calculer la nouvelle orientation du contour en fonction des voisins G et D */
void nouvelle_orientation(Orientation *orientation, Image I, int x, int y);
/* Fonction pour ecrire le contour dans un fichier */
void ecrire_contour_fichier(char *nom_fichier, Liste_Point contour, int compteur);
/* Fonction pour calculer et afficher le contour externe correspondant */
void calculer_et_afficher_contour(Image I, const char *contourFileName);

void sauvegarder_contour_eps(Image I, char *nom_fichier, int mode);

// TACHE 5
int trouver_pixel_noir(Image I, int *x, int *y);
Liste_Point calculer_contour_a_partir_de_point(Image I, int x, int y);
void ecrire_contours_fichier(const char *nom_fichier, Liste_Point *contours, int nombre_contours);
int trouver_pixel_noir(Image I, int *x, int *y);
int detecter_contours(Image I, Liste_Point **contours) ;
#endif // CONTOUR_H