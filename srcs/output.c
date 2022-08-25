#include "../includes/ft_nm.h"

void sortOutput(t_sym **symList)
{
	if (hasOptionEnabled(r))
		reverse_sort_symlist(symList);
	else
		sort_symlist(symList);
}

void displayOutput(t_sym *sym)
{
	t_sym *tmp = sym;

	if (!hasOneFileToCheck())
		printf("\n%s:\n", currentFile);
	while (tmp)
	{
		if (hasOptionEnabled(g) && ft_islower(tmp->symbol))
			;
		else
		{
			if (ft_strcmp(tmp->hexValue, "0000000000000000") == 0)
				printf("%18c %s\n", tmp->symbol, tmp->name);
			else
				printf("%s %c %s\n", tmp->hexValue, tmp->symbol, tmp->name);
		}
		tmp = tmp->next;
	}
}