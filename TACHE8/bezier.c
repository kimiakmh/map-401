#include <stdio.h>
#include <math.h>
#include "bezier.h"
#include "contour.h"
#include "geometrie2D.h"

// Calcule le point C(t) d'une courbe de Bézier de degré 2 pour une valeur de t entre 0 et 1
Point bezier2_point(Bezier2 bezier, double t) {
    Point result;
    result.x =(1-t)*(1-t)*bezier.C0.x + 2*t*(1-t)*bezier.C1.x + t*t*bezier.C2.x;
    result.y =(1-t)*(1-t)*bezier.C0.y + 2*t*(1-t)*bezier.C1.y + t*t*bezier.C2.y;
    return result;
}

// Calcule le point C(t) d'une courbe de Bézier de degré 3 pour une valeur de t entre 0 et 1
Point bezier3_point(Bezier3 bezier, double t) {
    Point result;
    result.x = (1-t)*(1-t)*(1-t)*bezier.C0.x + 3*t*(1-t)*(1-t)*bezier.C1.x + 3*t*t*(1-t)*bezier.C2.x + t*t*t*bezier.C3.x;
    result.y = (1-t)*(1-t)*(1-t)*bezier.C0.y + 3*t*(1-t)*(1-t)*bezier.C1.y + 3*t*t*(1-t)*bezier.C2.y + t*t*t*bezier.C3.y;
    return result;
}

// Calcule la distance entre un point et une courbe de Bézier de degré 2 à un certain paramètre t
double distance_bezier2(Point p, Bezier2 B, double t){
    Point C = bezier2_point(B, t);
    double d = distance_points(p, C);
    return d;
}

// Calcule la distance entre un point et une courbe de Bézier de degré 3 à un certain paramètre t
double distance_bezier3(Point p, Bezier3 B, double t)
{
    Point C = bezier3_point(B, t);
    double d = distance_points(p, C);
    return d;
}

// Convertit une courbe de Bézier de degré 2 en une courbe de Bézier de degré 3
Bezier3 bezier2_to_bezier3(Bezier2 bezier2) {
    Bezier3 bezier3;
    bezier3.C0 = bezier2.C0;
    bezier3.C1.x = (1.0 / 3.0) * bezier2.C0.x + (2.0 / 3.0) * bezier2.C1.x;
    bezier3.C1.y = (1.0 / 3.0) * bezier2.C0.y + (2.0 / 3.0) * bezier2.C1.y;
    bezier3.C2.x = (2.0 / 3.0) * bezier2.C1.x + (1.0 / 3.0) * bezier2.C2.x;
    bezier3.C2.y = (2.0 / 3.0) * bezier2.C1.y + (1.0 / 3.0) * bezier2.C2.y;
    bezier3.C3 = bezier2.C2;
    return bezier3;
}

// Approximation d'une courbe de Bézier de degré 2 (contour {Pj1, . . . , Pj2}) cf. page 46
Bezier2 approx_bezier2 (Tableau_Point P, UINT j1, UINT j2) {
    Bezier2 B;
    B.C0 = P.tab[j1];
    B.C2 = P.tab[j2];

    UINT n = j2 - j1;
    
    if (n == 1) {
        B.C1.x = (P.tab[j1].x + P.tab[j2].x) / 2;
        B.C1.y = (P.tab[j1].y + P.tab[j2].y) / 2;
    } else if (n >= 2) {
        double alpha = (3.0 * (double)n) / ((double)n * (double)n - 1.0);
        double beta = (1.0 - 2.0 * (double)n) / (2.0 * ((double)n + 1.0));
        double Sx = 0;
        double Sy = 0;
        for (int i = 1; i <= n - 1; i++) {
            Sx = Sx + P.tab[i + j1].x;
            Sy = Sy + P.tab[i + j1].y;
        }
        B.C1.x = alpha * Sx + beta * (P.tab[j1].x + P.tab[j2].x);
        B.C1.y = alpha * Sy + beta * (P.tab[j1].y + P.tab[j2].y);
    }
    return B;
}

