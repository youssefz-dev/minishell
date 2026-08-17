/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:30:36 by yzoullik          #+#    #+#             */
/*   Updated: 2025/06/26 12:25:18 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort1(t_env	**env)
{
	t_env	*head;
	t_env	*ptr;
	int		i;

	i = 1;
	ptr = *env;
	head = *env;
	while (1)
	{
		if ((*env)->key[0] == '_' && (*env)->key[1] == '\0')
			(*env)->exportflag = 0;
		if (ft_strcmp((*env)->key, ptr->key) > 0)
			i++;
		*env = (*env)->next;
		if (*env == head)
		{
			ptr->index = i;
			break ;
		}
	}
}

void	sort(t_env	**env)
{
	t_env	*head;

	head = *env;
	while (1)
	{
		sort1(env);
		*env = (*env)->next;
		if (*env == head)
			break ;
	}
}

int	get_max(t_env	**env)
{
	t_env	*head;
	int		i;

	head = *env;
	i = 0;
	while (1)
	{
		if ((*env)->index > i)
			i = (*env)->index;
		*env = (*env)->next;
		if (*env == head)
			break ;
	}
	return (i);
}

void	print_export(t_env **env)
{
	t_env	*head;
	int		i;

	sort(env);
	i = get_max(env);
	head = *env;
	while (i)
	{
		if ((*env)->index == i)
		{
			if ((*env)->exportflag)
			{
				(printf("declare -x "), printf("%s", (*env)->key));
				if ((*env)->val)
				{
					(printf("="), printf("\""));
					(printf("%s", (*env)->val), printf("\""));
				}
				printf("\n");
			}
			i--;
		}
		*env = (*env)->next;
	}
	*env = head;
}

t_env	*env_init2(char *str, int envflag, int exportflag)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	env->envflag = envflag;
	env->exportflag = exportflag;
	if (str)
		env->key = ft_strdup(str);
	else
		env->key = 0;
	env->val = 0;
	env->index = 0;
	env->next = 0;
	env->prev = 0;
	free(str);
	return (env);
}
