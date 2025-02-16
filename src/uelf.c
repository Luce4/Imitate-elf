#include "../include/uelf.h"
int Check_Elf(char *buf) {
  const char *comp = buf;
  if (comp[0] == 0x7f && comp[1] == 0x45 && comp[2] == 0x4c &&
      comp[3] == 0x46) {
    return 0;
  } else {
    fprintf(stderr, "error:No Elf file");
    exit(0);
  }
}
inline static const char *get_elf_identFour(unsigned char ident) {
  switch (ident) {
  case 1:
    return "ELF32";
  case 2:
    return "ELF64";
  default:
    return "error";
  }
}
inline static const char *get_elf_identFive(unsigned int ident) {

  switch (ident) {
  case 1:
    return "little endian";
  case 2:
    return "big endian";
  default:
    return "error";
  }
}
inline static const char *get_elf_identSixteen(unsigned int ident) {
  switch (ident) {
  case 0:
    return "NO file type";
  case 1:
    return "Relocatable file";
  case 2:
    return "Executable file";
  case 3:
    return "Shared object file ";
  case 4:
    return "Core file";
  default:
    return "error";
  }
}
inline static const char *get_elf_identSeven(unsigned int ident) {
  switch (ident) {
  case 0:
    return "UNIX System V ABI";

  case 97:
    return "ARM";

  default:
    return "ohter type or error";
  }
}
inline static const char *get_elf_machine(unsigned short machine) {
  switch (machine) {
  case 0:
    return "No machine";
  case 62:
    return "Advanced Micro Devices X86-64";
  case 40:
    return "ARM";
  case 183:
    return "aarch64";
  default:
    return "other type or error";
  }
}
inline static const char *get_section_type(unsigned int type) {
  switch (type) {
  case 0:
    return "NULL";
  case 1:
    return "PROGBITS";
  case 2:
    return "SYMTAB";
  case 3:
    return "STRTAB";
  case 4:
    return "RELA";
  case 5:
    return "HASH";
  case 6:
    return "DYNAMIC";
  case 7:
    return "NOTE";
  case 8:
    return "NOBITS";
  case 9:
    return "REL";
  case 10:
    return "SHLIB";
  case 11:
    return "DYNSYM";
  case 14:
    return "INIT_ARRAY";
  case 15:
    return "FINI_ARRAY";
  case 16:
    return "PREINIT_ARRAY";
  case 17:
    return "GROUP";
  case 18:
    return "SYMTAB_SHNDX";

  case 0x6ffffff6:
    return "GNU_HASH";
  case 0x6fffffff:
    return "GNU_VERSYM";
  case 0x6ffffffa:
    return "GNU_VERNEED";
  default:
    return "UNKNOWN";
  }
}
inline static const char *get_section_flags(unsigned long long sh_flags) {
  switch (sh_flags) {
  case 0x1:
    return "W";
  case 0x2:
    return "A";
  case 0x4:
    return "X";
  case 0x8:
    return "M";
  case 0x10:
    return "S";
  case 0x20:
    return "I";
  case 0x40:
    return "L";
  case 0x80:
    return "O";
  case 0x100:
    return "T";
  case 0x3:
    return "WA";
  case 0x6:
    return "AX";
  case 0x5:
    return "WX";
  case 0x7:
    return "WAX";
  default:
    return " ";
  }
}
inline static const char *get_segment_type(unsigned int type) {
  switch (type) {
  case 0:
    return "NULL";
  case 1:
    return "LOAD";
  case 2:
    return "DYNAMIC";
  case 3:
    return "INTERP";
  case 4:
    return "NOTE";
  case 5:
    return "SHLIB";
  case 6:
    return "PHDR";
  case 7:
    return "TLS";

    // GNU
  case 0x6474e553:
    return "GNU_PROPERTY ";
  case 0x6474e550:
    return "GNU_EH_FRAME";
  case 0x6474e551:
    return "GNU_STACK";
  case 0x6474e552:
    return "GNU_RELRO";
  default:
    return "UNKNOWN";
  }
}
inline static const char *get_segment_flags(unsigned int type) {
  switch (type) {
  case 0x1:
    return "E";
  case 0x2:
    return "W";
  case 0x3:
    return "WE";
  case 0x4:
    return "R";
  case 0x5:
    return "RE";
  case 0x6:
    return "RW";
  case 0x7:
    return "RWE";
  default:
    return "UNKNOWN";
  }
}

