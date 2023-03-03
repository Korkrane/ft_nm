#include "../includes/ft_nm.h"

int help()
{
	fprintf(stderr, "Usage\n  ./ft_nm [options] <objfile>\n"
					"\nOptions:\n"
					"  -h\tprint help and exit\n"
					"  -a\tDisplay debbuger-only symbols\n"
					"  -g\tDisplay only externals symbols\n"
					"  -u\tDisplay only undefined symbols\n"
					"  -r\tReverse the sense of the sort\n"
					"  -p\tDo not sort the symbols\n");
	return 0;
}

void addOptionWithoutParameter(char opt)
{
	switch(opt)
	{
		case 'a': options |= a; break;
		case 'g': options |= g; break;
		case 'u': options |= u; break;
		case 'r': options |= r; break;
		case 'p': options |= p; break;
	}
}

int parsing(int ac, char **av)
{
	int firstArgument = 0;
	int totalArguments = 0;
	int firstArgumentIndex = 0;
	for (int i = 1; i < ac; i++)
	{
		if (av[i][0] == '-')
		{
			for (int j = 1; av[i][j]; j++)
			{
				switch (av[i][j])
				{
					case 'a': case 'g': case 'u': case 'r': case 'p':
						addOptionWithoutParameter(av[i][j]);
						break;
					case 'h':
						return (help());
					default:
						printf("ft_nm: Invalid option -- '%c'\n", av[i][j]);
						return (help());
				}
			}
		}
		else
		{
			if(firstArgument == 0)
			{
				firstArgumentIndex = i;
				firstArgument = 1;
			}
			totalArguments++;
		}

	}
	//si pas d'argumetns on mets par defaut a.out a check
	if(totalArguments == 0)
	{
		files = malloc(sizeof(char *) * (2));
		files[0] = ft_strdup("a.out");
		files[1] = NULL;
	}
	else //autrements on va append chaque argument a la liste de fichier //inclure ici le recursive files
	{
		files = malloc(sizeof(char *) * (totalArguments + 1));
		for (int i = 0; i < totalArguments; i++)
			files[i] = ft_strdup(av[i + firstArgumentIndex]);
		files[totalArguments] = NULL;
	}
	#ifdef DEBUG
		logPrintEnabledOptions();
		logPrintArguments();
	#endif
	return true;
}