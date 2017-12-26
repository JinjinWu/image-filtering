#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "bitmap.h"


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


// TODO: Complete this function.
int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: image_filter input output [filter ...]\n");
        exit(1);
    } else if (argc > 3) {
	int fd[argc - 4][2];
    }

    int result;

    FILE *image = fopen(argv[1], "rb");
    if (image == NULL) {
	printf("in error\n");
	perror("fopen");
	exit(1);
    }

    FILE *image_out = fopen(argv[2], "wb");
    if (image_out == NULL) {
	printf("out error\n");
	perror("fopen");
	exit(1);
    }

    if (argc == 3) {
	result = fork();
	if (result > 0) {
	    ;
	} else if (result == 0) {
	    dup2(fileno(image), STDIN_FILENO);
	    dup2(fileno(image_out), STDOUT_FILENO);
	    execl("./copy", "copy", NULL);
	    perror("exec");
	    exit(1);
	} else {
	    perror("fork");
	}
    } else if (argc == 4) {
        result = fork();
        if (result > 0) {
            ;
        } else if (result == 0) {
            dup2(fileno(image), STDIN_FILENO);
            dup2(fileno(image_out), STDOUT_FILENO);
            run_command(argv[3]);
            perror("exec");
            exit(1);
        }



    }
/*
    // if applying more than 1 filter
    for (int i = 0; i < argc - 3; i++) {

	if (i != argc - 4) {
	    if (pipe(fd[i]) == -1) {
	        perror("pipe");
	        exit(1);
	    }
	}

	result = fork();

	if (result == 0) {
	    if (close(fd[i][0]) == -1) {
		perror("close");
	    }

	    // close previous unused reading pipe ends
	    for (int j = 0; j < i; j++) {
		if(close(pipe_fd[j][0]) == -1) {
                    perror("close");
                };
	    }



	    // exec the proper filter for the child
            run_command(argv[3 + i]);
            perror("exec");
            exit(1);
	} else if (result > 0) {
	    if (close(fd[i][0]) == -1) {
                perror("close");
            }
            if (close(fd[i][1]) == -1) {
                perror("close");
            }

	}




    }

    int status;

//    while (wait(&status)) > 0)
//	;

    int error = fclose(image);
    int error2 = fclose(image_out);
    if (error != 0 || error2 != 0) {
	perror("fclose");
	exit(1);
    }

*/
    printf(SUCCESS_MESSAGE);
    return 0;
}
