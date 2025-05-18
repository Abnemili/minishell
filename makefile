NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -I.
LDFLAGS = -lreadline

SRC = main.c utils.c init.c tokens.c token_utils.c help.c
OBJ = main.o utils.o init.o tokens.o token_utils.o help.o
LIBFT = libft/libft.a

# Colors for output
GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN)Building the project...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

$(LIBFT):
	@make -C libft

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
