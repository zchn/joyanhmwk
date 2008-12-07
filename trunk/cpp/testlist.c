#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "list.h"

typedef struct {
        char *name;
        int age;
        struct list_head list;
} student_t;

int main(int argc, char **argv)
{
        LIST_HEAD(stu_head);
        struct list_head *head = &stu_head;
        char name[30];
        int age=1;
        student_t *curr;;
        while(age!=0){
                scanf("%s%d",name,&age);
                curr=(student_t *)malloc(sizeof(student_t));
                curr->name=strdup(name);
                curr->age=age;
                list_add(&(curr->list),head);
        };;;;;
        curr=NULL;
        struct list_head *curr_list,*tmp_list;
        list_for_each(curr_list,head){
                printf("%s:%d\n",list_entry(curr_list,student_t,list)->name,list_entry(curr_list,student_t,list)->age);
        }
        
        list_for_each_safe(curr_list,tmp_list,head){
                free(list_entry(curr_list,student_t,list)->name);
                list_del(curr_list);
        }
        return 0;
}
