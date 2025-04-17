#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include "minishell.h"

void takes_cmds(t_cmd *cmd_list) {
    int cmd_index = 0;
    while (cmd_list) {
        printf("Command # %d:\n", cmd_index);
        t_file *file = cmd_list->file;
        int i = 0;

        while (file) {
            if (file->infile)
                printf("  Infile:  %s\n", file->infile);
            if (file->outfile)
                printf("  Outfile: %s %s\n",
                       file->append ? "(append)" : "(truncate)",
                       file->outfile);
            printf("  Append: %d\n", file->append);
            file = file->next;
        }

        i = 0;
        while (cmd_list->args && cmd_list->args[i]) {
            printf("  Arg[%d]: %s\n", i, cmd_list->args[i]);
            i++;
        }
        cmd_list = cmd_list->next;
        cmd_index++;
    }
}

char **takepaths(t_env *env_lnk) {
    char **path = NULL;
    char *take = NULL;

    while (env_lnk) {
        if (ft_strncmp(env_lnk->key, "PATH", 4) == 0) {
            take = env_lnk->value;
            break;
        }
        env_lnk = env_lnk->next;
    }

    if (!take)
        return NULL;

    path = ft_split(take, ':');
    for (int i = 0; path[i]; i++) {
        char *tmp = path[i];
        path[i] = ft_strjoin(tmp, "/");
        free(tmp);
    }
    return path;
}

int openoutfile(t_file* current) {
    int fd = 0;
    while (current) {
        if (!current->outfile)
            return -5;

        if (current->append)
            fd = open(current->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
        else
            fd = open(current->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);

        if (fd == -1) {
            perror("Failed to open output file");
            return 0;
        }

        if (current->next)
            close(fd);

        current = current->next;
    }
    return fd;
}

int checkinfile(t_file *current) {
    int fd = 0;
    while (current) {
        if (!current->infile)
            return -5;

        fd = open(current->infile, O_RDONLY);
        if (fd == -1) {
            perror("Failed to open input file");
            return 0;
        }

        if (current->next)
            close(fd);

        current = current->next;
    }
    return fd;
}

void pipecheck(int *pipefd) {
    if (pipe(pipefd) == -1) {
        perror("pipex");
        exit(EXIT_FAILURE);
    }
}

void forkfaild(pid_t pid, int *pipefd) {
    if (pid == -1) {
        perror("pipex");
        close(pipefd[0]);
        close(pipefd[1]);
        exit(EXIT_FAILURE);
    }
}

char *pick(char **path, char *cmd) {
    if (ft_strchr(cmd, '/')) {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);
        return NULL;
    }

    for (int i = 0; path && path[i]; i++) {
        char *realpath = ft_strjoin(path[i], cmd);
        if (access(realpath, X_OK) == 0)
            return realpath;
        free(realpath);
    }

    return NULL;
}

int first_command(int infile, char **paths, int *pipefd, char **arg) {
    if (dup2(infile, STDIN_FILENO) == -1 ||
        dup2(pipefd[1], STDOUT_FILENO) == -1) {
        perror("pipex");
        exit(1);
    }
    close(infile);
    close(pipefd[0]);
    close(pipefd[1]);

    char *path = pick(paths, arg[0]);
    if (!path)
        exit(1);

    execve(path, arg, NULL);
    perror("execve");
    exit(1);
}

int executing(int prev_pipe, char **cmd, char **paths, int outfile) {
    if (dup2(prev_pipe, STDIN_FILENO) == -1 ||
        dup2(outfile, STDOUT_FILENO) == -1) {
        perror("pipex");
        return 0;
    }
    close(prev_pipe);
    close(outfile);

    char *path = pick(paths, cmd[0]);
    if (!path)
        exit(1);

    execve(path, cmd, NULL);
    perror("execve");
    exit(1);
}

void handelprevpipe(int *pipefd, int *prev_pipe) {
    close(pipefd[1]);
    if (*prev_pipe != -1)
        close(*prev_pipe);
    *prev_pipe = pipefd[0];
}

t_cmd *loop_childs(int *prev_pipe, char **paths, t_cmd *args, int infd) {
    t_cmd *curr = args;
    int i = 0;

    while (curr->next) {
        int pipfd[2];
        pipecheck(pipfd);

        pid_t pid = fork();
        forkfaild(pid, pipfd);

        if (pid == 0) {
            if (i == 0)
                first_command(infd, paths, pipfd, curr->args);
            else
                executing(*prev_pipe, curr->args, paths, pipfd[1]);
        }

        handelprevpipe(pipfd, prev_pipe);
        curr = curr->next;
        i++;
    }
    return curr;
}

int last_child(int prev_pipe, char **cmd, char **paths, int outf) {
    pid_t pid = fork();
    if (pid == 0) {
        if (dup2(prev_pipe, STDIN_FILENO) == -1 ||
            dup2(outf, STDOUT_FILENO) == -1) {
            perror("pipex");
            exit(1);
        }
        close(prev_pipe);
        close(outf);

        char *path = pick(paths, cmd[0]);
        if (!path)
            exit(1);

        execve(path, cmd, NULL);
        perror("execve");
        exit(1);
    }
    return 0;
}

void execution(t_cmd *full, t_env *env)
{
    char **paths = takepaths(env);
    int prev_pipe = -1;

    int infile = checkinfile(full->file);
    int outfile = openoutfile(full->file);

    if (infile == -5)
        infile = STDIN_FILENO;
    if (outfile == -5)
        outfile = STDOUT_FILENO;

    t_cmd *last = loop_childs(&prev_pipe, paths, full, infile);
    last_child(prev_pipe, last->args, paths, outfile);

    while (wait(NULL) > 0);

    // Free resources here (paths, etc)
}
