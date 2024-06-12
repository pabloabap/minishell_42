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
LIBFT_DIR	= ./lib/libft/
OBJS_DIR	= ./build/
PROGRAM_DIR	= ./bin

# Include folders
INCLUDE		= -Iinclude -I$(LIBFT_DIR)

# Source files
SRC			=	src/debug/debug.c \
				src/lexer/lexer.c \
				src/lexer/lexer_utils.c \
				src/parser/parser_utils.c \
				src/parser/cmd_split.c \
				src/utils/initializer.c \
				src/utils/clean_memory.c \
				src/main.c
#				src/parser/expander.c \

# Object files
OBJS		=	$(addprefix $(OBJS_DIR), \
				$(notdir $(patsubst %.c, %.o, $(SRC))))

# Header files
HEADERS		=	./include/minishell.h \
				./include/lexer.h \
				./include/parser.h	

all: $(NAME)

# Program compiler
$(NAME): $(LIBFT_AR) $(OBJS) $(HEADERS) | $(PROGRAM_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(READLINE)

# Directories creation if not exist
$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(PROGRAM_DIR):
	mkdir $(PROGRAM_DIR)

# Debuger
$(OBJS_DIR)%.o: $(DEB_SRC_DIR)%.c $(HEADERS) | $(OBJS_DIR)
	@echo "Compiling ${notdir $<} in $(OBJS_DIR)"
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# Utils objects compiler
$(OBJS_DIR)%.o: $(UTL_SRC_DIR)%.c $(HEADERS) | $(OBJS_DIR)
	@echo "Compiling ${notdir $<} in $(OBJS_DIR)"
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# Lexer objects compiler
$(OBJS_DIR)%.o: $(LEX_SRC_DIR)%.c $(HEADERS) | $(OBJS_DIR)
	@echo "Compiling ${notdir $<} in $(OBJS_DIR)"
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# Parser objects compiler
$(OBJS_DIR)%.o: $(PAR_SRC_DIR)%.c $(HEADERS) | $(OBJS_DIR)
	@echo "Compiling ${notdir $<} in $(OBJS_DIR)"
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

# main objects compiler
$(OBJS_DIR)%.o: ./src/main.c $(HEADERS) | $(OBJS_DIR)
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
	rm minishell
	make fclean -C $(LIBFT_DIR)

# Remake
re: fclean all

# Norminette
norminette:
	norminette $(SRC) $(HEADERS)

.PHONY: all clean fclean re norminette