# CABECERA!!
# Para que detecte correctamente la libreria readline es necesario poner -lreadline
# después de los ficheros a compilar en gcc

# Name of the program
NAME 		= ./bin/minishell

# Custom libraries archives
LIBFT_AR	= ./lib/libft/libft.a

# Compiler and flags
CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror
READLINE	= -lreadline -lhistory
LIBFT		= -L./lib/libft -lft

# Directories
LEX_SRC_DIR	= ./src/lexer/
LIBFT_DIR	= ./lib/libft/
OBJS_DIR	= ./build/
PROGRAM_DIR	= ./bin

# Include folders
INCLUDE		= -Iinclude -I$(LIBFT_DIR)

# Source files
SRC			=	src/lexer/lexer.c \
				src/lexer/lexer_utils.c

# Object files
OBJS		=	$(addprefix $(OBJS_DIR), \
				$(notdir $(patsubst %.c, %.o, $(SRC))))

# Header files
HEADERS		=	./include/lexer.h \
				./include/minishell.h

all: $(NAME)

# Program compiler
$(NAME): $(LIBFT_AR) $(OBJS) $(HEADERS) | $(PROGRAM_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(READLINE)

# Directories creation if not exist
$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(PROGRAM_DIR):
	mkdir $(PROGRAM_DIR)

# Objects compiler
$(OBJS_DIR)%.o: $(LEX_SRC_DIR)%.c $(HEADERS) | $(OBJS_DIR)
	@echo "Compiling ${notdir $<} in $(OBJS_DIR)"
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
	rm -rf ./bin
	make fclean -C $(LIBFT_DIR)

# Remake
re: fclean all

# Norminette
norminette:
	norminette $(SRC) $(HEADERS)

.PHONY: all clean fclean re norminette