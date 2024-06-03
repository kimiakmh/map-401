#ifndef _BEZIER_
#define _BEZIER_

#include "contour.h" // Inclusion du fichier d'en-tête pour les contours

// Définition de la structure pour une courbe de Bézier de degré 2
typedef struct Bezier2_ {
    Point C0; // Premier point de contrôle
    Point C1; // Deuxième point de contrôle
    Point C2; // Troisième point de contrôle
} Bezier2;

// Définition de la structure pour une cellule d'une liste de Bézier2
typedef struct Cellule_Liste_Bezier2_ {
    Bezier2 data; // Données de la courbe de Bézier
    struct Cellule_Liste_Bezier2_* suiv; // Pointeur vers la cellule suivante dans la liste
} Cellule_Liste_Bezier2;

// Définition de la structure pour une liste de Bézier2
typedef struct Liste_Bezier2_ {
	unsigned int taille; // Taille de la liste
	Cellule_Liste_Bezier2 *first; // Pointeur vers la première cellule de la liste
	Cellule_Liste_Bezier2 *last;  // Pointeur vers la dernière cellule de la liste
} Liste_Bezier2;

typedef struct Cellule_Liste_Contour_Bezier2_
{
	Liste_Bezier2 data;						   /* donnée de l'élément de liste */
	struct Cellule_Liste_Contour_Bezier2_ *suiv; /* pointeur sur l'élément suivant */
} Cellule_Liste_Contour_Bezier2;

typedef struct Liste_Contour_Bezier2_
{
	unsigned int taille;		/* nombre d'éléments dans la liste */
	Cellule_Liste_Contour_Bezier2 *first; /* pointeur sur le premier élément de la liste */
	Cellule_Liste_Contour_Bezier2 *last;	/* pointeur sur le dernier élément de la liste */
								/* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Contour_Bezier2;

// Définition de la structure pour une courbe de Bézier de degré 3
typedef struct Bezier3_ {
    Point C0; // Premier point de contrôle
    Point C1; // Deuxième point de contrôle
    Point C2; // Troisième point de contrôle
    Point C3; // Quatrième point de contrôle
} Bezier3;

// Définition de la structure pour une cellule d'une liste de Bézier3
typedef struct Cellule_Liste_Bezier3_ {
    Bezier3 data; // Données de la courbe de Bézier
    struct Cellule_Liste_Bezier3_* suiv; // Pointeur vers la cellule suivante dans la liste
} Cellule_Liste_Bezier3;

// Définition de la structure pour une liste de Bézier3
typedef struct Liste_Bezier3_ {
	unsigned int taille; // Taille de la liste
	Cellule_Liste_Bezier3 *first; // Pointeur vers la première cellule de la liste
	Cellule_Liste_Bezier3 *last;  // Pointeur vers la dernière cellule de la liste
} Liste_Bezier3;

typedef struct Cellule_Liste_Contour_Bezier3_
{
	Liste_Bezier3 data;							 /* donnée de l'élément de liste */
	struct Cellule_Liste_Contour_Bezier3_ *suiv; /* pointeur sur l'élément suivant */
} Cellule_Liste_Contour_Bezier3;

typedef struct Liste_Contour_Bezier3_
{
	unsigned int taille;				  /* nombre d'éléments dans la liste */
	Cellule_Liste_Contour_Bezier3 *first; /* pointeur sur le premier élément de la liste */
	Cellule_Liste_Contour_Bezier3 *last;  /* pointeur sur le dernier élément de la liste */
										  /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Contour_Bezier3;

// Prototypes des fonctions pour les courbes de Bézier de degré 2
Point bezier2_point(Bezier2 bezier, double t);
double distance_bezier2(Point p, Bezier2 B, double t);
Bezier3 bezier2_to_bezier3(Bezier2 bezier2);
Bezier2 approx_bezier2(Tableau_Point P, UINT j1, UINT j2);

// Prototypes des fonctions pour les courbes de Bézier de degré 3
Point bezier3_point(Bezier3 bezier, double t);
double distance_bezier3(Point p, Bezier3 B, double t);

// Prototypes des fonctions pour manipuler les listes de Bézier2
Liste_Bezier2 creer_liste_Bezier2_vide();
Cellule_Liste_Bezier2 *creer_element_liste_Bezier2(Bezier2 b);
Liste_Bezier2 ajouter_element_liste_Bezier2(Liste_Bezier2 *L, Bezier2 e);
Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 L1, Liste_Bezier2 L2);
Liste_Bezier2 *detruire_liste_Bezier2(Liste_Bezier2 *liste);

// Prototypes des fonctions pour manipuler les listes de Bézier3
Liste_Bezier3 creer_liste_Bezier3_vide();
Cellule_Liste_Bezier3 *creer_element_liste_Bezier3(Bezier3 b);
Liste_Bezier3 ajouter_element_liste_Bezier3(Liste_Bezier3 *L, Bezier3 e);
Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 L1, Liste_Bezier3 L2);

#endif // Fin de la directive de préprocesseur
