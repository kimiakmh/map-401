#include <stdio.h>
#include "image.h"

int main(int argc, char *argv[]) {
    // ... (unchanged part of the code)

    // Dimensions of the square image
    int square_width = 5;
    int square_height = 5;

    // Matrix representing a square
    int carre[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
    };
    // Writing the square image to a file
    FILE *square_file = fopen("square.pbm", "w");
    if (square_file != NULL) {
        // Writing the P1 header
        fprintf(square_file, "P1\n");

        // Writing the dimensions of the image
        fprintf(square_file, "%d %d\n", square_width, square_height);

        // Writing the pixels of the image
        for (int y = 0; y < square_height; y++) {
            for (int x = 0; x < square_width; x++) {
                fprintf(square_file, "%d ", carre[y][x]);
            }
            fprintf(square_file, "\n");
        }

        fclose(square_file);
        printf("Square image saved in square.pbm\n");
    } else {
        fprintf(stderr, "Error opening the file\n");
    }

    return 0;
}
