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
#include "backpatch.h"

void yyerror(const char *);
extern int lineno;
char *errtext_ptr;
%}

%union {
	char *id_val;
	int num_val;
	int attrib_val;
	struct {
		symtab_head_t *psymhead;
	} declst_type;
	struct {
		symtab_node_t *psymnode;
	} dec_type;
	symtab_node_t *exp_type;
	struct {
		symtab_node_t *offsetvar;/*若是array类型的var，此域记录其offset*/
		symtab_node_t *retvar;
	} exexp_type;
	struct {
		backlist_head_t *breaklist;
		backlist_head_t *continuelist;
	}  stattype;
	int notype;
	struct {
		int gotooffaddr;
		symtab_node_t *retvar;
	} boolcheck_type;
	struct {
		int gotooffaddr;
		int falsegotoaddr;
		int truegotoaddr;
		int pc;
	} ctlstat_type;
}

%token MAIN PRINTF PRINTLN INT VOID CHAR AUTO STATIC STRUCT RETURN IF ELSE WHILE FOR
%token BREAK CONTINUE PUTCHAR GETCHAR
%token <num_val> NUM CHARACTER
%token <id_val> ID 

%type <num_val> constant

%type <dec_type> declarator direct_declarator
%type <dec_type> array_declarator array_dimdec_list declaration_specifiers_sup
%type <dec_type> declaration_specifiers type_specifier struct_specifier
%type <dec_type> function_defination_head parameter_declaration declaration_list
%type <dec_type> struct_reference

%type <notype> storage_class_specifier
%type <stattype> while_statement
%type <notype> type_specifier_sup function_defination argument_expression_list
%type <notype> cpp_prog translation_unit external_declare start_part
%type <stattype> if_statement return_statement

%type <declst_type> struct_declaration_list struct_declaration parameter_list
%type <declst_type> declaration declarator_list

%type <stattype> compound_statement block_item_list statement_list
%type <stattype> statement expression_statement printf_statement println_statement
%type <stattype> break_statement continue_statement

%type <exp_type> expression assignment_expression expression_or_null
%type <exp_type> conditional_expression logical_expression
%type <exp_type> binary_expression relational_expression
%type <exp_type> shift_expression arithmetic_exp
%type <exp_type> cast_expression unary_sup_expression
%type <exp_type> noarray_expression

%type <boolcheck_type> logical_expression_orcheck logical_expression_andcheck

%type <exexp_type> unary_expression postfix_expression primary_expression funccall_head

%type <ctlstat_type> if_head insert_goto get_pc while_head for_head

%right '='

%left LOGOR
%left LOGAND
%left LOGEQU LOGNEQ

%left MORETHAN LESSTHAN MOREEQU LESSEQU

%left '+' '-'
%left '*' '/'

%%
cpp_prog:
	start_part translation_unit {
		symtab_node_t *tmp = find_symnode_by_name("main",main_symtab);
		if(tmp == NULL){
			errtext_ptr = "main";
			yyerror("Cannot find main func");
			errtext_ptr = NULL;
		}else{
			codeblock[1] = get_esvar_cnt();
			codeblock[12] = tmp->extra.func.offset - 11;
		}
	}
;
start_part:{
		OUT_MAINBEGIN(0,0,0,0);
		OUT_FCALLBEGIN(INT_SIZE);
		OUT_CONSTANT(0);
		OUT_CONSTANT(0);
		OUT_FCALL(0);
		OUT_POPS;
		OUT_MAINEND;
	}
;
translation_unit:
	external_declare {}
	| translation_unit external_declare {}
;
external_declare:
	declaration {}
	| function_defination {}
;

declaration:
	declaration_specifiers_sup declarator_list ';' {
		$$ = $2;
		allocmemory($2.psymhead);
		splice_symtab($2.psymhead,main_symtab);
	}
	|  declaration_specifiers_sup declarator_list error{
		errtext_ptr = NULL;
		yyerror("';' expected.");
		$$ = $2;
                allocmemory($2.psymhead);
                splice_symtab($2.psymhead,main_symtab);
	}
