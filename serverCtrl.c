#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void create_process()
{
    int exit_code;
    if(fork() == 0)
    {
        int ret = execl("./payServer","date",0,0);
        printf("start server...");
	if(ret < 0) printf("failed");
	else printf("ok");
	printf("\n");
    }
    else
    {
        wait(&exit_code);
        if(WIFEXITED(exit_code))
        {
            /* Program terminated with exit */
            /* If you want, you could decode exit code here using
               WEXITSTATUS and you can start program again.
            */
            return;
        }
        else
        {
                /* Program didn't terminated with exit, restart */
            create_process();
        }

    }
}

int main()
{
    create_process();
    return 0;
}


