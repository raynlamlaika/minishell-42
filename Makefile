NAME=minishell
CC=cc
FLAGS=-Wall -Wextra -Werror
SRC = minishell.c
HEADER=minishell.h 
OBJ = $(SRC:.c=.o)
CFLAGS = -fsanitize=address -lreadline
# 
all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)


%.o: %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all