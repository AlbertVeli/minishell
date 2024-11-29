# minishell

**minishell** is a minimal shell implementation in C, designed to illustrate how a simple shell can be written and how it interacts with the SUID bit. This program supports basic command execution and demonstrates the use of `execvp()` to run commands with the privileges of the process owner when the SUID bit is set.

If you try to do the same thing using the system() library function, you will find that the SUID bit is ignored. But it works with execvp() because execvp() is a system call that replaces the current process with a new process, and the new process inherits the privileges of the process owner.

## Features
- Executes commands entered by the user.
- Supports navigating command history with the arrow keys (requires GNU Readline).
- Demonstrates how a shell can maintain elevated privileges when the SUID bit is set.

## Requirements
- A Linux/Unix-based operating system.
- GCC (GNU Compiler Collection).
- GNU Readline library (`libreadline-dev`).

## Compilation
To compile minishell, you can use the included `Makefile`:
```bash
make
```

This will generate the executable `minishell`.

## Example Usage
```bash
./minishell
$ cat /etc/shadow
cat: /etc/shadow: Permission denied
```

### SUID Functionality
To enable SUID functionality:
```bash
sudo make suid
```

### Example of SUID Usage
```bash
./minishell
$ cat /etc/shadow
<contents of /etc/shadow>
```

## Clean Up
To remove the SUID bit:
```bash
sudo make unsuid
```

To remove all compiled files:
```bash
make clean
```

## Security Warning
This program is for educational purposes only. Setting the SUID bit on a shell can lead to privilege escalation.

## Author
- [Albert Veli](https://www.linkedin.com/in/albert-veli-a51a2a3/)
- [GitHub Copilot](https://github.com/github/copilot.vim)

## License
[The Unlicense](https://unlicense.org/)
