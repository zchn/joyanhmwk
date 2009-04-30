#ifndef _BACKPATCH_H_
#define _BACKPATCH_H_

#include <malloc.h>
#include "list.h"
#include <string.h>


#define INVALID_ADDR 987654

typedef struct list_head backlist_head_t;
typedef struct _backlist_node_t{
        int offset;
        backlist_head_t list;
} backlist_node_t;

backlist_head_t *init_backlist();

backlist_node_t * get_new_backnode();

int insert_backnode(backlist_node_t *backnode,backlist_head_t *head);

int split_backlist(backlist_head_t *head1,backlist_head_t *head2);

int splice_backlist(const backlist_head_t *head1,backlist_head_t *head2);

int destroy_backlist(backlist_head_t * head);

int backpatch(backlist_head_t *head,int offset);

int backpatch_dis(backlist_head_t *head,int offset);

#endif /* _BACKPATCH_H_ */
