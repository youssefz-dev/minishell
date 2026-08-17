/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:49:47 by yzoullik          #+#    #+#             */
/*   Updated: 2025/06/25 10:11:40 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back1(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		new->next = new;
		new->prev = new;
		*lst = new;
	}
	else
	{
		last = (*lst)->prev;
		new->next = (*lst);
		new->prev = last;
		last->next = new;
		(*lst)->prev = new;
	}
}

t_env	*env_init(char *str, int envflag, int exportflag)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	env->envflag = envflag;
	env->exportflag = exportflag;
	if (str)
	{
		env->key = malloc(sizeof(char) * (ft_strchr(str, '=') + 1));
		if (!env->key)
			env->key = 0;
		else
			ft_strlcpy(env->key, str, ft_strchr(str, '=') + 1);
		env->val = ft_strdup(&str[ft_strchr(str, '=') + 1]);
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

t_shell	*ft_lstlast(t_shell *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*list_init(t_shell *shell)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		(free_shell(shell), exit(1));
	list->in = dup(0);
	list->out = dup(1);
	list->pid = 0;
	list->fd[0] = -1;
	list->fd[1] = -1;
	return (list);
}
