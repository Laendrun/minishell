/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:35:46 by saeby             #+#    #+#             */
/*   Updated: 2023/02/13 10:08:56 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_init(t_msh_data *m_data, char **env)
{
	int	ret;

	m_data->name = "shellusion";
	m_data->prompt = "shellusion-0.9> ";
	m_data->env = NULL;
	m_data->tokens = NULL;
	m_data->fd = NULL;
	m_data->pid = NULL;
	m_data->nb_cmd = 0;
	m_data->process = 0;
	m_data->path = NULL;
	m_data->env_upd = NULL;
	m_data->trunc_lst = NULL;
	m_data->cmds = NULL;
	ret = msh_env_init(m_data, env);
	return (ret);
}

int	msh_env_init(t_msh_data *m_data, char **env)
{
	char		**tmp;
	t_env_list	*new;

	while (*env)
	{
		tmp = ft_split(*env, '=');
		new = msh_env_lstnew(ft_strdup(tmp[0]), ft_strdup(tmp[1]));
		if (!new)
			return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
		msh_env_lstaddb(&m_data->env, new);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		env++;
	}
	if (!msh_env_ptr(m_data, "PATH"))
	{
		new = msh_env_lstnew(ft_strdup("PATH"), ft_strdup(getcwd(NULL, 0)));
		if (!new)
			return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
		msh_env_lstaddb(&m_data->env, new);
	}
	return (EXIT_SUCCESS);
}

void	msh_pip_reset(t_msh_data *m_data)
{
	free(m_data->pid);
	free_tab_char(m_data->path);
	free_tab_char(m_data->env_upd);
	free_t_cmd(m_data);
	free(m_data->trunc_lst);
	m_data->fd = NULL;
	m_data->pid = NULL;
	m_data->nb_cmd = 0;
	m_data->process = 0;
	m_data->path = NULL;
	m_data->env_upd = NULL;
	m_data->trunc_lst = NULL;
	m_data->cmds = NULL;
	// msh_free_cmds(m_data);
}
