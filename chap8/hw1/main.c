#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

/* Return the user name for a user ID, or "unknown" if it is not found. */
static const char *user_name(uid_t uid)
{
    struct passwd *pw = getpwuid(uid);
    return (pw != NULL) ? pw->pw_name : "unknown";
}

/* Return the group name for a group ID, or "unknown" if it is not found. */
static const char *group_name(gid_t gid)
{
    struct group *gr = getgrgid(gid);
    return (gr != NULL) ? gr->gr_name : "unknown";
}

/* -e [name]: print one environment variable, or all of them if no name is given. */
static void print_env(const char *name)
{
    char **ptr;
    char *value;

    if (name == NULL) {
        for (ptr = environ; *ptr != NULL; ptr++)
            printf("%s\n", *ptr);
        return;
    }

    value = getenv(name);
    if (value != NULL)
        printf("%s = %s\n", name, value);
    else
        printf("%s = (not set)\n", name);
}

/* -u: print the real and effective user IDs. */
static void print_uid(void)
{
    printf("My Realistic User ID : %d(%s)\n", (int)getuid(), user_name(getuid()));
    printf("My Valid User ID : %d(%s)\n", (int)geteuid(), user_name(geteuid()));
}

/* -g: print the real and effective group IDs. */
static void print_gid(void)
{
    printf("My Realistic Group ID : %d(%s)\n", (int)getgid(), group_name(getgid()));
    printf("My Valid Group ID : %d(%s)\n", (int)getegid(), group_name(getegid()));
}

/* Print how to use this program. */
static void usage(const char *prog)
{
    fprintf(stderr, "Usage: %s [-e [name]] [-u] [-g] [-i] [-p]\n", prog);
}

int main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        usage(argv[0]);
        exit(1);
    }

    for (i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-e", 2) == 0) {
            if (argv[i][2] != '\0')                         /* form: -ePATH */
                print_env(&argv[i][2]);
            else if (i + 1 < argc && argv[i + 1][0] != '-') /* form: -e PATH */
                print_env(argv[++i]);
            else                                            /* form: -e */
                print_env(NULL);
        } else if (strcmp(argv[i], "-u") == 0) {
            print_uid();
        } else if (strcmp(argv[i], "-g") == 0) {
            print_gid();
        } else if (strcmp(argv[i], "-i") == 0) {
            printf("my process number : [%d]\n", (int)getpid());
        } else if (strcmp(argv[i], "-p") == 0) {
            printf("my parent's process number : [%d]\n", (int)getppid());
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            usage(argv[0]);
            exit(1);
        }
    }

    exit(0);
}
