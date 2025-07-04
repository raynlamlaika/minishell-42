NAME = minishell

SRC =	env_heloper.c expand_3.c ft_heredoc.c my_malloc.c minishell_2.c tokens.c handel_quote.c here_doc_heler.c \
		env_null_helper.c expand.c expand_h.c handle_signal.c syntax.c syntax_imbg.c exec/expande_helper.c \
		envr.c expand_heper.c parce.c parse_helper.c here_doc_exp.c \
		expand_2.c expand_token.c minishell.c \
		builtins/ft_cd_2.c builtins/ft_echo.c builtins/ft_exit.c builtins/ft_export.c builtins/ft_pwd.c \
		builtins/ft_cd.c builtins/ft_env.c builtins/ft_expo.c builtins/ft_export_help.c builtins/ft_unset.c \
		builtins/utils.c builtins/sort_export.c builtins/updat_env.c\
		exec/exec_ulitls2.c exec/exec_ultils.c exec/exec_utils3.c exec/exec_2.c exec/exec_1.c\
		exec/execution.c exec/execution_helper.c  exec/exec_3.c exec/exec_h_2.c exec/fork_pipe_h.c\
		ulits/ft_itoa.c ulits/ft_strchr.c ulits/ft_strjoin.c ulits/ft_strndup.c ulits/utils.c \
		ulits/ft_split_h.c ulits/ft_strdup.c ulits/ft_strncmp.c ulits/ft_strrchr.c \
		ft_print_error.c expandmltpdolr.c


DEP= minishell.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

HEADER = minishell.h
all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(CFLAGS) $^ -o $(NAME) -lreadline


%.o: %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