// Fonction pour calculer gamma(k) selon la formule donnée
double calculer_gamma(UINT n, UINT k) {
    double nd = (double)n;
    double kd = (double)k;
    double gamma = 6.0 * kd * kd * kd * kd - 8.0 * nd * kd * kd * kd + 6.0 * kd * kd - 4.0 * nd * kd + nd * nd * nd * nd - nd * nd;
    return gamma;
}

// Approximation d'une courbe de Bézier de degré 3 (contour {Pj1, . . . , Pj2})
Bezier3 approx_bezier3(Tableau_Point P, UINT j1, UINT j2) {
    Bezier3 B;
    B.C0 = P.tab[j1];
    B.C3 = P.tab[j2];

    UINT n = j2 - j1;
    if (n == 1) {
        // C0 = P0, C1 = (2 P0 + P1)/3, C2 = (P0 + 2 P1)/3, et C3 = P1
        B.C1.x = (2.0 * P.tab[j1].x + P.tab[j2].x) / 3.0;
        B.C1.y = (2.0 * P.tab[j1].y + P.tab[j2].y) / 3.0;
        B.C2.x = (P.tab[j1].x + 2.0 * P.tab[j2].x) / 3.0;
        B.C2.y = (P.tab[j1].y + 2.0 * P.tab[j2].y) / 3.0;
    }else if (n == 2) {
        // C0 = P0, C1 = (4 P1 − P2)/3, C2 = (4 P1 − P0)/3, et C3 = P2
        B.C1.x = (4.0 * P.tab[j1 + 1].x - P.tab[j2].x) / 3.0;
        B.C1.y = (4.0 * P.tab[j1 + 1].y - P.tab[j2].y) / 3.0;
        B.C2.x = (4.0 * P.tab[j1 + 1].x - P.tab[j1].x) / 3.0;
        B.C2.y = (4.0 * P.tab[j1 + 1].y - P.tab[j1].y) / 3.0;

    }else if (n >= 3) {
        // Calcul des coefficients alpha, beta et lambda
        double nd =  (double)n;
        double alpha = (-15.0 * nd * nd * nd + 5.0 * nd * nd + 2.0 * nd + 4.0) / (3.0 * (nd + 2.0) * (3.0 * nd * nd + 1.0));
        double beta = (10.0 * nd * nd * nd - 15.0 * nd * nd + nd + 2.0) / (3.0 * (nd + 2.0) * (3.0 * nd * nd + 1.0));
        double lambda = (70.0 * nd) / (3.0 * (nd * nd - 1.0) * (nd * nd - 4.0) * (3.0 * nd * nd + 1.0));

        // Calcul des sommes utilisées dans les points de contrôle C1 et C2
        double Sx1 = 0.0, Sy1 = 0.0, Sx2 = 0.0, Sy2 = 0.0;
        for (int i = 1; i <= n - 1; i++) {
            double gamma1 = calculer_gamma(n, i);
            double gamma2 = calculer_gamma(n, n - i);
            Sx1 += gamma1 * P.tab[i + j1].x;
            Sy1 += gamma1 * P.tab[i + j1].y;
            Sx2 += gamma2 * P.tab[i + j1].x;
            Sy2 += gamma2 * P.tab[i + j1].y;
        }

        // Calcul des points de contrôle C1 et C2
        B.C1.x = alpha * P.tab[j1].x + lambda * Sx1 + beta * P.tab[j2].x;
        B.C1.y = alpha * P.tab[j1].y + lambda * Sy1 + beta * P.tab[j2].y;
        B.C2.x = beta * P.tab[j1].x + lambda * Sx2 + alpha * P.tab[j2].x;
        B.C2.y = beta * P.tab[j1].y + lambda * Sy2 + alpha * P.tab[j2].y;
    }
    return B;
}

// Crée une liste de Bézier2 vide
Liste_Bezier2 creer_liste_Bezier2_vide() {
    Liste_Bezier2 L = {0, NULL, NULL};
    return L;
}

// Crée une liste de Bézier3 vide
Liste_Bezier3 creer_liste_Bezier3_vide()
{
    Liste_Bezier3 L = {0, NULL, NULL};
    return L;
}

