# Four Stages of Compilation 

Every C (and many other high-level) programs go through four main stages before becoming an executable. Here’s how it works with **GCC**:

---

## 1. The Four Stages, at a Glance

```text
┌────────────────────┐
│ 1. Source code     │  main.c
└────────┬───────────┘
         │  (Preprocess)
         ▼
┌────────────────────┐
│ 2. Preprocessed    │  main.i
│    source          │
└────────┬───────────┘
         │  (Compile)
         ▼
┌────────────────────┐
│ 3. Assembly text   │  main.s
└────────┬───────────┘
         │  (Assemble)
         ▼
┌────────────────────┐
│ 4. Object file     │  main.o
└────────┬───────────┘
         │  (Link)
         ▼
┌────────────────────┐
│ Executable binary  │  hello
└────────────────────┘
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

## 3. “Hello, world!” Walk‑through

### 3.1 Write the C source

```c
// main.c
#include <stdio.h>

int main() {
    printf("Hello, world!\n");
    return 0;
}
```

### 3.2 Generate each stage

```bash
gcc -E  main.c -o main.i    # preprocess
gcc -S  main.c -o main.s    # compile → assembly
gcc -c  main.s -o main.o    # assemble → object
gcc      main.o -o hello    # link → executable
```

### 3.3 Inspect the assembly (`main.s`)

Open `main.s` in your editor – you’ll see something like:

```asm
	.file	"main.c"
	.text
	.globl	main
	.p2align	4, 0x90
main:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	L_.LC0(%rip), %rdi      # address of "Hello, world!\n"
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	ret
L_.LC0:
	.string	"Hello, world!\n"
```

---




