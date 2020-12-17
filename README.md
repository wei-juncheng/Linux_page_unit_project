# Linux Page Unit Project
## Introduction
- This project is a simple demonstration for translating virtual address to physical address.
- Using Page Global Directory(PGD), Page Upper Directory(PUD), Page Middle Directory(PMD), Page Table(PTE)
- Implemented with a Linux kernel module.

## Environment
- Linux Kernel 3.10.104
- Ubuntu Desktop 16.04 32-bit
- Ubuntu Package:
    - wget
    - gcc
    - bc
    - libgetopt-argvfile-perl
    - libncurses5-dev

## Setup
- Compile and install Linux kernel(v3.10.104) from source code
    - reference
        - https://blog.kaibro.tw/2016/11/07/Linux-Kernel%E7%B7%A8%E8%AD%AF-Ubuntu/
- Create `Makefile` for compiling Linux Module
    - reference
        - https://wwssllabcd.github.io/blog/2012/11/13/how-to-make-linux-module/
- Compile `hello.c` and using `dmesg` to watch the output of kernel module.