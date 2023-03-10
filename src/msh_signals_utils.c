/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:54:19 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 18:55:52 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	msh_set_gcode(1);
}

void	nothing(int v)
{
	(void)v;
	ft_putstr_fd("Quit: 3\n", 1);
	msh_set_gcode(131);
	rl_redisplay();
}

void	backslash_n(int v)
{
	(void)v;
	write(1, "\n", 1);
	msh_set_gcode(130);
	rl_redisplay();
}

void	sigquit_update(void)
{
	struct sigaction	action;

	action.sa_handler = &nothing;
	sigaction(SIGQUIT, &action, NULL);
}
