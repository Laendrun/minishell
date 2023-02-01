/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:44:48 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 11:45:18 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "structures.h"

// ----------------------------------------------
// builtins/msh_env.c
// ----------------------------------------------
int			msh_env(t_msh_data *m_data);

// ----------------------------------------------
// builtins/msh_pwd.c
// ----------------------------------------------
int			msh_pwd(t_msh_data *m_data);
char		*msh_getpwd(t_msh_data *m_data);
void		msh_setpwd(t_msh_data *m_data, char *new_path);

// ----------------------------------------------
// builtins/msh_cd.c
// ----------------------------------------------
int			msh_cd(t_msh_data *m_data, char *new_path);

// ----------------------------------------------
// builtins/msh_exit.c
// ----------------------------------------------
void		msh_exit(t_msh_data *m_data, int exit_code);

// ----------------------------------------------
// builtins/msh_clear.c
// ----------------------------------------------
int			msh_clear(t_msh_data *m_data);

// ----------------------------------------------
// builtins/msh_export.c
// ----------------------------------------------
int			msh_export(t_msh_data *m_d, char *key, char *val);

// ----------------------------------------------
// builtins/msh_unset.c
// ----------------------------------------------
int	msh_unset(t_msh_data *m_d, char *key);

#endif