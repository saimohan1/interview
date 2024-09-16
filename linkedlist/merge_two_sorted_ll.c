/* Write a c program to merge two sorted single list and return sorted merge list */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int data;
    struct node *next;
};

struct node *
create_a_list(int *nums, int size)
{
    struct node *List = NULL;
    struct node *head;

    for (int i = 0; i < size; i++) {
        struct node *new = malloc(sizeof(struct node));
        if (new == NULL) {
            assert(0);
        }
        new->data = nums[i];
        new->next = NULL;
        if (List == NULL) {
            List = new;
            head = List;
        } else {
            List->next = new;
            List = List->next;
        }

    }
    return head;
}

static void
print_list(struct node *head) {
    struct node *t = head;

    while (t != NULL) {
        printf("value of t:%d\n", t->data);
        t = t->next;
    }
}

struct node *
merge_list(struct node *l1, struct node *l2) {
    struct node dummy;
    struct node *tail = &dummy;


        while (l1 != NULL && l2 != NULL) {
                if (l1->data < l2->data) {
                        tail->next = l1;
                        l1 = l1->next;
                } else {
                        tail->next = l2;
                        l2 = l2->next;
                }
                tail = tail->next;
        }

        if (l1 != NULL) {
                tail->next = l1;
        } else {
                tail->next = l2;
        }
        return dummy.next;
}

int main() {
    int first[] = {1,2,3,8,9};
    int second[] = {4,5,6};

    print_list(merge_list(create_a_list((int *)first, 5), create_a_list((int *)second, 3)));

    return 0;
}
