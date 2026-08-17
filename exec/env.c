/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:19:13 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/02 15:17:36 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_env(t_env **env, char *key)
{
	int		i;
	t_env	*head;

	i = 0;
	head = *env;
	while (1)
	{
		if (ft_strnstr((*env)->key, key, ft_strlen(key)) && \
		ft_strlen(key) == ft_strlen((*env)->key))
			i = 1;
		*env = (*env)->next;
		if (head == *env)
			break ;
	}
	return (i);
}

t_env	*get_env2(t_env **env, char *key)
{
	t_env	*head;
	t_env	*node;

	head = *env;
	while (1)
	{
		if (ft_strnstr((*env)->key, key, ft_strlen(key)) && \
		ft_strlen(key) == ft_strlen((*env)->key))
		{
			node = *env;
			*env = head;
			return (node);
		}
		*env = (*env)->next;
		if (head == *env)
			break ;
	}
	return (0);
}

void	handel_sh(t_env **env)
{
	t_env	*node;
	long	val;

	node = get_env2(env, "SHLVL");
	val = ft_atoi1(node->val);
	free(node->val);
	if (val < 0 || val >= INT_MAX)
	{
		node->val = ft_strdup("0");
		return ;
	}
	if (val >= 999)
	{
		printf("bash: warning: shell level (%ld) too high, resetting to 1\n", \
		val + 1);
		val = -1;
	}
	node->val = ft_itoa(val + 1);
}

void	add_env(t_env **env)
{
	char	*buff;
	char	*ptr;

	buff = pwd1();
	ptr = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	if (!*env)
	{
		ft_lstadd_back1(env, env_init2(ft_strdup("OLDPWD"), 0, 1));
		ft_lstadd_back1(env, env_init(ft_strjoin1("PWD=", buff), 1, 1));
		ft_lstadd_back1(env, env_init(ft_strdup("SHLVL=1"), 1, 1));
		ft_lstadd_back1(env, env_init(ft_strdup("_=/usr/bin/env"), 1, 0));
		ft_lstadd_back1(env, env_init(ft_strdup(ptr), 0, 0));
	}
	else
	{
		if (!search_env(env, "OLDPWD"))
			ft_lstadd_back1(env, env_init2(ft_strdup("OLDPWD"), 0, 1));
		if (!search_env(env, "PWD"))
			ft_lstadd_back1(env, env_init(ft_strjoin1("PWD=", buff), 1, 1));
		if (!search_env(env, "SHLVL"))
			ft_lstadd_back1(env, env_init(ft_strdup("SHLVL=1"), 1, 1));
		if (!search_env(env, "PATH"))
			ft_lstadd_back1(env, env_init(ft_strdup(ptr), 0, 0));
	}
	free(buff);
}

int	env(t_shell *shell)
{
	t_env	*head;
	t_env	**env;

	env = shell->env;
	if (shell->cmd[1])
		return (1);
	head = *env;
	while (1)
	{
		if ((*env)->envflag == 1)
		{
			printf("%s", (*env)->key);
			printf("=");
			printf("%s\n", (*env)->val);
		}
		*env = (*env)->next;
		if (head == *env)
			break ;
	}
	return (0);
}
