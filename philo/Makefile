# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 19:04:01 by jaesjeon          #+#    #+#              #
#    Updated: 2022/08/02 20:02:30 by jaesjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
# CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
# LDFLAGS = -fsanitize=thread -g
RM = rm -f

NAME = philo

HEADER_DIR = .
HEADER = $(HEADER_DIR)/philo.h
SRCS_FILES = philo.c	\
				parser.c	\
				thread_function.c	\
				utils.c	\
				monitor_function.c
SRCS_DIR = .
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS): $(HEADER) | $(OBJS_DIR)

$(addprefix $(OBJS_DIR), %.o): %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $^ -I$(HEADER_DIR) -o $(NAME)

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all