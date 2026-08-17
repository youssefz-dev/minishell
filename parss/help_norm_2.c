/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_norm_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:26:40 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 17:45:09 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*handlle_oured(t_shell *help, t_tokens *tok, t_env **env, int *x)
{
	char	*file1;

	file1 = tok->next->token;
	if (is_dir(file1) == 1)
	{
		help->outfile = -3;
		free(help->outname);
		help->outname = ft_strdup(file1);
	}
	else if (is_dquote(file1) || is_sqoute(file1))
		help_outred1(file1, help, x, env);
	else if (ft_strcmp(file1, "/dev/stdout") == 0)
		help->outfile = 1;
	else if (hav_dolare(file1))
	{
		if (!help_outred3(file1, help, env, x))
			return (tok->next);
	}
	else if (help->infile != -2 && help->infile != -1 \
			&& help->outfile != -1 && help->outfile != -2 \
			&& help->errfile != -10)
	{
		help_outred2(help, tok, file1);
	}
	return (tok->next);
}

void	help_appnd1(char *file2, t_env **env, int *x, t_shell *help)
{
	file2 = get_in_quote(file2, env, x);
	if (is_dir(file2) == 1)
	{
		help->outfile = -3;
		free(help->outname);
		help->outname = ft_strdup(file2);
	}
	else
	{
		help->outfile = open(file2, O_CREAT | O_WRONLY \
			| O_APPEND, 0644);
		free(help->outname);
		help->outname = ft_strdup(file2);
	}
	free(file2);
}

void	help_appnd2(char *file2, int *x, t_shell *help, t_env **env)
{
	if (is_dir(file2) == 1)
	{
		help->outfile = -3;
		free(help->outname);
		help->outname = ft_strdup(file2);
	}
	else if ((is_dquote(file2) || is_sqoute(file2)) && help->errfile != -10)
		fun2(file2, env, help, x);
	else
	{
		help->outfile = open(file2, O_CREAT | O_WRONLY | O_APPEND, 0644);
		free(help->outname);
		help->outname = ft_strdup(file2);
	}
}

void	help_appnd3(char *s, t_shell *help)
{
	if (is_dir(s) == 1)
	{
		help->outfile = -3;
		free(help->outname);
		help->outname = ft_strdup(s);
	}
	else
	{
		help->outfile = open(s, O_CREAT | O_WRONLY \
			| O_APPEND, 0644);
	}
}

void	help_appnd4(char *file2, t_shell *help)
{
	free(help->outname);
	help->outname = ft_strdup(file2);
	if (help->infile == -1)
		help->infile = -2;
}
