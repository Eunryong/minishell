# minishell

make bash-like shell

-   허용 함수

      <img width="443" alt="image" src="https://github.com/Eunryong/minishell/assets/86572427/e16b3324-782d-4af7-8e7b-affcc71d565e">

    이 외의 함수들은 직접 구현해준다.

## 파이프

두 프로세스 간에 데이터 전송에 쓰인다.
pipe함수를 통해 부모와 자식 프로세스 간의 통신을 해준다.

```c
int	set_execute(t_line *line)
{
	pid_t	pid;
	int		fd[2];
	int		i;

	i = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (builtins_check(line->cmd->str) && line->size == 1)
		return (builtins_set(line));
	while (++i < line->size)
	{
		if (pipe(fd) < 0)
			print_error("pipe error", 1, 1);
		pid = fork();
		if (pid == -1)
			print_error("fork error", 1, 1);
		if (pid == 0)
			execute(line, fd, i);
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd[0], fd[1]);
	}
	backup_fd(line);
	return (wait_all(pid));
}
```

## 파싱

-   순서대로 진행하기 때문에 리스트를 이용했다.

-   처리하지 않아도 되는 부분

    -   닫히지 않은 쿼트
    -   특수문자
    -   \ or ;

-   파싱 순서

    1. quote를 구분해서 나눠준다.
    2. 타입별로 나눠준다.
    3. 공백을 기준으로 나눠준다.
    4. $를 환경변수를 통해 치환해준다.
    5. 공백기준으로 나눴던 문자열 부분을 quote체크 후 다시 붙여준다.

    ```c
    void	tokenize(t_line *line, char *rd_line)
    {
        seperate_quote(line, rd_line);
        if (line->syntax)
            return (syntax_error("syntax error", 1, 0));
        seperate_as_type(line);
        seperate_space(line);
        check_dollar(line);
        if (!line->cmd)
            return ;
        join_quote(line);
    }
    ```

## 명령어

-   built-in 함수

    -   echo
    -   cd
    -   pwd
    -   export
    -   unset
    -   env
    -   exit

-   일반 명령어

환경변수 PATH를 통해 bin안의 파일을 찾아 실행시켜준다.

## 시그널

signal함수를 통해 Ctrl + c, Ctrl + d, Ctrl + \를 관리해준다.

## 리다이렉션

각 리다이렉션에 맞게 입출력을 dup2를 통해 관리해준다.

## 종료코드

자식 프로세스의 종료코드를 wait함수를 통해 받아준다.

```c
int	wait_all(pid_t last_pid)
{
	int		temp;
	pid_t	pid;

	pid = 1;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (pid == last_pid)
		{
			if (WIFEXITED(temp))
				g_env->status = WEXITSTATUS(temp);
			else if (WIFSIGNALED(temp))
				g_env->status = WTERMSIG(temp) + 128;
			if (g_env->status == 131)
				ft_putstr_fd("Quit: 3\n", 2);
		}
	}
	return (1);
}
```

## 에러메세지

빌트인을 제외한 명령어들은 execve를 통해 실행하기 때문에 strerror함수를 통해 처리 할수 있지만
되도록 모든 예외처리를 해주었기 때문에 예외에 대한 에러를 출력해주었다.
