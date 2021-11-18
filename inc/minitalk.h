/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <goosterl@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 12:12:47 by goosterl      #+#    #+#                 */
/*   Updated: 2021/11/17 14:11:30 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <stdint.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# define ERR_BAD_PID			"Could not locate server PID"
# define ERR_STARTUP			"No arguments supplied (\"PID\" \"MESSAGE\")"
# define ERRMSG					"\033[0;31mError:\n  \033[0m"
# define CONTEXT_ALLOC_FAILURE	"Failed to allocate memory for signal context"
# define MESSAGE_ALLOC_FAILURE	"Failed to allocate memory for message"
# define SIGNAL_USR				int
# define BUFFER_SIZE			128

typedef enum e_contextparam
{
	FREE_MEMORY,
	DO_SOMETHING
}	t_contextparam;

typedef struct s_sigcontext
{
	char		*message;
	uint32_t	msg_length;
	uint32_t	msg_pos;
	pid_t		pid;
}	t_sigcontext;

typedef struct s_sigfeedback
{
	pid_t		pid;
	bool		received;
}	t_sigfeedback;

/*
**	Server functions
*/
void	redirect_decode_header_usr1(int signal, siginfo_t *info, void *context);
void	redirect_decode_header_usr2(int signal, siginfo_t *info, void *context);
void	redirect_decode_signal_usr1(int signal, siginfo_t *info, void *context);
void	redirect_decode_signal_usr2(int signal, siginfo_t *info, void *context);
void	*get_server_context(void);
void	decode_header(int signal, siginfo_t *info);
void	decode_signal(int signal, siginfo_t *info);

/*
**	Client functions
*/
void	redirect_received_sig_usr1(int signal, siginfo_t *info, void *context);
void	redirect_received_sig_usr2(int signal, siginfo_t *info, void *context);
void	*receive_signal_feedback(int signal, siginfo_t *info);
void	encode_header(const int32_t pid, const int32_t header);
void	encode_message(const int32_t pid, const char *message);

/*
**	Error handle
*/
bool	mt_error(const char *message);
bool	mt_error_free(const char *message, void *object);
void	mt_error_exit(const char *message);

/*
**	Utility
*/
int		mt_atoi(char *str, int *num);
size_t	mt_strlen(const char *str);
void	mt_putchar(char c);
void	mt_putnbr(int n);
void	mt_putstr(const char *s);
void	*mt_memset(void *b, int c, size_t len);

#endif
