/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:05:50 by saeby             #+#    #+#             */
/*   Updated: 2023/01/27 13:31:56 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*rl;
	t_msh_data	m_data;

	(void) ac;
	(void) av;
	msh_init(&m_data, env);
	printf("\e[1;1H\e[2J");
	while (1)
	{
		rl_on_new_line();
		rl = readline(m_data.prompt);
		add_history(rl);
		if (ft_strncmp(rl, "exit", 5) == 0)
			break ;
		if (ft_strncmp(rl, "clear", 5) == 0)
			msh_clear(&m_data);
		msh_lex(&m_data, rl);
		// parser
		msh_free_tok(&m_data);
	}
	free(rl);
	msh_free_tok(&m_data);
	msh_free_env(&m_data);
	return (SUCCESS);
}