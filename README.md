# Reverse Engineering 101 - 2025 PDE Offsite - HW & BW Learning Lab!

## What is reverse engineering (in general)

Reverse engineering is the process of discovering the principles of a device, object, or system through analysis of its structure, function, and operation. It involves taking something apart to understand how it works, often without having access to the original design documentation or source materials.

This practice spans far beyond software - engineers reverse engineer competitor products, archaeologists reverse engineer ancient technologies, and mechanics reverse engineer vintage car parts that are no longer manufactured. In essence, it's detective work: starting with the final product and working backwards to understand the original design decisions, materials, and processes that created it.

The goal isn't necessarily to copy, but to understand, learn, improve, or in some cases, find vulnerabilities or weaknesses that weren't intended by the original creators.

## A brief story about me and hacking

I grew up a very curious kid. I always loved to disassemble my toys. The problem is that I could never assemble them back properly. Well, it took some time until I figured out how to put them back together, but when I did, I had twice more fun.

Going forward a few years, I hacked into my school’s database for fun (I wanted to put funny pictures of my classmates on the website, go figure), but I accidentally wrote a bad SQL query and ended up updating all rows from the table that their website was using.

After that and many other stories, I figured what I loved to do. Graduated in computer engineering, and started working with software.

Oh, talking about computer engineering…

## A quick recap on computer software

Software reverse engineering focuses on understanding how programs work without access to their source code. When you compile a C program, the human-readable code gets transformed into machine code - a binary file containing instructions that the processor can execute directly.

The challenge is that this transformation is typically one-way: while we can compile source code into binaries easily, going from binary back to readable code is much harder. The original variable names, comments, and high-level structure are lost in the compilation process.

However, the core logic remains. Reverse engineers use tools like:

- **Disassemblers** (convert machine code back to assembly language)
- **Decompilers** (attempt to recreate higher-level code from binaries)
- **Debuggers** (step through program execution line by line)
- **Hex editors** (examine raw binary data)

The process often involves:

1. **Static analysis** - examining the binary without running it
2. **Dynamic analysis** - observing the program's behavior while it executes
3. **Pattern recognition** - identifying common programming constructs and algorithms
4. **Hypothesis testing** - making educated guesses about functionality and testing them

## From Source Code to Machine Code: The Compilation Journey

When you write C code, you're creating human-readable instructions that describe what you want the computer to do. However, processors don't understand C - they only understand machine code, which consists of binary patterns representing specific processor instructions.

The compilation process transforms your source code through several stages:

**1. Preprocessing** - The preprocessor handles directives like `#include` and `#define`, essentially copy-pasting header files and expanding macros to create a single, expanded source file.

**2. Compilation** - The compiler translates your C code into assembly language, which uses human-readable mnemonics (like `mov`, `add`, `cmp`) to represent processor instructions. This is where your variables get assigned to memory locations or CPU registers, and your control flow (`if`, `while`, `for`) becomes conditional jumps and branches.

**3. Assembly** - The assembler converts assembly language into object code - actual machine instructions represented as binary numbers. Your `printf("Hello")` becomes a series of bytes that tell the processor exactly which registers to use and which memory addresses to access.

**4. Linking** - The linker combines your object file with library code (like the standard C library) and resolves all function calls and memory addresses, producing the final executable binary.

The resulting binary file contains pure machine code - sequences of bytes that the processor can execute directly. When you run `./your_program`, the operating system loads these bytes into memory and tells the CPU to start executing them.

This is why reverse engineering is challenging: we're trying to work backwards from those raw bytes to understand the original programmer's intent, without the helpful variable names, comments, or high-level structure that existed in the source code.

Modern tools like Ghidra, IDA Pro, and x64dbg make this process more accessible, but the fundamental skill is learning to think like both the original programmer and the computer executing the code.

For our examples, we'll see how even simple password checks can be understood and bypassed through careful analysis of what the program actually does versus what it appears to do.

## Walkthrough/Challenge

…

We’ll be performing mainly static analysis.

The beauty of reverse engineering/cracking is that there is not just one correct answer or way to do it. Usually you can achieve the same goal using different techniques, ranging from brute forcing to patching.

Tools:

- Usually, I start with running [strings](https://linux.die.net/man/1/strings) against a file. It can give us some intereseting insights!
- We can also use [objdump](https://linux.die.net/man/1/objdump) to directly see

## First Binary

The first binary is pretty simple, there is actually no need for a specific reverse engineering software like GHidra.

## Second binary

This can be patched in multiple ways, we can alter the password_check function to always return true, or we can patch the branch operation that checks for the debug flag… The coolest way, in my opinion, is to always try and understand the original code and the original intention of the developer(s).

💡 There are more than 25 billion valid passwords for this one

## If we have time:

## GCC Installation Guide

This guide covers how to install GCC (GNU Compiler Collection) on different operating systems to compile your C program.

## Ubuntu/Debian Linux

GCC is usually pre-installed, but if not:

```bash
sudo apt update
sudo apt install gcc
```

To verify installation:

```bash
gcc --version
```

## macOS

### Option 1: Xcode Command Line Tools (Recommended)

```bash
xcode-select --install
```

### Option 2: Homebrew

First install Homebrew if you don't have it:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Then install GCC:

```bash
brew install gcc
```

Once GCC is installed, save your code to a file (e.g., `password_checker.c`) and compile:

```bash
make all
```

Then run:

- **Linux/macOS**: `./build/first`

## Troubleshooting

- If `gcc` command is not found, make sure it's in your PATH
- On some systems, you might need to use `gcc-11` or similar version-specific command

## Install GHidra

[NationalSecurityAgency/ghidra: Ghidra is a software reverse engineering (SRE) framework](https://github.com/NationalSecurityAgency/ghidra?tab=readme-ov-file#install)

---

# Tools

- https://linux.die.net/man/1/strings
- https://linux.die.net/man/1/objdump
- https://linux.die.net/man/1/strace
- https://github.com/NationalSecurityAgency/ghidra
- https://github.com/LaurieWired/GhidraMCP
- https://hex-rays.com/ida-free
