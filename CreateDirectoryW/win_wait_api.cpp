uint32_t WaitForSingleObject(pid_t pid, uint32_t milliseconds) {
    int status = 0;
    pid_t r = waitpid(pid, &status, 0);
    if (r < 0) return 0xFFFFFFFF; // WAIT_FAILED
    return 0; // WAIT_OBJECT_0
}
