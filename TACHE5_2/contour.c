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
    Cellule_Liste_Point *el = L.first;

    while (el)
    {
        Cellule_Liste_Point *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
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
    printf("nombre de segments: %d\n", compteur - 1);
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

int detecter_contours(Image I, Liste_Point **contours);

// void sauvegarder_contour_eps(Image I, char *nom_fichier, int mode)
// {
//     FILE *fichier_eps;
//     Liste_Point contour = detecter_contour(I); // Obtenir la liste des points de contour

//     // Ouvrir le fichier en mode écriture
//     fichier_eps = fopen(nom_fichier, "w");

//     if (fichier_eps == NULL)
//     {
//         fprintf(stderr, "Erreur lors de l'ouverture du fichier EPS.\n");
//         exit(EXIT_FAILURE);
//     }

//     // Écriture de l'en-tête EPS
//     fprintf(fichier_eps, "%%!PS-Adobe-3.0 EPSF-3.0\n");

//     // Définir la boîte englobante (BoundingBox)
//     int largeur = largeur_image(I);
//     int hauteur = hauteur_image(I);
//     fprintf(fichier_eps, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur);

//     // Début du contenu EPS
//     fprintf(fichier_eps, "newpath\n");

//     // Boucle pour écrire les points du contour
//     Cellule_Liste_Point *current = contour.first;
//     while (current != NULL)
//     {
//         Point p = current->data; // Obtenir le point de contour actuel

//         if (current == contour.first)
//         {
//             // Déplacer le point courant au premier point du contour
//             fprintf(fichier_eps, "%.1f %.1f moveto\n", p.x, hauteur - p.y);
//         }
//         else
//         {
//             // Relier les points suivants avec des lignes
//             fprintf(fichier_eps, "%.1f %.1f lineto\n", p.x, hauteur - p.y);
//         }

//         current = current->suiv;
//     }

//     // Fermeture du chemin
//     fprintf(fichier_eps, "closepath\n");

//     // Appliquer le mode (stroke ou fill)
//     if (mode == STROKE_MODE)
//     {
//         fprintf(fichier_eps, "0 setlinewidth\n"); // Épaisseur de tracé à 0
//         fprintf(fichier_eps, "stroke\n");
//     }
//     else if (mode == FILL_MODE)
//     {
//         fprintf(fichier_eps, "fill\n");
//     }

//     // Fin du contenu EPS
//     fprintf(fichier_eps, "showpage\n");

//     // Fermer le fichier EPS
//     fclose(fichier_eps);
// }

Image creer_image_masque(Image I)
{
    Image M = creer_image(largeur_image(I), hauteur_image(I));
    int i, j;
    for (i = 1; i <= hauteur_image(I); i++)
    {
        for (j = 1; j <= largeur_image(I); j++)
        {
            if (get_pixel_image(I, j, i) == NOIR && get_pixel_image(I, j, i - 1) == BLANC)
            {
                set_pixel_image(M, j, i, NOIR);
            }
            else
            {
                set_pixel_image(M, j, i, BLANC);
            }
        }
    }
    return M;
}

// Fonction pour trouver le prochain pixel noir dans l'image masque M
int trouver_pixel_noir(Image M, int *x, int *y)
{
    int largeur = largeur_image(M);
    int hauteur = hauteur_image(M);

    for (int i = 1; i <= hauteur; i++)
    {
        for (int j = 1; j <= largeur; j++)
        {
            if (get_pixel_image(M, j, i) == NOIR)
            {
                *x = j;
                *y = i;
                return 1; // Pixel noir trouvé
            }
        }
    }

    return 0; // Aucun pixel noir trouvé
}

int detecter_contours(Image I, Liste_Point **contours)
{
    // Etape 1 : Créer l'image masque M
    Image M = creer_image_masque(I);

    // Variables pour la détection des contours
    int x, y;
    int compteur_total_contours = 0; // Compteur total de contours
    int compteur_total_segments = 0; // Compteur total de segments

    // Tableau pour stocker les contours détectés
    Liste_Point *tableau_contours = NULL;
    int nombre_contours = 0;

    // Etape 2 : Boucle pour détecter les contours
    while (trouver_pixel_noir(M, &x, &y))
    {
        // Initialiser une nouvelle liste de points pour le contour
        Liste_Point contour = creer_liste_Point_vide();
        int compteur_segments = 0; // Compteur de segments dans le contour

        // Point de départ pour le contour
        int position_x = x - 1;
        int position_y = y - 1;
        Orientation orientation = Est; // Commencer à se déplacer vers l'Est

        // Boucle pour suivre le contour
        do
        {
            // Ajouter le point actuel au contour
            Point position = {position_x, position_y};
            contour = ajouter_element_liste_Point(contour, position);

            compteur_segments++;

            // Mettre à jour M en marquant le pixel SE comme blanc
            if (orientation == Est)
            {
                set_pixel_image(M, position_x + 1, position_y + 1, BLANC);
            }

            // Avancer dans la direction actuelle
            avancer(&position_x, &position_y, orientation);

            // Mettre à jour l'orientation
            nouvelle_orientation(&orientation, I, position_x, position_y);

        } while (!(position_x == x - 1 && position_y == y - 1 && orientation == Est));

        // Ajouter le dernier point pour fermer le contour
        Point dernier_point = {position_x, position_y};
        contour = ajouter_element_liste_Point(contour, dernier_point);
        compteur_segments++; // Incrémenter le compteur pour le dernier segment

        // Ajouter les compteurs du contour au total
        compteur_total_contours++;
        compteur_total_segments += compteur_segments;

        // Ajouter le contour détecté au tableau de contours
        tableau_contours = realloc(tableau_contours, (nombre_contours + 1) * sizeof(Liste_Point));
        tableau_contours[nombre_contours++] = contour;
    }

    // Assigner le tableau de contours au pointeur passé en argument
    *contours = tableau_contours;

    // Afficher le nombre total de contours et de segments
    printf("Nombre total de contours : %d\n", compteur_total_contours);
    printf("Nombre total de segments : %d\n", compteur_total_segments - compteur_total_contours);

    // Retourner le nombre total de contours détectés
    return compteur_total_contours;
}

void ecrire_contours_fichier(const char *nom_fichier, Liste_Point *contours, int nombre_contours)
{
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de contours\n");
        exit(EXIT_FAILURE);
    }

    // Écrire le nombre de contours dans le fichier
    fprintf(fichier, "%d\n", nombre_contours);

    // Parcourir tous les contours et écrire chaque contour dans le fichier
    for (int i = 0; i < nombre_contours; i++)
    {
        Liste_Point contour = contours[i];
        Cellule_Liste_Point *current = contour.first;

        // Écrire le nombre de points dans le contour
        int nombre_points = 0;
        while (current != NULL)
        {
            nombre_points++;
            current = current->suiv;
        }
        fprintf(fichier, "%d\n", nombre_points);

        // Écrire les coordonnées de chaque point du contour
        current = contour.first;
        while (current != NULL)
        {
            fprintf(fichier, "%.1f %.1f\n", current->data.x, current->data.y);
            current = current->suiv;
        }
    }

    fclose(fichier);
}

void sauvegarder_contour_eps(Image I, char *nom_fichier, int mode)
{
    FILE *fichier_eps;
    Liste_Point *contours;
    int nombre_contours = detecter_contours(I, &contours);

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
    for (int i = 0; i < nombre_contours; i++)
    {
        Liste_Point contour = contours[i];
        Cellule_Liste_Point *current = contour.first;

        while (current != NULL)
        {
            Point p = current->data; // Obtenir le point de contour actuel

            if (current == contour.first)
            {
                // Déplacer le point courant au premier point du contour
                fprintf(fichier_eps, "%.1f %.1f moveto\n", p.x, hauteur - p.y);
            }
            else
            {
                // Relier les points suivants avec des lignes
                fprintf(fichier_eps, "%.1f %.1f lineto\n", p.x, hauteur - p.y);
            }

            current = current->suiv;
        }

        // Fermeture du chemin
        fprintf(fichier_eps, "closepath\n");
    }

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

    // Libérer la mémoire utilisée par les contours
    for (int i = 0; i < nombre_contours; i++)
    {
        supprimer_liste_Point(contours[i]);
    }

    free(contours);
}
