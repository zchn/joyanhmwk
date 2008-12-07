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
	struct {
		symtab_node_t *psymnode;
	} dec_type;
	struct {
		int offset;
		symtab_node_t *retvar;
	} exp_type;
	symtab_node_t *typedefname;
}

%token MAIN PRINTF INT VOID CHAR AUTO STATIC TYPEDEF
%token <num_val> NUM CHARATER
%token <id_val> ID 
%token <typedefname> TYPEDEFNAME

%type <num_val> constant
%type <dec_type> declarator direct_delarator
%type <dec_type> declarator_list 
%type <dec_type> type_specifier struct_specifier
%type <offset_type> compound
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
function_defination:
	declaration_specifiers declarator compound_statement {
		/*将declaration_specifiers收集起来的返回值类型节点赋给declarator的节点*/
		$2.psymnode->extra.func.rettype = $1.psymnode;
	}
;
declaration_list:
	declaration {}
	| declaration_list declaration {}
;
declaration:
	declaration_specifiers declarator_list ';'
;
declaration_specifiers:
	storage_class_specifier
	| declaration_specifiers storage_class_specifier
	| type_specifier
	| declaration_specifiers type_specifier
;
storage_class_specifier:
	AUTO
	| STATIC
	| TYPEDEF
;
type_specifier:
	VOID {
		$$.psymnode = NULL;
	}
	| INT {
		$$.psymnode = find_symnode_by_name("int",main_symtab);
	}
	| struct_specifier {
		$$.psymnode = $1;
	}
	| TYPEDEFNAME {
		$$.psymnode = $1->extra.alias.origin;
	}
;
struct_specifier:
	STRUCT ID '{' struct_declaration_list '}' {
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = $2;
		tmp->type = TYPE_STRUCT;
		tmp->scope = current_scope;
		tmp->extra.struc.elemlist = deleted_symtab;
		insert_symnode(tmp,main_symtab);
		$$.psymnode = tmp;
	}
	| STRUCT '{' struct_declaration_list '}' {
                symtab_node_t *tmp = get_new_symnode();
                tmp->name = "czj";
                tmp->type = TYPE_STRUCT;
                tmp->scope = current_scope;
                tmp->extra.struc.elemlist = deleted_symtab;
                insert_symnode(tmp,main_symtab);
                $$.psymnode = tmp;
        }
	| STRUCT ID {
		symtab_node_t *tmp = find_symnode_by_name($2,main_symtab);
		$$.psymnode = tmp;
	}
;
struct_declaration_list:
	struct_declaration {}
	| struct_declaration_list struct_declaration {}
;
struct_declaration:
	type_specifier declarator_list ';'
;
declarator_list:
	declarator
	| declarator_list declarator
;
declarator:
	direct_declarator
