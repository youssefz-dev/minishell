/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_norm_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:21:56 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 17:43:27 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*handll_inred(t_shell *help, t_tokens *tok, t_env **env, int *x)
{
	char	*s;
	char	*file;

	file = tok->next->token;
	if (is_dquote(file) || is_sqoute(file))
		help_inred(file, help, x, env);
	else if (ft_strcmp(file, "/dev/stdin") == 0)
		help->infile = 0;
	else if (hav_dolare(file))
	{
		s = get_var(file, env, x);
		if ((ft_strlen(s) == 0 || is_space(s) == 1) && help->errfile != -10)
		{
			printf("bash: %s: ambiguous redirect\n", file);
			free(s);
			*x = 1;
			g_flag = 0;
			help->errfile = -10;
			return (tok->next);
		}
		help_inred_4(s, help);
	}
	else if (help->infile != -1 && help->infile != -2 && help->errfile != -10)
		help_infil3(file, env, x, help);
	return (tok->next);
}

void	help_outred1(char *file1, t_shell *help, int *x, t_env **env)
{
	char	*file2;

	file2 = get_in_quote(file1, env, x);
	if (is_dir(file2) == 1)
	{
		help->outfile = -3;
		free(help->outname);
		help->outname = file2;
	}
	else
	{
		close_fd(help->outfile);
		help->outfile = open(file2, O_WRONLY | O_CREAT \
			| O_RDONLY | O_TRUNC, 0644);
		free(help->outname);
		help->outname = file2;
	}
}

void	help_outred2(t_shell *help, t_tokens *tok, char *file1)
{
	close_fd(help->outfile);
	help->outfile = open(tok->next->token, O_WRONLY | O_CREAT \
		| O_RDONLY | O_TRUNC, 0644);
	free(help->outname);
	help->outname = ft_strdup(file1);
	if (help->outfile == -1)
	{
		help->outfile = -2;
	}
}

int	help_outred3(char *file1, t_shell *help, t_env **env, int *x)
{
	char	*s;

	s = get_var(file1, env, x);
	if (is_dir(s))
	{
		help->outfile = -3;
		free(help->outname);
		help->outname = ft_strdup(s);
	}
	else if ((ft_strlen(s) == 0 || is_space(s) == 1) && help->errfile != -10)
	{
		(printf("bash: %s: ambiguous redirect\n", file1), free(s));
		*x = 1;
		g_flag = 0;
		help->errfile = -10;
		return (0);
	}
	else if (help->errfile != -10)
	{
		close_fd(help->outfile);
		help->outfile = open(s, O_WRONLY | O_CREAT \
			| O_RDONLY | O_TRUNC, 0644);
	}
	free(s);
	return (1);
}
