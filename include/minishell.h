// CABECERA!!!

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>          //wait, waitpid
# include <stdio.h>             //printf, perror
# include <readline/readline.h> //readline, add_history, rl_clear_history
# include <readline/history.h>
# include <stdlib.h>            //malloc, free, exit, getenv
# include <unistd.h>            //write, access, read, close, fork, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe, isatty ttyname
# include <dirent.h>            //opendir, readdir, closedir
# include <fcntl.h>             //open
# include <signal.h>            //signal, sigaction, kill
# include <string.h>            //strerror
# include <errno.h>             //Define la varibale entera errno con el numero de un error

# include "../include/lexer.h"




#endif