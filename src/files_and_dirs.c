#include "uls.h"

int isFile(const char* name)
{
    DIR* directory = opendir(name);

    if(directory != NULL)
    {
     closedir(directory);
     return 0;
    }

    if(errno == ENOTDIR)
    {
     return 1;
    }

    return -1;
}

t_list *files_and_dirs(int argc, char *argv[], t_list **files, t_list **dirs) {
    t_list *err = NULL;
    for (int i = 1; i < argc; i++) {
        if (isFile(argv[i]) == 1) 
            mx_push_back(files, mx_strdup(argv[i]), mx_strlen(argv[i]));
        else if (isFile(argv[i]) == 0)
            mx_push_back(dirs, mx_strdup(argv[i]), mx_strlen(argv[i]));
        else if (isFile(argv[i]) == -1) {
            char *tmp = mx_strdup("uls: "),
            *tmp2 = mx_strjoin(tmp, argv[i]),
            *tmp3 = mx_strjoin(tmp2, ": "),
            *tmp4 = mx_strjoin(tmp3, strerror(errno));
            mx_push_back(&err, tmp4, mx_strlen(tmp2));
            mx_strdel(&tmp);
            mx_strdel(&tmp2);
            mx_strdel(&tmp3);
        }
    }
    return err;
}
