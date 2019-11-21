#include "uls.h"

static void print_one_dir(char *str) {
    mx_printstr(str);
    mx_printstr(":\n");
}

static void print_dirs(t_list *list, t_list *files) {
    for (t_list *i = list; i != NULL; i = i->next) {
        if (files != NULL)
            print_one_dir(i->data);
        if (i->next) {
            mx_uls_without_flag(i->data);
            mx_printchar('\n');
        } else 
            mx_uls_without_flag(i->data);
    }
}

static void print_errors(t_list *list) {
    for (t_list *i = list; i != NULL; i = i->next) {
        mx_printerr(i->data);
        mx_printerr("\n");
    }
}

void for_each_argv(int argc, char* argv[]) {
    t_list *files = NULL, *dirs = NULL;
    
    t_list *err = files_and_dirs(argc, argv, &files, &dirs);
    mx_sort_list(err);
    mx_sort_list(files);
    mx_sort_list(dirs);
    print_errors(err);
    if (dirs != NULL && files != NULL) {
        print_standart(files);
        mx_printchar('\n');
    }
    else
        print_standart(files);
    
    print_dirs(dirs, files);
    system("pause & leaks -q uls");
}
