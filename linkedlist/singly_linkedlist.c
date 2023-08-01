#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* Node Strucure */
struct node {
	int data;
	struct node *next;
};

struct node *alloc_node(int data)
{
	struct node *new = NULL;

	new = calloc(1, sizeof(struct node));
	if (new == NULL) {
		return NULL;
	}

	new->data = data;
	new->next = NULL;

	return new;
}

struct node *get_user_input_node(void)
{
	struct node *node = NULL;
	int data;
	
	printf("Please enter the number to insert to Linkedlist: ");
	scanf("%d", &data);	

	node = alloc_node(data);
	if (node == NULL) {
		printf("Failed to allocate memory for Node\n");
		return NULL;
	} 

	return node;
}


/* Insert node at beginning */
struct node * insert_node_at_begin(struct node *head)
{
	struct node *tmp = head;
	struct node *node = get_user_input_node();
	
	if (node == NULL)
		return head;

	if (head == NULL) {
		head = node;
	} else {
		node->next = head;
		head = node;
	}
	//printf("(%s:%d)The Head is:%p node:%p\n", __func__, __LINE__, head, node);
	return head;
}

/* Insert node at end */
struct node * insert_node_at_end(struct node *head)
{
	struct node *tmp = head;
	struct node *node = get_user_input_node();
	
	if (node == NULL)
		return head;

	/* Add end of the list */		
	if (head == NULL) {
		head = node;
	} else {
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}

	return head;
}

static struct node * reverse_a_list_iter(struct node *head)
{
	struct node *current = head;
	struct node *next;
	struct node *prev = NULL;

	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return prev;
}
/* Reverse a linkedlist using recurrsion */
static struct node * reverse_a_list_recur(struct node *head)
{
	if (head == NULL || head->next == NULL) {
		return head;
	}
	struct node *newHead = reverse_a_list_recur(head->next);
	head->next->next = head;
	head->next = NULL;
	return newHead;
}

/* Display Linked list */
static void display_list(struct node *head)
{
	struct node *tmp = head;

	//printf("(%s:%d)The Head is:%p\n", __func__, __LINE__, head);

	if (head == NULL) {
		printf("There is no node to display. List is empty!!\n");
		return;
	}

	while(tmp != NULL) {
		printf("%d\t", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}

static struct node * insert_node_after(struct node* head)
{
	struct node *temp = head;
	struct node *new = get_user_input_node();	
	int data;

	if (new == NULL)
		return head;

	printf("Please enter the node after which the new data will be insert: ");
	scanf("%d", &data);
	
	if (head == NULL)
		free(new);

	while (temp != NULL) {
		if (temp->data == data) {
			new->next = temp->next;
			temp->next = new;
		}
		temp = temp->next;
	}
	
	return head;	
}

static struct node *delete_kth_node_from_end(struct node *head)
{
	struct node *slow, *fast;
	int pos;
	
	/* Check the base condition */
	if (head == NULL) {
		printf("No Node to delete\n");
		return head;
	}

	printf("Please enter the kth position: ");
	scanf("%d", &pos);

	slow = head;
	fast = head;

	while(fast != NULL && pos--) {
		fast = fast->next;
	}	
	
	if (fast == NULL) {
		return slow->next;
	}

	while (fast->next != NULL) {
		slow = slow->next;
		fast = fast->next;
	}
	
	slow->next = slow->next->next;
	free(slow->next);
	
	return head;
}

static void display_list_using_recur(struct node*head)
{
	if (head == NULL)
		return;
	printf("%d ", head->data);
	display_list_using_recur(head->next);
}

static struct node * delete_node(struct node *head)
{
	struct node *tmp = head;
	struct node *prev = NULL;
	int data;

	printf("Please enter the node to delete: ");
	scanf("%d", &data);

	/* Check if the data in the first/head node */
	if (head != NULL && head->data == data) {
		head = head->next;
		return head;
	}

	/* Traverse the node till it matches the data,
	 * and keep track of prev node
	 */	
	while (tmp != NULL && tmp->data != data) {
		prev = tmp;
		tmp = tmp->next;
	}

	/* If we dont find any node with the desired */
	if (tmp == NULL) {
		printf("No Node to delete\n");
		return head;
	}

	/* found the node to be delete */
	prev->next = prev->next->next;
	free(tmp);

	return head;
}

int main() {
	int choice;
	struct node *head = NULL;
	
	while (1) {
		printf("\n");
		printf("1 - Insert at beginning\n");
		printf("2 - Insert at end\n");
		printf("3 - Insert after a node\n");
		printf("4 - Delete a node from list\n");
		printf("5 - Display List\n");
		printf("6 - Reverse a list iterative\n");
		printf("7 - Reverse a list recursive\n");
		printf("8 - Delete kth node from end\n");
		printf("9 - Display list using recursion\n");
		printf("99 - Exit\n");
		printf("Please enter the choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			head = insert_node_at_begin(head);
			break;
		case 2:
			head = insert_node_at_end(head);
			break;
		case 3:
			head = insert_node_after(head);
			break;
		case 4:
			head = delete_node(head);
			break;
		case 5:
			display_list(head);
			break;
		case 6:
			head = reverse_a_list_iter(head);
			break;
		case 7:
			head = reverse_a_list_recur(head);
			break;
		case 8:
			head = delete_kth_node_from_end(head);
			break;
		case 9:
			display_list_using_recur(head);
			break;
		case 99:
			exit(0);
		default:
			printf("Invalid Choice given! Please try Again.\n");
		}
		printf("\n");
	}
	return 0;
}
