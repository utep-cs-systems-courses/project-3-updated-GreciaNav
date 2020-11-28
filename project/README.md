Lab Project 3: Graphical LCD Toy
================================

## Description
This interrupt driven toy flashes the LED's, plays buzzing sounds, and has a
graphical LCD screen. Depending on what button you press (On the green
board), a different action will happen!

## How to Compile and Run
1. Inside the main directoy (project-3-updated-GreciaNav), type "make all" (No
quotes).

2. After this is done, type "cd project/" (No quotes) to go into the
project folder.

3. Once inside the project folder, plug in your MSP430 to your computer, and
type "make load" (No quotes). Whenever your MSP430 is plugged in, the program
will run.

4. If desired, type "make clean" (No quotes) to remove all compiled and .o
files.

## Button Functions:
On the green board, there are four buttons. On top, you can see each button is
labeled S1-S4 going from left to right. The following descriptions will use
this naming convention for the buttons.

- Pressing **S1**: This button will display a dancing Sonic the Hedgehog! This
  cute little Sonic will be dancing to the tune of his own theme song.

- Pressing **S2**: This button turns off the buzzer and will show link from the Legend of Zelda with a spooky message.

- Pressing **S3**: This button turns off the buzzer and displays a diamond that changes color every second.

- Pressing **S4**: This button turns off the buzzer, and makes de red LED turn
  on with different dim intensities.
