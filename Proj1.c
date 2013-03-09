#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Domino{
    int r;
    bool visited;
    struct list *paths;
};

struct list{
    int val;
    struct list *next;
};

/* Create a new list */
struct list* create_list(struct list *head, int val){
    struct list *ptr = (struct list*)malloc(sizeof(struct list));
    ptr->val = val;
    ptr->next = NULL;

    head = ptr;
    return ptr;
}

void addPath(struct Domino *domino, int val){
    if(domino->paths == NULL)
        domino->paths = create_list(domino->paths, val);
    else{
        struct list *ptr = (struct list*)malloc(sizeof(struct list));
        ptr->val = val;
        ptr->next = domino->paths;
        domino->paths = ptr;
    }
}

int pop_first_list(struct list *head){
    int value;
    struct list *ptr = head;

    if(head == NULL)
        return -1;
    value = head->val;
    head = head->next;
    free(ptr);
    return value;
}

void printPath(struct Domino *domino){
    struct list *ptr = domino->paths;

    while(ptr != NULL) {
        printf("[%d]",ptr->val+1);
        ptr = ptr->next;
    }

    return;
}

void printDominoList(struct Domino *domino, int size){
    int i = 0;

    for(;i < size; i++){
        printf("Domino %d -> ", i+1);
        printPath(&domino[i]);
        printf("\n");
    }
}

int main(void){

    int num_tests, num_paths, num_dominos, from, to;
    struct Domino *domino_list = NULL;

    if(1 != scanf("%d", &num_tests))
        exit(-1);
    //answer = (int*)malloc(num_tests*(sizeof(int)));

    while(num_tests-->0){

        if(2 != scanf("%d %d", &num_dominos, &num_paths))
            exit(-1);
        domino_list = (struct Domino*)malloc(num_dominos*(sizeof(struct Domino)));
        while(num_paths-->0){
            if(2 != scanf("%d %d", &from, &to))
                exit(-1);
            addPath(&domino_list[from-1], to-1);
        }
    }

    printDominoList(domino_list, num_dominos);

    return 0;
}