;
direct_declarator:
	ID {
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = $1;
		tmp->scope = current_scope;
		tmp->type = TYPE_VAR;
		tmp->extra.var.vartype = NULL;
		insert_symnode(tmp,main_symtab);
		$$.psymnode = tmp;
	}
	| '(' declarator ')'{ $$ = $2; }
	| direct_declarator '[' constant ']' {
                symtab_node_t *tmp = get_new_symnode();
                tmp->name = "czj";
                tmp->scope = current_scope;
                tmp->type = TYPE_ARRAY;
                tmp->extra.array.elemtype = NULL;
		tmp->extra.array.count = $3;
                insert_symnode(tmp,main_symtab);
		switch($1.psymnode->type){
		case TYPE_VAR:
			$1.psymnode->extra.var.vartype = tmp;
			break;
		case TYPE_ARRAY:
			$1.psymnode->extra.array.elemtype = tmp;
			break;
		default:
			yyerror("Invalid Array defination");
                $$.psymnode = tmp;
 
	| direct_declarator '(' parameter_list ')'
;
parameter_list:
	parameter_declaration
	parameter_list ',' parameter_declaration
;
parameter_declaration:
	declaration_specifiers declarator
;
compound_statement:
	'{' block_item_list '}'
	| '{' '}'
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
		OUT_LOCVAR_VALUE($3->offset);
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
	| primary_expression '=' assignment_expression {
		if($1->attrib==ATTR_CONST){
			yyerror("Can not assign to const");
		}else{
			OUT_LOCVAR($1->offset);
			OUT_LOCVAR_VALUE($3->offset);
			OUT_ASSIGN;
			OUT_POPS;
		}
		$$=$1;	
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
	unary_expression {
		$$=$1;
	}
;
unary_expression:
	postfix_expression {
		$$=$1;
	}
	| '-' unary_expression {
		$$ = alloc_loc_and_insert(TYPE_INT,NULL);
                OUT_LOCVAR($$->offset);
                OUT_LOCVAR_VALUE($2->offset);
                OUT_MINUS;
                OUT_ASSIGN;
		OUT_POPS;
        }
	| '!' unary_expression
;
postfix_expression:
	primary_expression {
		$$ = $1;
	}
	| postfix_expression '[' expression ']'
	| postfix_expression '(' argument_expression_list ')'
	| argument-expression-list '.' ID
	| argument-expression-list '-' '>' ID
;
primary_expression:
	ID {
		symtab_node_t *tmp = find_symnode_by_name($1,local_symtab);
		if(tmp == NULL){
			tmp = find_symnode_by_name($1,global_symtab);
			if(tmp == NULL){
				errtext_ptr=$1;
				yyerror("Undefined Variable");
				tmp=alloc_loc_and_insert(TYPE_INT,$1);
				$$=tmp;
			}else{
				$$=tmp;
			}
		}else{
			$$=tmp;
		}
	}
		
	| constant {
		symtab_node_t *tmp=alloc_loc_and_insert(TYPE_INT,NULL);
		tmp->attrib=ATTR_CONST;
		OUT_LOCVAR(tmp->offset);
		OUT_CONSTANT($1);
		OUT_ASSIGN;
		OUT_POPS;
		$$=tmp;
	}
	| '(' expression ')' {
		$$=$2;
	}
;
argument_expression_list:
	| assignment_expression
	| argument_expression_list ',' assignment_expression
;
constant:
	NUM
	| CHARACTER
;








/*=====================================================*/




prog_prelude:
	MAIN '(' ')' {
			symtab_node_t *tmp=get_new_symnode();
			tmp->name=strdup("main");
			tmp->type=TYPE_FUNC;
			tmp->offset=current_pc;
			tmp->scope=SCOPE_GLOBAL;
			tmp->other=(symfunc_t *)malloc(sizeof(symfunc_t));
			((symfunc_t *)(tmp->other))->locvar_cnt=0;
			((symfunc_t *)(tmp->other))->tmpvar_cnt=0;
			((symfunc_t *)(tmp->other))->symtab=init_symtab();
			insert_symnode(tmp,global_symtab);
			set_local_symtab(((symfunc_t *)(tmp->other))->symtab);
			OUT_MAINBEGIN(0,0,0,lineno);
}
;
compound_statement:
                        '{' declare_list statement_list '}' {OUT_MAINEND;fill_mainbegin();}
;
declarator:
	INT {$$=TYPE_INT;}
;
declarator_list:
	declarator ID {
		$$=$1;
		symtab_node_t * tmp=find_symnode_by_name($2,local_symtab);
		if(tmp != NULL){
			errtext_ptr=$2;
			yyerror("Variable redefination");
		}else{
			alloc_loc_and_insert($1,$2);
		}
	}
	| declarator_list ',' ID {
		$$ = $1;
		symtab_node_t * tmp=find_symnode_by_name($3,local_symtab);
		if(tmp != NULL){
			errtext_ptr=$3;
			yyerror("Variable redefination");
		}else{
			alloc_loc_and_insert($1,$3);
		}
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
