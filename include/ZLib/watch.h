#ifndef __ZLIB__WATCH_H__
    #define __ZLIB__WATCH_H__
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/ptrace.h>
    #include <signal.h>
    #include <iostream>
    #include <cstring>
    #include <ctime>
    #include <cstdlib>
    #include <fcntl.h>
    #include <thread>
    #include <chrono>

    namespace __ZLIB_INTERNAL__ {
        inline static void watchdogImpl(unsigned long intervalSendMs, unsigned long intervalKillMs){
            int pipefd[2];

            if (pipe(pipefd) == -1){
                perror("pipe");
                exit(1);
            }

            int parent_pid = getpid(), debugger_pid = 0;
            if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) debugger_pid = getppid();

            pid_t pid = fork();
            if (pid < 0){
                perror("fork");
                exit(1);
            }

            if (pid == 0){

                close(pipefd[1]);

                int flags = fcntl(pipefd[0], F_GETFL, 0);
                fcntl(pipefd[0], F_SETFL, flags | O_NONBLOCK);

                using clock = std::chrono::steady_clock;
                auto last_ping = clock::now();

                char buffer[1];
                while (true){
                    ssize_t count = read(pipefd[0], buffer, 1);
                    if (count > 0){

                        last_ping = clock::now();
                        usleep(1000);
                    }

                    auto now = clock::now();
                    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_ping).count();
                    if (elapsed > (long)intervalKillMs){
                        std::cerr << "Watchdog timeout. Killing parent PID " << parent_pid; if (debugger_pid) std::cerr << " and debugger PID " << debugger_pid << "...\n"; else std::cerr << "...\n";
                        if (!kill(parent_pid, 0)) kill(parent_pid, SIGHUP);
                        if (!kill(debugger_pid, 0)) kill(debugger_pid, SIGHUP);
                        usleep(1000000);
                        if (!kill(parent_pid, 0)) kill(parent_pid, SIGKILL);
                        if (!kill(debugger_pid, 0)) kill(debugger_pid, SIGKILL);
                        break;
                    }
                    usleep(1000);
                }

                close(pipefd[0]);
                exit(0);
            }

            close(pipefd[0]);

            char ping = '\0';
            while (true){
                ssize_t written = write(pipefd[1], &ping, 1);
                if (written == -1){
                    perror("write()");
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(intervalSendMs));
            }

            close(pipefd[1]);
        }
    }

    inline static void watchdog(unsigned long intervalSendMs, unsigned long intervalKillMs){
        std::thread wdThread(__ZLIB_INTERNAL__::watchdogImpl, intervalSendMs, intervalKillMs);
        wdThread.detach();
    }

#endif // ____ZLIB___WATCH_H____
