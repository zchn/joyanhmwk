#ifndef _ALLOCVAR_H_
#define _ALLOCVAR_H_

#include <string.h>

#include "initall.h"

int __locvar_cnt;
int __esvar_cnt;

int init_locpool()
{
        __locvar_cnt=2;
        return 0;
}

int init_espool()
{
        __esvar_cnt = 0;
        return 0;
}

int alloc_loc(symtab_node_t *varnode)
{
        int ret = __locvar_cnt;
        fprintf(stderr,"[DEBUG] locoffset %d allocated\n",ret);
        __locvar_cnt+=varnode->extra.var.vartype->width;
        return ret;
}

int alloc_es(symtab_node_t *varnode)
{
        int ret = __esvar_cnt;
        fprintf(stderr,"[DEBUG] esoffset %d allocated\n",ret);
        __esvar_cnt+=varnode->extra.var.vartype->width;
        return ret;
}

symtab_node_t *alloc_loc_and_insert(const symtab_node_t *type,const char *name)
{
        symtab_node_t *tmp=get_new_symnode();
        if(name == NULL){
                tmp->name="czj";
        }else{
                tmp->name=strdup(name);
        }
        tmp->type=TYPE_VAR;
        tmp->scope=current_scope;
        tmp->width=type->width;
        tmp->extra.var.vartype=(symtab_node_t *)type;
        tmp->extra.var.offset=alloc_loc(tmp);
        insert_symnode(tmp,main_symtab);
        return tmp;
}

int get_locvar_cnt()
{
        return __locvar_cnt;
}

int get_esvar_cnt()
{
        return __esvar_cnt;
}

int allocmemory(symtab_head_t *psymhead)
{
        symtab_node_t *tmp;
        symtab_head_t *curr;
        list_for_each(curr,psymhead){
                tmp = list_entry(curr,symtab_node_t,list);
                if(tmp->type == TYPE_VAR){
                        if(tmp->scope == SCOPE_GLOBAL){
                                tmp->extra.var.offset=alloc_es(tmp);
                        }else{
                                tmp->extra.var.offset=alloc_loc(tmp);
                        }
                }
                fprintf(stderr,"[DEBUG] in allocmemory, alloc %s to %d\n",
                        tmp->name,tmp->extra.var.offset);
        }
        return 0;
}

int allocmemberoffset(symtab_head_t *memlst)
{
        int offset=0;
        symtab_node_t *tmp;
        symtab_head_t *curr;
        list_for_each_prev(curr,memlst){
                tmp = list_entry(curr,symtab_node_t,list);
                if(tmp->type == TYPE_VAR){
                        tmp->extra.var.offset=offset;
                        offset+=tmp->extra.var.vartype->width;
                }
        }
        return 0;
}


#endif /* _ALLOCVAR_H_ */
