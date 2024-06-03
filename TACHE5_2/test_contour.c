#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types_macros.h"
#include "image.h"
#include "contour.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <nom_fichier_image.pbm> <nom_fichier_contour.eps> <mode>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Charger l'image PBM à partir du fichier spécifié en argument */
    Image monImage = lire_fichier_image(argv[1]);

    /* Convertir le mode en entier */
    int mode = atoi(argv[3]);

    /* Sauvegarder le contour au format EPS */
    sauvegarder_contour_eps(monImage, argv[2], mode);

    /* Libérer la mémoire allouée pour l'image */
    supprimer_image(&monImage);

    return EXIT_SUCCESS;
}
