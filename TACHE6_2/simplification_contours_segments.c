#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "simplification_contours_segments.h"


// Simplification d'un contour polygonal par l'algorithme de Douglas-Peucker
Liste_Point simplification_douglas_peucker(Tableau_Point CONT, UINT j1, UINT j2, double d) {
    Liste_Point L = creer_liste_Point_vide();
    Liste_Point L1 = creer_liste_Point_vide();
    Liste_Point L2 = creer_liste_Point_vide();

    // Approximation de la séquence de points CONT(j1..j2) par le segment [Pj1, Pj2]
    Segment S = { CONT.tab[j1], CONT.tab[j2] };

    // Recherche du point le plus éloigné du segment S
    double dmax = 0;
    UINT k = j1;
    for (UINT j = j1 + 1; j <= j2; j++) {
        double distance = distance_point_segment(CONT.tab[j], S.A, S.B);
        if (dmax < distance) {
            dmax = distance;
            k = j;
        }
    }

    if (dmax <= d) {
        // Si dmax <= d : simplification suivant le segment S
        L = ajouter_element_liste_Point(L, S.A);
    } else {
        // Si dmax > d : "diviser pour régner"
        // Simplification de la partie du contour CONT entre j1 et k avec la distance-seuil d
        L1 = simplification_douglas_peucker(CONT, j1, k, d);
        // Simplification de la partie du contour CONT entre k et j2 avec la distance-seuil d
        L2 = simplification_douglas_peucker(CONT, k, j2, d);
        // Fusion des deux séquences L1 et L2
        L = concatener_liste_Point(L1, L2);
    }

    return L;
}