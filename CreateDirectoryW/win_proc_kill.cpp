bool TerminateProcess(pid_t pid, int exitCode) {
    return kill(pid, SIGKILL) == 0;
}
