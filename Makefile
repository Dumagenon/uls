NAME = uls

NLIB = libmx/libmx.a

HDR = uls.h

SRC = mx_uls.c mx_uls_without_flag.c mx_print_names.c files_and_dirs.c \
for_each_argv.c flag-l.c sort.c

OBJ = $(SRC:.c=.o)

CFLAG = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: install clean

install:
	@cd libmx && make -f Makefile install
	@cp $(addprefix src/, $(SRC)) $(addprefix inc/, $(HDR)) .
	@clang $(CFLAG) -c $(SRC) -I $(HDR)
	@mkdir obj
	@clang $(CFLAG) $(OBJ) $(NLIB) -o $(NAME)
	@mv $(OBJ) ./obj

uninstall:
	@cd libmx && make -f Makefile uninstall
	@rm -rf $(NAME)

clean: 
	@cd libmx && make -f Makefile clean
	@rm -rf $(SRC) $(HDR)
	@rm -rf ./obj

reinstall: uninstall all
