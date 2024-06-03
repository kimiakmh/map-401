#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "simplification_contours_segments.h"
#include "bezier.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_image_pbm> <seuil>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *fichier_image_pbm = argv[1];
    double seuil = atof(argv[2]);

    // Charger l'image PBM
    Image image = lire_fichier_image(fichier_image_pbm);

    UINT largeur = largeur_image(image);
    UINT hauteur = hauteur_image(image);

    // Générer le nom du fichier EPS pour le contour simplifié

    // Convertir la valeur de la distance seuil en chaîne de caractères
    char seuil_str[20];
    sprintf(seuil_str, "d%.1f", seuil); // Utilisez "%.1f" pour formater la distance avec une décimale

    // Générer le nom du fichier EPS pour le contour simplifié
    char nom_fichier_eps[120]; // Augmentez la taille pour inclure "d" + la distance seuil + "_simplifie.eps"
    char *extension = "_bezier2.eps";

    // Ajouter "d" suivi de la distance seuil
    strcpy(nom_fichier_eps, seuil_str);

    // Ajouter le nom du fichier image PBM sans extension
    strcat(nom_fichier_eps, "_");
    strncat(nom_fichier_eps, fichier_image_pbm, strrchr(fichier_image_pbm, '.') - fichier_image_pbm);

    // Ajouter l'extension .eps à la fin
    strcat(nom_fichier_eps, extension);


    // Ouvrir le fichier EPS en mode écriture
    FILE *file = fopen(nom_fichier_eps, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", nom_fichier_eps);
        return EXIT_FAILURE;
    }

    // Écrire l'en-tête EPS
    fprintf(file, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(file, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur);
    fprintf(file, "%% Créé par simplification_contours\n");
    fprintf(file, "\n");

    // Écrire le contour simplifié
    fprintf(file, "newpath\n");

    // Calculer les contours de l'image
    Liste_Point *contours;
    int nombre_contours = detecter_contours(image, &contours);

    int total_segments_simplifies = 0; // Accumulateur pour le nombre total de segments simplifiés

    for (int i = 0; i < nombre_contours; i++) {
        // Convertir les contours en tableau de points
        Tableau_Point TP = sequence_points_liste_vers_tableau(contours[i]);

        // Simplifier les contours avec le seuil donné en utilisant des courbes de Bézier de degré 2
        Liste_Bezier2 courbes_bezier2 = simplification_douglas_peucker_bezier2(TP, 0, TP.taille - 1, seuil);

        // Déplacer le curseur vers le premier point du contour
        fprintf(file, "%f %f moveto\n", courbes_bezier2.first->data.C0.x, hauteur - courbes_bezier2.first->data.C0.y);
        
        // Boucle sur chaque courbe de Bézier simplifiée
        Cellule_Liste_Bezier2 *courbe = courbes_bezier2.first;
        while (courbe != NULL) {
            Bezier3 B3 = bezier2_to_bezier3(courbe->data);
            fprintf(file, "%f %f %f %f %f %f curveto\n", 
                B3.C1.x, hauteur - B3.C1.y, 
                B3.C2.x, hauteur - B3.C2.y, 
                B3.C3.x, hauteur - B3.C3.y);
            courbe = courbe->suiv;
            total_segments_simplifies++; // Incrémenter le nombre total de courbes de Bézier
        }
        // Libérer la mémoire allouée pour la liste des courbes de Bézier simplifiées
        detruire_liste_Bezier2(&courbes_bezier2);
        // Libérer la mémoire allouée pour le tableau de points du contour simplifié
        free(TP.tab);
    }



    // Fermer le chemin et remplir le contour
    fprintf(file, "closepath\n");
    fprintf(file, "fill\n");

    // Fermer le fichier
    fclose(file);

    // Afficher le nombre total de courbes de Bézier
    printf("Nombre total de courbes de Bézier : %d\n", total_segments_simplifies);

    // Libérer la mémoire allouée pour les contours et l'image
    for (int i = 0; i < nombre_contours; i++) {
        supprimer_liste_Point(contours[i]);
    }
    free(contours);
    supprimer_image(&image);

    return EXIT_SUCCESS;
}
