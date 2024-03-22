// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen
// by writing 'black' in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen by writing
// 'white' in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Initialize variables.
(LOOP)
@SCREEN
D=A
@0
M=D

// Listen for keyboard input.
@KBD
D=M
@BLACK
D;JNE
@WHITE
D;JEQ

// Set the colour to black.
(BLACK)
@1
M=-1
@RENDER
0;JMP

// Set the colour to be white.
(WHITE)
@1
M=0
@RENDER
0;JMP

// Render the screen with the chosen colour.
(RENDER)
@1
D=M
@0
A=M
M=D
@0
D=M+1
M=D
@KBD
D=A-D
@RENDER
D;JNE
@LOOP
0;JMP
