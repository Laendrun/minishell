/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2022/11/21 18:51:06 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f_error(char *str, char *erno, t_msh_data *d)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(erno, 2);
	write(2, "\n", 1);
	if (d->pid)
		free(d->pid);
	exit(0);
}

void	free_tab_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	close_fd_tab(int *fd, int size, t_msh_data *d)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (close(fd[i]) < 0)
			f_error("Close error :", strerror(errno), d);
		i++;
	}
	free(fd);
}
