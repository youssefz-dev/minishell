/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:02:04 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/03 17:57:49 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_utils(t_shell *shell, t_env **env)
{
	if (!env || !*env)
		return (0);
	if (search_env(env, "SHLVL"))
	{
		if (ft_strnstr(shell->cmd[0], "./minishell", ft_strlen("./minishell")))
			handel_sh(env);
		if (ft_strnstr(shell->cmd[0], "minishell", ft_strlen("minishell")))
			handel_sh(env);
	}
	return (1);
}

void	mini_utils(t_shell *shell, t_list *list)
{
	if (!shell->cmd)
		(free_shell(shell), free_list(list), exit(0));
	handel_under(shell);
}

void	file_error(t_shell *shell, t_list *list)
{
	if (shell->infile == -1 || shell->errfile == -10)
	{
		if (!shell->inname || shell->errfile == -10)
			(free_shell(shell), free_list(list), exit(0));
		dup2(2, 1);
		printf("bash: %s: No such file or directory\n", shell->inname);
		(free_shell(shell), free_list(list), exit(1));
	}
	if (shell->infile == -2)
	{
		(dup2(2, 1), printf("bash: %s: Permission denied\n", shell->inname));
		(free_shell(shell), free_list(list), exit(1));
	}
	if (shell->outfile == -1)
	{
		dup2(2, 1);
		printf("bash: %s: No such file or directory\n", shell->outname);
		(free_shell(shell), free_list(list), exit(1));
	}
	if (shell->outfile == -2)
		(dup2(2, 1), printf("bash: %s: Permission denied\n", shell->outname), \
		free_shell(shell), free_list(list), exit(1));
	if (shell->outfile == -3)
		(dup2(2, 1), printf("bash: %s: Is a directory\n", shell->outname), \
		free_shell(shell), free_list(list), exit(1));
}

int	file_error1(t_shell *shell, t_list *list)
{
	if (shell->infile == -1 || shell->errfile == -10)
	{
		if (!shell->inname || shell->errfile == -10)
			return (free_shell1(shell), free_list(list), 0);
		dup2(2, 1);
		printf("bash: %s: No such file or directory\n", shell->inname);
		return (free_shell1(shell), free_list(list), 0);
	}
	if (shell->infile == -2)
	{
		(dup2(2, 1), printf("bash: %s: Permission denied\n", shell->inname));
		return (free_shell1(shell), free_list(list), 0);
	}
	if (shell->outfile == -1)
		return (dup2(2, 1), printf("bash: %s: No such file or directory\n", \
			shell->outname), free_shell1(shell), free_list(list), 0);
	if (shell->outfile == -2)
		return (dup2(2, 1), printf("bash: %s: Permission denied\n", \
			shell->outname), free_shell1(shell), free_list(list), 0);
	if (shell->outfile == -3)
		return (dup2(2, 1), printf("bash: %s: Is a directory\n", \
			shell->outname), free_shell1(shell), free_list(list), 0);
	return (1);
}

void	cmd_exec(t_shell *shell, t_list *list, char **env)
{
	char	*ptr;

	ptr = 0;
	ptr = get_path(shell->cmd[0], env);
	if (!ptr && (!search_env(shell->env, "PATH") \
	|| !get_env2(shell->env, "PATH")->val \
	|| get_env2(shell->env, "PATH")->val[0] == '\0'))
	{
		(execve(shell->cmd[0], shell->cmd, env), exec_error(shell, list));
		if (!access(shell->cmd[0], X_OK))
			exec_file(shell, env);
	}
	execve(ptr, shell->cmd, env);
	free(ptr);
}
