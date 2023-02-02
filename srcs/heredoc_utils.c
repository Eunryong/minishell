#include "minishell.h"

char	*here_dollar(char *str)
{
	int		size;
	int		i;
	char	*ret;

	i = 0;
	size = is_dollar(str);
	if (size == 0)
		return (str);
	ret = change_dollar(str, size);
	return (ret);
}
