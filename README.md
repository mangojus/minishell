_This project has been created as part of the 42 curriculum by rshin, vakozhev._

# minishell

A small Unix shell written in **C**, modeled on bash. It reads a line, tokenizes and parses it, expands variables, and runs the resulting pipeline with `fork`, `execve`, `pipe` and `dup2`.

```console
$ ./minishell 1
minishell> echo "hello $USER" | tr a-z A-Z
HELLO RSHIN
minishell> cat << EOF > notes.txt
> heredoc line
> EOF
minishell> cat < notes.txt | wc -l
1
minishell> nosuchcmd
msh: nosuchcmd: Command not found
minishell> echo $?
127
```

## Features

- **Interactive prompt** with line editing and history (GNU readline).
- **Pipelines** of any length: `cmd1 | cmd2 | cmd3`.
- **Redirections**: `<`, `>`, `>>`, and heredoc `<<` (with its own `Ctrl-C` handling).
- **Quoting**: single quotes are fully literal, double quotes still expand `$`. Unclosed quotes are reported as syntax errors.
- **Expansion**: `$VAR` and `$?` (exit status of the last pipeline).
- **PATH lookup** for executables, plus relative and absolute paths.
- **Builtins**: `echo [-n]`, `cd`, `pwd`, `export`, `unset`, `env`, `exit [n]`.
- **Signals**: as in bash, `Ctrl-C` shows a new prompt, `Ctrl-D` exits and `Ctrl-\` is ignored at the prompt. Child processes get the default behavior back.
- **Exit statuses** follow bash, including `126`/`127` for non-executable/not-found commands and `128 + n` for signals.

Not supported, as these are outside the mandatory part: `;`, `&&`, `||`, subshells `( )` and wildcards `*`.

## Build & run

Requirements: `cc`, `make`, and the readline development headers (`libreadline-dev` on Debian/Ubuntu).

```bash
make
./minishell 1        # interactive mode
```

libft is bundled in [`libft/`](libft) and built automatically.

## How it works

```
readline ─▶ lexer ─▶ checker ─▶ expander ─▶ assembler ─▶ executor
            tokens    syntax     $VAR, $?,    command     fork / pipe / dup2,
                      & quotes   quotes       list        heredocs, builtins
```

| Stage | Source | Role |
|---|---|---|
| Lexer | `src/parsing/lexer.c` | splits the line into typed tokens (`CMD`, `PIPE`, `RIN`, `ROUT`, `APP`, `HDOC`, …) |
| Checker | `src/parsing/checker.c` | rejects syntax errors such as unclosed quotes and misplaced pipes or redirections |
| Expander | `src/parsing/expander.c` | substitutes variables and `$?`, removes quotes |
| Assembler | `src/parsing/assembler.c` | groups tokens into commands with their arguments and redirections |
| Executor | `src/exec/` | prepares heredocs, opens files, creates pipes, forks children, runs builtins in-process when needed, collects exit statuses |

The environment, tokens and commands are each stored in their own doubly linked list type (`src/env`, `src/token`, `src/command`).

## Project structure

```
src/
├── parsing/    lexer, checker, expander, assembler, parser entry point
├── exec/       executor, processes, pipes, fds, heredoc, builtin dispatch
├── builtins/   echo, cd, pwd, export, unset, env, exit
├── env/        environment list (envp ⇄ list conversion)
├── token/      token list
├── command/    command list
└── utils/      data lifecycle, errors, signals
include/        headers
libft/          personal C library (bundled)
```

## Team

- **rshin**: lexer/parser, environment, builtins, execution
- **vakozhev**: execution (processes, pipes, heredoc), builtins, error handling
