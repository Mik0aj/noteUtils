
#include <iostream>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <map>

template<typename Func>
class fileWatcher {
    int fileDescriptor;
    int *watchDescriptor;
    /* Some systems cannot read integer variables if they are not
       properly aligned. On other systems, incorrect alignment may
       decrease performance. Hence, the buffer used for reading from
       the inotify file descriptor should have the same alignment as
       struct inotify_event. */
    char buf;
    const struct inotify_event *event;
    int i;
    int poll_num;
    ssize_t len;
    nfds_t nfds;
    struct pollfd fds[2];
    std::map<int, Func> fileDescriptorFunctionMap;

public:
    fileWatcher(const std::vector<std::string> &paths,std::map<int, Func> map) {
        fileDescriptor = inotify_init1(IN_NONBLOCK);
        if (fileDescriptor == -1) {
            throw "inotify_init1 error";
        }
        fileDescriptorFunctionMap=map;
        updatePaths(paths);
    }

    void handle_events() {
        char bufArr[4096] __attribute__ ((aligned(__alignof__(struct inotify_event))));
        /* Loop while events can be read from inotify file descriptor. */
        for (;;) {
            /* Read some events. */
            len = read(fileDescriptor, bufArr, sizeof(bufArr));
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
            for (char *ptr = bufArr; ptr < bufArr + len; ptr += sizeof(struct inotify_event) + event->len) {
                event = (const struct inotify_event *) ptr;
                for (const auto & [mask, function]: fileDescriptorFunctionMap) {
                    if (event->mask & mask) function();
                }
            }
        }
    }

    void updatePaths(const std::vector<std::string> &paths) {
        watchDescriptor = static_cast<int *>(calloc(paths.size(), sizeof(int)));
        if (watchDescriptor == nullptr) {
            throw "calloc error";
        }
        for (i = 0; i < paths.size(); i++) {
            watchDescriptor[i] = inotify_add_watch(fileDescriptor, (const char *) paths[i].c_str(), IN_OPEN | IN_CLOSE);
            if (watchDescriptor[i] == -1) {
                throw "Cannot watch " + paths.at(i);
            }
        }
    }

    void loop() {
        std::cout << "Press ENTER key to terminate.\n";
        nfds = 2;


        fds[0].fd = STDIN_FILENO;       /* Console input */
        fds[0].events = POLLIN;

        fds[1].fd = fileDescriptor;     /* Inotify input */
        fds[1].events = POLLIN;
        std::cout << "Listening for events.\n";

        while (1) {
            poll_num = poll(fds, nfds, -1);
            if (poll_num == -1) {
                if (errno == EINTR)
                    continue;
                throw "poll";
            }
            if (poll_num > 0) {
                if (fds[0].revents & POLLIN) {
                    /* Console input is available. Empty stdin and quit. */
                    while (read(STDIN_FILENO, &buf, 1) > 0 && buf != '\n')
                        continue;
                    break;
                }
                if (fds[1].revents & POLLIN) {
                    /* Inotify events are available. */
                    handle_events();
                }
            }
        }
        std::cout << "Listening for events stopped.\n";
    }

    ~fileWatcher() {
        close(fileDescriptor);
        free(watchDescriptor);
    }
};