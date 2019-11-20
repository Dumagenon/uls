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
            mx_push_back(files, argv[i], mx_strlen(argv[i]));
        else if (isFile(argv[i]) == 0)
            mx_push_back(dirs, argv[i], mx_strlen(argv[i]));
        else if (isFile(argv[i]) == -1) {
            char *tmp = mx_strdup("uls: ");
            tmp = mx_strjoin(tmp, argv[i]);
            tmp = mx_strjoin(tmp, ": ");
            tmp = mx_strjoin(tmp, strerror(errno));
            mx_push_back(&err, tmp, mx_strlen(tmp));
        }
    }
    return err;
}
