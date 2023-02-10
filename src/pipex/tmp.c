/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:48:47 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/10 15:02:11 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

void	f_duplicate(int in, int out, t_msh_data *m_d)
{
	if (dup2(in, STDIN_FILENO) < 0)
		f_error("Dup2 error : ", strerror(errno), m_d);
	if (dup2(out, STDOUT_FILENO) < 0)
		f_error("Dup2 error : ", strerror(errno), m_d);
}

void	f_pre_duplicate(t_msh_data *m_d, t_cmd *tmp)
{
	if (m_d->process == 0)
	{
		if (tmp->infile != -1)
		{
			if (m_d->nb_cmd == 1)
			{
				f_duplicate(tmp->infile, STDOUT_FILENO, m_d);
				close(tmp->infile);
			}
			else
				f_duplicate(tmp->infile, m_d->fd[1], m_d);
		}
		else if (tmp->heredoc == 1)
		{
			if (m_d->nb_cmd == 1)
			{
				f_duplicate(tmp->hdoc[0], STDOUT_FILENO, m_d);
				close(tmp->hdoc[0]);
			}
			else
				f_duplicate(tmp->hdoc[0], m_d->fd[1], m_d);
		}
		else if (tmp->out_app != -1)
			f_duplicate(STDIN_FILENO, tmp->out_app, m_d);
		else if (tmp->out_trunc != -1)
			f_duplicate(STDIN_FILENO, tmp->out_trunc, m_d);
		else if (m_d->nb_cmd == 1)
			return ;
		else
			f_duplicate(STDIN_FILENO, m_d->fd[1], m_d);
	}
	else if (m_d->process == m_d->nb_cmd - 1)
	{
		if (tmp->out_app != -1)
			f_duplicate(m_d->fd[(2 * m_d->process) - 2], tmp->out_app, m_d);
		else if (tmp->out_trunc != -1)
			f_duplicate(m_d->fd[(2 * m_d->process) - 2], tmp->out_trunc, m_d);
		else if (tmp->infile != -1)
			f_duplicate(tmp->infile, STDOUT_FILENO, m_d);
		else if (tmp->heredoc == 1)
		{
			f_duplicate(tmp->hdoc[0], STDOUT_FILENO, m_d);
			close(tmp->hdoc[0]);
		}
		else
			f_duplicate(m_d->fd[(2 * m_d->process) - 2], STDOUT_FILENO, m_d);
	}
	else
	{
		if (tmp->out_app != -1)
			f_duplicate(m_d->fd[(2 * m_d->process) - 2], tmp->out_app, m_d);
		else if (tmp->out_trunc != -1)
			f_duplicate(m_d->fd[(2 * m_d->process) - 2], tmp->out_trunc, m_d);
		else if (tmp->infile != -1)
			f_duplicate(tmp->infile, m_d->fd[(2 * m_d->process) + 1], m_d);
		else if (tmp->heredoc == 1)
		{
			f_duplicate(tmp->hdoc[0], m_d->fd[(2 * m_d->process) + 1], m_d);
			close(tmp->hdoc[0]);
		}
		else 
			f_duplicate(m_d->fd[(2 * m_d->process) - 2], m_d->fd[(2 * m_d->process) + 1], m_d);
	}
	close_fd_tab(m_d->fd, 2 * (m_d->nb_cmd - 1), m_d);
	// close(m_d->infile);
	// close(m_d->outfile_app);
}

void	pip_no_exec(char *s)
{
	ft_putstr_fd("shellusion: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(" : command not found.\n", STDERR_FILENO);
	exit(1);
}

char	*pip_get_exec(char *cmd, char **paths)
{
	char	*path;

	if ((ft_strncmp(cmd, "./", 2) == 0) \
		&& access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		path = ft_strjoin(path, cmd);
		if (access(path, X_OK) == 0)
			return (path);
		paths++;
	}
	pip_no_exec(cmd);
	return (NULL);
}

char	**pip_get_path(char **env)
{
	char	**paths;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
			break ;
		env++;
	}
	paths = ft_split(*env + 5, ':');
	return (paths);
}

void	child_process(t_msh_data *m_d, t_cmd *tmp)
{
	f_pre_duplicate(m_d, tmp);
	tmp->args[0] = pip_get_exec(tmp->args[0], m_d->path);
	execve(tmp->args[0], tmp->args, m_d->env_upd);
}

void	f_fork(t_msh_data *m_d, t_cmd *tmp)
{
	m_d->pid[m_d->process] = fork();
	if (m_d->pid[m_d->process] < 0)
		f_error("Fork error : ", strerror(errno), m_d);
	if (!m_d->pid[m_d->process])
		child_process(m_d, tmp);
}