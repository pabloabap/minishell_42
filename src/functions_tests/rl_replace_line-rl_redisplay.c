#include <stdio.h>
#include <readline/readline.h>

int main() {
    char *input;
    input = readline("Enter a line of text: ");
    printf("You entered: %s\n", input);
    rl_replace_line("This is the new line", 0);
    rl_redisplay();
    input = readline("Enter another line of text: ");
    printf("You entered: %s\n", input);
    return 0;
}