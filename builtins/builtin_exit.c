
#include "../minishell.h"

//This function determines whether the given character can be
//counted as a white space
static int	is_whitespace(char c)
{
	return ((c == ' ') || (c == '\t') || (c == '\n')
		|| (c == '\v') || (c == '\f') || (c == '\r'));
}

//This function turns all digit characters into an integer and returns the 
//result it also checks for the limits and does not allow the integer
// to get pass these
static long int	addnumber(long int number, int negative, char *str, int index)
{
	while (ft_isdigit(str[index]))
	{
		if (number * negative <= -922337203685477580 && str[index] > '8')
			return (0);
		if (number * negative >= 922337203685477580 && str[index] >= '7')
			return (-1);
		number = (number * 10) + (str[index] - '0');
		index++;
	}
	return (number * negative);
}

//This function turns a character array into a number. It ignores
//any white spaces previous to a non-whitespace character and 
//takes the first positive/negative symbol into account for the integer.
long int	ms_atoi(const char *str)
{
	char			*newstr;
	int				negative;
	int				i;
	long long		number;

	newstr = (char *) str;
	number = 0;
	negative = 1;
	i = 0;
	while (is_whitespace(newstr[i]))
		i++;
	if (!ft_isdigit(newstr[i]))
	{
		if (newstr[i] == '-')
			negative *= -1;
		else if (newstr[i] != '+')
			return (0);
		i++;
	}
	return (addnumber(number, negative, newstr, i));
}

int	ft_put_error_exit(char *error_var, char *error_msg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(error_var, STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			if ((arg[i] == '+' || arg[i] == '-') && i == 0)
			{
				i++;
				continue;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_overflow(long int nbr, char *str)
{
	if (str[0] == '-' && nbr >= 0)
		return (1);
	if (str[0] != '-' && nbr < 0)
		return (1);
	return (0);
}

int	ft_exit(t_exec *exec)
{
	long int	code;

	code = 0;
	if (exec->argv[1])
	{
		if (exec->argv[2])
			return (ft_put_error_exit(NULL, "too many arguments"));
		code = ms_atoi(exec->argv[1]);
		if (!is_number(exec->argv[1]) || is_overflow(code, exec->argv[1]))
		{
			ft_put_error_exit(exec->argv[1], ": numeric argument required");
			free_hash_list(exec->env);
			free_exec(exec);
			exit(255);
		}
	}
	free_hash_list(exec->env);
	free_exec(exec);
	exit(code);
}
