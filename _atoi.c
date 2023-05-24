#include <signal.h>

typedef struct config {
    /* Members of config struct */
    // ...
} config;

config *config_init(config *build);
void handle_sigint(int signum);
void shell(config *build);
char *_getenv(const char *name, char **env);
void generateLinkedList(char **env);

int main(int ac, char **av)
{
    config build = {0};
    signal(SIGINT, handle_sigint);
    config_init(&build);
    build.shell_name = av[0];
    shell(&build);
    return 0;
}

config *config_init(config *build)
{
    build->env = generateLinkedList(environ);
    // Initialize other members
    return build;
}
