bool CreateProcessW(
    const std::wstring& appName,
    const std::wstring& cmdLine,
    void* lpProcessAttributes,
    void* lpThreadAttributes,
    bool inheritHandles,
    uint32_t creationFlags,
    void* lpEnvironment,
    const std::wstring& currentDir,
    STARTUPINFOW* startupInfo,
    PROCESS_INFORMATION* procInfo
) {
    pid_t pid = fork();
    if (pid < 0) {
        return false;
    }

    if (pid == 0) {
        // 子プロセス
        if (!currentDir.empty()) {
            std::string utf8dir = to_utf8(currentDir);
            chdir(utf8dir.c_str());
        }

        std::string utf8cmd = to_utf8(cmdLine);

        // execvp 用に引数を分解
        std::vector<char*> args;
        std::istringstream iss(utf8cmd);
        std::string token;
        while (iss >> token) {
            char* arg = strdup(token.c_str());
            args.push_back(arg);
        }
        args.push_back(nullptr);

        execvp(args[0], args.data());
        exit(1);
    }

    // 親プロセス
    procInfo->hProcess = pid;
    procInfo->hThread = pid;
    procInfo->dwProcessId = pid;
    procInfo->dwThreadId = pid;

    return true;
}
