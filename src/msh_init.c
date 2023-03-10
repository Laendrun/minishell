/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:35:46 by saeby             #+#    #+#             */
/*   Updated: 2023/02/17 13:10:08 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_init(t_msh_data *m_data, char **env)
{
	int	ret;

	m_data->name = "shellusion";
	m_data->prompt = "\033[0;96mshellusion-1.2>\033[0;39m ";
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
	if (ret != EXIT_SUCCESS)
		return (msh_error(ret, ERR_INIT, EXIT_FAILURE));
	return (ret);
}

int	msh_env_init(t_msh_data *m_data, char **env)
{
	char		**tmp;
	int			err;
	char		*tmp2;

	err = EXIT_SUCCESS;
	while (*env)
	{
		tmp = ft_split(*env, '=');
		insert_env(m_data, ft_strdup(tmp[0]), ft_strdup(tmp[1]), &err);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		env++;
	}
	if (!msh_env_ptr(m_data, "PATH"))
	{
		tmp2 = getcwd(NULL, 0);
		insert_env(m_data, ft_strdup("PATH"), ft_strdup(tmp2), &err);
		free(tmp2);
	}
	set_shlvl(m_data);
	if (err != EXIT_SUCCESS)
		return (msh_error(err, ERR_MALMES, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

void	msh_pip_reset(t_msh_data *m_data)
{
	if (m_data->fd)
		free(m_data->fd);
	if (m_data->pid)
		free(m_data->pid);
	if (m_data->path)
		free_tab_char(m_data->path);
	if (m_data->env_upd)
		free_tab_char(m_data->env_upd);
	if (m_data->cmds)
		free_t_cmd(m_data);
	if (m_data->trunc_lst)
		free(m_data->trunc_lst);
	m_data->fd = NULL;
	m_data->pid = NULL;
	m_data->nb_cmd = 0;
	m_data->process = 0;
	m_data->path = NULL;
	m_data->env_upd = NULL;
	m_data->trunc_lst = NULL;
	m_data->cmds = NULL;
}

void	set_shlvl(t_msh_data *m_d)
{
	t_env_list	*new;
	int			curlvl;
	char		*curval;

	if (!msh_env_ptr(m_d, "SHLVL"))
	{
		new = msh_env_lstnew(ft_strdup("SHLVL"), ft_strdup("1"));
		msh_env_lstaddb(&m_d->env, new);
	}
	else
	{
		curval = msh_get_env(m_d, "SHLVL");
		curlvl = ft_atoi(curval);
		free(curval);
		curlvl++;
		msh_replace_val(m_d, "SHLVL", ft_itoa(curlvl));
	}
}
