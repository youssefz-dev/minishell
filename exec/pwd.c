/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:18:45 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/02 15:16:37 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (1);
	printf("%s\n", buff);
	free(buff);
	return (0);
}

char	*pwd1(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (0);
	return (buff);
}
