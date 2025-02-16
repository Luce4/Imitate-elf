#ifndef USER_ELF
#define USER_ELF
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  unsigned char e_ident[16];
  unsigned short e_type;
  unsigned short e_machine;
  unsigned int e_version;
  unsigned long int e_entry;
  unsigned long int e_phoff;
  unsigned long int e_shoff;
  unsigned int e_flags;
  unsigned short e_ehsize;
  unsigned short e_phentsize;
  unsigned short e_phnum;
  unsigned short e_shentsize;
  unsigned short e_shnum;
  unsigned short e_shstrndx;

} ELF_Head;

typedef struct {
  unsigned int sh_name;
  unsigned int sh_type;
  unsigned long long sh_flags;
  unsigned long long sh_addr;
  unsigned long long sh_offset;
  unsigned long long sh_size;
  unsigned int sh_link;
  unsigned int sh_info;
  unsigned long long sh_addralign;
  unsigned long long sh_entsize;
} ELF_Section;

typedef struct {
  unsigned int p_type;
  unsigned int p_flags;
  unsigned long long p_offset;
  unsigned long long p_vaddr;
  unsigned long long p_paddr;
  unsigned long long p_filesz;
  unsigned long long p_memsz;
  unsigned long long p_align;
} ELF_Segment;

typedef struct {
  unsigned int  st_name; 
  unsigned char st_info;
  unsigned char st_other; 
  unsigned short  st_shndx; 
  unsigned long long st_value; 
  unsigned long long st_size;
} ELF_Symbols;

extern int Check_Elf(char *buf);
extern int Printable_Elf_Head(ELF_Head *p);
extern int Printable_Elf_Section(FILE* file, ELF_Head *Head);
extern int Printable_Elf_Segment(FILE* file, ELF_Head *Head);
#endif
