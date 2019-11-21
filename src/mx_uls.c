// В Мейнике находится все по флагу -l
// Обработка вывода без флагов осуществяется в mx_uls_without_flag.c
// mx_print_names, for_each_argv.c, files_and_dirs.c


#include "uls.h"

// ===================================================== //
//           Код первых одинадцати символов              //
//                     2 функции                         //

static char at_plus_space(char *file) {
	acl_t acl = acl_get_file(file, ACL_TYPE_ACCESS);
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
	char *res = mx_strnew(12);
	res[0] = S_ISDIR(sb.st_mode) ? 'd' : \
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
	res[9] = (S_IXOTH & sb.st_mode) ? 'x' : '-';
	res[10] = at_plus_space(file);
	res[11] = ' ';
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

static char *time_for_lflag(struct stat sb) {
	char *tmp = ctime(&sb.st_ctime);
	char *oneIndex = mx_memchr(tmp, ' ', mx_strlen(tmp));
	return mx_strndup(++oneIndex, 16);
}

// =================================================== //
//                   Печать строки                     //

static char *str_to_print(struct stat sb,  char *file) {
	char *res = eleven_chars_code(sb, file),
		*login = get_user(sb.st_uid),
		*group = get_group(sb.st_gid),
		*name = get_name(sb, file); // -rw-r--r--@ 
	res = mx_strjoin(res, mx_itoa(sb.st_nlink)); // 1
	res = mx_strjoin(res, " ");
	res = mx_strjoin(res, login); // psymonov
	res = mx_strjoin(res, "  ");
	res = mx_strjoin(res, group); // 4242
	res = mx_strjoin(res, "  ");
	res = mx_strjoin(res, mx_itoa(sb.st_size)); // 623
	res = mx_strjoin(res, " ");
	res = mx_strjoin(res, time_for_lflag(sb)); // Nov 18 17:33
	res = mx_strjoin(res, name); // Makefile
	mx_strdel(&name);
	return res;
}

void display_contents(char * name){
	struct stat sb;
	lstat(name, &sb);
	char *res = str_to_print(sb, name);
	printf("%s\n", res);
	mx_strdel(&res);
}

void get_contents(DIR *d){
	
	struct dirent *entry;
	
	// struct stat sb;
	// stat("..", &sb);
	entry = readdir(d);
	//while ((entry = readdir(d)) != NULL)
		display_contents(entry->d_name);
	// printf("%lld", sb.st_blocks); // - печатает  Total blocks size
}

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
	//system("leaks -q uls");
    return 0;
}
