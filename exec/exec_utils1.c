/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:07:08 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/03 17:54:11 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_finder(char **path, char *cmd)
{
	char	*res1;
	char	*res2;
	int		i;

	i = 0;
	while (path[i])
	{
		res1 = ft_strjoin1(path[i], "/");
		if (!res1)
			return (ft_free(path), NULL);
		res2 = ft_strjoin1(res1, cmd);
		if (!res2)
			return (ft_free(path), free(res1), NULL);
		if (access(res2, X_OK) != -1)
			return (ft_free(path), free(res1), res2);
		(free(res1), free(res2));
		i++;
	}
	return (ft_free(path), NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	path = ft_split(&env[i][5], ':');
	if (!path)
		return (NULL);
	return (path_finder(path, cmd));
}

int	env_size(t_env *env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = env;
	while (1)
	{
		if (env->envflag != 0)
			i++;
		env = env->next;
		if (head == env)
			break ;
	}
	return (i);
}

char	**get_env(t_env **env, t_shell *shell)
{
	int		i;
	t_env	*head;
	char	**ptr;

	head = *env;
	if (!env_utils(shell, env))
		return (0);
	i = env_size(*env);
	ptr = malloc(sizeof(char *) * (i + 2));
	if (!ptr)
		return (0);
	i = 0;
	if (search_env(env, "PATH"))
		get_env2(env, "PATH")->envflag = 1;
	while (1)
	{
		if ((*env)->envflag != 0)
			ptr[i++] = get_line((*env)->key, (*env)->val);
		*env = (*env)->next;
		if (head == *env)
			break ;
	}
	return (ptr[i] = 0, ptr);
}

void	mini_exec(t_shell *shell, t_list *list)
{
	char	**env;

	env = 0;
	free_shell0(shell->next);
	mini_utils(shell, list);
	close_fd(list->in);
	close_fd(list->out);
	if (is_builtins1(shell))
		exit(is_builtins(shell, list));
	else
	{
		env = get_env(shell->env, shell);
		if (!env || !*env)
			(free_shell(shell), free_list(list), exit(1));
		if (ft_strrchr(shell->cmd[0], '/') || ft_strrchr(shell->cmd[0], '.'))
			execve(shell->cmd[0], shell->cmd, env);
		if (!ft_strrchr(shell->cmd[0], '/') && !ft_strrchr(shell->cmd[0], '.'))
			cmd_exec(shell, list, env);
		if (!access(shell->cmd[0], X_OK))
			exec_file(shell, env);
		exec_error(shell, list);
	}
}
