#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geometrie2D.h"

// Crée un point à partir de ses composantes (x,y) et le retourne
Point set_point(double x, double y)
{
    Point P = {x, y};
    return P;
}

// Somme de deux points
Point addPoint(Point p1, Point p2)
{
    return set_point(p1.x + p2.x, p1.y + p2.y);
}

// Vecteur correspondant au bipoint AB
Vecteur vect_bipoint(Point A, Point B)
{
    Vecteur v = {B.x - A.x, B.y - A.y};
    return v;
}

// Additionne deux vecteurs et retourne le résultat
Vecteur add_vect(Vecteur v1, Vecteur v2)
{
    Vecteur result = {v1.x + v2.x, v1.y + v2.y};
    return result;
}

// Multiplie un point par un scalaire et retourne le résultat
Point reel_point(double scalaire, Point p)
{
    Point result = {scalaire * p.x, scalaire * p.y};
    return result;
}

// Multiplie un vecteur par un scalaire et retourne le résultat
Vecteur reel_vecteur(double scalaire, Vecteur v)
{
    Vecteur result = {scalaire * v.x, scalaire * v.y};
    return result;
}

// Calcule le produit scalaire entre deux vecteurs
double produit_scalaire(Vecteur v1, Vecteur v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

// Calcule la norme euclidienne d'un vecteur
double norme_euclidienne(Vecteur v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

// Calcule la distance entre deux points
double distance_entre_points(Point A, Point B)
{
    double distance = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
    return distance;
}
