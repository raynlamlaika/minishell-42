NAME = minishell

SRC = parse.c  tokens.c ft_strndup.c ft_strdup.c ft_strchr.c envr.c ft_strncmp.c \
		ft_strjoin.c  execution.c ft_split_h.c  ft_strrchr.c handle_signal.c expand.c gnl.c ft_heredoc.c\
		ft_malloc.c buildin/ft_cd.c  buildin/ft_echo.c   buildin/ft_env.c \
		buildin/ft_export.c   buildin/ft_pwd.c  buildin/ft_unset.c buildin/ft_exit.c


# BSRC = 
DEP= minishell.c
OBJ = $(SRC:.c=.o)
# BOBJ = $(BSRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address 

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