int Printable_Elf_Head(ELF_Head *p) {
  printf("magic: ");
  for (int i = 0; i < 16; i++) {
    printf("%02x ", p->e_ident[i]);
  }

  printf("\n Class: %s\n", get_elf_identFour(p->e_ident[4]));
  printf(" data: %s\n", get_elf_identFive(p->e_ident[5]));
  printf(" Version:0x%x\n", p->e_ident[6]);

  printf(" OS/ABI: %s\n", get_elf_identSeven(p->e_ident[7]));

  printf(" API Version:%d\n", p->e_ident[8]);

  printf(" type: %s\n", get_elf_identSixteen(p->e_ident[16]));

  printf(" System architecture: %s\n", get_elf_machine(p->e_machine));

  printf(" Version:0x%x\n", p->e_version);
  printf(" start address:%lx\n", p->e_entry);
  printf(" Program header offset: 0x%lx\n", p->e_phoff);
  printf(" Section header offset: 0x%lx\n", p->e_shoff);
  printf(" Flags: 0x%x\n", p->e_flags);
  printf(" ELF header size: %u\n", p->e_ehsize);
  printf(" Program header entry size: %u\n", p->e_phentsize);
  printf(" Number of program headers: %u\n", p->e_phnum);
  printf(" Size of section headers: %u\n", p->e_shentsize);
  printf(" Number of section headers: %u\n", p->e_shnum);
  printf(" Section header string table index: %u\n\n", p->e_shstrndx);
  return 0;
}
int Printable_Elf_Section(FILE *file, ELF_Head *Head) {

  char *Secbuf[Head->e_shentsize * Head->e_shnum];

  fseek(file, Head->e_shoff, 0);

  fread(Secbuf, 1, Head->e_shentsize * Head->e_shnum, file);

  ELF_Section *Sec = (ELF_Section *)Secbuf;

  printf("\nThere are %d section headers, starting at offset 0x%lx:\n",Head->e_shnum, Head->e_shoff);
  printf("Section Header:\n");
  printf("\r[Nr] Name Type Address Offset Size EnSize Flag Link Info Align\n");

  fseek(file, (Sec + Head->e_shstrndx)->sh_offset, 0);
  char value[(Sec + Head->e_shstrndx)->sh_size];
  fread(value, 1, (Sec + Head->e_shstrndx)->sh_size, file);

  int index = 0;

  for (int i = 0; i < Head->e_shnum; i++) {
    index = Sec[i].sh_name;
    printf("[%02d] %s ", i, value + index);
    printf("%s ", get_section_type(Sec[i].sh_type));
    printf("0x%llx ", Sec[i].sh_addr);
    printf("0x%llx 0x%llx %llx \n", Sec[i].sh_offset, Sec[i].sh_size,Sec[i].sh_entsize);
    printf(" [%02d] ",i);
    printf("%s ", get_section_flags(Sec[i].sh_flags));
    printf("%d %d %llx \n ", Sec[i].sh_link, Sec[i].sh_info,Sec[i].sh_addralign);
  }
  return 0;
}
int Printable_Elf_Segment(FILE *file, ELF_Head *Head) {
  if (fseek(file, Head->e_phoff, SEEK_SET) == -1) {
    fprintf(stderr, "error: lseek ");
    exit(0);
  }

  char Segbuf[Head->e_phentsize * Head->e_phnum];
  fread(Segbuf, 1, Head->e_phentsize * Head->e_phnum, file);

  ELF_Segment *segmnt = (ELF_Segment *)Segbuf;
  printf("\n\nElf file type %s\n",get_elf_identSixteen(Head->e_type));
  printf("Entry point 0x%lx\n",Head->e_entry);
  printf("There are %d program headers, starting at offset %ld\n",Head->e_phnum,Head->e_phoff);
  printf(" [Type] [Offset] [Physics_address] [Virtual_address] [Physics_size] [Virtual_size] [Flag] [Align]\n ");
  for (int i = 0; i < Head->e_phnum; i++) {
    printf("[%02d] %s ",i,get_segment_type(segmnt[i].p_type));
    printf("0x%llx ", segmnt[i].p_offset);
    printf("0x%llx 0x%llx ", segmnt[i].p_paddr, segmnt[i].p_vaddr);
    printf("0x%llx \n [%02d] 0x%llx ", segmnt[i].p_filesz,i, segmnt[i].p_memsz);
    printf("%s  0x%llx \n ", get_segment_flags(segmnt[i].p_flags),segmnt[i].p_align);

    if (segmnt[i].p_type == 3) {
      char dynBuf[segmnt[i].p_filesz + 1];
      if (fseek(file, segmnt[i].p_offset, SEEK_SET) == -1) {
        fprintf(stderr, "error: fseek ");
        exit(0);
      }
      fread(dynBuf, 1, segmnt[i].p_filesz, file);
      dynBuf[segmnt[i].p_filesz] = '\0';
      printf("Dynsym Loader:[%s]\n ", dynBuf);
    }
  }

  return 0;
}
