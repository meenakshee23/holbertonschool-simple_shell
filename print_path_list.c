#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	char *dir;
	struct Node *next;
} Node;

/**
 * create_node - Creates a new node with the given directory string.
 * @dir: Directory string to store in the node.
 *
 * Return: Pointer to the newly created node, or NULL on failure.
 */
Node *create_node(char *dir)
{
	Node *new_node = malloc(sizeof(Node));
	if (!new_node)
		return NULL;

	new_node->dir = strdup(dir);
	if (!new_node->dir)
	{
		free(new_node);
		return NULL;
	}

	new_node->next = NULL;

	return new_node;
}

/**
 * print_list - Prints each directory in the linked list.
 * @head: Pointer to the head of the linked list.
 */
void print_list(Node *head)
{
	while (head)
	{
		printf("%s\n", head->dir);
		head = head->next;
	}
}

/**
 * free_list - Frees all nodes and their directory strings in the linked list.
 * @head: Pointer to the head of the linked list.
 */
void free_list(Node *head)
{
	Node *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->dir);
		free(tmp);
	}
}

/**
 * build_path_list - Builds a linked list of directories from PATH string.
 * @path: The PATH environment variable string.
 *
 * Return: Pointer to the head of the linked list.
 */
Node *build_path_list(char *path)
{
	char *path_copy = strdup(path);
	char *token;
	Node *head = NULL;
	Node *tail = NULL;
	Node *node;

	if (!path_copy)
		return NULL;

	token = strtok(path_copy, ":");
	while (token)
	{
		node = create_node(token);
		if (!node)
		{
			free_list(head);
			free(path_copy);
			return NULL;
		}

		if (!head)
		{
			head = node;
			tail = node;
		}
		else
		{
			tail->next = node;
			tail = node;
		}

		token = strtok(NULL, ":");
	}

	free(path_copy);

	return head;
}

/**
 * main - Entry point of the program.
 *
 * Description: retrieves the PATH environment variable,
 * builds a linked list of directories from it,
 * prints each directory, and frees the list.
 *
 * Return: 0 on success, 1 if PATH variable is not found.
 */
int main(void)
{
	char *path = getenv("PATH");
	Node *list;

	if (!path)
	{
		printf("PATH variable not found\n");
		return 1;
	}

	list = build_path_list(path);
	if (!list)
	{
		printf("Failed to build path list\n");
		return 1;
	}

	print_list(list);
	free_list(list);

	return 0;
}