;
declarator_list:
	{ $$.psymhead = init_symtab();}
	| declarator {
		symtab_head_t *tmpsymhead = init_symtab();
		symtab_node_t *ret;
		if((ret = find_symnode_by_name($1.psymnode->name,main_symtab))
			&& ret->scope == current_scope){
			errtext_ptr = $1.psymnode->name;
			yyerror("Variable Redefination:");
			errtext_ptr = NULL;
		}
		insert_symnode($1.psymnode,tmpsymhead);
		$$.psymhead = tmpsymhead;
	}
	| declarator_list ',' declarator {
		symtab_node_t *ret;
		if((ret = find_symnode_by_name($3.psymnode->name,main_symtab))
			&& ret->scope == current_scope
			|| find_symnode_by_name($3.psymnode->name,$1.psymhead)){
			errtext_ptr = $3.psymnode->name;
			yyerror("Variable Redefination:");
			errtext_ptr = NULL;
		}
		insert_symnode($3.psymnode,$1.psymhead);
		$$ = $1;
	}
	| declarator_list declarator {
		errtext_ptr = $2.psymnode->name;
		yyerror("',' needed between declarators.");
		errtext_ptr = NULL;
		symtab_node_t *ret;
                if((ret = find_symnode_by_name($2.psymnode->name,main_symtab))
                        && ret->scope == current_scope
                        || find_symnode_by_name($2.psymnode->name,$1.psymhead)){
                        errtext_ptr = $2.psymnode->name;
                        yyerror("Variable Redefination:");
			errtext_ptr = NULL;
                }
                insert_symnode($2.psymnode,$1.psymhead);
                $$ = $1;
	}
;
declarator:
	direct_declarator {
		$$ = $1;
	}
	| '*' direct_declarator {
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = "czjpoin";
                tmp->scope = current_scope;
                tmp->type = TYPE_POINTER;
		tmp->width = INT_SIZE;
                tmp->extra.poin.ptype = $2.psymnode->extra.var.vartype;
		$2.psymnode->extra.var.vartype = tmp;
                //fprintf(stderr,"[DEBUG] set ID %s type to:%x\n",$1,current_type);
                $$ = $2;
	}
;
direct_declarator:
	ID {
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = $1;
		tmp->scope = current_scope;
		tmp->type = TYPE_VAR;
		tmp->extra.var.vartype = current_type;
		//fprintf(stderr,"[DEBUG] set ID %s type to:%x\n",$1,current_type);
		$$.psymnode = tmp;
	}
	| array_declarator {
		$$ = $1;
	}
	| '(' declarator ')'{
		$$ = $2;
	}
