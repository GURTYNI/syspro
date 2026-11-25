#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *top, int data)
{
    struct node *ptr;

    ptr = (struct node *)malloc(sizeof(struct node));

    if (ptr == NULL)
        exit(1);

    ptr->data = data;
    ptr->next = top->next;
    top->next = ptr;
}

int pop(struct node *top)
{
    struct node *ptr;
    int data;

    if (top->next == NULL)
        return -1;

    ptr = top->next;
    data = ptr->data;
    top->next = ptr->next;

    free(ptr);

    return data;
}

int main()
{
    struct node top;
    int data;

    top.next = NULL;

    while (scanf("%d", &data) == 1 && data > 0)
        push(&top, data);

    printf("Print stack\n");

    while (top.next != NULL)
        printf("%d\n", pop(&top));

    return 0;
}
