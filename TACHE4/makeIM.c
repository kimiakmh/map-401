#include <stdio.h>
#include "image.h"

int main(int argc, char *argv[]) {

    // Dimensions de la matrice (image)
    int MAT_width = 5;
    int MAT_height = 5;

    // Définition de la matrice (image)
    int MAT[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };

    // Ouverture du fichier pour écrire l'image au format PBM
    FILE *fileIM = fopen("IMtest.pbm", "w");
    if (fileIM != NULL) {

        // Écriture de l'en-tête P1
        fprintf(fileIM, "P1\n");

        // Écriture des dimensions de l'image
        fprintf(fileIM, "%d %d\n", MAT_width, MAT_height);

        // Écriture des pixels de l'image
        for (int y = 0; y < MAT_height; y++) {
            for (int x = 0; x < MAT_width; x++) {
                fprintf(fileIM, "%d ", MAT[y][x]);
            }
            fprintf(fileIM, "\n");
        }

        // Fermeture du fichier
        fclose(fileIM);
        printf("Image sauvegardée en format .pbm\n");
    } else {
        // En cas d'erreur lors de l'ouverture du fichier
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
    }

    return 0;
}