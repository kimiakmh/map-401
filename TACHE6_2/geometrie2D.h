#ifndef GEOMETRIE2D_H
#define GEOMETRIE2D_H
#include "contour.h"

typedef struct Vecteur_
{
    double x; // Composante en x
    double y; // Composante en y
} Vecteur;

// creer le point de coordonees x, y
Point set_point(double x, double y);

// somme de deux points
Point addPoint(Point p1, Point p2);

// difference de deux points
Point minusPoint(Point P1, Point P2);

// vect correspondant au bipoint AB
Vecteur vect_bipoint(Point A, Point B);

// additionne deux vecteurs
Vecteur add_vect(Vecteur v1, Vecteur v2);

// multiplie un point par un scalaire
Point reel_point(double scalaire, Point p);

// multiplie un vecteur par un scalaire
Vecteur reel_vecteur(double scalaire, Vecteur v);

// calcule le produit scalaire de 2 vects
double produit_scalaire(Vecteur v1, Vecteur v2);

// calcule la norme euclidienne du vect V
double norme_euclidienne(Vecteur v);

// calcule la distance entre deux points A et B
double distance_points(Point A, Point B);

// Calcule la distance entre un point P et un segment [A, B]
double distance_point_segment(Point P, Point A, Point B);

#endif
