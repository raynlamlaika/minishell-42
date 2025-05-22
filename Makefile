NAME = minishell
SRC = envr.c expand.c  ft_strjoin.c env_heloper.c   exec_ultils.c exec_ulitls2.c exec_utils3.c expand_token.c parce.c parse_helper.c\
		execution.c  expand_heper.c  ft_split_h.c  ft_strncmp.c  handle_signal.c  tokens.c ft_itoa.c syntax.c\
		expand_2.c   ft_heredoc.c ft_strchr.c ft_strndup.c syntax_imbg.c\
		expand_3.c ft_strdup.c   ft_strrchr.c  my_malloc.c utils.c \
		buildin/ft_cd.c  buildin/ft_echo.c   buildin/ft_env.c \
		buildin/ft_export.c   buildin/ft_pwd.c  buildin/ft_unset.c buildin/ft_exit.c
		
#  envr.c expand.c  ft_strjoin.c env_heloper.c  parse.c exec_ultils.c exec_ulitls2.c exec_utils3.c \
# 		execution.c  expand_heper.c  ft_split_h.c  ft_strncmp.c  handle_signal.c  tokens.c \
# 		expand_2.c   ft_heredoc.c ft_strchr.c ft_strndup.c \
# 		expand_3.c ft_strdup.c   ft_strrchr.c  my_malloc.c utils.c \
# 		buildin/ft_cd.c  buildin/ft_echo.c   buildin/ft_env.c \
# 		buildin/ft_export.c   buildin/ft_pwd.c  buildin/ft_unset.c buildin/ft_exit.c
		


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


%.o: %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@

# bonus/%.o: bonus/%.c $(HEADERB)
# 	$(CC) $(CFLAGS) -Ibonus -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
