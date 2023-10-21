#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* Node Strucure */
struct node {
	int data;
	struct node *next;
	struct node *prev;
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
	new->prev = NULL;

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

static struct node *
insert_node_at_begin(struct node *head)
{
	struct node *new = get_user_input_node();
	
	if (new == NULL) {
		printf("Failed to create a new node\n");
		return head;
	}

	if (head == NULL) {
		head = new;
	} else {
		head->prev = new;
		new->next = head;
		head = new;	
	}
	return head;
}

static struct node *
insert_node_at_end(struct node *head)
{
	struct node *temp = head;
	struct node *new = get_user_input_node();
	if (new == NULL) {
		printf("Failed to create a new node\n");
		return head;
	}

	if (head == NULL) {
		head = new;
	} else {
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	return head;
}


static void
print_list(struct node *head)
{
	struct node *temp = head;
	
	if (head == NULL) {
		printf("No node to display\n");
		return;
	}
	
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}

	printf("\n");
}

static struct node *
delete_a_node(struct node *head)
{
	struct node *temp = head;
	struct node *prev = NULL;
	int key;

	if (head == NULL) {
		printf("List is empty can not do delete operation\n");
		return head;
	}

	printf("Please enter the node to delete: ");
	scanf("%d", &key);

	if (head->data == key) {
		head = head->next;
		if (head != NULL) {
			head->prev = NULL;	
		}	
		free(temp);
	} else {
		while (temp->data != key) {
			prev = temp;
			temp = temp->next;
		}
		
		if (temp == NULL) {
			printf("No Node found to delete\n");
		} else {
			prev->next = prev->next->next;
			if (temp->next != NULL)
				temp->next->prev = prev;
			free(temp);
		}
	}

	return head;

}

int main() {
	int choice;
	struct node *head = NULL;
	
	while (1) {
		printf("\n");
		printf("1 - Insert at beginning\n");
		printf("2 - Display\n");
		printf("3 - Insert at End\n");
		printf("4 - Delete a node\n");
		printf("99 - Exit\n");
		printf("Please enter the choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			head = insert_node_at_begin(head);
			break;
		case 2:
			print_list(head);
			break;
		case 3:
			head = insert_node_at_end(head);
			break;
		case 4:
			head = delete_a_node(head);
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
