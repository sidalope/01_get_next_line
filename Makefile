# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abisani <abisani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/20 18:49:14 by abisani           #+#    #+#              #
#    Updated: 2025/09/20 09:44:58 by abisani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re bonus

CFLAGS=-Wall -Werror -Wextra

AR=ar rcs

CC=cc

NAME=libgetnextline.a

TEST_EXECUTABLE=test

BUFFER_SIZE=42

SRC_FILES = get_next_line.c get_next_line_utils.c

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_EXECUTABLE)

re: fclean all

test: re
	$(CC) -g $(CFLAGS) -Wl,--wrap=malloc -Wl,--wrap=free -o $(TEST_EXECUTABLE) -D BUFFER_SIZE=$(BUFFER_SIZE) tests.c $(SRC_FILES)
# 	./$(TEST_EXECUTABLE)
#-L. -lgetnextline
