# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mpeerdem <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/12 12:28:14 by mpeerdem      #+#    #+#                  #
#    Updated: 2019/12/23 10:21:47 by mpeerdem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
HEADER = libftprintf.h
LIBFT = libft.a
LIBFTMAP = libft
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SDIR = srcs
ODIR = objs
_SRCS = ft_printf.c flag_functions.c flag_functions2.c \
		string_functions.c convert_c.c convert_s.c convert_i.c \
		convert_u.c convert_x.c convert_p.c	convert_f.c convert_n.c \
		convert_e.c print_functions.c format_functions.c \
		float_functions.c convert_g.c exponent_functions.c
_LIBFTSRCS = ft_memcpy.c ft_strlen.c ft_strdup.c ft_isdigit.c ft_strlcpy.c \
			ft_max.c ft_ulltoa.c ft_itoa_base.c ft_n_times_ten.c \
			ft_n_divided_by_ten.c ft_wcbytelen.c ft_wstrlen.c ft_wstrdup.c \
			ft_intlen.c ft_lltoa.c
_LIBFTOBJS := $(_LIBFTSRCS:.c=.o)
_OBJS := $(_SRCS:.c=.o)
SRCS = $(addprefix $(SDIR)/, $(_SRCS))
OBJS = $(addprefix $(ODIR)/, $(_OBJS))
LIBFTOBJS = $(addprefix $(LIBFTMAP)/, $(_LIBFTOBJS))

all: $(NAME)

.PHONY: all bonus clean fclean re test

$(NAME): $(OBJS) $(HEADER) $(LIBFTMAP)/$(LIBFT)
	ar rcs $(NAME) $(OBJS) $(LIBFTOBJS)

$(LIBFTMAP)/$(LIBFT):
	cd $(LIBFTMAP) && make bonus

$(ODIR)/%.o: $(SDIR)/%.c $(HEADER)
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I.

bonus:	$(NAME)

clean:
	rm -f $(OBJS)
	cd $(LIBFTMAP) && make clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFTMAP) && make fclean

re: fclean all
