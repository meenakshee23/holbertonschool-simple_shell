#define _GNU_SOURCE
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

extern char **environ;

char *find_command(char *command)
{
    char *path_env = getenv("PATH");
    char *path_copy, *dir;
    char *full_path = malloc(1024);

    if (!path_env || !full_path)
        return NULL;

    if (strchr(command, '/'))
    {
        if (access(command, X_OK) == 0)
            return command;
        free(full_path);
        return NULL;
    }

    path_copy = strdup(path_env);
    if (!path_copy)
    {
        free(full_path);
        return NULL;
    }

    dir = strtok(path_copy, ":");
    while (dir)
    {
        snprintf(full_path, 1024, "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    free(full_path);
    return NULL;
}

/**
 * main - simple shell
 * Return: 0 on success
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;
    int interactive = isatty(STDIN_FILENO);
    int argc;
    char *argv[64];
    char *token;
    char *cmd_path;
    int i;

    while (1)
    {
        if (interactive)
            printf("simpleshell$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (interactive)
                printf("\n");
            break;
        }

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        if (line[0] == '\0')
            continue;

        argc = 0;
        token = strtok(line, " ");
        while (token != NULL && argc < 63)
        {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        if (argv[0] == NULL)
            continue;

        if (strcmp(argv[0], "exit") == 0)
        {
            free(line);
            exit(0);
        }

        if (strcmp(argv[0], "env") == 0)
        {
            for (i = 0; environ[i]; i++)
                printf("%s\n", environ[i]);
            continue;
        }

        cmd_path = find_command(argv[0]);
        if (!cmd_path)
        {
            fprintf(stderr, "%s: command not found\n", argv[0]);
            continue;
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free(line);
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            execve(cmd_path, argv, environ);
            perror("simpleshell");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return (0);
}
