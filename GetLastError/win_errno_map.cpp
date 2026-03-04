uint32_t errno_to_winerror(int e) {
    switch (e) {
        case ENOENT: return ERROR_FILE_NOT_FOUND;
        case EACCES: return ERROR_ACCESS_DENIED;
        case EEXIST: return ERROR_ALREADY_EXISTS;
        case ENOMEM: return ERROR_NOT_ENOUGH_MEMORY;
        case EINVAL: return ERROR_INVALID_PARAMETER;
        default:     return e; // 未対応はそのまま返す
    }
}
