#include "include/uelf.h"
int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage ./main file -a(-h -l -S)\n");
    exit(0);
  }

  FILE *elf_file = fopen(argv[1], "rb");

   char Hbuf[64];

   fread(Hbuf,1,sizeof(Hbuf),elf_file);

   Check_Elf(Hbuf);

  for (int i = 0; i < argc; i++) {
    const char *arg = argv[i];
    if (*arg == '-') {
      switch (arg[1]) {
      case 'a':
       Printable_Elf_Head((ELF_Head *)Hbuf);
        Printable_Elf_Section(elf_file, (ELF_Head *)Hbuf);
        Printable_Elf_Segment(elf_file, (ELF_Head *)Hbuf);
        Printable_Elf_Symbols(elf_file, (ELF_Head *)Hbuf);
        break;
      case 'h':
       Printable_Elf_Head((ELF_Head *)Hbuf);
        break;
      case 'S':
        Printable_Elf_Section(elf_file, (ELF_Head *)Hbuf);
        break;
      case 'l':
        Printable_Elf_Segment(elf_file, (ELF_Head *)Hbuf);
        break;
        case 's':
        Printable_Elf_Symbols(elf_file,(ELF_Head*)Hbuf);
        break;
      default:
        printf("usage ./main -a(-h -l -S)");
        break;
      }
    }
  }

  fclose(elf_file);
  return 0;
}
