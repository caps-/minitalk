/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:15:11 by pwhittin          #+#    #+#             */
/*   Updated: 2022/11/07 17:38:36 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* First up, (void)data is a workaround for compiler warnings. The data 
 * variable is just all the data from the message, we don't actually want to 
 * assign anything to it, so (void)data makes the compiler ignore the fact 
 * we're not going to do that and lets it just use the stuff it already has in 
 * it. 
 *
 * The way the bit conversion works here is a bit funky tbh, but it DOES work
 * so shut up. Basically we're taking the 1's and 0's the function recieves
 * and storing them in our static variable c, shifting them over to the left
 * and repeating 8 times so we eventually fill each byte with 1's and 0's in
 * the correct order for each character. If the character ends up being a null 
 * terminator we write a newline and then reset the signals and the counters to
 * get them ready to recieve the next lot of bits/next byte.  */
static void	sig_handler(int sig, siginfo_t *info, void *data)
{
	static int	i;
	static int	c;
	int			bit;

	(void)data;
	if (sig == SIGUSR2)
		bit = 0;
	else
		bit = 1;
	c += (bit << i);
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
		{
			write (1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
		}
		i = 0;
		c = 0;
	}
}

/* OK, so here we we're basically setting up a way for the server to recieve
 * some signals and then do something with them. We start by defining the
 * sa.sa_sigaction struct to be our own signal handler function, and then set
 * sa_flags to be SA_SIGINFO which is what you need to do in order to specify
 * your own signal handling function. Otherwise it would just use some other
 * shit that's part of the whole signal.h library. So yeah, because we've 
 * defined the sigaction to be our own sig_handler() function it'll use that.
 *
 * Next we get the server PID and display it along with some other messages
 * on the output. Once that's done we use sigaction() to send SIGUSR1 and
 * SIGUSR2 signals to our sig_handler() function.
 *
 * Finally we just got a while loop that just keeps the program running. And
 * that's it for the main.  */
int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	pid = getpid();
	ft_printf(YELLOW);
	ft_printf(SRVINIT);
	ft_printf(CYAN);
	ft_printf("%d\n", pid);
	ft_printf(WHITE);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
