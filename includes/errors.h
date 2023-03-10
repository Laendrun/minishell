/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:22:06 by saeby             #+#    #+#             */
/*   Updated: 2023/02/16 18:05:58 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// source: https://www.adminschoice.com/exit-error-codes-in-bash-and-linux-os

// success
# define EXIT_SUCCESS 0
// failure, as defined by the program
# define EXIT_FAILURE 1
// command line usage error
# define EXIT_ERROR 2

// catch all error code | errors such as divide by 0 or oper. not permitted.
# define ERR_ALL 1

// misuse of shell builtin
# define ERR_MISUSE 2

// missing execute permission
# define ERR_NOPERM 126

// cmd not found in path or wrong cmd name
# define ERR_NOEXEC 127

// invalid argument to exit
# define ERR_INVEXARG 128

// Script terminated by ctrl-c
# define ERR_SIGTERM 130

// exit status out of range (OutOfRange)
# define ERR_EXITOOR 255

// syntax error
# define ERR_SYNT 258

// malloc error
# define ERR_MALLOC 260

// ----------------------------------------------
// Error messages
// ----------------------------------------------
# define ERR_CD_ARGS "shellusion: cd: too many arguments"
# define ERR_CD_CD1 "shellusion: cd: "
# define ERR_CD_CD2 ": no such file or directory\n"
# define ERR_CD_CD3 ": Not a directory\n"
# define ERR_CD_HOME "shellusion: cd: HOME not set\n"

# define ERR_ENV_ARGS "shellusion: env: too many arguments"

# define ERR_LEX_DQUO "shellusion: lexer: unclosed double quote"
# define ERR_LEX_SQUO "shellusion: lexer: unclosed single quote"

# define ERR_EXP_KEY1 "shellusion: export: `"
# define ERR_EXP_KEY2 "': not a valid identifier\n"

# define ERR_EXIT_ARGS "shellusion: exit: too many arguments"

# define ERR_MALMES "shellusion: memory allocation error"

# define ERR_NEAR_TOK "shellusion: syntax error near unexpected token"

# define ERR_PIPE "error creating pipe :"
# define ERR_CLOSE "close error :"
# define SH_NAME "shellusion: "
# define ERR_PERM ": Permission denied\n"
# define ERR_FORK "fork error: "
# define ERR_DUP2 "dup2 error: "
# define ERR_INIT "shellusion: initialization error"

#endif