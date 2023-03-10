/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_escape_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/15 19:58:43 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// character that can be escaped in bash :
// \	$	`	"

void	escape_back_loop(int (*i)[3], char *new_val, t_tok_list *cur)
{
	if ((*i)[1] == (*i)[0])
		(*i)[2]++;
	new_val[(*i)[1]] = cur->val[(*i)[1] + (*i)[2]];
		(*i)[1]++;
}

int	escape_backslash(t_tok_list *cur)
{
	int		i[3];
	char	*new_val;

	i[0] = 0;
	while (cur->val[i[0]])
	{
		if (cur->val[i[0]] == '\\' && (cur->val[i[0] + 1] == '\\'
				|| cur->val[i[0] + 1] == '$' || cur->val[i[0] + 1] == '`'
				|| cur->val[i[0] + 1] == '"'))
		{
			new_val = ft_calloc(sizeof(char), ft_strlen(cur->val));
			if (!new_val)
				return (msh_error(1, ERR_MALMES, ERR_MALLOC));
			i[1] = 0;
			i[2] = 0;
			while (cur->val[i[1]])
				escape_back_loop(&i, new_val, cur);
			free(cur->val);
			cur->val = new_val;
		}
		i[0]++;
	}
	return (EXIT_SUCCESS);
}

int	msh_escape_char(t_msh_data *m_d)
{
	t_tok_list	*cur;

	cur = m_d->tokens;
	while (cur)
	{
		if ((cur->type == STR && cur->prev->type == DQUOTE)
			|| cur->type == WORD)
			if (escape_backslash(cur) != 0)
				return (EXIT_FAILURE);
		cur = cur->next;
	}
	return (EXIT_SUCCESS);
}
