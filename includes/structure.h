#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum e_type
{
	cmd,
	red,
	pipe
}	t_type;

typedef struct s_cmd
{
	char			*str;
	int				type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_line
{
	char	**str;
	int		*cmd_size;
	t_cmd	*cmd;
	int		size;
	char	**env;
	int		status;
}	t_line;

#endif
