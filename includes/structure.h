#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum e_type
{
	cmd,
	red,
	pip
}	t_type;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*str;
	int				type;
	int				quotes;
	int				dollar;
	int				status;
	int				pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_line
{
	char	**str;
	int		*cmd_size;
	t_cmd	*cmd;
	int		size;
	char	**env;
	int		input;
	int		output;
	int		status;
}	t_line;

#endif
