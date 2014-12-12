char* str = "hello world!\n";
void print()
{
    __asm__(
        "movl $13,%%edx \n\t"
        "movl %0,%%ecx \n\t"
        "movl $0,%%ebx \n\t"
        "movl $4,%%eax \n\t"
        "int $0x80"
        :
        :"r"(str)
        :"ebx","ecx","edx"
    );
}

void exit()
{
    __asm__(
        "movl $42,%ebx \n\t"
        "movl $1,%eax \n\t"
        "int $0x80"
    );
}

void nomain()
{
    print();
    exit();
}
