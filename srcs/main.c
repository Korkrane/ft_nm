/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:38:04 by bahaas            #+#    #+#             */
/*   Updated: 2022/07/27 19:32:56 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

//16 times
char *hex_value(int lul)
{
    char hex_val[50];

    sprintf(hex_val, "%x", lul);
    int pad = 0;
    int currsize = ft_strlen(hex_val);
    pad = 16 - currsize;
    char *l;
    if(pad)
    {
        l = ft_memalloc(pad);
        ft_memset(l, '0', pad);
    }
    return ft_strjoin(l, hex_val);
}

char *save_first_letter(char *str)
{
    for (int i = 0; i < ft_strlen(str); i++)
    {
        if (str[i] != '_')
        {
            char *tmp = &str[i];
            return (ft_strdup(ft_strlower(tmp)));
        }
    }
    return 0;
}

// st_shndx == 13 && st_size == 0  = t
// st_shndx == 13 && st_size != 0  = T
// st_shndx == 24 = b/B
// st_shndx == 23 = d/D /TODO diff to learn  local or global binding value :)
// st_shndx == 0 = U undefined
// R/r read only data section

int compSectionName(Elf64_Sym *sym)
{
 return true;
}

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

void handle_64(char *ptr)
{
    Elf64_Ehdr *header;
    Elf64_Sym *symbol;
    Elf64_Shdr *section;
    Elf64_Shdr *sectionHeaderStringTable;
    t_sym *symList;
    int nSymbols;

    header = (Elf64_Ehdr *)ptr;
    nSymbols = 0;

    // = the name section header : ptr + the header offset + the size of a section * the index of name section header
    // allowing us to save sectionHeaderStringTable on the good section :(.shrstrtab)

    // .shstrtab This  section  holds  section  names.   This  section  is  of type SHT_STRTAB.No attribute types are used.
    sectionHeaderStringTable = (Elf64_Shdr *)(ptr + header->e_shoff + (header->e_shentsize * header->e_shstrndx));

    logPrintHeader(header);

    for(int i = 0; i < header->e_shnum; i++)
    {
        section = (Elf64_Shdr *)(ptr + header->e_shoff + (header->e_shentsize * i));
        logPrintSection(section, ptr, i, sectionHeaderStringTable);
        if (section->sh_type == SHT_SYMTAB)
        {
            Elf64_Shdr *shstr;
            nSymbols += section->sh_size / section->sh_entsize;
            // same technique than sectionHeaderStringTable, to place us on the good section : ptr + the header offset + size of a secton times the section index
            shstr = (Elf64_Shdr *)(ptr + header->e_shoff + (header->e_shentsize * section->sh_link));
            int tot = 0;
            for( int j = 0; j < nSymbols; j++)
            {
                // ptr + section offset + size * symbols index
                symbol = (Elf64_Sym *)(ptr + section->sh_offset + (section->sh_entsize* j));
                if (symbol->st_info == STT_SECTION || symbol->st_info == STT_FILE)
                    tot--;
                else
                {
                    t_sym *new;
                    new = ft_symnew();
                    new->name = ptr + shstr->sh_offset + symbol->st_name;
                    new->symbol = set_symbol(symbol, sectionHeaderStringTable, section, ptr, shstr, header);
                    new->value = hex_value(symbol->st_value);
                    new->firstLetterInName = save_first_letter(ptr + shstr->sh_offset + symbol->st_name);
                    ft_symadd_back(&symList, new);
                    tot++;
                    logPrintSymbol(symbol, ptr, shstr);
                }
            }
            //printf("tot = %d\n", tot);
        }
    }
    sort_symlist(&symList);
    symlist_display(symList);
}

void handle_32(char *ptr)
{
    ;
}

void nm(char *ptr)
{
    if (ptr[0] == ELFMAG0 && ptr[1] == ELFMAG1 && ptr[2] == ELFMAG2 && ptr[3] == ELFMAG3)
    {
        if (ptr[4] == ELFCLASS64)
        {
            printf("64 format");
            handle_64(ptr);
        }
        else if (ptr[4] == ELFCLASS32)
        {
            printf("32 format");
            handle_32(ptr);
        }
        else if (ptr[4] == ELFCLASSNONE)
        {
            printf("Invalid class file");
        }
        else
        {
            ;
        }
    }
    else
        printf("File format unknown");
}

int main(int ac, char **av)
{
    int fd;
    char *ptr;
    struct stat buf;

    if(ac != 2)
    {
        fprintf(stderr, "give arg\n");
        return(EXIT_FAILURE);
    }
    if((fd = open(av[1], O_RDONLY)) < 0)
    {
        perror("open");
        return(EXIT_FAILURE);
    }
    if(fstat(fd, &buf) < 0)
    {
        perror("fstat");
        return (EXIT_FAILURE);
    }
    if((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    {
        perror("mmap");
        return (EXIT_FAILURE);
    }
    nm(ptr);
    if(munmap(ptr, buf.st_size) < 0)
    {
        perror("munmap");
        return (EXIT_FAILURE);
    }

   return(EXIT_SUCCESS);
}