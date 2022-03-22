#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "pi.h"

// converts an RGB value to a 16-bit color for use on the sense hat
uint16_t getColor(int red, int green, int blue) {
    red = (float)red / 255.0 * 31.0 + 0.5;
    green = (float)green / 255.0 * 63.0 + 0.5;
    blue = (float)blue / 255.0 * 31.0 + 0.5;
    return red<<11|green<<5|blue;
}

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

    // these lines come from the 'sense.h' library
    pi_framebuffer_t *fb = getFrameBuffer();
    sense_fb_bitmap_t *bm=fb->bitmap;
    clearFrameBuffer(fb, 0x0000); // make the whole sense hat board black

    // nested loop goes here which assigns the colors to each tile
    for (int i = 0; i < 64; i++) {
        uint16_t color = getColor(red[i], green[i], blue[i]);
        int x = i % 8;
        int y = (int)(i / 8);

        // these lines utilize functions included with 'sense.h'
        setPixel(&bm, x, y, color);
    }

    return 0;
}