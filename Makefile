# CABECERA!!
# Para que detecte correctamente la libreria readline es necesario poner -lreadline
# después de los ficheros a compilar en gcc

# Name of the program
NAME 		= minishell

# Custom libraries archives
LIBFT_AR	= ./lib/libft/libft.a

# Compiler and flags
CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror
READLINE	= -lreadline -lhistory
LIBFT		= -L./lib/libft -lft

# Directories
LEX_SRC_DIR	= ./src/lexer/
PAR_SRC_DIR	= ./src/parser/
DEB_SRC_DIR	= ./src/debug/
UTL_SRC_DIR	= ./src/utils/
EXP_SRC_DIR	= ./src/expander/
EXE_SRC_DIR	= ./src/executor/
BUI_SRC_DIR	= ./src/builtins/
LIBFT_DIR	= ./lib/libft/
OBJS_DIR	= ./build/

# Include folders
INCLUDE		= -Iinclude -I$(LIBFT_DIR)

# Source files
SRC			=	src/lexer/lexer.c \
				src/lexer/lexer_utils.c \
				src/lexer/consecutive_quotes_utils.c \
				src/lexer/consecutive_quotes_split.c \
				src/lexer/consecutive_quotes_fill.c \
				src/lexer/complex_str_checker.c \
				src/lexer/complex_str_builder.c \
				src/lexer/complex_str_utils.c \
				src/parser/parser_utils.c \
				src/parser/cmd_split.c \
				src/parser/redirection_utils.c \
				src/utils/initializer.c \
				src/utils/ft_readline.c \
				src/utils/ft_readline_utils.c \
				src/utils/utils.c \
				src/utils/clean_memory.c \
				src/utils/error.c \
				src/utils/signals.c \
				src/expander/expander.c \
				src/expander/expander_utils.c \
				src/expander/expansion_malloc.c \
				src/expander/fill_expansion.c \
				src/executor/ft_executor.c \
				src/executor/ft_path_finder.c \
				src/executor/ft_mng_redirs.c \
				src/executor/ft_mng_cmds.c \
				src/executor/ft_hdoc.c \
				src/builtins/builtin_pwd.c \
				src/builtins/builtin_cd.c \
				src/builtins/builtin_export.c \
				src/builtins/builtin_echo.c \
				src/builtins/builtin_unset.c \
				src/builtins/builtin_exit.c \
				src/builtins/builtin_env.c \
				src/builtins/builtins.c \
				src/builtins/builtins_utils.c \
				src/builtins/builtin_export_utils.c \
				src/builtins/builtin_update_export_list.c \
				src/builtins/builtin_print_export_list.c \
				src/main.c

# Object files
OBJS		=	$(addprefix $(OBJS_DIR), \
				$(notdir $(patsubst %.c, %.o, $(SRC))))

# Header files
HEADERS		=	./include/minishell.h

all: $(NAME)

# Program compiler
$(NAME): $(LIBFT_AR) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(READLINE)

# Directories creation if not exist
$(OBJS_DIR):
	mkdir $(OBJS_DIR)

# Debuger
$(OBJS_DIR)%.o: $(DEB_SRC_DIR)%.c $(HEADERS) Makefile | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

valgrind: $(NAME)
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

# Utils objects compiler
$(OBJS_DIR)%.o: $(UTL_SRC_DIR)%.c $(HEADERS) Makefile | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# Lexer objects compiler
$(OBJS_DIR)%.o: $(LEX_SRC_DIR)%.c $(HEADERS) Makefile | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# Parser objects compiler
$(OBJS_DIR)%.o: $(PAR_SRC_DIR)%.c $(HEADERS) Makefile | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# Expander objects compiler
$(OBJS_DIR)%.o: $(EXP_SRC_DIR)%.c $(HEADERS) Makefile | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# Executor objects compiler
$(OBJS_DIR)%.o: $(EXE_SRC_DIR)%.c $(HEADERS) Makefile | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# Builtins objects compiler
$(OBJS_DIR)%.o: $(BUI_SRC_DIR)%.c $(HEADERS) Makefile | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# main objects compiler
$(OBJS_DIR)%.o: ./src/main.c $(HEADERS) Makefile | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@


# Libft make
$(LIBFT_AR):
	make -C $(LIBFT_DIR)

# Objects cleaner
clean:
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

# Object + program cleaner
fclean: clean
	rm minishell
	make fclean -C $(LIBFT_DIR)

# Remake
re: fclean all

# Norminette
norminette:
	norminette $(SRC) $(HEADERS)

.PHONY: all clean fclean re norminette
