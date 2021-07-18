// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(START)
	@SCREEN
	D=A
	@R0 // store screen start location in R0
	M=D

	@KBD
	D=M
	@BLACK
	D;JNE	// if val @kbd!=0, key is presses-> turn screen black

	@WHITE
	0;JMP	// if val @kbd==0 then control will reach here-> turn screen white

(BLACK)
	@R0		// R0 stores current register
	D=M 	// store current register address in D
	M=M+1	// R0 will now store the next register address

	A=D     // select current register
	M=-1    // turn it black

	D=D+1	// store next register in D
	@KBD		
	D=D-A	// D=next register - @kbd

	@START  
	D;JEQ 	// if next register == kbd -> break since, // last pixel of screen is @kbd-1

	@BLACK
	0;JMP

(WHITE)
	@R0		// R0 stores current register
	D=M 	// store current register address in D
	M=M+1	// R0 will now store the next register address

	A=D     // select current register
	M=0    // turn it white

	D=D+1	// store next register in D
	@KBD		
	D=D-A	// D=next register - @kbd

	@START  
	D;JEQ 	// if next register == kbd -> break since, // last pixel of screen is @kbd-1
	
	@WHITE
	0;JMP