/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:09:10 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 22:48:04 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f_fork(t_msh_data *m_d, t_cmd *tmp)
{
	if (m_d->nb_cmd == 1 && msh_is_builtin(tmp->args[0]))
		msh_exec_builtin(tmp, m_d);
	else
	{
		m_d->pid[m_d->process] = fork();
		if (m_d->pid[m_d->process] < 0)
			return (msh_error(1, ERR_FORK, 1));
		if (!m_d->pid[m_d->process])
			child_process(m_d, tmp);
	}
	return (EXIT_SUCCESS);
}

char	**pip_get_path(char **env)
{
	char	**paths;
	char	*tmp;
	char	*tmp2;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
			break ;
		env++;
	}
	if (!*env)
	{
		tmp2 = getcwd(NULL, 0);
		tmp = (char *) malloc(sizeof(char) * ft_strlen(tmp2) + 1);
		ft_strlcat(tmp, tmp2, ft_strlen(tmp2));
		tmp[ft_strlen(tmp2)] = 0;
		paths = ft_split(tmp, ':');
		free(tmp);
		free(tmp2);
	}
	else
		paths = ft_split(*env + 5, ':');
	return (paths);
}

char	*pip_get_exec(char *cmd, char **paths)
{
	char	*path;

	if ((ft_strncmp(cmd, "/", 1) == 0)
		&& access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if ((ft_strncmp(cmd, "./", 2) == 0)
		&& access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		if (!path)
			return (NULL);
		path = ft_strjoin(path, cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		paths++;
	}
	pip_no_exec(cmd);
	return (NULL);
}

int	f_pre_duplicate(t_msh_data *m_d, t_cmd *tmp)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (m_d->process == 0)
		ret = first_process(m_d, tmp);
	else if (m_d->process == m_d->nb_cmd - 1)
		ret = last_process(m_d, tmp);
	else
		ret = middle_process(m_d, tmp);
	if (close_fd_tab(m_d->fd, 2 * (m_d->nb_cmd - 1)) != 0)
		return (EXIT_FAILURE);
	return (ret);
}
