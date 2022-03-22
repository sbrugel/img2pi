#include <stdio.h>

int main(void) {
    char* fileName = "your file path here"; // the text file containing colors
    FILE* file = fopen(fileName, "r");
    char line[256];

    int red[64], green[64], blue[64]; // there are 64 tiles to fill

    while (fgets(line, sizeof(line), file)) {
        // make this get substring of each color, put in color arrays
        printf("%s", line);
    }

    fclose(file);

    // nested loop goes here which assigns the colors to each tile
    
    return 0;
}

char* substring(char* string, int start) {  // gets 3 characters from the start point of the specified string
                                            // use this to get each RGB value
    char subbuff[4];
    memcpy(subbuff, string[start], 3);
    subbuff[3] = '\0';
    return subbuff;
}