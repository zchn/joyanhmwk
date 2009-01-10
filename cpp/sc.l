%{
#include <stdio.h>
#include <string.h>
#include "symtab.h"
extern int* codeblock;
#include "backpatch.h"
#include "y.tab.h"
int lineno;
extern symstack_head_t *main_symstack;
extern symtab_head_t *main_symtab;/* 主（当前）符号表  */
extern symtab_head_t *deleted_symtab;/* 刚刚摘下的符号表 */
extern int current_scope;
%}

MACRO_NUMBER ([[:digit:]]+)
MACRO_ID ([_[:alpha:]][_[:alnum:]]*)
%x COMMENT
%%
<COMMENT>.|\n { /* keep going */ }
<COMMENT>"*/" { BEGIN(0); }
"/*"          { BEGIN(COMMENT); }
[ \t\r] ;
\n {lineno++;}
printf {return PRINTF;}
println {return PRINTLN;}
putchar {return PUTCHAR;}
getchar {return GETCHAR;}
int {return INT;}
void {return VOID;}
char {return CHAR;}
auto {return AUTO;}
static {return STATIC;}
return {return RETURN;}
struct {return STRUCT;}
if {return IF;}
else {return ELSE;}
while {return WHILE;}
for {return FOR;}
break {return BREAK;}
continue {return CONTINUE;}
\|\| {return LOGOR;}
\&\& {return LOGAND;}
\=\= {return LOGEQU;}
\!\= {return LOGNEQ;}
\< {return LESSTHAN;}
\> {return MORETHAN;}
\<\= {return LESSEQU;}
\>\= {return MOREEQU;}
\-\> {return POINTTO;}
\{ {push_symstack(main_symstack, main_symtab->next); current_scope++; return '{';}
\} {
	deleted_symtab = main_symtab->next;
	split_symtab(pop_symstack(main_symstack),deleted_symtab);
	current_scope--;
	return '}'; }
\'.\' {yylval.num_val=yytext[1]; return CHARACTER;}
{MACRO_NUMBER} {yylval.num_val=atof(yytext); return NUM;}
{MACRO_ID} {yylval.id_val=strdup(yytext); return ID;}
, {return yytext[0];}
. {return yytext[0];}

%%

