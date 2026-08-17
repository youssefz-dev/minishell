/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pro_mpt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:23:44 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/04 10:07:09 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_run_ex(t_shell *lst, int *x)
{
	g_flag = 0;
	if (lst)
		*x = execshell(lst);
}

int	help_tokens(t_tokens **tok, char *input, int *x)
{
	*tok = tokeni_zation(input);
	if (help_seg(input, *tok, x))
		return (0);
	return (1);
}

int	check_hes(char *s)
{
	char	*ptr;

	ptr = 0;
	ptr = ft_strtrim77(s, " ");
	if (!ptr)
		return (0);
	free(ptr);
	return (1);
}

int	check_it(char *input, int x, t_env **env)
{
	char	*ptr;

	ptr = 0;
	if (check_hes(input))
		add_history(input);
	hand_exit(input, x, env);
	ptr = ft_strtrim77(input, "\t ");
	if (!ptr)
		return (free(input), 0);
	free(ptr);
	return (1);
}

void	pro_mpte(t_env **env)
{
	t_tokens	*tok;
	t_shell		*lst;
	int			x;
	t_her		*her;
	char		*input;

	help_inis(&x, env);
	while (1)
	{
		input = inpu_red();
		if (!check_it(input, x, env))
			continue ;
		if (!help_tokens(&tok, input, &x))
			continue ;
		free(input);
		her = 0;
		if (!handle_it(&her, tok, env, &x))
		{
			free_token(tok);
			continue ;
		}
		lst = parse_token(tok, env, &x, &her);
		free_token(tok);
		help_run_ex(lst, &x);
	}
}
