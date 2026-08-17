/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:09:41 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 18:18:08 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	int		i;
	t_env	*envptr;

	i = 0;
	envptr = 0;
	if (!isatty(0) || !isatty(1))
		return (0);
	if (ac > 1)
	{
		printf("minishell: %s: No such file or directory\n", av[1]);
		return (127);
	}
	while (env[i])
		ft_lstadd_back1(&envptr, env_init(ft_strdup(env[i++]), 1, 1));
	pro_mpte(&envptr);
}
