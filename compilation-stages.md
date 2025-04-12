# Four Stages of Compilation 

Every C (and many other high-level) programs go through four main stages before becoming an executable. Here’s how it works with **GCC**:

---

## 1. The Four Stages, at a Glance

```ascii
                          +-------------------------+
                          |  Source code (.c) file  |
                          +------------+------------+
                                       |
                                       v
       +-------------------------------+-------------------------------+
       |                   THE COMPILATION PROCESS                     |
       |                                                               |
       |   +------------------+                                        |
       |   |  Pre-Processor   |   // Handles directives like #include  |
       |   +--------+---------+   // and #define. Removes comments.    |
       |            |                                                  |
       |            v                                                  |
       |   +------------------+        +---------------------------+   |
       |   |     Compiler     |------>|    Assembly code (.s)     |    |
       |   +--------+---------+        +---------------------------+   |
       |            |               // Converts preprocessed code      |
       |            v               // into assembly instructions.     |
       |   +------------------+                                        |
       |   |     Assembler     |---------+                             |
       |   +--------+---------+          |                             |
       |            |                    |                             |
       |            v                    v                             |
       |   +------------------+     +----------------------+           |
       |   |      Linker       |<---|   Object file (.o)   |           |
       |   +--------+---------+     +----------------------+           |
       |            ^               // Converts assembly to            |
       |            |               // machine code. Output = .o       |
       |     +------+-------+                                          |
       |     |   Libraries  |     // Links external libraries and      |
       |     +--------------+     // functions with object file.       |
       +-------------------------------+-------------------------------+
                                       |
                                       v
                            +-------------------------+
                            |    Executable file      |
                            +-------------------------+
                               // Final binary ready
                               // to run on the system

```

```

---

## 2. Commands

```bash
# 1) Preprocess
gcc -E main.c -o main.i

# 2) Compile to assembly
gcc -S main.c -o main.s

# 3) Assemble to object file
gcc -c main.s -o main.o

# 4) Link into executable
gcc main.o -o hello

# Shortcut: all in one
gcc main.c -o hello
```
GCC can do all those steps for you and leave the intermediates lying around with one flag

```bash
gcc -save-temps main.c -o hello
```
---


### 3. Write the C source

```c
// main.c
#include <stdio.h>

int main() {
    printf("Hello, world!\n");
    return 0;
}
```

### 3.1 Generate each stage

```bash
gcc -E  main.c -o main.i    # preprocess
gcc -S  main.c -o main.s    # compile → assembly
gcc -c  main.s -o main.o    # assemble → object
gcc     main.o -o hello     # link → executable
```

### 3.3 Inspect the assembly (`main.s`)

Open `main.s` in your editor – you’ll see something like:

```asm
   1   |    .file   "main.c"
   2   │     .text
   3   │     .section    .rodata
   4   │ .LC0:
   5   │     .string "Hello, world!"
   6   │     .text
   7   │     .globl  main
   8   │     .type   main, @function
   9   │ main:
  10   │ .LFB0:
  11   │     .cfi_startproc
  12   │     pushq   %rbp
  13   │     .cfi_def_cfa_offset 16
  14   │     .cfi_offset 6, -16
  15   │     movq    %rsp, %rbp
  16   │     .cfi_def_cfa_register 6
  17   │     leaq    .LC0(%rip), %rax
  18   │     movq    %rax, %rdi
  19   │     call    puts@PLT
  20   │     movl    $0, %eax
  21   │     popq    %rbp
  22   │     .cfi_def_cfa 7, 8
  23   │     ret
  24   │     .cfi_endproc
  25   │ .LFE0:
  26   │     .size   main, .-main
  27   │     .ident  "GCC: (Debian 14.2.0-19) 14.2.0"
  28   │     .section    .note.GNU-stack,"",@progbits

```

---




