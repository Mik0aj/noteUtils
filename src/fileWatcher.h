//
// Created by mikoaj on 03.09.22.
//

#ifndef NOTEUTILS_FILEWATCHER_H
#define NOTEUTILS_FILEWATCHER_H

#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>

static void handle_events(int fd, int *wd, int argc, char *argv[]);


#endif //NOTEUTILS_FILEWATCHER_H
