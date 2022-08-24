#include "../includes/ft_nm.h"

void logPrintHeader(Elf64_Ehdr *header)
{
    printf("%s\n", header->e_ident); /* ELF "magic number" */
    printf("e_type %d\n", header->e_type); /* Object file type */
    printf("e_machine %d\n", header->e_machine); /* Architecture */
    printf("e_version %d\n", header->e_version); /* Object file version */
    printf("e_entry %ld\n", header->e_entry); /* Entry point virtual address */
    printf("e_phoff %ld\n", header->e_phoff); /* Program header table file offset */
    printf("e_shoff %ld\n", header->e_shoff); /* Section header table file offset */
    printf("e_flags %d\n", header->e_flags);  /* Processor-specific flags */
    printf("e_ehsize %d\n", header->e_ehsize); /* ELF header size in bytes */
    printf("e_phentsize %d\n", header->e_phentsize); /* Program header table entry size */
    printf("e_phnum %d\n", header->e_phnum);         /* Program header table entry count */
    printf("e_shentsize %d\n", header->e_shentsize); /* Section header table entry size */
    printf("e_shnum %d\n", header->e_shnum);         /* Section header table entry count */
    printf("e_shstrndx %d\n", header->e_shstrndx);   /* Section header string table index */ //-1 e_shnum
}

void logPrintSection(Elf64_Shdr *section, char *ptr, int i, Elf64_Shdr *sectionHeaderStringTable)
{
    printf("---- Section %d -----\n", i);
    printf("Section name = %u (%s)\n", section->sh_name, ptr + sectionHeaderStringTable->sh_offset + section->sh_name);
    printf("Section type = %u\n", section->sh_type);            /* Type of section */
    printf("Section flags = %lu\n", section->sh_flags);         /* Miscellaneous section attributes */
    printf("Section addr = %lu\n", section->sh_addr);           /* Section virtual addr at execution */
    printf("Section offset = %lu\n", section->sh_offset);       /* Section file offset */
    printf("Section size = %lu\n", section->sh_size);           /* Size of section in bytes */
    printf("Section link = %u\n", section->sh_link);            /* Index of another section */
    printf("Section info = %u\n", section->sh_info);            /* Additional section information */
    printf("Section addralign = %lu\n", section->sh_addralign); /* Section alignment */
    printf("Section entsize = %lu\n", section->sh_entsize);     /* Entry size if section holds table */
}

void logPrintSymbol(Elf64_Sym *symbol, char *ptr, Elf64_Shdr *shstr)
{
    printf("----------\n");
    printf("st_name %u (%s)\n", symbol->st_name, ptr + shstr->sh_offset + symbol->st_name); /* Symbol name, index in string tbl */
    printf("st_info %u\n", symbol->st_info);                                                /* Type and binding attributes */
    printf("st_other %u\n", symbol->st_other);                                              /* No defined meaning, 0 */
    printf("st_shndx %u\n", symbol->st_shndx);                                            /* Associated section index */
    char *s = getHexValue(symbol->st_value);
    printf("st_value %lu (%s)\n", symbol->st_value, s);           /* Value of the symbol */

    printf("st_size %lu\n", symbol->st_size);                                               /* Associated symbol size */
    printf("ELF64_ST_TYPE: %d, ELF64_ST_BIND:%d\n", ELF64_ST_TYPE(symbol->st_info), ELF64_ST_BIND(symbol->st_info));
    if (ELF64_ST_BIND(symbol->st_info) == STB_LOCAL)
        printf("LOCAL\n");
    else if (ELF64_ST_BIND(symbol->st_info) == STB_WEAK)
        printf("WEAK\n");
    else if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
        printf("GLOBAL\n");
    printf("%s %s\n", s, ptr + shstr->sh_offset + symbol->st_name); // FOR EASY DISPLAY
    free(s);
}

void logPrintEnabledOptions()
{
	printf("--- OPTIONS ENABLED ---\n");
	if(options & a)
		printf("a opt enabled\n");
	if(options & g)
		printf("g opt enabled\n");
	if(options & u)
		printf("u opt enabled\n");
	if(options & r)
		printf("r opt enabled\n");
	if(options & p)
		printf("p opt enabled\n");
}