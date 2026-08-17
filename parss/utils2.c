/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:22:31 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/24 15:52:47 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*handle_specials(char *token, t_tokens *lst, int *i)
{
	if (token[*i] == '|')
		lst = add_token(lst, "|", PIPE);
	else if (token[*i] == '>' && token[*i + 1] == '>')
	{
		lst = add_token(lst, ">>", APPND);
		(*i)++;
	}
	else if (token[*i] == '<' && token[*i + 1] == '<')
	{
		lst = add_token(lst, "<<", HRDC);
		(*i)++;
	}
	else if (token[*i] == '>')
		lst = add_token(lst, ">", OUT_RED);
	else if (token[*i] == '<')
		lst = add_token(lst, "<", IN_RED);
	(*i)++;
	return (lst);
}

t_tokens	*handle_word(char *token, t_tokens *lst, int *i)
{
	char	*word;
	int		start;
	char	quote;

	start = *i;
	while (token[*i] && token[*i] != ' ' && token[*i] != '|' && \
	token[*i] != '<' && token[*i] != '>' && \
	!(token[*i] >= 9 && token[*i] <= 13))
	{
		if (token[*i] == '"' || token[*i] == '\'')
		{
			quote = token[(*i)++];
			while (token[*i] && token[*i] != quote)
				(*i)++;
			if (token[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	word = ft_strndup(&token[start], *i - start);
	if (ft_strlen(word) > 0)
		lst = add_token(lst, word, WORD);
	free(word);
	return (lst);
}

t_tokens	*tokeni_zation(char *token)
{
	t_tokens	*lst;
	int			i;

	lst = NULL;
	i = 0;
	while (token[i])
	{
		if (token[i] == ' ' || (token[i] >= 9 && token[i] <= 13))
			i++;
		else if (token[i] == '|' || token[i] == '<' || token[i] == '>')
			lst = handle_specials(token, lst, &i);
		else
			lst = handle_word(token, lst, &i);
	}
	return (lst);
}

int	is_dir(char *ptr)
{
	DIR	*dir;

	dir = opendir(ptr);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	is_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}
