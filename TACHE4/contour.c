#include <stdio.h>
#include <stdlib.h>
#include "types_macros.h"
#include "image.h"
#include "contour.h"

#define STROKE_MODE 1
#define FILL_MODE 2

Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
    Cellule_Liste_Point *el;
    el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
    if (el == NULL)
    {
        fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}
/* creer une liste vide */
Liste_Point creer_liste_Point_vide()
{
    Liste_Point L = {0, NULL, NULL};
    return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
    Cellule_Liste_Point *el;

    el = creer_element_liste_Point(e);
    if (L.taille == 0)
    {
        /* premier element de la liste */
        L.first = L.last = el;
    }
    else
    {
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* Fonction pour trouver le pixel de départ du contour */
void trouver_pixel_depart(Image I, int *x, int *y)
{
    int i, j;
    *x = 0;
    *y = 0;

    for (i = 1; i <= hauteur_image(I); i++)
    {
        for (j = 1; j <= largeur_image(I); j++)
        {
            if (get_pixel_image(I, j, i) == NOIR && get_pixel_image(I, j, i - 1) == BLANC)
            {
                *x = j;
                *y = i;
                return;
            }
        }
    }
}

void print_list(Liste_Point L)
{
    Cellule_Liste_Point *current = L.first;

    printf("List content: [");
    while (current != NULL)
    {
        printf(" (%.1f, %.1f)", current->data.x, current->data.y);
        current = current->suiv;
    }
    printf(" ]\n");
}

/* Fonction pour mémoriser la position du robot */
void memoriser_position(int x, int y, Orientation orientation, Liste_Point *L)
{
    if (L == NULL)
    {
        L = (Liste_Point *)malloc(sizeof(Liste_Point)); // Allouer la mémoire la première fois
        if (L == NULL)
        {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
        *L = creer_liste_Point_vide();
    }

    // printf("Position mémorisée : (%d, %d), Orientation : ", x, y);
    Point position = {x, y};
    *L = ajouter_element_liste_Point(*L, position);

    switch (orientation)
    {
    case Nord:
        // printf("Nord\n");
        break;
    case Est:
        // printf("Est\n");
        break;
    case Sud:
        // printf("Sud\n");
        break;
    case Ouest:
        // printf("Ouest\n");
        break;
    }
    // print_list(*L);
}

/* Fonction pour avancer d'une unité dans la direction du contour */
void avancer(int *x, int *y, Orientation orientation)
{
    switch (orientation)
    {
    case Nord:
        (*y)--;
        break;
    case Est:
        (*x)++;
        break;
    case Sud:
        (*y)++;
        break;
    case Ouest:
        (*x)--;
        break;
    }
}

/* Fonction pour calculer la nouvelle orientation du contour en fonction des voisins G et D */
void nouvelle_orientation(Orientation *orientation, Image I, int x, int y)
{
    int xG, yG, xD, yD;
    Pixel pG, pD;

    switch (*orientation)
    {
    case Nord:
        xG = x;
        yG = y;
        xD = x + 1;
        yD = y;

        pG = get_pixel_image(I, xG, yG);
        pD = get_pixel_image(I, xD, yD);

        if (pG == NOIR)
        {
            /* Tourner de 90° dans le sens des aiguilles d'une montre */
            *orientation = (*orientation + 3) % 4;
        }
        else if (pD == BLANC)
        {
            /* Tourner de 270° dans le sens des aiguilles d'une montre */
            *orientation = (*orientation + 1) % 4;
        }
        break;
    case Est:
        xG = x + 1;
        yG = y;
        xD = x + 1;
        yD = y + 1;

        pG = get_pixel_image(I, xG, yG);
        pD = get_pixel_image(I, xD, yD);

        if (pG == NOIR)
        {
            /* Tourner de 90° dans le sens des aiguilles d'une montre */
            *orientation = (*orientation + 3) % 4;
        }
        else if (pD == BLANC)
        {
            /* Tourner de 270° dans le sens des aiguilles d'une montre */
            *orientation = (*orientation + 1) % 4;
        }
        break;
    case Sud:
        xG = x + 1;
        yG = y + 1;
        xD = x;
        yD = y + 1;

        pG = get_pixel_image(I, xG, yG);
        pD = get_pixel_image(I, xD, yD);

        if (pG == NOIR)
        {
            /* Tourner de 90° dans le sens des aiguilles d'une montre */
            *orientation = (*orientation + 3) % 4;
        }
        else if (pD == BLANC)
        {
            /* Tourner de 270° dans le sens des aiguilles d'une montre */
            *orientation = (*orientation + 1) % 4;
        }
        break;
    case Ouest:
        xG = x;
        yG = y + 1;
        xD = x;
        yD = y;

        pG = get_pixel_image(I, xG, yG);
        pD = get_pixel_image(I, xD, yD);

        if (pG == NOIR)
        {
            /* Tourner de 90° dans le sens des aiguilles d'une montre */
            *orientation = (*orientation + 3) % 4;
        }
        else if (pD == BLANC)
        {
            /* Tourner de 270° dans le sens des aiguilles d'une montre */
            *orientation = (*orientation + 1) % 4;
        }
        break;
    }
}

/* Fonction pour écrire le contour dans un fichier texte */
void ecrire_contour_fichier(char *nom_fichier, Liste_Point contour, int compteur)
{
    FILE *fichier = fopen(nom_fichier, "w");

    if (fichier == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    // Écrire le nombre de contours (pour l'instant 1)
    fprintf(fichier, "1\n");

    // Écrire le compteur sur la deuxième ligne
    fprintf(fichier, "%d\n", compteur);

    // Écrire les différents points au format réel
    Cellule_Liste_Point *current = contour.first;

    while (current != NULL)
    {
        fprintf(fichier, "%.1f %.1f\n", current->data.x, current->data.y);
        current = current->suiv;
    }

    fclose(fichier);
}




/* Fonction pour calculer et afficher le contour externe correspondant */
void calculer_et_afficher_contour(Image I, const char *contourFileName)
{
    int x, y;
    int x0, y0;
    int position_x, position_y;
    Orientation orientation;
    int boucle = 1;

    /* Trouver le pixel de départ pour le contour */
    trouver_pixel_depart(I, &x, &y);

    x0 = x - 1;
    y0 = y - 1;
    position_x = x0;
    position_y = y0;
    orientation = Est;

    int compteur = 0;
    Liste_Point L = creer_liste_Point_vide(); // Declarer une list

    while (boucle)
    {
        /* Mémoriser la position */
        memoriser_position(position_x, position_y, orientation, &L);
        compteur++;

        /* Avancer d'une unité dans la direction actuelle */
        avancer(&position_x, &position_y, orientation);

        /* Calculer la nouvelle orientation */
        nouvelle_orientation(&orientation, I, position_x, position_y);

        /* Vérifier si la boucle doit se terminer */
        if (position_x == x0 && position_y == y0 && orientation == Est)
            boucle = 0;
    }

    /* Mémoriser la position finale */
    memoriser_position(position_x, position_y, orientation, &L);
    compteur++; // Increment the counter for the final position

    // Ouverture du fichier de contour pour l'écriture
    FILE *contourFile = fopen(contourFileName, "w");
    if (contourFile == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de contour\n");
        exit(EXIT_FAILURE);
    }

    // Ecrit le nombre de contours dans le fichier (dans ce cas, toujours 1)
    fprintf(contourFile, "1\n");

    // Écrit le nombre de points et les points eux-mêmes dans le fichier
    fprintf(contourFile, "%d\n", compteur);

    Cellule_Liste_Point *current = L.first;
    while (current != NULL)
    {
        fprintf(contourFile, " %.1f %.1f \n", current->data.x, current->data.y);
        current = current->suiv;
    }

    fclose(contourFile);
    printf("nombre de segments: %d\n", compteur-1);
}


Liste_Point calculer_contour(Image I)
{
    Liste_Point contour = creer_liste_Point_vide();
    int x, y;
    int x0, y0;
    int position_x, position_y;
    Orientation orientation;
    int boucle = 1;

    /* Trouver le pixel de départ pour le contour */
    trouver_pixel_depart(I, &x, &y);

    x0 = x - 1;
    y0 = y - 1;
    position_x = x0;
    position_y = y0;
    orientation = Est;

    while (boucle)
    {
        Point position = {position_x, position_y};
        contour = ajouter_element_liste_Point(contour, position);

        /* Avancer d'une unité dans la direction actuelle */
        avancer(&position_x, &position_y, orientation);

        /* Calculer la nouvelle orientation */
        nouvelle_orientation(&orientation, I, position_x, position_y);

        /* Vérifier si la boucle doit se terminer */
        if (position_x == x0 && position_y == y0 && orientation == Est)
            boucle = 0;
    }

    /* Ajouter le dernier point pour fermer le contour */
    Point dernier_point = {position_x, position_y};
    contour = ajouter_element_liste_Point(contour, dernier_point);

    return contour;
}

void sauvegarder_contour_eps(Image I, char *nom_fichier, int mode)
{
    FILE *fichier_eps;
    Liste_Point contour = calculer_contour(I); // Obtenir la liste des points de contour

    // Ouvrir le fichier en mode écriture
    fichier_eps = fopen(nom_fichier, "w");

    if (fichier_eps == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier EPS.\n");
        exit(EXIT_FAILURE);
    }

    // Écriture de l'en-tête EPS
    fprintf(fichier_eps, "%%!PS-Adobe-3.0 EPSF-3.0\n");

    // Définir la boîte englobante (BoundingBox)
    int largeur = largeur_image(I);
    int hauteur = hauteur_image(I);
    fprintf(fichier_eps, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur);

    // Début du contenu EPS
    fprintf(fichier_eps, "newpath\n");

    // Boucle pour écrire les points du contour
    Cellule_Liste_Point *current = contour.first;
    while (current != NULL)
    {
        Point p = current->data; // Obtenir le point de contour actuel

        if (current == contour.first)
        {
            // Déplacer le point courant au premier point du contour
            fprintf(fichier_eps, "%.1f %.1f moveto\n", p.x, hauteur-p.y);
        }
        else
        {
            // Relier les points suivants avec des lignes
            fprintf(fichier_eps, "%.1f %.1f lineto\n", p.x, hauteur-p.y);
        }

        current = current->suiv;
    }

    // Fermeture du chemin
    fprintf(fichier_eps, "closepath\n");

    // Appliquer le mode (stroke ou fill)
    if (mode == STROKE_MODE)
    {
        fprintf(fichier_eps, "0 setlinewidth\n"); // Épaisseur de tracé à 0
        fprintf(fichier_eps, "stroke\n");
    }
    else if (mode == FILL_MODE)
    {
        fprintf(fichier_eps, "fill\n");
    }

    // Fin du contenu EPS
    fprintf(fichier_eps, "showpage\n");

    // Fermer le fichier EPS
    fclose(fichier_eps);
}
