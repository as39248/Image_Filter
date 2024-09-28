#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "bitmap.h"
#include <sys/stat.h>
#include <fcntl.h>


#define ERROR_MESSAGE "Warning: one or more filter had an error, so the output image may not be correct.\n"
#define SUCCESS_MESSAGE "Image transformed successfully!\n"


/*
 * Check whether the given command is a valid image filter, and if so,
 * run the process.
 *
 * We've given you this function to illustrate the expected command-line
 * arguments for image_filter. No further error-checking is required for
 * the child processes.
 */
void run_command(const char *cmd) {
    if (strcmp(cmd, "copy") == 0 || strcmp(cmd, "./copy") == 0 ||
        strcmp(cmd, "greyscale") == 0 || strcmp(cmd, "./greyscale") == 0 ||
        strcmp(cmd, "gaussian_blur") == 0 || strcmp(cmd, "./gaussian_blur") == 0 ||
        strcmp(cmd, "edge_detection") == 0 || strcmp(cmd, "./edge_detection") == 0) {
        execl(cmd, cmd, NULL);
    } else if (strncmp(cmd, "scale", 5) == 0) {
        // Note: the numeric argument starts at cmd[6]
        execl("scale", "scale", cmd + 6, NULL);
    } else if (strncmp(cmd, "./scale", 7) == 0) {
        // Note: the numeric argument starts at cmd[8]
        execl("./scale", "./scale", cmd + 8, NULL);
    } else {
        fprintf(stderr, "Invalid command '%s'\n", cmd);
        exit(1);
    }
}

void piping(int counter, int num_commands, int *fd, int r, char **argv ){


            if(r > 0) {
                if((dup2(fd[1], fileno(stdout))) == -1) {
                    perror("dup2");
                    exit(1);
                }

                // close  read
                if ((close(fd[0])) == -1) {
                    perror("close");
                }

                // close  write
                if ((close(fd[1])) == -1) {
                    perror("close");
                }
                run_command(argv[counter]);
            }

            else if (r == 0){

                // reset stdin
                if((dup2(fd[0], fileno(stdin))) == -1) {
                    perror("dup2");
                    exit(1);
                }

                // close  write
                if ((close(fd[1])) == -1) {
                    perror("close");
                }
        
                // close  read
                if ((close(fd[0])) == -1) {
                    perror("close");
                }
                counter++;
                if(counter < num_commands){
                    r = fork();
                    piping(counter, num_commands, fd, r, argv);
                }

                
            }

            else{
                perror("fork");
                exit(1);
            }
        
}


// TODO: Complete this function.
int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: image_filter input output [filter ...]\n");
        exit(1);
    }
    
    else if (argc == 3){

        int inputfd = open(argv[1], O_RDONLY);

        //reset stdin
        if((dup2(inputfd, fileno(stdin))) == -1) {
            perror("dup2");
            exit(1);
        }
        
        int outputfd = open(argv[2], O_WRONLY | O_CREAT);
        // reset stdout
        if((dup2(outputfd, fileno(stdout))) == -1) {
            perror("dup2");
            exit(1);
        }

        //close input fd
        if ((close(inputfd)) == -1) {
            perror("close");
        }

        //close output fd
        if ((close(outputfd)) == -1) {
            perror("close");
        }
        run_command("./copy");
    }


    else if (argc > 3){

        int inputfd = open(argv[1], O_RDONLY);

        //reset stdin
        if((dup2(inputfd, fileno(stdin))) == -1) {
            perror("dup2");
            exit(1);
        }

        int fd[2], r;
        r = fork();

        if (pipe(fd) == -1) {
            perror("pipe");
            exit(1);
        }

        piping(3, argc, fd, r, argv);

        int outputfd = open(argv[2], O_WRONLY | O_CREAT);
        // reset stdout
        if((dup2(outputfd, fileno(stdout))) == -1) {
            perror("dup2");
            exit(1);
        }
        run_command(argv[argc]);

    }








/*


    int fd[2], r;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    
    
    
    //parent
    if((r = fork()) > 0) {
        

        int inputfd = open(argv[1], O_RDONLY);

        //reset stdin
        if((dup2(inputfd, fileno(stdin))) == -1) {
            perror("dup2");
            exit(1);
        }

        //reset stdout
        if((dup2(fd[1], fileno(stdout))) == -1) {
            perror("dup2");
            exit(1);
        }

        // close  read
        if ((close(fd[0])) == -1) {
            perror("close");
        }

        // close  write
        if ((close(fd[1])) == -1) {
            perror("close");
        }
        
        //close input fd
        if ((close(inputfd)) == -1) {
            perror("close");
        }

        run_command(argv[3]);
    }

    //child
    else if (r == 0){

        int outputfd = open(argv[2], O_WRONLY | O_CREAT);

        // reset stdin
        if((dup2(fd[0], fileno(stdin))) == -1) {
            perror("dup2");
            exit(1);
        }

        // reset stdout
        if((dup2(outputfd, fileno(stdout))) == -1) {
            perror("dup2");
            exit(1);
        }

        // close  write
        if ((close(fd[1])) == -1) {
            perror("close");
        }

        // close  read
        if ((close(fd[0])) == -1) {
            perror("close");
        }

        //close output fd
        if ((close(outputfd)) == -1) {
            perror("close");
        }

        run_command(argv[4]);

    }

    else{
        perror("fork");
        exit(1);
    }

*/



    printf(SUCCESS_MESSAGE);
    return 0;
}
