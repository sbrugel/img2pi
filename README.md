# img2pi
A pair of scripts that display a jpg/png image on a Raspberry Pi's sense hat. Not too practical of a project; this was simply a bit of messing around I did to see what I could do with a sense hat, made shortly after finishing a college computer science project that utilized it.

This entails a Python script that takes a user-specified image, shrinks it down to 8x8 (the resolution of the tiles on a sense hat), and stores the RGB values of each pixel in text files.

A C script is also included which takes the data from those text files and displays the pixelated image on the sense hat.

You can find a short demonstration of this program [here](https://youtu.be/IDtjmli2TMs)

## Running the Program

Before you start, ensure that you have access to a Linux system to run the C file (since it uses some Linux-specific libraries such as *linux/fb.h*)

1) Run the get_colors.py file, inputting the path (can be absolute or relative) of the image you'd like to display on the Pi.
2) At this point, four new files will be generated. "result.png" is a downscaled version of this image, you can ignore this. However, the three text files made, named "r", "g", and "b", will need to be used later - these contain the color data of the downscaled image which will be displayed on the Pi.
3) Now go over to your Pi's system. Copy over "displayimg.c" and "pi.h" to somewhere on there, if you haven't done that already. Create three new files in this directory, "r" "g" and "b".
4) Using a text editor (in my demo, I used Vim, but you can use whatever), open the "r" file on your Pi. Have the "r.txt" file containing the color data handy here since you'll need to copy the contents of the former into the latter. Ensure there are no empty lines at the end of the file; there should be exactly 64 lines in the file
5) Repeat step 4 for the "g" and "b" files, using "g.txt" and "b.txt" respectively.
6) Compile the displayimg.c file and run, of course ensuring your Pi and sense hat are powered on!

## Acknowledgements

A number of functions relating to the frame buffer were taken from the "sense.h" C library made by Greg Silber, a professor at my college (University of Delaware).
