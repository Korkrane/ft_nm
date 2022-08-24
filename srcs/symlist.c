#include "../includes/ft_nm.h"

t_sym		*ft_symnew(void)
{
	t_sym		*new;

	new = (t_sym*)malloc(sizeof(t_sym));
	if (!new)
		return (NULL);
	new->name = 0;
    new->symbol = 0;
    new->hexValue = 0;
    new->firstLetterInName = 0;
	new->next = NULL;
    //new->prev = NULL;
    return (new);
}

t_sym *ft_symlast(t_sym *sym)
{
    if (!sym)
        return (NULL);
    while (sym->next)
        sym = sym->next;
    return (sym);
}

void ft_symadd_back(t_sym **asym, t_sym *new)
{
    t_sym *list;

    if (!asym || !*asym)
    {
        *asym = new;
    }
    else
    {
        list = ft_symlast(*asym);
        list->next = new;
    }
}

void freeSymbols(t_sym **symbolsHead)
{
   	t_sym		*curr;
	t_sym		*next;

	curr = *symbolsHead;
	while (curr)
	{
		next = curr->next;
        free(curr->firstLetterInName);
        free(curr->hexValue);
		free(curr);
		curr = next;
	}
	*symbolsHead = NULL;
}

// Function to insert a given node at its correct sorted position into a given
// list sorted in increasing order
void sortedInsert(struct t_sym **head, struct t_sym *newNode)
{
    struct t_sym dummy;
    struct t_sym *current = &dummy;
    dummy.next = *head;

    //printf("%s, %s\n", current->next->firstLetterInName, newNode->firstLetterInName);
    //while (current->next != NULL && current->next->firstLetterInName < newNode->firstLetterInName)
    while (current->next != NULL && current->next->firstLetterInName != NULL && strcmp(current->next->firstLetterInName, newNode->firstLetterInName) < 0)
    {
            current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    *head = dummy.next;
}

// Given a list, change it to be in sorted order (using `sortedInsert()`).
void sort_symlist(struct t_sym **head)
{
    struct t_sym *result = NULL;   // build the answer here
    struct t_sym *current = *head; // iterate over the original list
    struct t_sym *next;

    while (current != NULL)
    {
        // tricky: note the next pointer before we change it
        next = current->next;

        sortedInsert(&result, current);
        current = next;
    }
    *head = result;
}

// Function to insert a given node at its correct sorted position into a given
// list sorted in increasing order
void rsortedInsert(struct t_sym **head, struct t_sym *newNode)
{
    struct t_sym dummy;
    struct t_sym *current = &dummy;
    dummy.next = *head;

    //printf("%s, %s\n", current->next->firstLetterInName, newNode->firstLetterInName);
    //while (current->next != NULL && current->next->firstLetterInName < newNode->firstLetterInName)
    while (current->next != NULL && current->next->firstLetterInName != NULL && strcmp(current->next->firstLetterInName, newNode->firstLetterInName) > 0)
    {
            current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    *head = dummy.next;
}

// Given a list, change it to be in rsorted order (using `sortedInsert()`).
void reverse_sort_symlist(struct t_sym **head)
{
    struct t_sym *result = NULL;   // build the answer here
    struct t_sym *current = *head; // iterate over the original list
    struct t_sym *next;

    while (current != NULL)
    {
        // tricky: note the next pointer before we change it
        next = current->next;

        rsortedInsert(&result, current);
        current = next;
    }
    *head = result;
}