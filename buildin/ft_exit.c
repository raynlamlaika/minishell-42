#include "../minishell.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

int is_numeric(char *str)
{
	int i = 0;

	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

long long	ft_str_to_ll(const char *str, int *overflow)
{
	int				sign = 1;
	unsigned long	result = 0;
	int i;

	*overflow = 0;
	i= 0;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i])
	{
		if (result > (unsigned long)(LLONG_MAX - (str[i] - '0')) / 10)
		{
			*overflow = 1;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (sign == -1 && result > (unsigned long)LLONG_MAX + 1)
		*overflow = 1;
	if (sign == 1 && result > (unsigned long)LLONG_MAX)
		*overflow = 1;
	return ((long long)(result * sign));
}

void	ft_exit(char **args, int exit_status)
{
	long long	value;
	int			overflow;

	printf("exit\n");
	if (!args[1])
		exit(exit_status);
	if (!is_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	value = ft_str_to_ll(args[1], &overflow);
	if (overflow)
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return;
	}
	exit((unsigned char)value);
}