NLIB = libmx.a

HDR = libmx.h

SRC = mx_printchar.c mx_strlen.c mx_printstr.c mx_printint.c mx_strcmp.c \
mx_strnew.c mx_strcpy.c mx_strdup.c mx_strdel.c mx_get_char_index.c \
mx_strndup.c mx_strncpy.c mx_count_words.c mx_strsplit.c mx_printerr.c \
mx_isalpha.c mx_isdigit.c mx_atoi.c mx_isspace.c mx_itoa.c \
mx_create_node.c mx_push_back.c mx_sort_list.c mx_list_size.c mx_strjoin.c \
mx_strcat.c mx_del_strarr.c mx_memchr.c mx_memrchr.c

OBJ = $(SRC:.c=.o)

CFLAG = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: install clean

install:
	@mkdir obj
	@cp $(addprefix src/, $(SRC)) $(addprefix inc/, $(HDR)) .
	@clang $(CFLGS) -c $(SRC) -I $(HDR)
	@ar -rc $(NLIB) $(OBJ)
	@mv $(OBJ) ./obj

uninstall:
	@rm -rf $(NLIB)

clean: 
	@rm -rf $(SRC) $(HDR)
	@rm -rf ./obj

reinstall: uninstall all
