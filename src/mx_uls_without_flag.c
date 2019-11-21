#include "uls.h"

static void error_print(char *str)
{
    char *err = strerror(errno);
    mx_printerr("uls: ");
    mx_printerr(str);
    mx_printerr(": ");
    mx_printerr(err);
    mx_printerr("\n");
    mx_strdel(&str);
    mx_strdel(&err);
    exit(1);
}

static void non_standart(t_list *list)
{
    for (t_list *j = list; j != NULL; j = j->next)
    {
        mx_printstr(j->data);
        mx_printchar('\n');
    }
}

void print_standart(t_list *list)
{
    if (isatty(1)) {
        int maxLen = max_name_len(list),
        listSize = mx_list_size(list),
        rows = 0, cols = 0;
        char **names = array_of_names(list, listSize);
        struct winsize win;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        cols = win.ws_col / (maxLen + 1);
        if (listSize % cols)
            rows = listSize / cols + 1;
        else
            rows = listSize / cols;
        print_names(names, maxLen, rows, listSize);
        mx_del_strarr(&names);
    } else 
        non_standart(list);
}

void mx_uls_without_flag(char *dir)
{
    DIR *mydir;
    struct dirent *myfile;
    t_list *ul = NULL;
    mydir = opendir(dir);
    if (mydir == NULL) 
        error_print(dir);
    while ((myfile = readdir(mydir)) != NULL)
        if ((myfile->d_name[0] == '.' ? false : true))
            mx_push_back(&ul, myfile->d_name, mx_strlen(myfile->d_name));
    closedir(mydir);
    mx_sort_list(ul);
    print_standart(ul);
}
