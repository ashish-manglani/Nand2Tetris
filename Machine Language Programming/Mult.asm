// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm
// @ashish-manglani

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

@R2
M=0 // initialize answer to zero

// ans=R0*R1
// can be iterpreted as adding R1 to ans R0 times

(LOOP)
	@R0
	D=M
	@END
	D;JLE 	// goto end if R0 becomes zero i.e all iterations are done

	@R1
	D=M
	@R2
	M=M+D 	// add R1 to R2

	@R0		
	M=M-1	// R0--
	@LOOP
	M;JGT
(END)
	@END
	0;JMP
