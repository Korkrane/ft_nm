/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:38:04 by bahaas            #+#    #+#             */
/*   Updated: 2022/08/08 16:30:34 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

char *file = "a.out";

int errorExit(char *cmd)
{
	perror(cmd);
	return(EXIT_FAILURE);
}

char *getHexValue(int value)
{
	char *paddingString = NULL;
	int paddingIteration;
	char hexValue[50];
	char *res = NULL;


	sprintf(hexValue, "%x", value);
	paddingIteration = 16 - ft_strlen(hexValue);

	if(paddingIteration > 0)
	{
		paddingString = ft_strnew(paddingIteration);
		for(int i = 0; i < paddingIteration; i++)
			paddingString[i] = '0';

		res = ft_strjoin(paddingString, hexValue);
		free(paddingString);
		return res;
	}
	return NULL;
}

char *save_first_letter(char *str)
{
	for (int i = 0; i < ft_strlen(str); i++)
	{
		if (str[i] != '_')
		{
			char *tmp = &str[i];
			return ft_strlower(tmp);
		}
	}
	return NULL;
}

// st_shndx == 13 && st_size == 0  = t
// st_shndx == 13 && st_size != 0  = T
// st_shndx == 24 = b/B
// st_shndx == 23 = d/D /TODO diff to learn  local or global binding value :)
// st_shndx == 0 = U undefined
// R/r read only data section

char set_symbol(Elf64_Sym *sym, Elf64_Shdr *sectionHeaderStringTable, Elf64_Shdr *section, char *ptr, Elf64_Shdr *shstr, Elf64_Ehdr *header)
{
	if (ft_strcmp(ptr + shstr->sh_offset + sym->st_name, "main") == 0)
	{
		printf("lol\nlol\nlol\n");
		printf("Section name = %u (%s)\n", section->sh_name, ptr + sectionHeaderStringTable->sh_offset + section->sh_name);
		Elf64_Shdr *tsection = (Elf64_Shdr *)(ptr + header->e_shoff + (header->e_shentsize * sym->st_shndx));
		printf("Section name = %u (%s)\n", tsection->sh_name, ptr + sectionHeaderStringTable->sh_offset + tsection->sh_name);
	}
	Elf64_Shdr *linkedSection = (Elf64_Shdr *)(ptr + header->e_shoff + (header->e_shentsize * sym->st_shndx));
	char *linkedSectionName = ptr + sectionHeaderStringTable->sh_offset + linkedSection->sh_name;


	// if (sym->st_shndx == 13 && ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	if (ft_strcmp(linkedSectionName, ".text") == 0 && ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
		return 't';
	if (ft_strcmp(linkedSectionName, ".text") == 0 && ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
		return 'T';
	if (ft_strcmp(linkedSectionName, ".bss") == 0 && ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
		return 'b';
	if (ft_strcmp(linkedSectionName, ".bss") == 0 && ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
		return 'B';
	if (ft_strcmp(linkedSectionName, ".data") == 0 && ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
		return 'd';
	if (ft_strcmp(linkedSectionName, ".data") == 0 && ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
		return 'D';
	if (ELF64_ST_BIND(sym->st_info) == STB_WEAK && sym->st_value != 0)
		return 'W';
	if (ELF64_ST_BIND(sym->st_info) == STB_WEAK && ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE)
		return 'w';

	if (sym->st_shndx == 0)
		return 'U';
	return '.';
}

void handle64(char *ptr)
{
	Elf64_Ehdr	*header = (Elf64_Ehdr *)ptr;
	Elf64_Sym	*symbol;
	Elf64_Shdr	*section;
	Elf64_Shdr	*sectionHeaderStringTable;
	t_sym		*symbolsList = NULL;
	int			nSymbols = 0;

	// = the name section header : ptr + the header offset + the size of a section * the index of name section header
	// allowing us to save sectionHeaderStringTable on the good section :(.shrstrtab)

	// .shstrtab This  section  holds  section  names.   This  section  is  of type SHT_STRTAB.No attribute types are used.
	sectionHeaderStringTable = (Elf64_Shdr *)(ptr + header->e_shoff + (header->e_shentsize * header->e_shstrndx));
	#ifdef DEBUG
		logPrintHeader(header);
	#endif
	for(int i = 0; i < header->e_shnum; i++)
	{
		section = (Elf64_Shdr *)(ptr + header->e_shoff + (header->e_shentsize * i));
		#ifdef DEBUG
			logPrintSection(section, ptr, i, sectionHeaderStringTable);
		#endif
		if (section->sh_type == SHT_SYMTAB)
		{
			Elf64_Shdr *shstr;
			nSymbols += section->sh_size / section->sh_entsize;
			// same technique than sectionHeaderStringTable, to place us on the good section : ptr + the header offset + size of a secton times the section index
			shstr = (Elf64_Shdr *)(ptr + header->e_shoff + (header->e_shentsize * section->sh_link));
			int tot = 0;
			for (int j = 0; j < nSymbols; j++)
			{
				// ptr + section offset + size * symbols index
				symbol = (Elf64_Sym *)(ptr + section->sh_offset + (section->sh_entsize* j));
				if (symbol->st_info == STT_SECTION || symbol->st_info == STT_FILE)
					tot--;
				else
				{
					t_sym *new;
					new = ft_symnew();
					//initSymbol(new);
					new->name = ptr + shstr->sh_offset + symbol->st_name;
					new->symbol = set_symbol(symbol, sectionHeaderStringTable, section, ptr, shstr, header);
					new->hexValue = getHexValue(symbol->st_value);
					new->firstLetterInName = save_first_letter(ptr + shstr->sh_offset + symbol->st_name);

					//addBackSymbol(&symbolsList, new);

					ft_symadd_back(&symbolsList, new);
					tot++;
					#ifdef DEBUG
						logPrintSymbol(symbol, ptr, shstr);
					#endif
				}
			}
		}
	}
	sortOutput(&symbolsList);
	displayOutput(symbolsList);
	freeSymbols(&symbolsList);
}

void handle32(char *ptr)
{
	#ifdef DEBUG
		printf("32 format");
	#endif
}

void nm(char *ptr)
{
	if (hasElfMagicNumber(ptr))
	{
		if (is64bitArchitecture(ptr))
			handle64(ptr);
		else if (is32bitArchitecture(ptr))
			handle32(ptr);
		else if (isInvalidClass(ptr))
			printf("ft_nm: Invalid class file\n");
		else
			printf("ft_nm: %s: file format not recognized\n", file);
	}
	else
		printf("ft_nm: %s: file format not recognized\n", file);
}



int main(int ac, char **av)
{
	int			fd;
	char		*ptr;
	struct stat	buf;

	if(parsing(ac, av))
	{
		if(!openFile(file, &fd))
			return errorExit("open");
		if(!getFileStatus(&buf, fd))
			return errorExit("fstat");
		if((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return errorExit("mmap");

		nm(ptr);
		if(munmap(ptr, buf.st_size) < 0)
			return errorExit("munmap");
		closeFile(fd);
	}
	return (EXIT_SUCCESS);
}