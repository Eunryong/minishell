#include "minishell.h"
/*
int	set_heredoc()
{
	///tmp/.heredoc open 후 한줄씩 받아서 저장
	//limiter가 나오면 종료
	//새로 열어서 infile에 담기
	//infile return
}
*/
char	*get_cmd(char *path, char *cmd)//path를 env안에서 가져와야함
{
	char	**path2;
	char	*path_cmd;
	char	*ret_cmd;
	int		i;

	i = -1;
	path2 = ft_split(path, ':');
	if (access(cmd, X_OK) != -1)
		return (cmd);
	path_cmd = ft_strjoin("/", cmd);
	while (path2[++i])
	{
		ret_cmd = ft_strjoin(path2[i], path_cmd);
		if (access(ret_cmd, X_OK) != -1)
		{
			free(path_cmd);
			return (ret_cmd);
		}
		free(ret_cmd);
	}
	free(path_cmd);
	return (0);
}

void	excute(char *line, char **envp) // 명령어 실행 infile, outfile 등 체크 후 있으면 처음과 마지막에 처리해줌
{
	char	*cmd1;
	char	**cmd2;

	// 중간에 dup2(arg.fd[1], 1);
	// oufile 일때 dup2(outfile, 1);
	// if (infile && 처음)
	// open 또는 heredoc처리
	// dup2(infile, 0);
	// if (oufile && 마지막)
	// dup2(outfile, 1);
	// if (중간)
	// dup2(arg.fd[0], 0);
	// dup2(arg.fd[1], 1);
	cmd2 = ft_split(line, ' ');
	cmd1 = get_cmd(getenv("PATH") ,cmd2[0]);
	if (!cmd1)
		print_error("command not found", 1);
	if (execve(cmd1, cmd2, envp) == -1)
		print_error("execve error", 1);
}

void	set_excute(char *line, char **envp)
{
	pid_t	pid;
	static int		status;

	if (!builtins_check(line, status))
	{
		//파이프 개수만큼 반복 마지막에 리다이렉션 후 출력
		//i = -1;
		//while (++i < pipe_size)
		//pipe(arg.fd) == -1
		//print_error("pipe error", 1);
		pid = fork();
		// pid == -1
		// print_error("fork error", 1);
		if (pid == 0)
		{
			excute(line, envp);
		}
		// wait_all을 통해 종료 종료시 마지막 status를 받음
		wait(&status);
	}
}
