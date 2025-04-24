# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/23 10:52:20 by ygaiffie          #+#    #+#              #
#    Updated: 2025/04/24 21:40:42 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS			:= --no-print-directory
# ifndef VERBOSE
# MAKEFLAGS += --no-print-directory --silent
# endif

SHELL				:=	/bin/bash

BLINK_GREEN			:=	\033[5;32m
BGREEN				:=	\033[1;32m
BHYEL				:= 	\033[1;93m
BOLD				:=	\033[1m
NC					:=	\033[0m

NAME				:= 	ircserv
NAME_BOT			:=	meteobot

# includes --------------------------------------------------------------------#

DIR_INC				:=	include \
						class \
						class/command

I_FLAG				:=	$(addprefix -I,$(DIR_INC)) -MMD -MP

# sources ---------------------------------------------------------------------#

SRC_DIR				:=	src

SRCS				:= 	main.cpp \
						error.cpp \
						reply.cpp \
						log.cpp \
						utils.cpp \
						signal.cpp \
						socket.cpp

SRCS				:=	$(SRCS:%=$(SRC_DIR)/%)

SRCS_BOT			:=	log.cpp \
						meteobot.cpp \
						signal.cpp \
						socket.cpp \
						utils.cpp

SRCS_BOT			:=	$(SRCS_BOT:%=$(SRC_DIR)/%)

# sources madatory only -------------------------------------------------------#

SRC_CLASS_DIR		:=	class

SRCS_CLASS			:=	Client.cpp \
						Server.cpp \
						Channel.cpp \
						Message.cpp \
						Params.cpp \
						Protocole_error.cpp \
						Elements.cpp \
						Mode_rpl.cpp \
						Command.cpp \
						command/Who.cpp \
						command/Nick.cpp \
						command/User.cpp \
						command/Pass.cpp \
						command/Join.cpp \
						command/Ping.cpp \
						command/Topic.cpp \
						command/Quit.cpp \
						command/Kick.cpp \
						command/Invite.cpp \
						command/Privmsg.cpp \
						command/Notice.cpp \
						command/Mode.cpp \
						command/List.cpp \
						command/Part.cpp

SRCS_CLASS			:=	$(SRCS_CLASS:%=$(SRC_CLASS_DIR)/%)

SRCS_BOT_CLASS		:=	AccuWeatherAPI.cpp \
						Bot.cpp \
						Message.cpp \
						Params.cpp

SRCS_BOT_CLASS		:=	$(SRCS_BOT_CLASS:%=$(SRC_CLASS_DIR)/%)

# objects ---------------------------------------------------------------------#

OBJ_DIR				:=	.build/

OBJS				:= 	$(SRCS:%.cpp=$(OBJ_DIR)%.o)

OBJS				:= 	$(OBJS) $(SRCS_CLASS:%.cpp=$(OBJ_DIR)%.o)

DEPS				:=	$(OBJS:.o=.d)


OBJS_BOT			:= 	$(SRCS_BOT:%.cpp=$(OBJ_DIR)%.o)

OBJS_BOT			:= 	$(OBJS_BOT) $(SRCS_BOT_CLASS:%.cpp=$(OBJ_DIR)%.o)

DEPS_BOT			:=	$(OBJS_BOT:.o=.d)

# compilation -----------------------------------------------------------------#

CXX 				:= 	c++
CFLAGS 				:= 	-Wall -Werror -Wextra

#------------------------------------------------------------------------------#
# rules                                                                        #
#------------------------------------------------------------------------------#

all: init
	@$(MAKE) -j makeall
	@echo -e "\t$(BLINK_GREEN)$(NAME) = COMPILATION FINISHED !$(NC)"

clean:
	@rm -fr $(OBJ_DIR) && printf "Cleaning : $(OBJ_DIR)\n"

fclean: clean
	@rm -f $(NAME) && printf "Cleaning: $(NAME) \n"
	@rm -f $(NAME_BOT)  && printf "Cleaning: $(NAME_BOT) \n"

re: fclean
	@$(MAKE) all

init:
	@echo -e ""
	@echo -e "\t\t$(BHYEL)┍━━━━━━━━»•» 🌸 «•«━┑$(NC)"
	@echo -e "\t\t$(BHYEL) IRCSERV COMPILATION $(NC)"
	@echo -e "\t\t$(BHYEL)┕━»•» 🌸 «•«━━━━━━━━┙$(NC)"
	@echo -e ""

test: all
	./$(NAME) 6666 "admin"

bot:
	@$(MAKE) -j makebot

makeall: $(NAME)
makebot: $(NAME_BOT)

#------------------------------------------------------------------------------#
# compilation                                                                  #
#------------------------------------------------------------------------------#

$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) $(I_FLAG) -o $@ -c $< && echo -e "$(BGREEN)[✔]$(NC)\tCompiling:\t$(BOLD)$(notdir $<)$(NC)"

-include $(DEPS)
-include $(DEPS_BOT)

#------------------------------------------------------------------------------#
# linkage                                                                      #
#------------------------------------------------------------------------------#

$(NAME): $(OBJS)
	@$(CXX) $(CFLAGS) $(OBJS) -o $@ && echo -e "$(BGREEN)[✔]$(NC)\tLinking Exe:\t$(BOLD)$@\n$(NC)"

$(NAME_BOT): $(OBJS_BOT)
	@$(CXX) $(CFLAGS) $(OBJS_BOT) -o $@ && echo -e "$(BGREEN)[✔]$(NC)\tLinking Exe:\t$(BOLD)$@\n$(NC)"

#------------------------------------------------------------------------------#
# specifications                                                               #
#------------------------------------------------------------------------------#

.PHONY: clean \
		fclean \
		all \
		re \
		test \
		init \
		makeall
