#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node *head, struct node *tail, int data)
{
    struct node *ptr;

    ptr = (struct node *)malloc(sizeof(struct node));

    if (ptr == NULL)
        exit(1);

    ptr->data = data;
    ptr->next = NULL;

    if (head->next == NULL)
        head->next = ptr;
    else
        tail->next->next = ptr;

    tail->next = ptr;
}

int delete(struct node *head, struct node *tail)
{
    struct node *ptr;
    int data;

    if (head->next == NULL)
        return -1;

    ptr = head->next;
    data = ptr->data;
    head->next = ptr->next;

    if (head->next == NULL)
        tail->next = NULL;

    free(ptr);

    return data;
}

int main()
{
    struct node head, tail;
    int data;

    head.next = NULL;
    tail.next = NULL;

    while (scanf("%d", &data) == 1 && data > 0)
        addq(&head, &tail, data);

    printf("Print queue\n");

    while (head.next != NULL)
        printf("%d\n", delete(&head, &tail));

    return 0;
}
