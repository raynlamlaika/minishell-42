NAME = minishell

SRC = parse.c  tokens.c ft_strndup.c ft_strdup.c ft_strchr.c envr.c ft_strncmp.c \
		ft_strjoin.c  execution.c ft_split_h.c  ft_strrchr.c handle_signal.c expand.c gnl.c ft_heredoc.c\
		ft_malloc.c

# BSRC = 
DEP= minishell.c
OBJ = $(SRC:.c=.o)
# BOBJ = $(BSRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

HEADER = minishell.h
# HEADERB = bonus/pipexb.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -lreadline $(CFLAGS) $^ -o $(NAME)

# bonus: $(BOBJ)
# 	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# bonus/%.o: bonus/%.c $(HEADERB)
# 	$(CC) $(CFLAGS) -Ibonus -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

