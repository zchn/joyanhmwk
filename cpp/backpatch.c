#include <malloc.h>
#include "list.h"
#include "backpatch.h"

extern int codeblock[];

backlist_head_t *init_backlist()
{
        backlist_head_t * tmp = (backlist_head_t *)malloc(sizeof(backlist_head_t));
        INIT_LIST_HEAD(tmp);
        return tmp;
}

backlist_node_t * get_new_backnode()
{
        backlist_node_t *tmp = (backlist_node_t *)malloc(sizeof(backlist_node_t));
        memset(tmp,0,sizeof(backlist_node_t));
        INIT_LIST_HEAD(&(tmp->list));
        return tmp;
}

int insert_backnode(backlist_node_t *backnode,backlist_head_t *head)
{
        list_add(&(backnode->list),head);
        return 0;
}

int split_backlist(backlist_head_t *head1,backlist_head_t *head2)
{
        list_split(head1,head2);
        return 0;
}

int splice_backlist(const backlist_head_t *head1,backlist_head_t *head2)
{
        if(head1 == NULL)
                return 0;
        list_splice(head1,head2);
        return 0;
}

int destroy_backlist(backlist_head_t * head)
{
        backlist_head_t *curr,*tmp;
        list_for_each_safe(curr,tmp,head){
                list_del(curr);
                free(curr);
        }
        free(head);
        return 0;
}

/* int backpatch(backlist_head_t *head,int offset) */
/* { */
/*         if(head == NULL) */
/*                 return 0; */
/*         backlist_head_t *curr; */
/*         backlist_node_t *tmp; */
/*         list_for_each(curr,head){ */
/*                 tmp = list_entry(curr,backlist_node_t,list); */
/*                 codeblock[tmp->offset] = offset; */
/*         } */
/*         return 0; */
/* } */

int backpatch_dis(backlist_head_t *head,int offset)
{
        if(head == 0)
                return 0;
        backlist_head_t *curr;
        backlist_node_t *tmp;
        list_for_each(curr,head){
                tmp = list_entry(curr,backlist_node_t,list);
                codeblock[tmp->offset] = offset-tmp->offset;
        }
        return 0;
}
