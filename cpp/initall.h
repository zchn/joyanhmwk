#ifndef _INITALL_H_
#define _INITALL_H_

#include "symtab.h"

#define INT_SIZE 1
#define CB_LEN 8192

#define INT_TYPE_POINTER pint_type
#define CHAR_TYPE_POINTER pchar_type

int codeblock[CB_LEN];/* 最终生成的二进制cpmachine代码 */
int current_pc;/* 当前翻译到的pc指针 */
symtab_node_t *current_type;/* 在解析delclaration类语句时，存放delarator_list前的那部分类型说明 */
symtab_node_t *current_func;
int current_scope;
symtab_head_t *main_symtab;/* 主（当前）符号表  */
symtab_head_t *deleted_symtab;/* 刚刚摘下的符号表 */

symstack_head_t *main_symstack;

int error_count;/* 错误数 */
int warning_count;/* 警告数 */

symtab_node_t *pint_type;
symtab_node_t *pchar_type;

int init_all()
{
        current_pc = 0;
        current_scope = 0;
        error_count=0;
        warning_count=0;
        main_symtab = init_symtab();
        main_symstack = init_symstack();
        init_espool();
        symtab_node_t *tmp;
        
        tmp = get_new_symnode();
        tmp->name = "int";
        tmp->type = TYPE_INT;
        tmp->scope = SCOPE_GLOBAL;
        tmp->width = INT_SIZE;
        insert_symnode(tmp,main_symtab);
        pint_type = tmp;

        tmp = get_new_symnode();
        tmp->name = "char";
        tmp->type = TYPE_CHAR;
        tmp->scope = SCOPE_GLOBAL;
        tmp->width = INT_SIZE;
        insert_symnode(tmp,main_symtab);
        pchar_type = tmp;
       
        deleted_symtab = NULL;
}

int output_code(FILE *file)
{
        int i;
        for(i = 0; i <= current_pc;i++){
                fprintf(file,"%d\n",codeblock[i]);
        }
}

#endif /* _INITALL_H_ */
