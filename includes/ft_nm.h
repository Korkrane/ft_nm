/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:39:54 by bahaas            #+#    #+#             */
/*   Updated: 2022/06/22 18:40:35 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include "../libft/libft.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <elf.h>

typedef enum e_flags
{
	a = 1 << 0,
	g = 1 << 1,
	u = 1 << 2,
	r = 1 << 3,
	p = 1 << 4,
} t_flags;

typedef struct t_sym
{
    char *hexValue;
    char *name;
    char symbol;
    char *firstLetterInName;
    int shndx;
    struct t_sym *next;
} t_sym;

extern char *file;

int help();
void addOptionWithoutParameter(char opt);
int parsing(int ac, char **av);

bool getFileStatus(struct stat *buf, int fd);
bool openFile(char *path, int *fd);
void closeFile(int fd);

bool hasElfMagicNumber(char *ptr);
bool is64bitArchitecture(char *ptr);
bool is32bitArchitecture(char *ptr);
bool isInvalidClass(char *ptr);

void sortOutput(t_sym **symList);
void displayOutput(t_sym *sym);

t_sym *ft_symnew(void);
void ft_symadd_back(t_sym **asym, t_sym *new);
void displayOutput(t_sym *sym);
void freeSymbols(t_sym **lst);

void reverse_sort_symlist(struct t_sym **head);
void sort_symlist(struct t_sym **head);

void logPrintSymbol(Elf64_Sym *symbol, char *ptr, Elf64_Shdr *shstr);
void logPrintSection(Elf64_Shdr *section, char *ptr, int i, Elf64_Shdr *shstrhdr);
void logPrintHeader(Elf64_Ehdr *header);

char *getHexValue(int value)
void logPrintEnabledOptions();

int errorExit(char *cmd);
#endif