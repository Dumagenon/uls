#include "uls.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
		mx_uls_without_flag(".");
    else if (mx_strcmp(argv[1], "-l") != 0)
        for_each_argv(argc, argv);
	else if (mx_strcmp(argv[1], "-l") == 0) {
		DIR *d = opendir(".");
		get_contents(d);
		closedir(d);
	}
	// system("leaks -q uls");
    return 0;
}
