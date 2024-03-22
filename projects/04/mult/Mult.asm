// Multiply Two Numbers
// This program will multiply the two numbers stored in R0 and R1. These numbers will be non-negative integers and their product will be less than 32,768. The product will be stored in R2.

// Initialize the product to zero in R2.
@2
M=0

// Check if R0 is zero.
@0
D=M
@END
D;JEQ

// Check if R1 is zero.
@1
D=M
@END
D;JEQ

// Use repeated addition to multiply.
(LOOP)
@1
D=M
@2
M=D+M
@0
M=M-1
D=M
@LOOP
D;JNE

// End the program.
(END)
@END
0;JMP
