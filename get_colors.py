from PIL import Image
from math import sqrt
import numpy as np

# list of U16 colors
COLORS = (
    (0,0,0), # black - 0x0000
    (255,255,255), # white - 0xffff
    (255,0,0), # red - 0xf800
    (255,255,0), # yellow - 0xffe0
    (255,125,0), # orange - 0xfbe0
    (123,61,0), # brown - 0x79e0
    (0,255,0), # green - 0x07e0 (0x7e0)
    (0,255,255), # cyan - 0x07ff (0x7ff)
    (0,0,255), # blue - 0x001f (0x1f)
    (255,0,255) # pink - 0xf81f
)

def closest(colors,color):
    colors = np.array(COLORS)
    color = np.array(color)
    distances = np.sqrt(np.sum((colors-color)**2,axis=1))
    index_of_smallest = np.where(distances==np.amin(distances))
    smallest_distance = colors[index_of_smallest]
    return smallest_distance 

def main():
    # resize the image to 8x8 (resolution of Pi sense hat)
    img = Image.open('septa.png')
    result = img.resize((8, 8),resample=Image.BILINEAR)

    result.save('result.png')

    # now get the color of each pixel
    imgColors = []
    imgU16Colors = []

    img = Image.open('result.png')
    imgFinal = img.convert('RGB').load()

    width, height = result.size
    for i in range(width):
        for j in range(height):
            imgColors.append(imgFinal[i,j])

    # round each pixel color to the nearest U16 color
    for i in range(len(imgColors)):
        imgU16Colors.append(closest(COLORS, imgColors[i]))
        print(imgColors[i])
        print(imgU16Colors[i])

    # write colors to file (one row at a time)

main()
