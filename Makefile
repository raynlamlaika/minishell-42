NAME = minishell

SRC =	env_heloper.c expand_3.c ft_heredoc.c my_malloc.c tokens.c \
		env_null_helper.c expand.c handle_signal.c syntax.c syntax_imbg.c \
		envr.c expand_heper.c parce.c parse_helper.c \
		expand_2.c expand_token.c minishell.c \
		buildin/ft_cd_2.c buildin/ft_echo.c buildin/ft_exit.c buildin/ft_export.c buildin/ft_pwd.c \
		buildin/ft_cd.c buildin/ft_env.c buildin/ft_expo.c buildin/ft_export_help.c buildin/ft_unset.c \
		exec/exec_ulitls2.c exec/exec_ultils.c exec/exec_utils3.c \
		exec/execution.c exec/execution_helper.c \
		ulits/ft_itoa.c ulits/ft_strchr.c ulits/ft_strjoin.c ulits/ft_strndup.c ulits/utils.c \
		ulits/ft_split_h.c ulits/ft_strdup.c ulits/ft_strncmp.c ulits/ft_strrchr.c


DEP= minishell.c
OBJ = $(SRC:.c=.o)
# BOBJ = $(BSRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

HEADER = minishell.h
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -lreadline $(CFLAGS) $^ -o $(NAME)


%.o: %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
