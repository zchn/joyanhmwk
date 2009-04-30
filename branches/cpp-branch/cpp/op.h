#ifndef _OP_H_
#define _OP_H_

#define OUT_OUT(x) {codeblock[current_pc]=(x);current_pc++;}
/* #define OUT_OUT(x) {printf("%d\n",x);} */
#define OUT_OUT2(x,y) {OUT_OUT(x);OUT_OUT(y);}

#define OUT_ADD OUT_OUT(0)
#define OUT_INC OUT_OUT(1)
#define OUT_ANDX OUT_OUT(2)
#define OUT_ASSIGN OUT_OUT(3)
#define OUT_CONSTANT(x) {OUT_OUT(4);OUT_OUT(x);}
#define OUT_CONTINUEJ OUT_OUT(5)
#define OUT_DIVIDE OUT_OUT(6)
#define OUT_DOX(x) {OUT_OUT(7);OUT_OUT(x);}
#define OUT_EQUAL OUT_OUT(8)
#define OUT_ESVAR(x) {OUT_OUT(9);OUT_OUT(x);}
#define OUT_ESVAR_VALUE(x) {OUT_OUT(10);OUT_OUT(x);}
#define OUT_FBEGIN(x,y,z) {OUT_OUT(11);OUT_OUT(x);OUT_OUT(y);OUT_OUT(z);}
#define OUT_FCALL(x) OUT_OUT2(12,x)
#define OUT_FCALLBEGIN(x) OUT_OUT2(13,x)
#define OUT_FEND(x) OUT_OUT2(14,x)
#define OUT_FIELD(x) OUT_OUT2(15,x)
#define OUT_GOTOX(x) OUT_OUT2(16,x)
#define OUT_GREATER OUT_OUT(17)
#define OUT_GREATEREQUAL OUT_OUT(18)
#define OUT_INDEX(x,y) {OUT_OUT(19);OUT_OUT(x);OUT_OUT(y);}
#define OUT_LESS OUT_OUT(20)
#define OUT_LESSEQUAL OUT_OUT(21)
#define OUT_LOCVAR(x) OUT_OUT2(22,x)
#define OUT_LOCVAR_VALUE(x) OUT_OUT2(23,x)
#define OUT_MAINBEGIN(x,y,z,m) {OUT_OUT(24);OUT_OUT(x);OUT_OUT(y);OUT_OUT(z);OUT_OUT(m);}
#define OUT_MAINEND OUT_OUT(25)
#define OUT_MINUS OUT_OUT(26)
#define OUT_MODULO OUT_OUT(27)
#define OUT_MULTIPLY OUT_OUT(28)
#define OUT_NEXTLINE OUT_OUT(29)
#define OUT_NOTEQUAL OUT_OUT(30)
#define OUT_NOTX OUT_OUT(31)
#define OUT_ORX OUT_OUT(32)
#define OUT_READCHAR OUT_OUT(33)
#define OUT_READINTX OUT_OUT(34)
#define OUT_RETURNF(x,y) {OUT_OUT(35);OUT_OUT2(x,y);}
#define OUT_SUBTRACT OUT_OUT(36)
#define OUT_DEC OUT_OUT(37)
#define OUT_VALUE OUT_OUT(38)
#define OUT_WRITECHAR OUT_OUT(39)
#define OUT_WRITEINTX OUT_OUT(40)
#define OUT_POPS OUT_OUT(41)
#define OUT_ASSIGNL(x) OUT_OUT2(42,x)
#define OUT_VALUEL(x) OUT_OUT2(43,x)

#endif /* _OP_H_ */
