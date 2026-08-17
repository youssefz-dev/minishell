/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlle_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:40:56 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/15 12:40:03 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handlle_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handlle_int_herdoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
