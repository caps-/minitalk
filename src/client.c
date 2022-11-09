/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:29:42 by pwhittin          #+#    #+#             */
/*   Updated: 2022/11/09 15:11:12 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* Checks for any input errors when the user runs the program. First one should
 * be self explanitory, if you don't remember what ft_strchr() does in the
 * second one we're just using it to make sure only numbers are used for the
 * PID. Prints the appropriate error message to the screen, the strings being
 * defined in our header. */
static int	input_errors(int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc != 3)
	{
		ft_printf(YELLOW);
		ft_printf(ARG_ERR);
		return (1);
	}
	while (argv[1][++i])
	{
		if (!ft_strchr("0123456789", argv[1][i]))
		{
			ft_printf(RED);
			ft_printf(INT_ERR);
			return (1);
		}
	}
	return (0);
}

/*Sends the message string as binary to the server. Best way I can describe is 
 * that if the character is right shifted by i and if the shifted bits are both
 * 1 then we send SIGUSR1, otherwise we treat it as a 0 and use SIGUSR2. Next 
 * we increment i and repeat it seven more times untill we've sent all 8 bits
 * for each character to the server. */
static void	send_bin(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(42);
	}
}

/* Grabs the message string from the main function and then passes it on char
 * by char to the conversion function.*/
static void	send_msg(int pid, char *msg)
{
	int	i;

	i = -1;
	while (msg[++i])
		send_bin(pid, msg[i]);
	send_bin(pid, 0);
}

/* Quick little function to print out a "messaga recieved" type of thing if the
 * server has indeed recieved a message. */
static void	recieved(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf(GREEN);
		ft_printf(MSGRCVD);
	}
}

/* try changing return(-1) to exit(EXIT_FAILURE)
 *
 * sigaction here is just establishing the sig handler sa
 *
 * The main function. Obviously. First thing I wanna point out is the sa
 * variable using the sigaction structure from signal.h. Man sigaction(2) for
 * more info, but basically we're just using it in conjunction with sa_handler
 * to define our own handler function. When the server recieves a signal from
 * the client the client program will run the handler and return a message to
 * the screen. Noice. */
int	main(int argc, char **argv)
{
	int					pid;
	char				*msg;
	struct sigaction	sa;

	if (input_errors(argc, argv))
		return (-1);
	else if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		msg = argv[2];
		ft_printf(PURPLE);
		ft_printf(SENT001, (ft_strlen(msg)));
		sa.sa_handler = recieved;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		send_msg(pid, msg);
	}
	return (0);
}
