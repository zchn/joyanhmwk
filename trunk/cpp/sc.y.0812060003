/***************************
  Yacc源程序的一般格式是：

    说明部分

    ％％

    语法规则部分

    ％％

    程序段部分

****************************/
%{

#include <stdio.h>

#include "symtab.h"
#include "allocvar.h"
#include "allocfunc.h"
#include "op.h"
#include "initall.h"

void yyerror(const char *);
extern int lineno;
char *errtext_ptr;
%}

%union {
	char *id_val;
	int num_val;
	int attrib_val;
	symtab_node_t *psymnode;
	struct {
		symtab_node_t *psymnode;
	} dec_type;
	symtab_node_t *exp_type;
	struct {
		int codeoffset;/*翻译出来的代码的起始地址*/
		symtab_node_t *offsetvar;/*若是array类型的var，此域记录其offset*/
		symtab_node_t *retvar;
	} exexp_type;
}

%token MAIN PRINTF INT VOID CHAR AUTO STATIC
%token <num_val> NUM CHARATER
%token <id_val> ID 

%type <num_val> constant
%type <dec_type> declarator direct_delarator
%type <dec_type> declarator_list 
%type <dec_type> type_specifier struct_specifier delaration_specifier
%type <attrib_val> storage_class_specifier
%type <offset_type> compound_statement
%type <exp_type> expression assignment_expression conditional_expression logical_expression
%type <exp_type> binary_expression relational_expression shift_expression arithmetic_exp
%type <exp_type> cast_expression unary_expression postfix_expression primary_expression

%right '='

%left LOGOR
%left LOGAND
%left LOGEQU LOGNEQ

%left MORETHAN LESSTHAN MOREEQU LESSEQU

%left '+' '-'
%left '*' '/'

%%
cpp_prog:
	translation_unit {
		/*这里填入调用mainbegin、mainend和callmain的代码*/
	}
;
translation_unit:
	external_declare {}
	| translate_unit external_declare {}
;
external_declare:
	function_defination {}
	| declaration {}
;

declaration:
	declaration_specifiers_sup declarator_list ';' {
		$$ = $2;
		allocmemory($2.psymhead);
		splice_symtab($2.psymhead,main_symtab);
	}
;
declarator_list:
	declarator {
		symtab_node_t *tmpsymhead = init_symtab();
		if(find_symnode_by_name($1.psymnode->name,main_symtab)){
			errtext_ptr = $1.psymnode->name;
			yyerror("Variable Redefination:");
		}
		insert_symtab($1.psymnode,tmpsymhead);
		$$.psymhead = tmpsymhead;
	}
	| declarator_list ',' declarator {
		if(find_symnode_by_name($3.psymnode->name,main_symtab)
			|| find_symnode_by_name($3.psymnode->name,$1.psymhead)){
			errtext_ptr = $1.psymnode->name;
			yyerror("Variable Redefination:");
		}
		insert_symtab($3.psymnode,$1.psymhead);
		$$ = $1;
	}
;
declarator:
	direct_declarator {
		$$ = $1;
	}
;
direct_declarator:
	ID {
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = $1;
		tmp->scope = current_scope;
		tmp->type = TYPE_VAR;
		tmp->extra.var.vartype = current_type;
		$$.psymnode = tmp;
	}
	| array_declarator {
		$$ = $1;
	}
;
array_declarator:
	ID array_dimdec_list {
		symtab_node_t *tmp = get_new_symnode();
                tmp->name = $1;
                tmp->scope = current_scope;
                tmp->type = TYPE_VAR;
                tmp->extra.var.vartype = $2.psymnode;
                $$.psymnode = tmp;
        }
;
array_dimdec_list:
	'[' constant ']' {
                symtab_node_t *tmp = get_new_symnode();
                tmp->name = "czj";
                tmp->scope = current_scope;
                tmp->type = TYPE_ARRAY;
		tmp->width = $2 * current_type->width;
                tmp->extra.array.elemtype = current_type;
		tmp->extra.array.count = $2;
                $$.psymnode = tmp;
	}
	| array_dimdec_list '[' constant ']' {
                symtab_node_t *tmp = get_new_symnode();
                tmp->name = "czj";
                tmp->scope = current_scope;
                tmp->type = TYPE_ARRAY;
		tmp->width = $3 * $1.psymnode->width;
                tmp->extra.array.elemtype = $1.psymnode;
		tmp->extra.array.count = $3;
                $$.psymnode = tmp;
	}
