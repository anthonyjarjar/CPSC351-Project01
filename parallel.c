#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void fetchWeather(int locationNumber) {
    char filename[20];
    sprintf(filename, "file%d.json", locationNumber);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("Child %d: PID %d, Parent PID %d\n", locationNumber, getpid(), getppid());

        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        open("/dev/null", O_WRONLY);  
        open("/dev/null", O_WRONLY);  

        execlp("/usr/bin/curl", "curl", "-o", filename,
               "https://api.open-meteo.com/v1/forecast?latitude=52.520000&longitude=13.410000&current_weather=True", NULL);

        perror("execlp");
        exit(EXIT_FAILURE);
    }
}

int main() {
    FILE *file = fopen("locations.txt", "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int locationNumber = 1;
    while (fscanf(file, "%*f %*f") != EOF) {
        fetchWeather(locationNumber);
        locationNumber++;
    }

    fclose(file);

    for (int i = 0; i < locationNumber - 1; i++) {
        wait(NULL);
    }

    return 0;
}
