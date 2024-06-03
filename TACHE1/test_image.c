#include <stdio.h>
#include "image.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_fichier_image>\n", argv[0]);
        return 1;
    }

    // Lecture de l'image à partir du fichier
    Image img = lire_fichier_image(argv[1]);

    // Affichage de l'image originale
    printf("Image originale :\n");
    ecrire_image(img);

    // Création de l'image négatif
    Image img_negatif = negatif_image(img);
    printf("\nImage négatif :\n");
    ecrire_image(img_negatif);

    // Sauvegarde de l'image dans un fichier
    FILE *fichier = fopen("image_negatif.pbm", "w");
    if (fichier != NULL) {
        // Écriture de l'en-tête P1
        fprintf(fichier, "P1\n");

        // Écriture des dimensions de l'image
        fprintf(fichier, "%u %u\n", img_negatif.la_largeur_de_l_image, img_negatif.la_hauteur_de_l_image);

        // Écriture des pixels de l'image
        for (UINT y = 1; y <= img_negatif.la_hauteur_de_l_image; y++) {
            for (UINT x = 1; x <= img_negatif.la_largeur_de_l_image; x++) {
                fprintf(fichier, "%d ", get_pixel_image(img_negatif, x, y) == NOIR ? 1 : 0);
            }
            fprintf(fichier, "\n");
        }

        fclose(fichier);
        printf("Image sauvegardée dans image_negatif.pbm\n");
        } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
    }
    // Libération de la mémoire
    supprimer_image(&img);
    supprimer_image(&img_negatif);

        // Dimensions de l'image
    int largeur = 5;
    int hauteur = 9;

    // Matrice représentant le caractère '3'
    int image[9][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };

    // Écriture de l'image dans un fichier
    FILE *fichier2 = fopen("caractere3.pbm", "w");
    if (fichier2 != NULL) {
        // Écriture de l'en-tête P1
        fprintf(fichier2, "P1\n");

        // Écriture des dimensions de l'image
        fprintf(fichier2, "%d %d\n", largeur, hauteur);

        // Écriture des pixels de l'image
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                fprintf(fichier2, "%d ", image[y][x]);
            }
            fprintf(fichier2, "\n");
        }

        fclose(fichier2);
        printf("Image sauvegardée dans caractere3.pbm\n");
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
    }

    return 0;
}
