NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft
LDFLAGS = -lreadline

# Source files by folder
SRC = main.c \
	  lexer/init.c lexer/tokens.c lexer/lexer.c \
	  parser/parsing.c parser/utils.c parser/check_syntax.c \
	  parser/syntax_utils.c 
OBJ = $(SRC:.c=.o)

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Colors
GREEN = \033[0;32m
RESET = \033[0m

# Default target
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN)Building the project...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

# Compile libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Clean object files
clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re



#tokchiandap
 