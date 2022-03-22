#include <stdint.h>
#include <linux/fb.h>

typedef struct {
    uint16_t pixel[8][8];
} sense_fb_bitmap_t;

typedef struct {
    int fd;
    struct fb_fix_screeninfo info;
    sense_fb_bitmap_t* bitmap;
} pi_framebuffer_t;