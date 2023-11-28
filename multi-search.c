#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_STRINGS 1000

int linearSearch(char *strings[], int start, int end, const char *key) {
    for (int i = start; i < end; i++) {
        if (strcmp(strings[i], key) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <FILE NAME> <KEY> <NUMBER OF PROCESSES>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *fileName = argv[1];
    const char *key = argv[2];
    int numProcesses = atoi(argv[3]);

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char *strings[MAX_STRINGS];
    int stringCount = 0;

    char buffer[100];
    while (fscanf(file, "%s", buffer) != EOF && stringCount < MAX_STRINGS) {
        strings[stringCount] = strdup(buffer);
        stringCount++;
    }

    fclose(file);

    int segmentSize = stringCount / numProcesses;

    for (int i = 0; i < numProcesses; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            int start = i * segmentSize;
            int end = (i == numProcesses - 1) ? stringCount : (i + 1) * segmentSize;
            int result = linearSearch(strings, start, end, key);

            exit(result);
        }
    }

    int found = 0;

    for (int i = 0; i < numProcesses; i++) {
        int exitStatus;
        wait(&exitStatus);

        if (WIFEXITED(exitStatus) && WEXITSTATUS(exitStatus) == 1) {
            continue;
        } else if (WIFEXITED(exitStatus) && WEXITSTATUS(exitStatus) == 0) {
            found = 1;
            break;
        } else {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }

    if (found) {
        printf("String found!\n");
    } else {
        printf("String not found!\n");
    }

    for (int i = 0; i < stringCount; i++) {
        free(strings[i]);
    }

    return 0;
}
