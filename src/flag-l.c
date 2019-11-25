#include "uls.h"

// ===================================================== //
//           Код первых одинадцати символов              //
//                     2 функции                         //

static char at_plus_space(char *file) {
	acl_t acl = acl_get_file(file, ACL_TYPE_EXTENDED);
    ssize_t xattr = listxattr(file, NULL, 0, XATTR_NOFOLLOW);
    char chr;

    if (xattr > 0)
        chr = '@';
    else if (acl != NULL)
        chr = '+';
    else
        chr = ' ';

    return chr;
}

static char *eleven_chars_code(struct stat sb, char *file) {
	char *res = mx_strnew(11);
	res[0] = S_ISBLK(sb.st_mode) ? 'b' : \
			 S_ISCHR(sb.st_mode) ? 'c' : \
			 S_ISDIR(sb.st_mode) ? 'd' : \
			 S_ISSOCK(sb.st_mode) ? 's' : \
			 S_ISFIFO(sb.st_mode) ? 'p' : \
			 S_ISLNK(sb.st_mode) ? 'l' : '-';
	res[1] = (S_IRUSR & sb.st_mode) ? 'r' : '-';
	res[2] = (S_IWUSR & sb.st_mode) ? 'w' : '-';
	res[3] = (S_IXUSR & sb.st_mode) ? 'x' : '-';
	res[4] = (S_IRGRP & sb.st_mode) ? 'r' : '-';
	res[5] = (S_IWGRP & sb.st_mode) ? 'w' : '-';
	res[6] = (S_IXGRP & sb.st_mode) ? 'x' : '-';
	res[7] = (S_IROTH & sb.st_mode) ? 'r' : '-';
	res[8] = (S_IWOTH & sb.st_mode) ? 'w' : '-';
	res[9] = (S_ISTXT & sb.st_mode) ? 't' : \
			 (S_IXOTH & sb.st_mode) ? 'x' : '-';
	res[10] = at_plus_space(file);
	return res;
}

// ===================================================== //
//            Получение Логина пользователя              //

char *get_user(uid_t uid)
{
    struct passwd *pws;
    pws = getpwuid(uid);
        return pws->pw_name;
}

// ===================================================== //
//            Получение Группы пользователя              //

char *get_group(gid_t gid)
{
    struct group *g;
	if ((g = getgrgid(gid)) != NULL)
    	return g->gr_name;
	else
    	return mx_itoa(gid);
}

//  ======================================================  //
// Получение названия файла, будь то ссылка или просто файл //

char *get_name(struct stat sb,  char *file) {
	char link_read[255];
	ssize_t bytes_read;
	char *res = NULL, *tmp = NULL;
	if(S_ISLNK(sb.st_mode)){
		//printf("@\033[35m%s ", file);
		//printf("\033[37m");
		tmp = mx_strjoin(file, " -> ");
	    bytes_read = readlink(file, link_read, 254);
		link_read[bytes_read] = '\0';
		res = mx_strjoin(tmp, link_read);
		mx_strdel(&tmp);
	}
	else if((S_IXUSR & sb.st_mode) || (S_IXGRP & sb.st_mode) || (S_IXOTH & sb.st_mode))
		res = mx_strdup(file); //printf("\033[31m%s\033[37m\n", file);
	else if(S_ISFIFO(sb.st_mode))
		res = mx_strdup(file); //printf("\033[33m%s\033[37m\n", file);
	else 
		res = mx_strdup(file); //printf("%s\n", file);
	return res;
}

static void time_for_lflag(struct stat sb, char **arr) {
	char *tmp = ctime(&sb.st_mtime);
	char *oneIndex = mx_memchr(tmp, ' ', mx_strlen(tmp));
    arr[5] = mx_strndup(++oneIndex, 3);
    char *twoIndex = mx_memchr(oneIndex, ' ', mx_strlen(tmp));
	arr[6] = mx_strndup(++twoIndex, 2);
    char *triIndex = mx_memchr(twoIndex, ' ', mx_strlen(tmp));
    arr[7] = mx_strndup(++triIndex, 5);
}

// =================================================== //
//             Добавление строки в список              //

static t_str *create_item(char **data) {
    t_str *node = (t_str *)malloc(sizeof(t_str));
    if (node == NULL)
        return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

static void mx_push(t_str **list, t_str *node) {
    if (*list == NULL) 
        *list = node;
    else {
        t_str *p = *list;
        while (p->next)
            p = p->next;
        p->next = node;
    }
}

static t_str *str_to_list(struct stat sb,  char *file) {
	char **arr = (char**) malloc(sizeof(char*) * 10);
    arr[9] = NULL;
    arr[0] = eleven_chars_code(sb, file); // -rw-r--r--@ 
    arr[1] = mx_strdup(mx_itoa(sb.st_nlink)); // 1
	arr[2] = get_user(sb.st_uid); // psymonov
	arr[3] = get_group(sb.st_gid); // 4242
    arr[4] = mx_strdup(mx_itoa(sb.st_size)); // 623
    time_for_lflag(sb, arr); // Nov 18 17:33
	arr[8] = get_name(sb, file); // Makefile
	return create_item(arr);
}

t_str *display_contents(char * name){
	struct stat sb;
	lstat(name, &sb);
    return str_to_list(sb, name);
}

void get_contents(DIR *d){
	
	struct dirent *entry;
	t_str *listAttr = NULL;
	// struct stat sb;
	// stat("..", &sb);
	//entry = readdir(d);
	while ((entry = readdir(d)) != NULL)
		if (entry->d_name[0] != '.')
            mx_push(&listAttr, display_contents(entry->d_name));
    sort(listAttr);
    for (t_str *i = listAttr; i != NULL; i = i->next) {
        for (int j = 0; i->data[j] != NULL; j++) {
            if (i->data[j + 1] != NULL)
                printf("%s ", i->data[j]);
            else 
                printf("%s\n", i->data[j]);
        }
    }
    // mx_del_strarr(&listAttr->data);
	// printf("%lld", sb.st_blocks); // - печатает  Total blocks size
}
