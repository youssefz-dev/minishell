/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_prmpt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:50:11 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/01 10:14:39 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	herdoc_limit(t_tokens *tok, t_env **env, t_her **her)
{
	if (count_hrdc(tok) > 16)
	{
		printf("minishell: maximum here-document count exceeded\n");
		free_token(tok);
		free_env(env);
		free_her(her);
		exit(2);
	}
}

int	handle_it(t_her **her, t_tokens *tok, t_env **env, int *x)
{
	t_tokens	*head;
	int			y;

	head = tok;
	herdoc_limit(tok, env, her);
	while (tok)
	{
		if (tok->type == HRDC)
		{
			y = dup(0);
			ft_lstadd_back4 \
			(her, her_init(create_file(tok->next->token, env, x)));
			if ((*her)->prev->file == -4)
			{
				dup2(y, 0);
				close(y);
				free_her(her);
				return (0);
			}
			close(y);
		}
		tok = tok->next;
	}
	tok = head;
	return (1);
}

char	*inpu_red(void)
{
	signal(SIGINT, sig_action);
	signal(SIGQUIT, SIG_IGN);
	return (readline("youmoumn@yzoullik$ "));
}

int	help_seg(char *input, t_tokens *tok, int *x)
{
	if (checked_syntax(tok, x) || check_unclosed_quote(input, x) \
	|| input[0] == '\0')
	{
		free_token(tok);
		free(input);
		return (1);
	}
	return (0);
}

void	help_inis(int *x, t_env **env)
{
	*x = 0;
	add_env(env);
}
