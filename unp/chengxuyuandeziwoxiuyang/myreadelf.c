#include <elf.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
void printShdr(Elf32_Shdr* shdr, void* shstroff)
{
    printf("{\n");
    printf("\tsh_name = %d (%s)\n",shdr->sh_name, (char*)(shstroff+shdr->sh_name));
    printf("\tsh_type = %d\n",shdr->sh_type);
    printf("\tsh_flags = %d\n",shdr->sh_flags);
    printf("\tsh_addr = %d\n",shdr->sh_addr);
    printf("\tsh_offset = %d\n",shdr->sh_offset);
    printf("\tsh_size = %d\n",shdr->sh_size);
    printf("\tsh_link = %d\n",shdr->sh_link);
    printf("\tsh_info = %d\n",shdr->sh_info);
    printf("\tsh_addralign = %d\n",shdr->sh_addralign);
    printf("\tsh_entsize = %d\n",shdr->sh_entsize);
    printf("}\n");
}
int main(int argc,char* argv[])
{
    if(argc<=1) {
        fprintf(stderr,"usage: %s <file ...>\n",argv[0]);
        return 1;
    }
    for(int i=1;i<argc;++i) {
        const char *filepath = argv[i];
        struct stat filestat;
        stat(filepath, &filestat);
        int fd = open(filepath, O_RDWR);
        void *mapaddr = mmap(NULL, filestat.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
        Elf32_Ehdr *ehdr = (Elf32_Ehdr*)mapaddr;
        printf("section header offset: %x\n",ehdr->e_shoff);
        for(int j=0;j<ehdr->e_shnum;++j) { //number of sections
            Elf32_Shdr *shdr = (Elf32_Shdr*)(mapaddr+ehdr->e_shoff+j*ehdr->e_shentsize);
            printf("%d",j);
            void *shstraddr_section = mapaddr+ehdr->e_shoff+(ehdr->e_shstrndx)*ehdr->e_shentsize;
            //printShdr(shstraddr_section, mapaddr);
            //exit(1);
            printShdr(shdr, (void*)(((Elf32_Shdr*)shstraddr_section)->sh_offset+mapaddr));
        }
        printf("file %d finished.\n",i);
    }
    return 0;
}