;
declaration_specifiers_sup:
	declaration_specifiers {
		current_type = $1.psymnode;
	}
;
declaration_specifiers:
	storage_class_specifier type_specifier {
		$$ = $2;
	}
;
storage_class_specifier:
		/*empty perform as auto*/
	| AUTO
	| STATIC
;
type_specifier:
	INT {
		$$.psymnode = INT_SYMNODE_POINTER;
	}
	| struct_specifier {
		$$ = $1;
	}
;
struct_specifier:
	struct_defination {
		$$ = $1;
	}
	| STRUCT ID {
		symtab_node_t *tmp = find_symnode_by_name($2,main_symtab);
		if(tmp == NULL || tmp->type != TYPE_STRUCT){
			errtext_ptr = $2;
			yyerror("Cannot find struct named ");
		}
		$$.psymnode = tmp;
	}
;
struct_defination:
	STRUCT ID '{' struct_declaration_list '}' {
		allocmemberoffset($4.psymhead);
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = $2;
		tmp->type = TYPE_STRUCT;
		tmp->scope = current_scope;
		tmp->extra.struc.elemlist = $4.psymhead;
		tmp->width = sum_all_width(tmp->extra.struc.elemlist);
		$$.psymnode = tmp;
	}
	| STRUCT '{' struct_declaration_list '}' {
		alocmemberoffset($3.psymhead);
                symtab_node_t *tmp = get_new_symnode();
                tmp->name = "czj";
                tmp->type = TYPE_STRUCT;
                tmp->scope = current_scope;
                tmp->extra.struc.elemlist = $4.psymhead;
		tmp->width = sum_all_width(tmp->extra.struc.elemlist);
                $$.psymnode = tmp;
        }
;
struct_declaration_list:
	struct_declaration {
		$$ = $1;
	}
	| struct_declaration_list struct_declaration {
		splice_symtab($2.psymhead,$1.psymhead);
		$$ = $1;
	}
;
struct_declaration:
	type_specifier_sup declarator_list ';'{
		$$ = $2;
	}
;
type_specifier_sup:
	type_specifier {
		current_type = $1.psymnode;
	}
;

function_defination:
	function_defination_head compound_statement {
	        deleted_symtab = main_symtab->next;
		symtab_split(pop_symstack(main_symstack),deleted_symtab);
		$1->extra.func.offset = $2.offset;
	}
;
function_defination_head:
	INT ID '(' parameter_list ')' {
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = $2;
		tmp->type = TYPE_FUNC;
		tmp->scope = SCOPE_GLOBAL;
		tmp->width = 0;
		tmp->extra.func.rettype = INT_TYPE_POINTER;
		tmp->extra.func.paramlength = sum_all_width($4.psymhead);
		allocfuncparam($4.psymhead);
		push_symstack(main_symstack, main_symtab->next);
		splice_symtab($4.psymhead,main_symtab);
		tmp->extra.func.offset = 0;
		$$ = tmp;
	}
;
parameter_list:
        parameter_declaration {
		symtab_head_t *tmpsymhead = init_symtab();
		insert_symtab($1.psymtab,tmpsymhead);
		$$.psymhead = tmpsymhead;
	}
        | parameter_list ',' parameter_declaration {
		insert_symtab($3.psymtab,$1.psymhead);
                $$ = $1;
        }
;
parameter_declaration:
	declaration_specifiers_sup declarator {
		$$ = $1;
	}
;

compound_statement:
	'{' block_item_list '}'
	| '{' '}'
;
declaration_list:
	declaration {}
	| declaration_list declaration {}
;
block_item_list:
	declaration_list
	| statement_list
	| block_item_list declaration_list
	| block_item_list statement_list
;
statement_list:
	statement
	| statement_list statement
;
statement:
	printf_statement
	| expression_statement
;
expression_statement:
	expression ';'
	| ';'
;
printf_statement:
	PRINTF '(' expression ')' ';' {
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_WRITEINTX;
	}
;
expression:
	assignment_expression {
		$$=$1;
	}
	| expression ',' assignment_expression {
		$$=$3;
	}
