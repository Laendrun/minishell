/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:09:10 by saeby             #+#    #+#             */
/*   Updated: 2023/02/16 15:12:17 by saeby            ###   ########.fr       */
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

	if ((ft_strncmp(cmd, "/", 1) == 0 && ft_strlen(cmd) > 1)
		&& access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if ((ft_strncmp(cmd, "./", 2) == 0 && ft_strlen(cmd) > 2)
		&& access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (*paths
		&& (ft_strncmp(cmd, "/", 1))
		&& (ft_strncmp(cmd, "./", 2))
		&& (ft_strncmp(cmd, ".", 1)))
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
