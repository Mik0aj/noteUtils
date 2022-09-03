//
// Created by mikoaj on 03.09.22.
//

#include "fileWatcher.h"


/* Read all available inotify events from the file descriptor 'fd'.
   wd is the table of watch descriptors for the directories in argv.
   argc is the length of wd and argv.
   argv is the list of watched directories.
   Entry 0 of wd and argv is unused. */

static void handle_events(int fd, int *wd, int argc, char *argv[]) {
    /* Some systems cannot read integer variables if they are not
       properly aligned. On other systems, incorrect alignment may
       decrease performance. Hence, the buffer used for reading from
       the inotify file descriptor should have the same alignment as
       struct inotify_event. */

    char buf[4096]
            __attribute__ ((aligned(__alignof__(struct inotify_event))));
    const struct inotify_event *event;
    ssize_t len;

    /* Loop while events can be read from inotify file descriptor. */

    for (;;) {

        /* Read some events. */

        len = read(fd, buf, sizeof(buf));
        if (len == -1 && errno != EAGAIN) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        /* If the nonblocking read() found no events to read, then
           it returns -1 with errno set to EAGAIN. In that case,
           we exit the loop. */

        if (len <= 0)
            break;

        /* Loop over all events in the buffer. */

        for (char *ptr = buf; ptr < buf + len;
             ptr += sizeof(struct inotify_event) + event->len) {

            event = (const struct inotify_event *) ptr;

            /* Print event type. */

            if (event->mask & IN_OPEN)
                printf("IN_OPEN: ");
            if (event->mask & IN_CLOSE_NOWRITE)
                printf("IN_CLOSE_NOWRITE: ");
            if (event->mask & IN_CLOSE_WRITE)
                printf("IN_CLOSE_WRITE: ");

            /* Print the name of the watched directory. */

            for (int i = 1; i < argc; ++i) {
                if (wd[i] == event->wd) {
                    printf("%s/", argv[i]);
                    break;
                }
            }

            /* Print the name of the file. */

            if (event->len)
                printf("%s", event->name);

            /* Print type of filesystem object. */

            if (event->mask & IN_ISDIR)
                printf(" [directory]\n");
            else
                printf(" [file]\n");
        }
    }
}
