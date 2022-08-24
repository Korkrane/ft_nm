#include "../includes/ft_nm.h"

bool hasElfMagicNumber(char *ptr)
{
	if (ptr[0] == ELFMAG0 && ptr[1] == ELFMAG1 && ptr[2] == ELFMAG2 && ptr[3] == ELFMAG3)
		return true;
	return false;
}

bool is64bitArchitecture(char *ptr)
{
	if (ptr[4] == ELFCLASS64)
		return true;
	return false;
}

bool is32bitArchitecture(char *ptr)
{
	if (ptr[4] == ELFCLASS32)
		return true;
	return false;
}

bool isInvalidClass(char *ptr)
{
	if (ptr[4] == ELFCLASSNONE)
		return true;
	return false;
}