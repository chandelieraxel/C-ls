#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "pwd.c"

#define ANSI_COLOR_CYAN    "\x1b[96m"
#define ANSI_COLOR_RESET   "\x1b[0m"


int main() 
{
    // char path[PATH_MAX];

    // pwd(path, PATH_MAX);    
    // printf("%s\n", path);

    DIR * directory;

    directory = opendir(".");

    struct dirent *content;

    while ((content = readdir(directory)) != NULL)
    {

        struct stat fileContent;

        stat(content->d_name, &fileContent);

        printf(S_ISDIR(fileContent.st_mode) ? "d" : "-");

        // Why do we need to test the std_mod ?
        printf((fileContent.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileContent.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileContent.st_mode & S_IXUSR) ? "x" : "-");

        printf((fileContent.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileContent.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileContent.st_mode & S_IXGRP) ? "x" : "-");

        printf((fileContent.st_mode & S_IROTH) ? "r" : "-");
        printf((fileContent.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileContent.st_mode & S_IXOTH) ? "x" : "-");
        
        printf(" ");
        printf("%*hu", 3, fileContent.st_nlink);

        struct passwd *userInfos;
        userInfos = getpwuid(fileContent.st_uid);
        
        printf(" ");
        printf("%s", userInfos->pw_name);
        
        struct group *groupInfos;
        groupInfos = getgrgid(fileContent.st_gid);
        
        printf(" ");
        printf("%s", groupInfos->gr_name);
        
        printf(" ");
        printf("%*lld", 5, fileContent.st_size);

        printf(" ");

        time_t t = time(&fileContent.st_ctimespec.tv_sec);
        struct tm tm = *localtime(&t);
        printf("%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        
        printf(" ");
        if (S_ISDIR(fileContent.st_mode)) {
            printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET, content->d_name);
        } else {
        printf("%s", content->d_name);

        }

        
        printf("\n");


        // printf("%hu\n", fileContent.st_birthtimespec);
    }
    
    closedir(directory);

    return 0;
}