#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types_macros.h"
#include "image.h"
#include "contour.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <nom_fichier_image.pbm>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Charger l'image PBM à partir du fichier spécifié en argument */
    Image monImage = lire_fichier_image(argv[1]);

/* Extrait le nom de base du fichier image (sans extension) */
    char *imageName = argv[1];
    char *dot = strrchr(imageName, '.'); 
    if (dot != NULL) {
        *dot = '\0'; // le terminateur nul pour supprimer l'extension
    }

/* Génère le nom du fichier de contour en ajoutant ".contours" au nom de base */
    char contourFileName[256];  // Ajuster la taille du tableau si nécessaire
    snprintf(contourFileName, sizeof(contourFileName), "%s.contours", imageName);

    /* Calculer et afficher le contour */
    calculer_et_afficher_contour(monImage, contourFileName);

    /* Libérer la mémoire allouée pour l'image */
    supprimer_image(&monImage);

    return EXIT_SUCCESS;
}
