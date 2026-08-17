/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:26:43 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/30 11:22:07 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	*new_lst(void)
{
	t_shell	*new;

	new = malloc(sizeof(t_shell));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->cmd = NULL;
	new->infile = 0;
	new->outfile = 1;
	new->errfile = 0;
	new->outname = NULL;
	new->inname = NULL;
	return (new);
}

t_tokens	*add_token(t_tokens *lst, char *str, int type)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->next = 0;
	new->prev = 0;
	new->token = 0;
	new->type = 0;
	tmp = lst;
	new->token = ft_strdup(str);
	if (!new->token)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	if (!lst)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}

char	*ft_strndup(char *s1, int n)
{
	int		i;
	char	*str;
	int		x;

	x = ft_strlen(s1);
	str = malloc(x * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
		{
			return (1);
		}
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

int	is_qutes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
