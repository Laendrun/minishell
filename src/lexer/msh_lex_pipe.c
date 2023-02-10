/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:48:21 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 16:48:27 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_pipe(t_msh_data *m_d, char *line, unsigned int *i)
{
	(void) line;
	msh_tok_lstaddb(&m_d->tokens, msh_tok_lstnew(PIPE, 0));
	*i += 1;
	return (SUCCESS);
}