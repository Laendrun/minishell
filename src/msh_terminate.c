/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_terminate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:15:34 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 18:57:09 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_terminate(t_msh_data *m_data)
{
	if (m_data->tokens)
		msh_free_tok(m_data);
	if (m_data->cmds)
		msh_free_cmds(m_data);
	free(m_data->env_upd);
	if (m_data->env)
		msh_free_env(m_data);
}
