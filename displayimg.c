#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include "pi.h"

// converts an RGB value to a 16-bit color for use on the sense hat
uint16_t getColor(int red, int green, int blue) {
    red = (float)red / 255.0 * 31.0 + 0.5;
    green = (float)green / 255.0 * 63.0 + 0.5;
    blue = (float)blue / 255.0 * 31.0 + 0.5;
    return red<<11|green<<5|blue;
}

static int isFrameBuffer(const struct dirent *dev){
    return strncmp("fb",dev->d_name,2)==0;
}

void clearFrameBuffer(pi_framebuffer_t* fb,uint16_t color){
    int i,j;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
            fb->bitmap->pixel[i][j]=color;
}

static pi_framebuffer_t* getFBDevice(const char* name){
    pi_framebuffer_t* result=0;
    int fd=open(name,O_RDWR);
    if (fd<0) return 0;

    result=malloc(sizeof(pi_framebuffer_t));
    ioctl(fd,FBIOGET_FSCREENINFO,&result->info);
    if (strcmp("RPi-Sense FB",result->info.id)!=0){
        close(fd);
        free(result);
        return 0;
    }
    result->fd=fd;
    result->bitmap=mmap(0,128,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    return result;
}

pi_framebuffer_t* getFrameBuffer() {
    pi_framebuffer_t* result = 0;
    struct dirent **list;
    int i, ndev;
    ndev = scandir("/dev", &list, isFrameBuffer, versionsort);
    if (ndev <= 0) return 0; // no framebuffers found
    for (i = 0; i < ndev; i++) {
        char fname[512];
        snprintf(fname, sizeof(fname), "/dev/%s", list[i]->d_name);
        result = getFBDevice(fname);
        if (result) break;
    }
    for (i = 0; i < ndev; i++) {
        free(list[i]);
    }
    return result;
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
        &bm->pixel[y][x]=color;
    }

    return 0;
}