// Crée un élément de liste de Bézier2 avec la courbe donnée
Cellule_Liste_Bezier2 *creer_element_liste_Bezier2(Bezier2 b) {
    Cellule_Liste_Bezier2 *el;
    el = (Cellule_Liste_Bezier2 *)malloc(sizeof(Cellule_Liste_Bezier2));
    if (el == NULL) {
        fprintf(stderr, "creer_element_liste_Bezier2 : allocation impossible\n");
        exit(-1);
    }
    el->data = b;
    el->suiv = NULL;
    return el;
}

// Crée un élément de liste de Bézier3 avec la courbe donnée
Cellule_Liste_Bezier3 *creer_element_liste_Bezier3(Bezier3 b) {
    Cellule_Liste_Bezier3 *el;
    el = (Cellule_Liste_Bezier3 *)malloc(sizeof(Cellule_Liste_Bezier3));
    if (el == NULL) {
        fprintf(stderr, "creer_element_liste_Bezier3 : allocation impossible\n");
        exit(-1);
    }
    el->data = b;
    el->suiv = NULL;
    return el;
}

// Ajoute un élément à une liste de Bézier2
Liste_Bezier2 ajouter_element_liste_Bezier2(Liste_Bezier2 *L, Bezier2 e) {
    Cellule_Liste_Bezier2 *el;

    el = creer_element_liste_Bezier2(e);
    if (L->taille == 0) {
        /* premier élément de la liste */
        L->first = L->last = el;
    } else {
        L->last->suiv = el;
        L->last = el;
    }
    L->taille++;
    return *L;
}

// Ajoute un élément à une liste de Bézier3
Liste_Bezier3 ajouter_element_liste_Bezier3(Liste_Bezier3 *L, Bezier3 e) {
    Cellule_Liste_Bezier3 *el;

    el = creer_element_liste_Bezier3(e);
    if (L->taille == 0) {
        /* premier élément de la liste */
        L->first = L->last = el;
    } else {
        L->last->suiv = el;
        L->last = el;
    }
    L->taille++;
    return *L;
}

// Concatène deux listes de Bézier2
Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 L1, Liste_Bezier2 L2) {
    /* cas où l'une des deux listes est vide */
    if (L1.taille == 0)
        return L2;
    if (L2.taille == 0)
        return L1;

    /* les deux listes sont non vides */
    L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
    L1.last = L2.last;         /* le dernier élément de L1 est celui de L2 */
    L1.taille += L2.taille;    /* nouvelle taille pour L1 */
    return L1;
}

// Concatène deux listes de Bézier3
Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 L1, Liste_Bezier3 L2) {
    /* cas où l'une des deux listes est vide */
    if (L1.taille == 0)
        return L2;
    if (L2.taille == 0)
        return L1;

    /* les deux listes sont non vides */
    L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
    L1.last = L2.last;         /* le dernier élément de L1 est celui de L2 */
    L1.taille += L2.taille;    /* nouvelle taille pour L1 */
    return L1;
}

// Cette fonction libère la mémoire associée à une liste de courbes de Bézier de degré 2
Liste_Bezier2* detruire_liste_Bezier2(Liste_Bezier2 *liste)
{
    Cellule_Liste_Bezier2 *courant = liste->first;
    
    while (courant)
    {
        Cellule_Liste_Bezier2 *suivant = courant->suiv;
        free(courant);
        courant = suivant;
    }
    
    liste->first = liste->last = NULL;
    liste->taille = 0;
    
    return liste;
}

// Cette fonction libère la mémoire associée à une liste de courbes de Bézier de degré 3
Liste_Bezier3* detruire_liste_Bezier3(Liste_Bezier3 *liste)
{
    Cellule_Liste_Bezier3 *courant = liste->first;
    
    while (courant)
    {
        Cellule_Liste_Bezier3 *suivant = courant->suiv;
        free(courant);
        courant = suivant;
    }
    
    liste->first = liste->last = NULL;
    liste->taille = 0;
    
    return liste;
}
