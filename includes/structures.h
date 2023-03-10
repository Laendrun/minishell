/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:42:54 by saeby             #+#    #+#             */
/*   Updated: 2023/02/10 16:11:59 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_env_list
{
	char				*key;
	char				*val;
	struct s_env_list	*next;
	struct s_env_list	*prev;
}				t_env_list;

typedef struct s_tok_list
{
	int					type;
	char				*val;
	struct s_tok_list	*next;
	struct s_tok_list	*prev;
}				t_tok_list;

typedef struct s_cmd_list
{
	char				*cmd;
	char				**args;
	int					infile;
	int					heredoc;
	char				*delim;
	int					hdoc[2];
	int					out_app;
	int					out_trunc;
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
}				t_cmd;

typedef struct s_msh_data
{
	char			*name;
	char			*prompt;
	int				*pid;
	int				*fd;
	int				nb_cmd;
	int				process;
	char			**path;
	char			**env_upd;
	t_env_list		*env;
	t_tok_list		*tokens;
	t_tok_list		**trunc_lst;
	t_cmd			*cmds;
}				t_msh_data;

#endif