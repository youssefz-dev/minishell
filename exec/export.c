/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:18:57 by yzoullik          #+#    #+#             */
/*   Updated: 2025/06/18 13:08:01 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_init1(char *str, int i, int envflag, int exportflag)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	env->envflag = envflag;
	env->exportflag = exportflag;
	if (str)
	{
		env->key = malloc(sizeof(char) * i + 1);
		if (!env->key)
			env->key = 0;
		else
			ft_strlcpy(env->key, str, i + 1);
		env->val = ft_strdup(&str[i + 2]);
	}
	else
	{
		env->key = 0;
		env->val = 0;
	}
	(1 && (env->index = 0, env->next = 0, env->prev = 0));
	free(str);
	return (env);
}

int	validate_export(char *ptr)
{
	int	i;

	i = 1;
	if (ptr[0] == '_' && (ptr[1] == '\0' || ptr[1] == '='))
		return (0);
	if (ft_isdigit(ptr[0]) || \
	(!ft_isalpha(ptr[0]) && ptr[0] != '_' && ptr[0] != 32))
		return (dup2(2, 1), \
		printf("bash: export: `%s': not a valid identifier\n", ptr), 0);
	while (ptr[i] == '_' || ptr[i] == 32)
		i++;
	while (ptr[i] && ptr[i] != '=')
	{
		if (ptr[i] == '+' && ptr[i + 1] == '=')
		{
			i++;
			continue ;
		}
		if (!ft_isalpha(ptr[i]) && !ft_isdigit(ptr[i]) \
		&& ptr[i] != '=' && ptr[i] != '_' && ptr[i] != 32)
			return (dup2(2, 1), \
			printf("bash: export: `%s': not a valid identifier\n", ptr), 0);
		i++;
	}
	return (1);
}

void	update_env(t_shell *shell, t_env **env, int i)
{
	if (is_env(shell->cmd[i], shell->env, flag_pos(shell->cmd[i])))
	{
		if (is_key(shell->cmd[i]) == 1)
			replace(shell->cmd[i], shell->env, flag_pos(shell->cmd[i]));
		if (is_key(shell->cmd[i]) == 2)
			add_to(shell->cmd[i], shell->env, flag_pos(shell->cmd[i]));
	}
	else
	{
		if (is_key(shell->cmd[i]) == 1)
			ft_lstadd_back1(env, env_init(ft_strdup(shell->cmd[i]), 1, 1));
		if (is_key(shell->cmd[i]) == 2)
			ft_lstadd_back1(env, env_init1(ft_strdup(shell->cmd[i]), \
			flag_pos(shell->cmd[i]), 1, 1));
	}
}

int	run_export(t_shell *shell, t_env **env)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (shell->cmd[i])
	{
		if (!validate_export(shell->cmd[i]))
		{
			i++;
			j = 1;
			continue ;
		}
		if (!is_env(shell->cmd[i], env, ft_strlen(shell->cmd[i])) \
		&& is_env1(shell->cmd[i]))
			ft_lstadd_back1(env, env_init2(ft_strdup(shell->cmd[i]), 0, 1));
		else
			update_env(shell, env, i);
		i++;
	}
	return (j);
}

int	export(t_shell *shell)
{
	t_env	**env;

	env = shell->env;
	if (!shell->cmd[1])
	{
		if ((*shell->env) == (*shell->env)->next)
			return (0);
		print_export(env);
		return (0);
	}
	return (run_export(shell, env));
}
