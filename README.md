# Minishell

## Project structure
|- README.md
|- Makefile
|- LICENSE
|- .gitignore
|- src/
|	|- main.c (main) Entry point of the program
|	|- *.c files
|- include/
|	|- *.h files
|- lib/
|	|- Third party libraries, for example readline in this project
|- tests/
|	|- Some-unit-tests.c files
|- build
|	|- intermedite build files e.g *.o files (created by make)
|- docs
|	|- documentation
|- bin
|	|- 	the executable (created by make)
|- .devcontainer
|	|- configuration for GitHub Codespaces
|- .github
|	|- configuration GitHub Actions and other GitHub featuress
