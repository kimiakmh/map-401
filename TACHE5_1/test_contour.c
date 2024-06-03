#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types_macros.h"
#include "image.h"
#include "contour.h"

int main(int argc, char *argv[]) {
    // if (argc != 3) {
    //     fprintf(stderr, "Usage: %s <image_file> <contours_file>\n", argv[0]);
    //     return EXIT_FAILURE;
    // }

    // Charger l'image depuis le fichier spécifié en argument
    Image image = lire_fichier_image(argv[1]);

    // Détecter les contours de l'image
    Liste_Point *contours = NULL;
    detecter_contours(image, &contours);

    // Écrire les contours dans un fichier texte
    // ecrire_contours_fichier(argv[2], contours, nombre_contours);

    // Libérer la mémoire utilisée par l'image
    supprimer_image(&image);

    // Libérer la mémoire utilisée par les contours
    // for (int i = 0; i < nombre_contours; i++) {
    //     supprimer_liste_Point(contours[i]);
    // }
    free(contours);

    return EXIT_SUCCESS;
}