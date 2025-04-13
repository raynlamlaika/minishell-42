NAME = minishell

SRC = minishell.c parse.c  tokens.c ft_strndup.c ft_strdup.c ft_strchr.c envr.c
BSRC = 

OBJ = $(SRC:.c=.o)
# BOBJ = $(BSRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

HEADER = minishell.h
# HEADERB = bonus/pipexb.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -lreadline   $(CFLAGS) $^ -o $(NAME)

bonus: $(BOBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c $(HEADERB)
	$(CC) $(CFLAGS) -Ibonus -c $< -o $@

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
