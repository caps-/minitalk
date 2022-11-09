# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 12:41:06 by pwhittin          #+#    #+#              #
#    Updated: 2022/11/08 14:25:50 by pwhittin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#names
SERVER = server
CLIENT = client

#directories
SRCDIR = src
OBJDIR = obj
PRINTFDIR = ft_printf

#ft_printf
PRINTFA = $(addprefix $(PRINTFDIR)/, libftprintf.a)
FT_PRINTF = $(PRINTFA)

#sources
SRVSRC = $(addprefix $(SRCDIR)/, server.c)
CLISRC = $(addprefix $(SRCDIR)/, client.c)

#object files
SRVOBJ = $(subst $(SRCDIR),$(OBJDIR),$(SRVSRC:.c=.o))
CLIOBJ = $(subst $(SRCDIR),$(OBJDIR),$(CLISRC:.c=.o))

#compiler
CC = gcc
INC = include
CLAGS = -Wall -Wextra -Werror

#let's make this shit
all: $(OBJDIR) $(FT_PRINTF) $(SERVER) $(CLIENT)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(CLIENT): $(CLIOBJ)
	$(CC) $(FLAGS) -I$(INC) $(FT_PRINTF) $(CLIOBJ) -o $(CLIENT)

$(CLIOBJ): $(CLISRC)
	$(CC) $(FLAGS) -I$(INC) -c $(CLISRC) -o $(CLIOBJ)

$(SERVER): $(SRVOBJ)
	$(CC) $(FLAGS) -I$(INC) $(FT_PRINTF) $(SRVOBJ) -o $(SERVER)

$(SRVOBJ): $(SRVSRC)
	$(CC) $(FLAGS) -I$(INC) -c $(SRVSRC) -o $(SRVOBJ)

$(PRINTFA):
	$(MAKE) -C $(PRINTFDIR)

#clean it all up
clean:
	$(MAKE) clean -C $(PRINTFDIR)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) -r $(FT_PRINTF)
	$(RM) -r $(SERVER) $(CLIENT)

re: fclean
	$(MAKE)

.PHONY:	all clean fclean re
