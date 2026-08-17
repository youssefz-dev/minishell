/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:37:40 by yzoullik          #+#    #+#             */
/*   Updated: 2025/06/27 12:00:39 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_error2(t_shell *shell, t_list *list)
{
	char	*ptr;

	if (shell->cmd[0][ft_strlen(shell->cmd[0]) - 1] == '/')
	{
		ptr = ft_substr(shell->cmd[0], 0, ft_strchr(shell->cmd[0], '/'));
		if (access(ptr, F_OK) == 0)
		{
			printf("bash: %s: Not a directory\n", shell->cmd[0]);
			(free_shell(shell), free_list(list), exit(126));
		}
	}
	printf("bash: %s: No such file or directory\n", shell->cmd[0]);
	(free_shell(shell), free_list(list), exit(127));
}

void	exec_error1(t_shell *shell, t_list *list)
{
	int		x;

	if (access(shell->cmd[0], F_OK) == -1)
		exec_error2(shell, list);
	else
	{
		x = open(shell->cmd[0], O_RDONLY);
		if (x == -1 || shell->cmd[0][0] == '.' \
		|| !search_env(shell->env, "PATH") \
		|| !get_env2(shell->env, "PATH")->val \
		|| get_env2(shell->env, "PATH")->val[0] == '\0')
		{
			if (x != -1)
				close(x);
			printf("bash: %s: Permission denied\n", shell->cmd[0]);
			(free_shell(shell), free_list(list), exit(126));
		}
		close(x);
	}
}

void	exec_error(t_shell *shell, t_list *list)
{
	DIR		*dir;

	dup2(2, 1);
	if (ft_strchr(shell->cmd[0], '/') != -1 || !search_env(shell->env, "PATH") \
	|| !get_env2(shell->env, "PATH")->val \
	|| get_env2(shell->env, "PATH")->val[0] == '\0')
	{
		dir = opendir(shell->cmd[0]);
		if (dir)
		{
			printf("bash: %s: Is a directory\n", shell->cmd[0]);
			closedir(dir);
			(free_shell(shell), free_list(list), exit(126));
		}
		else
			exec_error1(shell, list);
	}
	printf("%s: command not found\n", shell->cmd[0]);
	(free_shell(shell), free_list(list), exit(127));
}

char	*get_line(char	*key, char *val)
{
	char	*ptr;
	char	*line;

	ptr = ft_strjoin1(key, "=");
	line = ft_strjoin1(ptr, val);
	free(ptr);
	return (line);
}

void	exec_file(t_shell *shell, char **env)
{
	char	**ptr;

	ptr = malloc(sizeof(char *) * 3);
	if (!ptr)
		return ;
	ptr[0] = "/bin/bash";
	ptr[1] = shell->cmd[0];
	ptr[2] = 0;
	execve("/bin/bash", ptr, env);
}
