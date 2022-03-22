from PIL import Image
import os.path

def main():
    # resize the image to 8x8 (resolution of Pi sense hat)
    img = Image.open('septa.png')
    result = img.resize((8, 8),resample=Image.BILINEAR)

    result.save('result.png')

    img = Image.open('result.png')
    imgFinal = img.convert('RGB').load()

    # get colors from image, put in file
    width, height = result.size
    openMode = "x"
    if os.path.exists('colors.txt'):
        openMode = "w"
    f = open('colors.txt', openMode)

    for i in range(width):
        for j in range(height):
            f.write(str(imgFinal[i,j]) + '\n')

    f.close()

main()