;
assignment_expression:
	conditional_expression {
		$$=$1;
	}
	| unary_expression '=' assignment_expression {
		if($1.retvar->extra.var.vartype->type==TYPE_ARRAY){
			OUT_LOCVAR_VALUE($1.offsetvar->extra.var.offset);
			VALUE;
		}else{
			OUT_LOCVAR($1.retvar->extra.var.offset);
		}
		OUT_LOCVAR_VALUE($3->offset);
		OUT_ASSIGNL($1.retvar->extra.var.vartype->width);
		OUT_POPS;
		$$=$3;
	}
;
conditional_expression:
	logical_expression {
		$$ = $1;
	}
;
logical_expression:
	binary_expression {
		$$ = $1;
	}
	| logical_expression LOGOR logical_expression
	| logical_expression LOGAND logical_expression
	| logical_expression LOGEQU logical_expression
	| logical_expression LOGNEQ logical_expression
;
binary_expression:
	relational_expression {
		$$ = $1;
	}
;
relational_expression:
	shift_expression {
		$$ = $1;
	}
	| relational_expression MORETHAN relational_expression
	| relational_expression LESSTHAN relational_expression
	| relational_expression MOREEQU relational_expression
	| relational_expression LESSEQU relational_expression
;
shift_expression:
	arithmetic_exp {
		$$ = $1;
	}
