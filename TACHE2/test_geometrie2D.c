#include <stdio.h>
#include "geometrie2D.h"

int main() {
    Point A, B;
    Vecteur V1, V2;
    double scalaire;

    // Demander à l'utilisateur les coordonnées du point A
    printf("Entrez les coordonnées du point A (x y) : ");
    if (scanf("%lf %lf", &A.x, &A.y) != 2) {
        fprintf(stderr, "Erreur : Entrée invalide pour le point A\n");
        return 1; // Code d'erreur
    }

    // Demander à l'utilisateur les coordonnées du point B
    printf("Entrez les coordonnées du point B (x y) : ");
    if (scanf("%lf %lf", &B.x, &B.y) != 2) {
        fprintf(stderr, "Erreur : Entrée invalide pour le point B\n");
        return 1; // Code d'erreur
    }

    // Afficher les coordonnées des points
    printf("Point A : (%.2f, %.2f)\n", A.x, A.y);
    printf("Point B : (%.2f, %.2f)\n", B.x, B.y);

    // Somme de deux points
    Point C = addPoint(A, B);
    printf("Somme de A et B : (%.2f, %.2f)\n", C.x, C.y);

    // Vecteur correspondant au bipoint AB
    Vecteur AB = vect_bipoint(A, B);
    printf("Vecteur AB : (%.2f, %.2f)\n", AB.x, AB.y);

    // Demander à l'utilisateur les composantes du vecteur V1
    printf("Entrez les composantes du vecteur V1 (x y) : ");
    if (scanf("%lf %lf", &V1.x, &V1.y) != 2) {
        fprintf(stderr, "Erreur : Entrée invalide pour le vecteur V1\n");
        return 1; // Code d'erreur
    }

    // Demander à l'utilisateur les composantes du vecteur V2
    printf("Entrez les composantes du vecteur V2 (x y) : ");
    if (scanf("%lf %lf", &V2.x, &V2.y) != 2) {
        fprintf(stderr, "Erreur : Entrée invalide pour le vecteur V2\n");
        return 1; // Code d'erreur
    }

    // Addition de deux vecteurs
    Vecteur V_sum = add_vect(V1, V2);
    printf("Somme des vecteurs V1 et V2 : (%.2f, %.2f)\n", V_sum.x, V_sum.y);

    // Demander à l'utilisateur d'entrer un scalaire
    printf("Entrez un scalaire : ");
    if (scanf("%lf", &scalaire) != 1) {
        fprintf(stderr, "Erreur : Entrée invalide pour le scalaire\n");
        return 1; // Code d'erreur
    }

    // Afficher le scalaire
    printf("Scalaire : %.2f\n", scalaire);

    // Multiplication d'un point par un scalaire
    Point point_echelle = reel_point(scalaire, A);
    printf("Point A multiplié par %.2f : (%.2f, %.2f)\n", scalaire, point_echelle.x, point_echelle.y);

    // Multiplication d'un vecteur par un scalaire
    Vecteur vecteur_echelle = reel_vecteur(scalaire, V1);
    printf("Vecteur V1 multiplié par %.2f : (%.2f, %.2f)\n", scalaire, vecteur_echelle.x, vecteur_echelle.y);

    // Produit scalaire de deux vecteurs
    double produit_scalaire_V1_V2 = produit_scalaire(V1, V2);
    printf("Produit scalaire de V1 et V2 : %.2f\n", produit_scalaire_V1_V2);

    // Norme euclidienne d'un vecteur
    double norm_V1 = norme_euclidienne(V1);
    printf("Norme euclidienne de V1 : %.2f\n", norm_V1);

    // Distance entre les points A et B
    double distance_AB = distance_entre_points(A, B);
    printf("Distance entre A et B : %.2f\n", distance_AB);

    return 0;
}
