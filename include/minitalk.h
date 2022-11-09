/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:47:22 by pwhittin          #+#    #+#             */
/*   Updated: 2022/11/03 16:24:34 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include "../ft_printf/include/libftprintf.h"

/* message macros */
# define SENT001 "Sent %d characters\n"
# define ARG_ERR "Usage: ./client [pid] [message]\n"
# define INT_ERR "PIDs are numbers only, try it again.\n"
# define MSGRCVD "Message recieved!\n"
# define SRVINIT "Server is up, let's talk!\nServer PID: "

/* colour macros */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RED_B "\033[1;31m"
# define GREEN_B "\033[1;32m"
# define YELLOW_B "\033[1;33m"
# define BLUE_B "\033[1;34m"
# define PURPLE_B "\033[1;35m"
# define CYAN_B "\033[1;36m"
# define WHITE_B "\033[1;37m"

#endif
