#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

/* Print the user IDs and group IDs of this process. */
int main()
{
    /* real user ID and effective user ID */
    printf("My Realistic User ID: %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
    printf("My Valid User ID: %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);

    /* real group ID and effective group ID */
    printf("My Realistic Group ID: %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
    printf("My Valid Group ID: %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);

    return 0;
}
