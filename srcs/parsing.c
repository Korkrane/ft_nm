#include "../includes/ft_nm.h"

int help()
{
	fprintf(stderr, "Usage\n  ./ft_nm [options] <objfile>\n"
					"\nOptions:\n"
					"  -h\t\t		print help and exit\n"
					"  -a\t\t		Display debbuger-only symbols\n"
					"  -g\t\t		Display only externals symbols\n"
					"  -u\t\t		Display only undefined symbols\n"
					"  -r\t\t		Reverse the sense of the sort\n"
					"  -p\t\t		Do not sort the symbols\n");
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
			file = av[i];
			#ifdef DEBUG
				logPrintEnabledOptions();
			#endif
			return (true);
		}
	}
	return true;
}