#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef struct {
    // Add necessary members here
} config;

void handle_sigint(int sig) {
    // Handle SIGINT signal
}

void shell(config *build) {
    // Implement shell logic here
}

config *config_init(config *build) {
    build->env = generateLinkedList(environ);
    build->env_list = NULL;
    build->args = NULL;
    build->buffer = NULL;
    build->path = _getenv("PATH", environ);
    build->full_path = NULL;
    build->count_line = 0;
    build->shell_name = NULL;
    build->error_status = 0;
    return build;
}

int main(int ac, char **av) {
    config build;
    signal(SIGINT, handle_sigint);
    config_init(&build);
    build.shell_name = av[0];
    shell(&build);
    return 0;
}
