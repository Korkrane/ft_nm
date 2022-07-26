/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:38:04 by bahaas            #+#    #+#             */
/*   Updated: 2022/07/26 21:30:50 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
//#include <mach-o/loader.h>
//#include <mach-o/nlist.h>
#include <elf.h>

#define MH_MAGIC_64 0xfeedfacf

void print_output(int nsyms, int symoff, int stroff, char *ptr)
{
    // int i;
    // char *stringtable;
    // struct nlist_64 *array;

    // array = (void *) ptr + symoff;
    // stringtable = (void *)ptr + stroff;

    // for(i = 0; i < nsyms; ++i)
    // {
    //     printf("%s\n", stringtable + array[i].n_un.n_strx);
    // }
}

//16 times
char *hex_value(int lul)
{
    char hex_val[50];

    sprintf(hex_val, "%x", lul);
    //char *value = ft_itoa(hex_val);
    int pad = 0;
    int currsize = ft_strlen(hex_val);
    pad = 16 - currsize;
    char *l;
    if(pad)
    {
        l = ft_memalloc(pad);
        ft_memset(l, '0', pad);
        //printf("pad = %d //// %s\n", pad, l);
    }
    return ft_strjoin(l, hex_val);
}

char *save_first_letter(char *str)
{
    //printf("%s\n", str);
    for (int i = 0; i < ft_strlen(str); i++)
    {
        if (str[i] != '_')
        {
            char *tmp = &str[i];
            // printf("%s\n", tmp);
            // for (int j = 0; j < strlen(tmp); j++)
            //     if (tmp[j] >= 'A' && tmp[j] <= 'Z')
            //     {
            //         printf("%cd", tmp[j]);
            //         tmp[j] += 32;
            //     }
            return (ft_strdup(ft_strlower(tmp)));
        }
    }
    return 0;
}

// st_shndx == 13 && st_size == 0  = t
// st_shndx == 13 && st_size != 0  = T
// st_shndx == 24 = b/B /TODO diff to learn
// st_shndx == 23 = d/D /TODO diff to learn
// st_shndx == 0 = U undefined
char set_symbol()
{
    return 'x';
}

void handle_64(char *ptr)
{
    //printf("lol\n");
    // int ncmds;
    // int i;
    // struct mach_header_64 *header;
    // struct load_command *lc;
    // struct symtab_command *sym;
    Elf64_Ehdr *header;
    Elf64_Sym *elf_sym;
    Elf64_Shdr *sheader;
    t_sym *lSym;

    header = (Elf64_Ehdr *)ptr;
    //printf("%s\n", header->e_ident); /* ELF "magic number" */
    //printf("e_type %d\n", header->e_type);
    //printf("e_machine %d\n", header->e_machine);
    //printf("e_version %d\n", header->e_version);
    //printf("e_entry %ld\n", header->e_entry); /* Entry point virtual address */
    //printf("e_phoff %ld\n", header->e_phoff); /* Program header table file offset */
    //printf("e_shoff %ld\n", header->e_shoff); /* Section header table file offset */
    //printf("e_flags %d\n", header->e_flags);
    //printf("e_ehsize %d\n", header->e_ehsize);
    //printf("e_phentsize %d\n", header->e_phentsize);
    //printf("e_phnum %d\n", header->e_phnum);
    //printf("e_shentsize %d\n", header->e_shentsize);
    //printf("e_shnum %d\n", header->e_shnum);
    //printf("e_shstrndx %d\n", header->e_shstrndx);
    // header = (struct mach_header_64 *)ptr;
    // ncmds = header->ncmds;
    // lc = ptr + sizeof(*header);
    // for(i = 0; i < ncmds; ++i)
    // {
    //     if(lc->cmd == LC_SYMTAB)
    //     {
    //         sym = (struct symtab_command *)lc;
    //         printf("nb symboles; %d\n",sym->nsyms);
    //         print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
    //         break;
    //     }
    //     lc = (void *)lc + lc->cmdsize;
    // }
    Elf64_Shdr *shstrhdr;
    int sym_count = 0;
    shstrhdr = (Elf64_Shdr *)(ptr + header->e_shoff + (header->e_shentsize * header->e_shstrndx));
    //printf("%lu\n", shstrhdr->sh_offset);
    for(int i = 0; i < header->e_shnum; ++i)
    {
        sheader = (Elf64_Shdr *)(ptr + header->e_shoff + (header->e_shentsize * i));
        printf("---- Section %d -----\n", i);
        printf("Section name = %u (%s)\n", sheader->sh_name, ptr + shstrhdr->sh_offset + sheader->sh_name);
        printf("Section type = %u\n", sheader->sh_type);        /* Type of section */
        printf("Section flags = %lu\n", sheader->sh_flags); /* Miscellaneous section attributes */
        printf("Section addr = %lu\n", sheader->sh_addr);   /* Section virtual addr at execution */
        printf("Section offset = %lu\n", sheader->sh_offset); /* Section file offset */
        printf("Section size = %lu\n", sheader->sh_size);     /* Size of section in bytes */
        printf("Section link = %u\n", sheader->sh_link);      /* Index of another section */
        printf("Section info = %u\n", sheader->sh_info);      /* Additional section information */
        printf("Section addralign = %lu\n", sheader->sh_addralign); /* Section alignment */
        printf("Section entsize = %lu\n", sheader->sh_entsize);    /* Entry size if section holds table */
        if (sheader->sh_type == SHT_SYMTAB)
        {
            Elf64_Shdr *shstr;
            sym_count += sheader->sh_size / sheader->sh_entsize;
            //printf("has %d symbols\n", sym_count);
            shstr = (Elf64_Shdr *)(ptr + header->e_shoff+ (header->e_shentsize * sheader->sh_link));
            int tot = 0;
            for( int j = 0; j < sym_count; j++)
            {
                elf_sym = (Elf64_Sym *)(ptr + sheader->sh_offset + (sheader->sh_entsize* j));
                if (elf_sym->st_info == STT_SECTION || elf_sym->st_info == STT_FILE)
                {
                    tot--;
                }
                else
                {
                    t_sym *new;
                    new = ft_symnew();
                    new->name = ptr + shstr->sh_offset + elf_sym->st_name;
                    new->symbol = set_symbol();
                    new->value = hex_value(elf_sym->st_value);
                    new->firstLetterInName = save_first_letter(ptr + shstr->sh_offset + elf_sym->st_name);
                    ft_symadd_back(&lSym, new);
                    //sort_symlist(&lSym);
                    tot++;
                    printf("----------\n");
                    printf("st_name %u (%s)\n", elf_sym->st_name, ptr + shstr->sh_offset + elf_sym->st_name);     /* Symbol name, index in string tbl */
                    printf("st_info %u\n", elf_sym->st_info);                                                     /* Type and binding attributes */
                    printf("st_other %u\n", elf_sym->st_other);                                                   /* No defined meaning, 0 */
                    printf("st_shndx %u\n", elf_sym->st_shndx);                                                   /* Associated section index */
                    printf("st_value %lu (%s)\n", elf_sym->st_value, hex_value(elf_sym->st_value));               /* Value of the symbol */
                    printf("st_size %lu\n", elf_sym->st_size);                                                /* Associated symbol size */
                    printf("%d\n", ELF64_ST_TYPE(elf_sym->st_info));
                    printf("%s %s\n", hex_value(elf_sym->st_value), ptr + shstr->sh_offset + elf_sym->st_name); // FOR EASY DISPLAY
                }
                //symlist_display(lSym);
            }
            //printf("tot = %d\n", tot);
        }
    }
    //sort_symlist(&lSym);
    //symlist_display(lSym);
    sort_symlist(&lSym);
    //printf("------------------------\n");
    symlist_display(lSym);
}

void nm(char *ptr)
{
    // int magic_number;

    // magic_number = *(int *)ptr;
    // printf("lol: %d\n", magic_number);
    // if(magic_number == MH_MAGIC_64)
    //     handle_64(ptr);
    //printf("lol: %s\n", ptr);
    if (ptr[0] == ELFMAG0 && ptr[1] == ELFMAG1 && ptr[2] == ELFMAG2 && ptr[3] == ELFMAG3)
    {
        if (ptr[4] == ELFCLASS64)
        {
            //printf("64 format");
            handle_64(ptr);
        }
        else if (ptr[4] == ELFCLASS32)
            printf("32 format");
    }
    else
        printf("File format not recognized");
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