;
arithmetic_exp:
	cast_expression	{
		$$ = $1;
	}	
	| arithmetic_exp '+' arithmetic_exp {
		$$ = alloc_loc_and_insert(TYPE_INT,NULL);
		OUT_LOCVAR($$->offset);
		OUT_LOCVAR_VALUE($1->offset);
		OUT_LOCVAR_VALUE($3->offset);
		OUT_ADD;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| arithmetic_exp '-' arithmetic_exp {
		$$ = alloc_loc_and_insert(TYPE_INT,NULL);
		OUT_LOCVAR($$->offset);
		OUT_LOCVAR_VALUE($1->offset);
		OUT_LOCVAR_VALUE($3->offset);
		OUT_MINUS;
		OUT_ADD;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| arithmetic_exp '*' arithmetic_exp {		
		$$ = alloc_loc_and_insert(TYPE_INT,NULL);
		OUT_LOCVAR($$->offset);
		OUT_LOCVAR_VALUE($1->offset);
		OUT_LOCVAR_VALUE($3->offset);
		OUT_MULTIPLY;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| arithmetic_exp '/' arithmetic_exp {
		$$ = alloc_loc_and_insert(TYPE_INT,NULL);
		OUT_LOCVAR($$->offset);
		OUT_LOCVAR_VALUE($1->offset);
		OUT_LOCVAR_VALUE($3->offset);
		OUT_DIVIDE;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| arithmetic_exp '%' arithmetic_exp {
		$$ = alloc_loc_and_insert(TYPE_INT,NULL);
		OUT_LOCVAR($$->offset);
		OUT_LOCVAR_VALUE($1->offset);
		OUT_LOCVAR_VALUE($3->offset);
		OUT_MODULO;
		OUT_ASSIGN;
		OUT_POPS;
	}
;
cast_expression:
	unary_sup_expression {
		$$ = $1;
	}
;
unary_sup_expression:
	noarray_expression {
		$$=$1;
	}
	| '-' unary_sup_expression {
		$$ = alloc_loc_and_insert(TYPE_INT,NULL);
                OUT_LOCVAR($$->offset);
                OUT_LOCVAR_VALUE($2->offset);
                OUT_MINUS;
                OUT_ASSIGN;
		OUT_POPS;
        }
	| '!' unary_sup_expression
;
noarray_expression:
	unary_expression {
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		if($1.retvar->extra.var.vartype->type==TYPE_ARRAY){
			OUT_LOCVAR_VALUE($1.offsetvar->extra.var.offset);
			OUT_VALUE;
		}else{
			if($1.retvar->scope == SCOPE_GLOBAL){
				OUT_ESVAR_VALUE($1.retvar->extra.var.offset);
			}else{
				OUT_LOCVAR_VALUE($1.retvar->extra.var.offset);
			}
		}
		OUT_ASSIGN;
		OUT_POPS;
	}
;
unary_expression:
	postfix_expression {
		$$ = $1;
	}
;
postfix_expression:
	primary_expression {
		$$ = $1;
	}
	| postfix_expression '[' expression ']' {
		if($1.retvar->extra.var.vartype->type != TYPE_ARRAY){
			errtext_ptr = $1.retvar->name;
			yyerror("Can't convert to array:");
			$$ = $1;
		}else{
			symtab_node_t *tmp = $1.retvar;
			tmp->extra.var.vartype = tmp->extra.var.vartype->extra.array.elemtype;
			OUT_LOCVAR($1.offsetvar->extra.var.offset);
			OUT_LOCVAR_VALUE($1.offsetvar->extra.var.offset);
			OUT_CONSTANT(tmp->extra.var.vartype->width);
			OUT_LOCVAR_VALUE($3->extra.var.offset);
			OUT_MULTIPLY;
			OUT_ADD;
			OUT_ASSIGN;
			OUT_POPS;
			$$.retvar = tmp;
			$$.offsetvar = $1.offsetvar;
		}
		/**/
	}
	| postfix_expression '.' ID {
		if($1.retvar->extra.var.vartype->type != TYPE_SRTUCT){
			errtext_ptr = $1.retvar->name;
                        yyerror("Can't convert to struct:");
                        $$ = $1;
		}else{
			symtab_node_t *tmp = $1.retvar;
			tmp = find_symnode_by_name($3,tmp->extra.struc.elemlist);
			if(tmp == NULL){
				errtextptr = $3;
				yyerror("No such member variable:");
				$$ = $1;
			}else{
                        	OUT_LOCVAR($1.offsetvar->extra.var.offset);
                        	OUT_LOCVAR_VALUE($1.offsetvar->extra.var.offset);
                        	OUT_CONSTANT(tmp->extra.var.offset);
                        	OUT_ADD;
                        	OUT_ASSIGN;
                        	OUT_POPS;
                        	$$.retvar = tmp;
                        	$$.offsetvar = $1.offsetvar;
			}
		}
		/*用新建一个symtab_node_t来保存加点后的变量*/
	}
;
primary_expression:
	ID {
		tmp = find_symnode_by_name($1,main_symtab);
		if(tmp == NULL){
			errtext_ptr = $1;
			yyerror("Undefined Variable");
			tmp=alloc_loc_and_insert(INT_TYPE_POINTER,$1);
			$$.retvar = tmp;
			$$.offsetvar = NULL;
		}else{
			$$.retvar = get_new_symnode();
                	memcpy($$.retvar,tmp,sizeof(tmp));
			if($$.retvar->extra.var.vartype->type == TYPE_INT ||
				$$.retvar->extra.var.vartype->type == TYPE_CHAR){
				$$.offsetvar = NULL;
			}else{
				$$.offsetvar = alloc_loc_and_insert(INT_TYPE_POINTER,"czj");
				OUT_LOCVAR($$.offsetvar->extra.var.offset);
				OUT_LOCVAR($$.retvar->extra.var.offset);
				OUT_ASSIGN;
				OUT_POPS;
			}
		}
	}
		
	| constant {
		symtab_node_t *tmp=alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR(tmp->offset);
		OUT_CONSTANT($1);
		OUT_ASSIGN;
		OUT_POPS;
		$$.retvar=get_new_symnode();
		memcpy($$.retvar,tmp,sizeof(tmp));
		$$.offsetvar=NULL;
	}
	| '(' expression ')' {
		$$.retvar=$2;
		$$.offsetvar=NULL;
	}
;
argument_expression_list:
	| assignment_expression {
		OUT_LOCVAR_VALUE($1->extra.var.offset);
	}
	| argument_expression_list ',' assignment_expression {
		OUT_LOCVAR_VALUE($1->extra.var.offset);
	}
;
constant:
	NUM {
		$$=$1;
	}
	| CHARACTER {
		$$=$1;
	}
;
%%
extern FILE *yyin;
extern char *yytext;
void yyerror(const char *msg)
{
	error_count++;
	printf("ERROR[%d]:line %d,%s:%s.\n",error_count,lineno,msg,errtext_ptr);
}
int main(int argc, char **argv)
{
	FILE *compile_out;;
	if(argc > 1){
		yyin = fopen( argv[1], "r" );
	}
	else{
		yyin = stdin;
	}

	if(argc > 2){
		compile_out = fopen( argv[2], "w" );
	}
	else{
		compile_out = stdout;
	}
	lineno=1;
        init_all();
	yyparse();
	output_code(compile_out);
	return 0;
}
