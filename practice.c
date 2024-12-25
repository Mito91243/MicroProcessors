
/*
void AGAIN() {
    counter = 1000
    sum = 0
    sum = sum + 9
    counter = counter - 1
    BNE AGAIN()
}
MOV R4, R0
*/

//! Write a program to place value 0x55 into 100 consecutive bytes of RAM locations.

// RAM_ADDR EQU 0x20000000 
// EXPORT __main 
// AREA EXAMPLE4_2, CODE, READONLY __main
// MOV RAM_ADDR_Shift , #8
// MOV RAM_ADDR_Counter , #0
// MOV RAM_ADDR_S , #8

/*
AGAIN   MOV R0 , #0x55
        MOV  , RAM_ADDR

*/