;
array_declarator:
	ID array_dimdec_list {
		symtab_node_t *tmp = get_new_symnode();
                tmp->name = $1;
                tmp->scope = current_scope;
                tmp->type = TYPE_VAR;
                tmp->extra.var.vartype = $2.psymnode;
		//fprintf(stderr,"[DEBUG] set ID %s type to:%x\n",$1,$2.psymnode);
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
	| '[' constant ']' array_dimdec_list {
                symtab_node_t *tmp = get_new_symnode();
                tmp->name = "czj";
                tmp->scope = current_scope;
                tmp->type = TYPE_ARRAY;
		tmp->width = $2 * $4.psymnode->width;
                tmp->extra.array.elemtype = $4.psymnode;
		tmp->extra.array.count = $2;
                $$.psymnode = tmp;
	}
;
declaration_specifiers_sup:
	declaration_specifiers {
		current_type = $1.psymnode;
		$$ = $1;
		//fprintf(stderr,"[DEBUG] set current_type to:%x\n",$1.psymnode);
	}
;
declaration_specifiers:
	storage_class_specifier type_specifier {
		$$ = $2;
	}
;
storage_class_specifier:
	{$$=current_scope;}	/*empty perform as auto*/
	| AUTO {$$=current_scope;}
	| STATIC {$$=0;}
;
type_specifier:
	INT {
		$$.psymnode = INT_TYPE_POINTER;
	}
	| struct_specifier {
		$$ = $1;
	}
	| CHAR {$$.psymnode=CHAR_TYPE_POINTER;}
	| VOID {$$.psymnode=INT_TYPE_POINTER;/*FIXME*/}
;
struct_specifier:
	STRUCT ID '{' struct_declaration_list '}' {
		allocmemberoffset($4.psymhead);
		symtab_node_t *tmp = find_symnode_by_name($2,main_symtab);
		if(tmp != NULL){
			errtext_ptr = $2;
			yyerror("Struct Redefination:");
			errtext_ptr = NULL;
		}
		tmp = get_new_symnode();
		tmp->name = $2;
		tmp->type = TYPE_STRUCT;
		tmp->scope = current_scope;
		tmp->extra.struc.elemlist = $4.psymhead;
		tmp->width = sum_all_width(tmp->extra.struc.elemlist);
		insert_symnode(tmp,main_symtab);
		$$.psymnode = tmp;
	}
	|  STRUCT '{' struct_declaration_list '}' {
		allocmemberoffset($3.psymhead);
                symtab_node_t *tmp = get_new_symnode();
                tmp->name = "czj";
                tmp->type = TYPE_STRUCT;
                tmp->scope = current_scope;
                tmp->extra.struc.elemlist = $3.psymhead;
		////fprintf(stderr,"[DEBUG]Struct NULL get elemlist:%x\n",$3.psymhead);
		tmp->width = sum_all_width(tmp->extra.struc.elemlist);
		insert_symnode(tmp,main_symtab);
                $$.psymnode = tmp;
        }
	| struct_reference {
		$$ = $1;
	}
;	
struct_reference:
	STRUCT ID {
		symtab_node_t *tmp = find_symnode_by_name($2,main_symtab);
		if(tmp == NULL){
			errtext_ptr = $2;
                        yyerror("Cannot find struct named ");
			errtext_ptr = NULL;
			$$.psymnode = INT_TYPE_POINTER;
		}else if(tmp->type != TYPE_STRUCT){
			errtext_ptr = $2;
			yyerror("The ID is not a struct: ");
			errtext_ptr = NULL;
			$$.psymnode = INT_TYPE_POINTER;
		}else{
			$$.psymnode = tmp;
		}
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
		split_symtab(pop_symstack(main_symstack),deleted_symtab);
		OUT_CONSTANT(0);
		OUT_RETURNF(current_func->extra.func.paramlength,
                                current_func->extra.func.rettype->width);
		codeblock[current_func->extra.func.offset+1] = get_locvar_cnt();
	}
;
function_defination_head:
	declaration_specifiers_sup ID '(' parameter_list ')' {
		if(current_scope != SCOPE_GLOBAL){
			errtext_ptr = $2;
			yyerror("Cannot define func in local scope:");
			errtext_ptr = NULL;
		}
		init_locpool();
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = $2;
		//fprintf(stderr,"[DEBUG] Got func :%s\n",$2);
		tmp->type = TYPE_FUNC;
		tmp->scope = SCOPE_GLOBAL;
		tmp->width = 0;
		tmp->extra.func.rettype = $1.psymnode;
		tmp->extra.func.paramlength = sum_all_width($4.psymhead);
		insert_symnode(tmp,main_symtab);
		allocfuncparam($4.psymhead);
		push_symstack(main_symstack, main_symtab->next);
		splice_symtab($4.psymhead,main_symtab);
		tmp->extra.func.offset = current_pc;

		OUT_FBEGIN(0,0,lineno);

		current_func=tmp;
		$$.psymnode = tmp;
	}
;
parameter_list:
	 {$$.psymhead=init_symtab();}
        |parameter_declaration {
		symtab_head_t *tmpsymhead = init_symtab();
		insert_symnode($1.psymnode,tmpsymhead);
		$$.psymhead = tmpsymhead;
	}
        | parameter_list ',' parameter_declaration {
		insert_symnode($3.psymnode,$1.psymhead);
                $$ = $1;
        }
;
parameter_declaration:
	declaration_specifiers_sup declarator {
		if($2.psymnode->extra.var.vartype->type == TYPE_ARRAY){
			symtab_node_t *tmp = get_new_symnode();
			tmp->name = "CZJ";
			tmp->type = TYPE_POINTER;
			tmp->scope = 1;
			tmp->width = INT_SIZE;
			tmp->extra.poin.ptype = $2.psymnode->extra.var.vartype->extra.array.elemtype;
			$2.psymnode->extra.var.vartype = tmp;
		}
		$2.psymnode->scope = 1;
		$$ = $2;
	}
;

compound_statement:
	'{' block_item_list '}'{$$=$2;}
	| '{' '}' {
		$$.breaklist = NULL;
		$$.continuelist = NULL;
	}
;
declaration_list:
	declaration {}
	| declaration_list declaration {}
;
block_item_list:
	declaration_list {
		$$.breaklist = NULL;
                $$.continuelist = NULL;
	}
	| statement_list {$$=$1;}
	| block_item_list declaration_list {
		$$=$1;
	}
	| block_item_list statement_list {
		if($1.breaklist == NULL)
			$1.breaklist = $2.breaklist;
		else
			splice_backlist($2.breaklist,$1.breaklist);
		$$.breaklist = $1.breaklist;
		if($1.continuelist == NULL)
			$1.continuelist = $2.continuelist;
		else
			splice_backlist($2.continuelist,$1.continuelist);
		$$.continuelist = $1.continuelist;
	}
;
statement_list:
	statement {
		$$ = $1;
	}
	| statement_list statement{
		if($1.breaklist == NULL)
                        $1.breaklist = $2.breaklist;
                else
                        splice_backlist($2.breaklist,$1.breaklist);
                $$.breaklist = $1.breaklist;
                if($1.continuelist == NULL)
                        $1.continuelist = $2.continuelist;
                else
                        splice_backlist($2.continuelist,$1.continuelist);
                $$.continuelist = $1.continuelist;
        }
;
statement:
	if_statement{
		$$ = $1;
	}
	| printf_statement{
		$$.breaklist = $$.continuelist = NULL;
	}
	| putchar_statement{
		$$.breaklist = $$.continuelist = NULL;
	}
	| println_statement {
		$$.breaklist = $$.continuelist = NULL;
	}
	| expression_statement {
		$$.breaklist = $$.continuelist = NULL;
	}
	| return_statement {
		$$.breaklist = $$.continuelist = NULL;
	}
	| compound_statement {
		$$ = $1;
	}
	| while_statement {
		$$.breaklist = $$.continuelist = NULL;
	}
	| for_statement {
		$$.breaklist = $$.continuelist = NULL;
	}
	| break_statement {
		$$ = $1;
	}
	| continue_statement {
		$$ = $1;
	}
;
putchar_statement:
	PUTCHAR '(' expression ')' ';'{
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_WRITECHAR;
	}
;
break_statement:
	BREAK ';' {
		OUT_GOTOX(2);
		$$.breaklist = init_backlist();
		backlist_node_t *tmp = get_new_backnode();
		tmp->offset = current_pc - 1;
		insert_backnode(tmp,$$.breaklist);
		$$.continuelist = NULL;
	}
;
continue_statement:
	CONTINUE ';' {
		OUT_GOTOX(2);
                $$.continuelist = init_backlist();
                backlist_node_t *tmp = get_new_backnode();
                tmp->offset = current_pc - 1;
                insert_backnode(tmp,$$.continuelist);
                $$.breaklist = NULL;
	}
;
for_statement:
	for_head get_pc expression_or_null ')' insert_goto get_pc statement insert_goto {
		codeblock[$5.gotooffaddr] = $1.pc - ($5.gotooffaddr-1);
		codeblock[$8.gotooffaddr] = $2.pc - ($8.gotooffaddr-1);
		codeblock[$1.truegotoaddr] = $6.pc - ($1.truegotoaddr-1);
		codeblock[$1.falsegotoaddr] = current_pc - ($1.falsegotoaddr-1);
		backpatch_dis($7.breaklist,current_pc + 1);
		backpatch_dis($7.continuelist,$2.pc + 1);
	}
; 
for_head:
	FOR '(' expression_or_null ';' get_pc expression_or_null ';'{
		if($6 == NULL){
			OUT_CONSTANT(1);
		}else{
			OUT_LOCVAR_VALUE($6->extra.var.offset);
		}
		OUT_DOX(INVALID_ADDR);
		$$.falsegotoaddr = current_pc - 1;
		OUT_GOTOX(INVALID_ADDR);
		$$.truegotoaddr = current_pc - 1;
		$$.pc = $5.pc;
	}
;
expression_or_null:
	expression {
		$$ = $1;
	}
	| {
		$$ = NULL;
	}
;
while_statement:
	while_head statement get_pc insert_goto {
		codeblock[$4.gotooffaddr] = $1.pc - $3.pc;
		codeblock[$1.gotooffaddr] = current_pc - ($1.gotooffaddr-1);
		backpatch_dis($2.breaklist,current_pc+1);
		backpatch_dis($2.continuelist,$1.pc+1);
	}
;
while_head:
	WHILE get_pc '(' expression ')'{
	        OUT_LOCVAR_VALUE($4->extra.var.offset);
                OUT_DOX(INVALID_ADDR);
                $$.gotooffaddr = current_pc-1;
		$$.pc = $2.pc;
	}	
;
get_pc:
	{
		$$.pc = current_pc;
	}
;
if_statement:
	if_head statement insert_goto ELSE statement {
		codeblock[$1.gotooffaddr] = $3.gotooffaddr+1-($1.gotooffaddr-1);
		codeblock[$3.gotooffaddr] = current_pc-($3.gotooffaddr-1);
		if($5.breaklist == NULL)
                        $5.breaklist = $2.breaklist;
                else
                        splice_backlist($2.breaklist,$5.breaklist);
                $$.breaklist = $5.breaklist;
                if($5.continuelist == NULL)
                        $5.continuelist = $2.continuelist;
                else
                        splice_backlist($2.continuelist,$5.continuelist);
                $$.continuelist = $5.continuelist;
	}
	| if_head statement insert_goto {
		codeblock[$1.gotooffaddr] = $3.gotooffaddr+1-($1.gotooffaddr-1);
		codeblock[$3.gotooffaddr] = current_pc-($3.gotooffaddr-1);
		$$ = $2;
	}
;
if_head:
	IF '(' expression ')' {
	        OUT_LOCVAR_VALUE($3->extra.var.offset);
                OUT_DOX(INVALID_ADDR);
                $$.gotooffaddr = current_pc-1;
	}
;

insert_goto:	{	
		OUT_GOTOX(INVALID_ADDR);
		$$.gotooffaddr = current_pc-1;
	}
;
return_statement:
	RETURN expression_or_null ';' {
		if($2 == NULL){
			OUT_CONSTANT(0);
		}else{
			OUT_LOCVAR_VALUE($2->extra.var.offset);
		}
		OUT_RETURNF(current_func->extra.func.paramlength,
				current_func->extra.func.rettype->width);
	}
;
expression_statement:
	expression ';' {}
	| ';' {}
	| expression error ';' 
	{
		errtext_ptr = NULL;
		yyerror("';' expected.");
	}
;
printf_statement:
	PRINTF '(' expression ')' ';' {
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		//fprintf(stderr,"[DEBUG] print offset:%d\n",$3->extra.var.offset);
		OUT_WRITEINTX;
	}
;
println_statement:
	PRINTLN '(' ')' ';' {
		OUT_NEXTLINE;
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
		if($1.offsetvar == NULL){
			yyerror("Cannot lvalue");
		}else{
			OUT_LOCVAR_VALUE($1.offsetvar->extra.var.offset);
			OUT_LOCVAR_VALUE($3->extra.var.offset);
			OUT_ASSIGN;
			OUT_POPS;
			$$=$3;
		}
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
	| logical_expression_orcheck LOGOR logical_expression {
		codeblock[$1.gotooffaddr] = current_pc-($1.gotooffaddr-1);
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1.retvar->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_ORX;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| logical_expression_andcheck LOGAND logical_expression {
		codeblock[$1.gotooffaddr] = current_pc-($1.gotooffaddr-1);
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1.retvar->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_ANDX;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| logical_expression LOGEQU logical_expression {
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_EQUAL;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| logical_expression LOGNEQ logical_expression {
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_EQUAL;
		OUT_NOTX;
		OUT_ASSIGN;
		OUT_POPS;
	}
;
logical_expression_orcheck:
	logical_expression {
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_NOTX;
		OUT_DOX(INVALID_ADDR);
		$$.retvar = $1;
		$$.gotooffaddr = current_pc-1;
	}
;
logical_expression_andcheck:
	logical_expression {
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_DOX(INVALID_ADDR);
		$$.retvar = $1;
		$$.gotooffaddr = current_pc-1;
	}
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
	| relational_expression MORETHAN relational_expression {
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_GREATER;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| relational_expression LESSTHAN relational_expression {
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_LESS;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| relational_expression MOREEQU relational_expression {
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_GREATEREQUAL;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| relational_expression LESSEQU relational_expression {
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_LESSEQUAL;
		OUT_ASSIGN;
		OUT_POPS;
	}
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
		symtab_node_t *type;
		type = $3->extra.var.vartype;
		if($1->extra.var.vartype->type == TYPE_POINTER){
			type = $1->extra.var.vartype;
		}
		$$ = alloc_loc_and_insert(type,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_ADD;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| arithmetic_exp '-' arithmetic_exp {
		symtab_node_t *type;
                type = $3->extra.var.vartype;
                if($1->extra.var.vartype->type == TYPE_POINTER){
                        type = $1->extra.var.vartype;
                }
		$$ = alloc_loc_and_insert(type,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_MINUS;
		OUT_ADD;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| arithmetic_exp '*' arithmetic_exp {		
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_MULTIPLY;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| arithmetic_exp '/' arithmetic_exp {
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
		OUT_DIVIDE;
		OUT_ASSIGN;
		OUT_POPS;
	}
	| arithmetic_exp '%' arithmetic_exp {
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$->extra.var.offset);
		OUT_LOCVAR_VALUE($1->extra.var.offset);
		OUT_LOCVAR_VALUE($3->extra.var.offset);
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
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
                OUT_LOCVAR($$->extra.var.offset);
                OUT_LOCVAR_VALUE($2->extra.var.offset);
                OUT_MINUS;
                OUT_ASSIGN;
		OUT_POPS;
        }
	| '!' unary_sup_expression {
		$$ = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
                OUT_LOCVAR($$->extra.var.offset);
                OUT_LOCVAR_VALUE($2->extra.var.offset);
                OUT_NOTX;
                OUT_ASSIGN;
                OUT_POPS;
	}
;
noarray_expression:
	unary_expression {
		$$ = $1.retvar;
	}
;
unary_expression:
	postfix_expression {
		$$ = $1;
	}
	| '*' unary_expression {
		if($2.retvar->extra.var.vartype->type == TYPE_POINTER){
			$$.offsetvar = alloc_loc_and_insert($2.retvar->extra.var.vartype,
								"czjtmppointer");
			OUT_LOCVAR($$.offsetvar->extra.var.offset);
			if($2.retvar->scope == SCOPE_GLOBAL){
				OUT_ESVAR_VALUE($2.retvar->extra.var.offset);
			}else{
				OUT_LOCVAR_VALUE($2.retvar->extra.var.offset);
			}
			OUT_ASSIGN;
			OUT_POPS;
			$$.retvar = alloc_loc_and_insert($2.retvar->extra.var.vartype->extra.poin.ptype,
                                                                "czjtmppointer");
			OUT_LOCVAR( $$.retvar->extra.var.offset);
			if($2.retvar->scope == SCOPE_GLOBAL){
                                OUT_ESVAR_VALUE($2.retvar->extra.var.offset);
                        }else{
                                OUT_LOCVAR_VALUE($2.retvar->extra.var.offset);
                        }
			OUT_VALUEL($2.retvar->extra.var.vartype->extra.poin.ptype->width);
			OUT_ASSIGNL($2.retvar->extra.var.vartype->extra.poin.ptype->width);
		}else{
			errtext_ptr = $2.retvar->name;
			yyerror("Not a pointer");
			errtext_ptr = NULL;
		}
	}
	| '&' unary_expression {
		$$.retvar = $2.offsetvar;
		$$.offsetvar = NULL;
	}
;
postfix_expression:
	primary_expression {
		$$ = $1;
	}
	| postfix_expression '[' expression ']' {
		if($1.retvar == NULL || $1.retvar->extra.var.vartype->type != TYPE_POINTER){
			errtext_ptr = $1.retvar->name;
			yyerror("Can't convert to array");
			errtext_ptr = NULL;
			$$ = $1;
		}else if($1.retvar->extra.var.vartype->extra.poin.ptype->type == TYPE_ARRAY){
			symtab_node_t *poin = get_new_symnode();
			memcpy(poin,$1.retvar->extra.var.vartype,sizeof(symtab_node_t));
			poin->extra.poin.ptype = 
				$1.retvar->extra.var.vartype->extra.poin.ptype->extra.array.elemtype;
			$$.retvar=alloc_loc_and_insert(poin,"czj");
			OUT_LOCVAR($$.retvar->extra.var.offset);
			OUT_LOCVAR_VALUE($1.retvar->extra.var.offset);
			OUT_LOCVAR_VALUE($3->extra.var.offset);
			OUT_INDEX($1.retvar->extra.var.vartype->extra.poin.ptype->width,lineno);
			OUT_ASSIGN;
			OUT_POPS;
			$$.offsetvar = NULL;
		}else{
			$$.retvar=alloc_loc_and_insert($1.retvar->extra.var.vartype->extra.poin.ptype,"czj");
			$$.offsetvar=alloc_loc_and_insert($1.retvar->extra.var.vartype,"czjpoin");
			OUT_LOCVAR($$.retvar->extra.var.offset);
			OUT_LOCVAR($$.offsetvar->extra.var.offset);
			OUT_LOCVAR_VALUE($1.retvar->extra.var.offset);
			OUT_LOCVAR_VALUE($3->extra.var.offset);
			OUT_INDEX($1.retvar->extra.var.vartype->extra.poin.ptype->width,lineno);
			OUT_ASSIGN;
			OUT_VALUEL($1.retvar->extra.var.vartype->extra.poin.ptype->width);
			OUT_ASSIGNL($1.retvar->extra.var.vartype->extra.poin.ptype->width);
		}
	}
	| postfix_expression '.' ID {
		if($1.offsetvar == NULL || $1.offsetvar->extra.var.vartype->type != TYPE_POINTER
			|| $1.offsetvar->extra.var.vartype->extra.poin.ptype->type != TYPE_STRUCT){
			errtext_ptr = $1.offsetvar->name;
                        yyerror("Can't convert to struct:");
			errtext_ptr = NULL;
                        $$ = $1;
		}else{
			symtab_node_t *tmp;
			tmp = find_symnode_by_name($3,
				$$.offsetvar->extra.var.vartype->extra.poin.ptype->extra.struc.elemlist);
			if(tmp == NULL){
				errtext_ptr = $3;
				yyerror("No such member variable:");
				errtext_ptr = NULL;
				$$ = $1;
			}else{
                        	OUT_LOCVAR($1.offsetvar->extra.var.offset);
                        	OUT_LOCVAR_VALUE($1.offsetvar->extra.var.offset);
                        	OUT_FIELD(tmp->extra.var.offset);
                        	OUT_ASSIGN;
                        	OUT_POPS;
				$1.offsetvar->extra.var.vartype->extra.poin.ptype = tmp->extra.var.vartype;
                        	$$.offsetvar = $1.offsetvar;
				$$.retvar = alloc_loc_and_insert(tmp->extra.var.vartype,"CZJtmpvalue");
                                OUT_LOCVAR($$.retvar->extra.var.offset);
                                if($$.offsetvar->scope == SCOPE_GLOBAL){
                                        OUT_ESVAR_VALUE($$.offsetvar->extra.var.offset);
                                }else{
                                        OUT_LOCVAR_VALUE($$.offsetvar->extra.var.offset);
                                }
				OUT_VALUEL(tmp->extra.var.vartype->width);
				OUT_ASSIGNL(tmp->extra.var.vartype->width);
			}
		}
	}
	| funccall_head '(' argument_expression_list ')' {
		int disp = $1.offsetvar->extra.func.offset-current_pc;
		OUT_FCALL(disp);
		OUT_ASSIGN;
		OUT_POPS;
		$$.retvar=$1.retvar;
		$$.offsetvar=NULL;
	}
	| GETCHAR '(' ')'{
		$$.retvar=alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$.retvar->extra.var.offset);
		OUT_READCHAR;
		OUT_ASSIGN;
		OUT_POPS;
		$$.offsetvar=NULL;
	}
;
funccall_head:
	ID {
		$$.retvar=alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR($$.retvar->extra.var.offset);
		
		symtab_node_t *tmp = find_symnode_by_name($1,main_symtab);
                if(tmp == NULL){
                        errtext_ptr = $1;
                        yyerror("Undefined Function");
			errtext_ptr = NULL;
		}else{
			OUT_FCALLBEGIN(tmp->extra.func.rettype->width);
		}
		$$.offsetvar=tmp;
	}
;
primary_expression:
	ID {
		symtab_node_t *tmp = find_symnode_by_name($1,main_symtab);
		if(tmp == NULL){
			errtext_ptr = $1;
			yyerror("Undefined Variable:");
			errtext_ptr = NULL;
			tmp=alloc_loc_and_insert(INT_TYPE_POINTER,$1);
			$$.retvar = tmp;
			$$.offsetvar = NULL;
		}else{
			if(tmp->type != TYPE_VAR){
				errtext_ptr = $1;
                        	yyerror("Not A Variable:");
                        	errtext_ptr = NULL;
				tmp=alloc_loc_and_insert(INT_TYPE_POINTER,$1);
	                        $$.retvar = tmp;
        	                $$.offsetvar = NULL;
			}else if(tmp->extra.var.vartype->type == TYPE_INT ||
				tmp->extra.var.vartype->type == TYPE_CHAR ||
				tmp->extra.var.vartype->type == TYPE_POINTER){
				symtab_node_t *poin = get_new_symnode();
                                poin->name = "czjpointer";
                                poin->scope = current_scope;
                                poin->type = TYPE_POINTER;
                                poin->width = INT_SIZE;
                                poin->extra.poin.ptype = tmp->extra.var.vartype;
				symtab_node_t *tmp2 = alloc_loc_and_insert(poin,"CZJPOINTER");
				OUT_LOCVAR(tmp2->extra.var.offset);
				if(tmp->scope == SCOPE_GLOBAL){
					OUT_ESVAR(tmp->extra.var.offset);
				}else{
					OUT_LOCVAR(tmp->extra.var.offset);
				}
				OUT_ASSIGN;
				OUT_POPS;
				$$.retvar = tmp;
                                $$.offsetvar = tmp2;
			}else if(tmp->extra.var.vartype->type == TYPE_ARRAY){
				symtab_node_t *poin = get_new_symnode();
				poin->name = "czjpointer";
				poin->scope = current_scope;
				poin->type = TYPE_POINTER;
				poin->width = INT_SIZE;
				poin->extra.poin.ptype = tmp->extra.var.vartype->extra.array.elemtype;
				$$.retvar = alloc_loc_and_insert(poin,"czjtmppoin");
				OUT_LOCVAR($$.retvar->extra.var.offset);
				if(tmp->scope == SCOPE_GLOBAL){
					OUT_ESVAR(tmp->extra.var.offset);
				}else{
					OUT_LOCVAR(tmp->extra.var.offset);
				}
				OUT_ASSIGN;
				OUT_POPS;
				$$.offsetvar == NULL;
			}else{
				$$.retvar = tmp;
				symtab_node_t *poin = get_new_symnode();
                                poin->name = "czjpointer";
                                poin->scope = current_scope;
                                poin->type = TYPE_POINTER;
                                poin->width = INT_SIZE;
                                poin->extra.poin.ptype = tmp->extra.var.vartype;
                                $$.offsetvar = alloc_loc_and_insert(poin,"czjstructpoin");
                                OUT_LOCVAR($$.offsetvar->extra.var.offset);
                                if(tmp->scope == SCOPE_GLOBAL){
                                        OUT_ESVAR(tmp->extra.var.offset);
                                }else{
                                        OUT_LOCVAR(tmp->extra.var.offset);
                                }
                                OUT_ASSIGN;
                                OUT_POPS;
                        }
		}
	}
		
	| constant {
		symtab_node_t *tmp=alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		//fprintf(stderr,"[DEBUG] Find constant offset %d value %d\n",tmp->extra.var.offset,$1);
		OUT_LOCVAR(tmp->extra.var.offset);
		OUT_CONSTANT($1);
		OUT_ASSIGN;
		OUT_POPS;
		$$.retvar=get_new_symnode();
		memcpy($$.retvar,tmp,sizeof(symtab_node_t));
		$$.offsetvar=NULL;
	}
	| '(' expression ')' {
		$$.retvar=$2;
		$$.offsetvar=NULL;
	}
;
argument_expression_list:
	{;}
	| assignment_expression {
		OUT_LOCVAR_VALUE($1->extra.var.offset);
	}
	| argument_expression_list ',' assignment_expression {
		OUT_LOCVAR_VALUE($3->extra.var.offset);
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
