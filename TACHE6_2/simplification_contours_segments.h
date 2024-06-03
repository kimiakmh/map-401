#ifndef SIMPLIFICATION_CONTOURS_SEGMENTS_H
#define SIMPLIFICATION_CONTOURS_SEGMENTS_H

#include "contour.h"
#include "geometrie2D.h"

// Définition du type Segment
typedef struct {
    Point A; // Point de départ du segment
    Point B; // Point de fin du segment
} Segment;

// Prototypes de fonctions
Liste_Point simplification_douglas_peucker(Tableau_Point CONT, UINT j1, UINT j2, double d);

#endif /* SIMPLIFICATION_CONTOURS_SEGMENTS_H */
