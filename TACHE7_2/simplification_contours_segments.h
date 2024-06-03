#ifndef SIMPLIFICATION_CONTOURS_SEGMENTS_H
#define SIMPLIFICATION_CONTOURS_SEGMENTS_H

#include "contour.h"
#include "geometrie2D.h"
#include "bezier.h"

// Définition du type Segment
typedef struct {
    Point A; // Point de départ du segment
    Point B; // Point de fin du segment
} Segment;

// Simplification d'un contour polygonal par l'algorithme de Douglas-Peucker
Liste_Point simplification_douglas_peucker(Tableau_Point CONT, UINT j1, UINT j2, double d);

// Simplification d'un contour polygonal par une séquence de Bézier de degré 2 avec l'algorithme de Douglas-Peucker
Liste_Bezier2 simplification_douglas_peucker_bezier2(Tableau_Point CONT, UINT j1, UINT j2, double d);
Liste_Bezier3 simplification_douglas_peucker_bezier3(Tableau_Point CONT, UINT j1, UINT j2, double d);

#endif /* SIMPLIFICATION_CONTOURS_SEGMENTS_H */
