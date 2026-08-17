/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:39:22 by yzoullik          #+#    #+#             */
/*   Updated: 2025/05/14 15:39:42 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd1(t_env **env, int i, char *buff)
{
	t_env	*head;
	char	*ptr;

	ptr = 0;
	head = *env;
	while (1)
	{
		if (ft_strnstr("PWD", (*env)->key, 3) && \
		(int) ft_strlen((*env)->key) == 3)
		{
			if (i == 1)
				ptr = ft_strjoin1((*env)->val, "/..");
			free((*env)->val);
			if (i == 0)
				(*env)->val = ft_strdup(buff);
			else
				(*env)->val = ptr;
			(*env)->envflag = 1;
			*env = head;
			return ;
		}
		*env = (*env)->next;
		if (head == *env)
			break ;
	}
}

void	change_pwd(t_shell *shell)
{
	char	*buff;
	t_env	**env;
	int		i;

	i = 0;
	env = shell->env;
	buff = pwd1();
	if (!buff)
	{
		i = 1;
		dup2(2, 1);
		printf("cd: error retrieving current directory: getcwd");
		printf(": cannot access parent directories:");
		printf("No such file or directory\n");
	}
	change_pwd1(env, i, buff);
	free(buff);
}

char	*get_pwd(t_env *env)
{
	char	*ptr;
	t_env	*head;

	ptr = 0;
	head = env;
	while (1)
	{
		if (ft_strnstr("PWD", env->key, 3) && \
		(int) ft_strlen(env->key) == 3)
		{
			ptr = ft_strdup(env->val);
			env = head;
			return (ptr);
		}
		env = (env)->next;
		if (head == env)
			break ;
	}
	return (0);
}

void	change_oldpwd(t_shell *shell)
{
	t_env	**env;
	t_env	*head;

	env = shell->env;
	head = *env;
	while (1)
	{
		if (ft_strnstr("OLDPWD", (*env)->key, 6) && \
		(int) ft_strlen((*env)->key) == 6)
		{
			(*env)->envflag = 1;
			free((*env)->val);
			(*env)->val = get_pwd(head);
			*env = head;
			return ;
		}
		*env = (*env)->next;
		if (head == *env)
			break ;
	}
}

int	cd_utils(t_shell *shell, char *str)
{
	if (!search_env(shell->env, str) || \
	!get_env2(shell->env, str)->val \
	|| get_env2(shell->env, str)->val[0] == '\0')
	{
		dup2(2, 1);
		printf("bash: cd: %s not set\n", str);
		return (0);
	}
	ft_free(shell->cmd);
	shell->cmd = malloc(sizeof(char *) * 3);
	if (!shell->cmd)
		return (0);
	shell->cmd[0] = ft_strdup("cd");
	if (!shell->cmd[0])
		return (0);
	shell->cmd[1] = ft_strdup(get_env2(shell->env, str)->val);
	if (!shell->cmd[1])
		return (0);
	shell->cmd[2] = 0;
	return (1);
}
