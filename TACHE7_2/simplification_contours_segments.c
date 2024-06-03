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

// Simplification d'un contour polygonal par une séquence de Bézier de degré 2 avec l'algorithme de Douglas-Peucker
Liste_Bezier2 simplification_douglas_peucker_bezier2(Tableau_Point CONT, UINT j1, UINT j2, double d) {
    Liste_Bezier2 L = creer_liste_Bezier2_vide(); // Crée une liste vide pour stocker les courbes de Bézier simplifiées
    Liste_Bezier2 L1 = creer_liste_Bezier2_vide(); // Crée une liste vide pour stocker les courbes de Bézier de la première moitié
    Liste_Bezier2 L2 = creer_liste_Bezier2_vide(); // Crée une liste vide pour stocker les courbes de Bézier de la deuxième moitié

    // Approximation de la séquence de points CONT(j1..j2) par la courbe de Bézier de degré 2 B(Pj1, Pj2)
    Bezier2 B = approx_bezier2(CONT, j1, j2);

    // Calcul de la distance maximale entre les points de la séquence et la courbe de Bézier
    double dmax = 0; // Initialise la distance maximale à 0
    UINT k = j1; // Initialise l'indice k à j1
    UINT n = j2 - j1; // Calcule le nombre de segments
    for (UINT j = j1 + 1; j <= j2; j++) { // Parcourt tous les points de la séquence de points
        UINT i = j - j1; // Calcule l'indice i relatif à j1
        double t = (double)i / (double)n; // Calcule le paramètre t pour la courbe de Bézier
        double distance = distance_bezier2(CONT.tab[j], B ,t); // Calcule la distance entre le point et la courbe de Bézier
        if (dmax < distance) { // Si la distance est supérieure à la distance maximale actuelle
            dmax = distance; // Met à jour la distance maximale
            k = j; // Met à jour l'indice k
        }
    }

    if (dmax <= d) { // Si la distance maximale est inférieure ou égale à la distance-seuil
        // Si dmax <= d : la courbe de Bézier approxime bien la séquence de points
        L = ajouter_element_liste_Bezier2(&L, B); // Ajoute la courbe de Bézier à la liste
    } else {
        // Si dmax > d : "diviser pour régner"
        // Simplification de la partie du contour CONT entre j1 et k avec la distance-seuil d
        L1 = simplification_douglas_peucker_bezier2(CONT, j1, k, d); // Appel récursif sur la première moitié
        // Simplification de la partie du contour CONT entre k et j2 avec la distance-seuil d
        L2 = simplification_douglas_peucker_bezier2(CONT, k, j2, d); // Appel récursif sur la deuxième moitié
        // Fusion des deux séquences L1 et L2
        L = concatener_liste_Bezier2(L1, L2); // Concatène les listes de courbes de Bézier
    }

    return L; // Retourne la liste de courbes de Bézier simplifiées
}

// Simplification d'un contour polygonal par une séquence de Bézier de degré 3 avec l'algorithme de Douglas-Peucker
Liste_Bezier3 simplification_douglas_peucker_bezier3(Tableau_Point CONT, UINT j1, UINT j2, double d) {
    Liste_Bezier3 L = creer_liste_Bezier3_vide(); // Crée une liste vide pour stocker les courbes de Bézier simplifiées
    Liste_Bezier3 L1 = creer_liste_Bezier3_vide(); // Crée une liste vide pour stocker les courbes de Bézier de la première moitié
    Liste_Bezier3 L2 = creer_liste_Bezier3_vide(); // Crée une liste vide pour stocker les courbes de Bézier de la deuxième moitié

    // Approximation de la séquence de points CONT(j1..j2) par la courbe de Bézier de degré 3 B(Pj1, Pj2)
    Bezier3 B = approx_bezier3(CONT, j1, j2);

    // Calcul de la distance maximale entre les points de la séquence et la courbe de Bézier
    double dmax = 0; // Initialise la distance maximale à 0
    UINT k = j1; // Initialise l'indice k à j1
    UINT n = j2 - j1; // Calcule le nombre de segments
    for (UINT j = j1 + 1; j <= j2; j++) { // Parcourt tous les points de la séquence de points
        UINT i = j - j1; // Calcule l'indice i relatif à j1
        double t = (double)i / (double)n; // Calcule le paramètre t pour la courbe de Bézier
        double distance = distance_bezier3(CONT.tab[j], B ,t); // Calcule la distance entre le point et la courbe de Bézier
        if (dmax < distance) { // Si la distance est supérieure à la distance maximale actuelle
            dmax = distance; // Met à jour la distance maximale
            k = j; // Met à jour l'indice k
        }
    }

    if (dmax <= d) { // Si la distance maximale est inférieure ou égale à la distance-seuil
        // Si dmax <= d : la courbe de Bézier approxime bien la séquence de points
        L = ajouter_element_liste_Bezier3(&L, B); // Ajoute la courbe de Bézier à la liste
    } else {
        // Si dmax > d : "diviser pour régner"
        // Simplification de la partie du contour CONT entre j1 et k avec la distance-seuil d
        L1 = simplification_douglas_peucker_bezier3(CONT, j1, k, d); // Appel récursif sur la première moitié
        // Simplification de la partie du contour CONT entre k et j2 avec la distance-seuil d
        L2 = simplification_douglas_peucker_bezier3(CONT, k, j2, d); // Appel récursif sur la deuxième moitié
        // Fusion des deux séquences L1 et L2
        L = concatener_liste_Bezier3(L1, L2); // Concatène les listes de courbes de Bézier
    }

    return L; // Retourne la liste de courbes de Bézier simplifiées
}