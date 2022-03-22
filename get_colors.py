from PIL import Image
import os.path

def find_occurences(string, char):
    return [i for i, letter in enumerate(string) if letter == char]

def main():
    # resize the image to 8x8 (resolution of Pi sense hat)
    imageLoc = input('Enter the location of the image > ')
    img = Image.open(imageLoc)
    result = img.resize((8, 8),resample=Image.BILINEAR)

    result.save('result.png')

    img = Image.open('result.png')
    imgFinal = img.convert('RGB').load()

    # get colors from image, put in file
    width, height = result.size
    openMode = "x"
    if os.path.exists('r.txt'):
        openMode = "w"
    red = open('r.txt', openMode)

    openMode = "x"
    if os.path.exists('g.txt'):
        openMode = "w"
    green = open('g.txt', openMode)

    openMode = "x"
    if os.path.exists('b.txt'):
        openMode = "w"
    blue = open('b.txt', openMode)

    for i in range(width):
        for j in range(height):
            colorString = str(imgFinal[i, j])
            commas = find_occurences(colorString, ',')
            red.write(colorString[1:commas[0]] + '\n') # don't include "("
            green.write(colorString[commas[0] + 2:commas[1]] + '\n') # don't include comma
            blue.write(colorString[commas[1] + 2:-1] + '\n') # don't include ")" or comma

    red.close()
    green.close()
    blue.close()

main()