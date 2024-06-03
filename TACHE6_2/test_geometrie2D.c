#include <stdio.h>
#include "geometrie2D.h"

int main() {
    // Déclaration des variables pour les points P, A et B
    Point P, A, B;

    // Demander à l'utilisateur d'entrer les coordonnées du point P
    printf("Entrez les coordonnées du point P (x y) : ");
    scanf("%lf %lf", &P.x, &P.y);

    // Demander à l'utilisateur d'entrer les coordonnées du point A
    printf("Entrez les coordonnées du point A (x y) : ");
    scanf("%lf %lf", &A.x, &A.y);

    // Demander à l'utilisateur d'entrer les coordonnées du point B
    printf("Entrez les coordonnées du point B (x y) : ");
    scanf("%lf %lf", &B.x, &B.y);

    // Calculer la distance entre le point P et le segment [A, B]
    double distance = distance_point_segment(P, A, B);

    // Afficher le résultat
    printf("La distance entre le point P et le segment [A, B] est : %lf\n", distance);

    return 0;
}
