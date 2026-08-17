/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_er.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:17:08 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 17:34:40 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handlle_no_quotes(t_shell *help, t_tokens *tok, t_env **env, int *x)
{
	char	*s;
	char	*s1;

	if (hav_dolare(tok->token) != 0)
	{
		s = get_var(tok->token, env, x);
		if (ft_strlen(s) == 0)
			return (free(s), 0);
		if (!fun1(&s, &s1))
			return (0);
		if (hav_dolare(tok->token) && help->flgexp == 1 \
		&& help->validexp != 1 && is_min(s))
			(1 && (help->cmd = add_to_array(help->cmd, s), free(s), s = 0));
		else if (ft_strchr(s, ' ') != -1)
			help_no_quotes1(s, help, x, env);
		else
		{
			help->cmd = add_to_array(help->cmd, s);
			free(s);
		}
	}
	else
		help->cmd = add_to_array(help->cmd, tok->token);
	return (0);
}

void	handlle_word(t_shell *help, t_tokens *tok, t_env **env, int *x)
{
	char	*d;

	d = get_prev_equale(tok->token);
	if (is_squote_end(d) || is_dquote(d))
	{
		help->validexp = 1;
	}
	if (ft_strcmp(tok->token, "export") == 0)
	{
		help->flgexp = 1;
	}
	if (is_sqoute(tok->token) == 1 && is_sqoute(d) != 1)
		handlle_sq(help, tok, env, x);
	else if (is_dquote(tok->token) == 1 && is_dquote(d) != 1)
	{
		if (is_dquote_end(tok->token))
			handlle_val_dq(help, tok, env, x);
		else
			handlle_inval_dq(help, tok, env, x);
	}
	else
		handlle_no_quotes(help, tok, env, x);
	free(d);
}

int	help_parss_token1(t_shell *help, t_tokens **tok, int *x, t_env **env)
{
	if ((*tok)->next && (*tok)->type == IN_RED)
		*tok = handll_inred(help, *tok, env, x);
	else if ((*tok)->next && (*tok)->type == OUT_RED)
		*tok = handlle_oured(help, *tok, env, x);
	else if ((*tok)->next && (*tok)->type == APPND)
		*tok = handlle_appnd(help, *tok, env, x);
	else if ((*tok)->type == WORD)
		handlle_word(help, *tok, env, x);
	return (1);
}

void	handlle_pipe(t_shell **help)
{
	t_shell	*new;

	new = new_lst();
	(*help)->next = new;
	new->prev = (*help);
	(*help) = new;
}

t_shell	*parse_token(t_tokens *tok, t_env **env, int *x, t_her **her)
{
	t_shell	*lst;
	t_shell	*help;

	lst = new_lst();
	help = lst;
	while (tok)
	{
		help->env = env;
		if (tok->next && tok->type == PIPE)
			handle_pipe(&help);
		else if (tok->next && tok->type == HRDC)
		{
			close_fd(help->infile);
			help->infile = (*her)->file;
			*her = (*her)->next;
			tok = tok->next;
		}
		else
			help_parss_token1(help, &tok, x, env);
		tok = tok->next;
	}
	return (free_her0(her), lst);
}
