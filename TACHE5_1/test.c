#include <stdio.h>
#include <stdlib.h>

#define LARGEUR 9
#define HAUTEUR 9
#define NOIR 1
#define BLANC 0

// Fonction pour afficher une image
void afficher_image(int image[LARGEUR][HAUTEUR]) {
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            printf("%d ", image[x][y]);
        }
        printf("\n");
    }
}

// Fonction pour détecter les contours
void detecter_contours(int image[LARGEUR][HAUTEUR]) {
    // Création de l'image masque
    int masque[LARGEUR][HAUTEUR];
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            masque[x][y] = (image[x][y] == NOIR && image[x][y - 1] == BLANC) ? NOIR : BLANC;
        }
    }

    // Recherche des contours
    int nb_contours = 0;
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            if (masque[x][y] == NOIR) {
                nb_contours++;
                printf("Contour %d:\n", nb_contours);
                int contour_length = 0;
                int current_x = x;
                int current_y = y;
                while (masque[current_x][current_y] == NOIR) {
                    printf("(%d, %d) ", current_x, current_y);
                    masque[current_x][current_y] = BLANC; // Marquer le pixel visité
                    contour_length++;
                    if (masque[current_x + 1][current_y] == NOIR) {
                        current_x++;
                    } else if (masque[current_x][current_y + 1] == NOIR) {
                        current_y++;
                    } else if (masque[current_x - 1][current_y] == NOIR) {
                        current_x--;
                    } else if (masque[current_x][current_y - 1] == NOIR) {
                        current_y--;
                    }
                }
                printf("\n");
                printf("Nombre de points : %d\n", contour_length);
            }
        }
    }
    printf("Nombre total de contours : %d\n", nb_contours);
}

int main() {
    // Exemple d'image
    int image[LARGEUR][HAUTEUR] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    printf("Image originale :\n");
    afficher_image(image);
    printf("\n");

    detecter_contours(image);

    return 0;
}
