#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

/* Option flags */
int opt_i = 0;
int opt_p = 0;
int opt_Q = 0;

/* Function declarations */
char type(mode_t mode);
char *perm(mode_t mode);
void printStat(char *pathname, char *file, struct stat *st);

/* Main function: Custom ls program supporting -i, -p, -Q options */
int main(int argc, char **argv)
{
    DIR *dp;
    char *dir = ".";
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    int opt;

    /* Parse command-line options using getopt() */
    while ((opt = getopt(argc, argv, "ipQ")) != -1) {
        switch (opt) {
            case 'i': opt_i = 1; break;
            case 'p': opt_p = 1; break;
            case 'Q': opt_Q = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-i] [-p] [-Q] [dir]\n", argv[0]);
                exit(1);
        }
    }

    /* Set directory path if specified after options */
    if (optind < argc) {
        dir = argv[optind];
    }

    /* Open target directory using opendir() */
    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    /* Iterate through directory entries */
    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st);
    }

    closedir(dp);
    exit(0);
}

/* Prints file status according to selected options */
void printStat(char *pathname, char *file, struct stat *st)
{
    printf("%5ld ", st->st_blocks);

    /* Option -i: Print inode number before permissions */
    if (opt_i) {
        printf("%lu ", st->st_ino);
    }

    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);

    /* Format filename according to options */
    char formatted_name[BUFSIZ];
    strcpy(formatted_name, file);

    /* Option -p: Append '/' if it is a directory */
    if (opt_p && S_ISDIR(st->st_mode)) {
        strcat(formatted_name, "/");
    }

    /* Option -Q: Quote the filename */
    if (opt_Q) {
        printf("\"%s\"\n", formatted_name);
    } else {
        printf("%s\n", formatted_name);
    }
}

/* Returns character corresponding to file type */
char type(mode_t mode)
{
    if (S_ISREG(mode))  return('-');
    if (S_ISDIR(mode))  return('d');
    if (S_ISCHR(mode))  return('c');
    if (S_ISBLK(mode))  return('b');
    if (S_ISLNK(mode))  return('l');
    if (S_ISFIFO(mode)) return('p');
    if (S_ISSOCK(mode)) return('s');
    return('?');
}

/* Returns string representing access permissions */
char *perm(mode_t mode)
{
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }
    return perms;
}
