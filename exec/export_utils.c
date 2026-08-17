/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:03:41 by yzoullik          #+#    #+#             */
/*   Updated: 2025/06/18 13:09:22 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_key(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '+')
			if (ptr[i + 1] == '=')
				return (2);
		if (ptr[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	flag_pos(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '+')
			if (ptr[i + 1] == '=')
				return (i);
		if (ptr[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	is_env(char *ptr, t_env **env, int pos)
{
	t_env	*head;

	head = *env;
	while (1)
	{
		if (ft_strnstr(ptr, (*env)->key, pos) && \
		(int) ft_strlen((*env)->key) == pos)
		{
			*env = head;
			return (1);
		}
		*env = (*env)->next;
		if (head == *env)
			break ;
	}
	return (0);
}

void	replace(char *ptr, t_env **env, int pos)
{
	t_env	*head;

	head = *env;
	while (1)
	{
		if (ft_strnstr(ptr, (*env)->key, pos) && \
		(int) ft_strlen((*env)->key) == pos)
		{
			free((*env)->val);
			(*env)->val = ft_strdup(&ptr[pos + 1]);
			(*env)->envflag = 1;
			if (ft_strnstr(ptr, "PATH", 5))
				(*env)->exportflag = 1;
			*env = head;
			return ;
		}
		*env = (*env)->next;
		if (head == *env)
			break ;
	}
}

void	add_to(char *ptr, t_env **env, int pos)
{
	t_env	*head;
	char	*ptr1;

	head = *env;
	while (1)
	{
		if (ft_strnstr(ptr, (*env)->key, pos) && \
		(int) ft_strlen((*env)->key) == pos)
		{
			ptr1 = ft_strjoin1((*env)->val, &ptr[pos + 2]);
			free((*env)->val);
			(*env)->val = ptr1;
			(*env)->envflag = 1;
			if (ft_strnstr(ptr, "PATH", 5))
				(*env)->exportflag = 1;
			*env = head;
			return ;
		}
		*env = (*env)->next;
		if (head == *env)
			break ;
	}
}
