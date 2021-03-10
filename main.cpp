#include<stdio.h>
#include<memory.h>
#include<sys/mman.h>

typedef int (* inc_func)(int a); 

int main() {
    // The following machine codes are picked from the objdump output
    char code[] = {
        0x55,             // push rbp
        0x48, 0x89, 0xe5, // mov rsp, rbp
        0x89, 0xf8,       // mov edi, eax
        0x83, 0xc0, 0x01, // add $1, eax
        0x5d,             // pop rbp
        0xc3              // ret
    };
    
    // Allocate a piece of memory to store machine code
    void * temp = mmap(NULL, sizeof(code), PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    // Store machine code into memory
    memcpy(temp, code, sizeof(code));
    // Type conversion, converting memory to a function pointer
    inc_func p_inc = (inc_func)temp;
    // Call the function pointer
    printf("%d\n", p_inc(7));
    return 0;
}