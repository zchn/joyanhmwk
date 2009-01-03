#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "symtab.h"

typedef struct _symstack_node_t{
        symtab_head_t *elem;
        symstack_head_t list;
} symstack_node_t;


symtab_head_t * init_symtab()
{
        symtab_head_t * tmp = (symtab_head_t *)malloc(sizeof(symtab_head_t));
        INIT_LIST_HEAD(tmp);
        return tmp;
}

symtab_node_t * get_new_symnode()
{
        symtab_node_t *tmp = (symtab_node_t *)malloc(sizeof(symtab_node_t));
        memset(tmp,0,sizeof(symtab_node_t));
        INIT_LIST_HEAD(&(tmp->list));
        return tmp;
}

int insert_symnode(symtab_node_t *symnode,symtab_head_t *head)
{
        list_add(&(symnode->list),head);
        return 0;
}

int split_symtab(symtab_head_t *head1,symtab_head_t *head2)
{
        list_split(head1,head2);
        return 0;
}

int splice_symtab(const symtab_head_t *head1,symtab_head_t *head2)
{
        list_splice(head1,head2);
        return 0;
}


symtab_node_t * find_symnode_by_name(const char *name,const symtab_head_t *head)
{
        symtab_node_t * curr;
        list_for_each_entry(curr,head,list){
                if(strcmp(name,curr->name) == 0){
                        return curr;
                }
        }
        return NULL;
}

int destroy_symtab(symtab_head_t * head)
{
        struct list_head *curr,*tmp;
        list_for_each_safe(curr,tmp,head){
                free(list_entry(curr,symtab_node_t,list)->name);
                list_del(curr);
                free(curr);
        }
        free(head);
        return 0;
}

symstack_head_t * init_symstack()
{
        symstack_head_t *tmp = (symstack_head_t *)malloc(sizeof(symstack_head_t));
        INIT_LIST_HEAD(tmp);
        return tmp;
}

int push_symstack(symstack_head_t *S, symtab_head_t *elem)
{
        symstack_node_t *E = (symstack_node_t *)malloc(sizeof(symstack_node_t));
        E->elem = elem;
        list_add(&(E->list),S);
}

symtab_head_t * gettop_symstack(symstack_head_t *S)
{
        if(list_empty(S))
                return NULL;
        else
                return (list_entry(S->next,symstack_node_t,list)->elem);
}

symtab_head_t * pop_symstack(symstack_head_t *S)
{
        if(list_empty(S))
                return NULL;
        symstack_node_t *tmp = list_entry(S->next,symstack_node_t,list);
        symtab_head_t *ret = tmp->elem;
        list_del(S->next);
        free(tmp);
        return ret;
}

int sum_all_width(symtab_head_t *list)
{
        int sum = 0;
        symtab_head_t *curr;
        symtab_node_t *tmp;
        list_for_each(curr,list){
                tmp = list_entry(curr,symtab_node_t,list);
                if(tmp->type == TYPE_VAR){
                        sum += tmp->extra.var.vartype->width;
                }
        }
        //fprintf(stderr,"[DEBUG] sum_all_width: %d\n",sum);
        return sum;
}
