#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char* reds = "./r"; // the text file containing all red colors
    char* greens = "./g"; // the text file containing all green colors
    char* blues = "./b"; // the text file containing all blue colors
    
    FILE* redFile = fopen(reds, "r");
    FILE* greenFile = fopen(greens, "r");
    FILE* blueFile = fopen(blues, "r");
    char line[256];

    int red[64], green[64], blue[64]; // there are 64 tiles to fill
    int i = 0;

    while (fgets(line, sizeof(line), redFile)) {
        red[i] = atoi(line); // convert char* to int
        i++;
    }
    fclose(redFile);

    i = 0;
    while (fgets(line, sizeof(line), greenFile)) {
        green[i] = atoi(line);
        i++;
    }
    fclose(greenFile);

    i = 0;
    while (fgets(line, sizeof(line), blueFile)) {
        blue[i] = atoi(line);
        i++;
    }
    fclose(blueFile);

    // nested loop goes here which assigns the colors to each tile
    for (int i = 0; i < 64; i++) {
        printf("RED: %d, GREEN: %d, BLUE: %d\n", red[i], green[i], blue[i]);
    }

    return 0;
}

// put in getColor method from sense.h here