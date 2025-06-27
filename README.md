# 💻 minishell - 42 School

**minishell** is a custom shell implementation developed in C as a core project for 42 School. It mimics the behavior of standard Unix shells, focusing on robust command execution, process management, and memory hygiene. The project emphasizes a deep understanding of system calls and low-level programming to create a functional and leak-free command-line interface. 🧠

---

## 📋 Features

- 🚀 **Command Execution:** Supports basic commands, built-ins, and external executables.
- 🔄 **I/O Redirection:** Handles input (`<`), output (`>`), and append output (`>>`) redirection.
- ⚙️ **Pipes:** Implements inter-process communication using pipes (`|`).
- 🌳 **Environment Variables:** Manages shell environment variables, including `PATH`.
- 🧠 **Memory Management:** Full manual control over memory with no leaks (checked with Valgrind).
- 🧹 **Error Handling:** Robust error reporting for invalid commands, syntax errors, and system call failures.
- 📚 Built following 42's Norminette coding standards.

---

## 🛠️ Installation

### Prerequisites

Make sure you have:

- 🐧 Linux system (the project is developed and tested on Linux)
- 🧰 GCC or compatible C compiler
- 📦 make utility
- 📁 libft included in the project (`libs/`)

### Steps to Build

Clone the repository:

```bash
git clone https://github.com/your-username/minishell.git
cd minishell
```

Compile the project:

```bash
make
```

This will generate the `minishell` executable.

---

## 🚀 Usage

To run minishell, simply execute the compiled binary:

```bash
./minishell
```

You'll then see a prompt where you can enter commands, similar to a standard shell.

Example commands:

```bash
ls -l
cat < file.txt > output.txt
ls -la | grep "minishell"
echo $PATH
```

---

## 🧹 Cleaning Up

Remove object files:

```bash
make clean
```

Remove all compiled files and executables:

```bash
make fclean
```

Recompile everything from scratch:

```bash
make re
```

---

## 🛡️ Memory Leak Testing

Use Valgrind to check for memory leaks:

```bash
valgrind ./minishell
```

Then, interact with the shell (run some commands, exit with `exit`). Your Valgrind output should confirm that all allocated memory is freed properly.

---

Made with ❤️ and manual memory management as part of the 42 School core projects.
