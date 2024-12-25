/*
This header file contains some usefull macros for bitwise operations on registers.
Which simplifies the code and makes it more readable.
*/

#ifndef __BITOP_H__
#define	__BITOP_H__

#define FALSE 0
#define TRUE 1
#define NULL 0
#define __IO volatile
typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int 		uint32_t;
typedef unsigned long int	uint64_t;
typedef float float32_t;


#define MAX_REG         (0xffffffffUL)
#define BIT0                (1<<0)
#define BIT1                (1<<1)
#define BIT2                (1<<2)
#define BIT3                (1<<3)
#define BIT4                (1<<4)
#define BIT5                (1<<5)
#define BIT6                (1<<6)
#define BIT7                (1<<7)

#define SET_BIT(X,BIT_NO)   (X)|=(1<<(BIT_NO))
#define CLR_BIT(X,BIT_NO)   (X)&=~(1<<(BIT_NO))
#define TOG_BIT(X,BIT_NO)   (X)^=(1<<(BIT_NO))
#define READ_BIT(X,BIT_NO)  (((X)&(1<<(BIT_NO)))>>(BIT_NO))
#define CHK_BIT(X, BIT_NO)  (((X)&(1<<BIT_NO))==1)
#define NCHK_BIT(X, BIT_NO) (((X)&(1<<BIT_NO))==0)

#define SET(X)				((X)=1)
#define CLR(X)				(X=0)
#define TOG(X)				(X^=1)
#define READ(X)				(X)
#define CHK(X)				(((X)&(1))==1)
#define NCHK(X)				((((X)&(1))==0))

#define SET_MBIT(X, M, V)           (X)=(((X)&((MAX_REG)^(M)))|((V)&(M)))
#define READ_MBIT(X, M)		        ((X)&(M))
#define SET_MBIT_SHF(X, M, V, S)    SET_MBIT(X, (M)<<(S), (V)<<(S))

#define SET_REG(X)          (X)=0xFF
#define CLR_REG(X)          (X)=0x00
#define FLP_REG(X)          (X)~=(X)


#endif	/* BITOP_H */

