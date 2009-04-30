#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include "list.h"

#define TYPE_VAR 500
#define TYPE_ARRAY 501
#define TYPE_STRUCT 502
#define TYPE_FUNC 503
#define TYPE_INT 504
#define TYPE_CHAR 505
#define TYPE_ALIAS 506
#define TYPE_POINTER 507

#define VAR_AUTO 601
#define VAR_STATIC 602

#define SCOPE_GLOBAL 0

#define ATTR_CONST 8

typedef struct list_head symtab_head_t;

struct _symtab_node_t;

typedef struct _vartype_info_t{
        int offset;
        int varattrib;
        struct _symtab_node_t *vartype;
} vartype_info_t;

typedef struct _arraytype_info_t{
        int count;
        struct _symtab_node_t *elemtype;
} arraytype_info_t;

typedef struct _structtype_info_t{
        symtab_head_t *elemlist;
} structtype_info_t;

typedef struct _functype_info_t{
        struct _symtab_node_t *rettype;
        int paramlength;
        int offset;
} functype_info_t;

typedef struct _pointertype_info_t{
        struct _symtab_node_t *ptype;
} pointertype_info_t;

typedef struct _symtab_node_t{
        char *name;
        int type;
        int scope;
        int width;
        union {
                vartype_info_t var;
                arraytype_info_t array;
                structtype_info_t struc;
                functype_info_t func;
                pointertype_info_t poin;
        } extra;                
        symtab_head_t list;
} symtab_node_t;

typedef struct list_head symstack_head_t;

symtab_head_t * init_symtab();
symtab_node_t * get_new_symnode();
int insert_symnode(symtab_node_t *symnode,symtab_head_t *head);
int split_symtab(symtab_head_t *head1,symtab_head_t *head2);
int splice_symtab(const symtab_head_t *head1,symtab_head_t *head2);
symtab_node_t * find_symnode_by_name(const char *name,const symtab_head_t *head);
int destroy_symtab(symtab_head_t * head);
int process_array_type(symtab_node_t * node);

symstack_head_t * init_symstack();
int push_symstack(symstack_head_t *S, symtab_head_t *elem);
symtab_head_t * gettop_symstack(symstack_head_t *S);
symtab_head_t * pop_symstack(symstack_head_t *S);
int sum_all_width(symtab_head_t *list);

#endif /* _SYMTAB_H_ */
