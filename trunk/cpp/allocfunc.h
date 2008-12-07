#ifndef _ALLOCFUNC_H_
#define _ALLOCFUNC_H_

#include "symtab.h"

typedef struct {
        int locvar_cnt;
        int tmpvar_cnt;
        symtab_head_t *symtab;
} symfunc_t;

int allocfuncparam(symtab_head_t *paramlst)
{
        int offset=0;
        symtab_head_t *curr;
        symtab_node_t *tmp;      
        list_for_each(curr,paramlst){
                tmp = list_entry(curr,symtab_node_t,list);
                if(tmp->type == TYPE_VAR){
                        tmp->scope++;
                        offset -= tmp->extra.var.vartype->width;
                        tmp->extra.var.offset = offset;
                }
        }
        return 0;
}

#endif /* _ALLOCFUNC_H_ */
