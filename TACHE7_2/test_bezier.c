#include <stdio.h>
#include <stdlib.h>
#include "bezier.h"

// int main() {
//     int nombre_points;

//     // Demande à l'utilisateur de saisir le nombre de points
//     printf("Combien de points voulez-vous entrer ? ");
//     scanf("%d", &nombre_points);

//     // Vérification du nombre de points
//     if (nombre_points < 2) { // Modification : Au moins 3 points pour une courbe de degré 3
//         fprintf(stderr, "Le nombre de points doit être au moins 3 pour une courbe de degré 3.\n");
//         return EXIT_FAILURE;
//     }

//     // Allocation dynamique du tableau de points
//     Point *points = malloc(nombre_points * sizeof(Point));

//     // Demande à l'utilisateur de saisir les coordonnées de chaque point
//     printf("Veuillez entrer les coordonnées de chaque point :\n");
//     for (int i = 0; i < nombre_points; i++) {
//         printf("Point %d (x y) : ", i + 1);
//         scanf("%lf %lf", &points[i].x, &points[i].y);
//     }

//     // Indices de début et de fin du contour
//     UINT j1 = 0;
//     UINT j2 = nombre_points - 1;

//     // Création du tableau de points
//     Tableau_Point P;
//     P.taille = nombre_points;
//     P.tab = points;

//     // Calcul de la courbe de Bézier de degré 3
//     Bezier3 bezier = approx_bezier3(P, j1, j2); // Modification : Utilisation de la fonction approx_bezier3

//     // Affichage du résultat
//     printf("Courbe de Bézier de degré 3 :\n");
//     printf("C0 = (%f, %f)\n", bezier.C0.x, bezier.C0.y);
//     printf("C1 = (%f, %f)\n", bezier.C1.x, bezier.C1.y);
//     printf("C2 = (%f, %f)\n", bezier.C2.x, bezier.C2.y);
//     printf("C3 = (%f, %f)\n", bezier.C3.x, bezier.C3.y);

//     // Libération de la mémoire
//     free(points);

//     return 0;
// }


int main() {
    // Points de contrôle pour la courbe de Bézier
    Point Q0 = {1, 2};
    Point Q1 = {3, 4};
    Point Q2 = {5, 6};
    Point Q3 = {7, 8};

    // Calcul de la courbe de Bézier de degré 2 pour les points de contrôle
    Bezier3 bezier_Q = {Q0, Q1, Q2, Q3};

    // Création du contour polygonal à partir de la courbe de Bézier
    int n = 5;
    Tableau_Point P;
    P.taille = n + 1;
    P.tab = malloc(P.taille * sizeof(Point));
    for (int i = 0; i <= n; i++) {
        double t = (double)i / (double)n;
        P.tab[i] = bezier3_point(bezier_Q, t);
    }

    // Calcul de la courbe de Bézier de degré 2 pour le contour polygonal
    Bezier3 bezier_P = approx_bezier3(P, 0, n);

    // Vérification du résultat
    printf("Cas n >= 3 :\n");
    printf("C0 = (%f, %f)\n", bezier_P.C0.x, bezier_P.C0.y);
    printf("C1 = (%f, %f)\n", bezier_P.C1.x, bezier_P.C1.y);
    printf("C2 = (%f, %f)\n", bezier_P.C2.x, bezier_P.C2.y);
    printf("C3 = (%f, %f)\n", bezier_P.C3.x, bezier_P.C3.y);

    // Libération de la mémoire
    free(P.tab);

    return 0;
}

