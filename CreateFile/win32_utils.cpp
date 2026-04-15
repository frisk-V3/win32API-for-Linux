#include <fcntl.h>

int to_posix_flags(FileAccess access, CreationDisposition disp) {
    int flags = 0;

    // 1. アクセス権の決定
    // POSIXでは O_RDONLY (0), O_WRONLY (1), O_RDWR (2) は独立した値（マスク）
    // であることが多いため、else if で排他的に指定するのが正しい。
    switch (access) {
        case FileAccess::Read:      flags = O_RDONLY; break;
        case FileAccess::Write:     flags = O_WRONLY; break;
        case FileAccess::ReadWrite: flags = O_RDWR;   break;
        default:                    flags = O_RDWR;   break; // 安全策
    }

    // 2. 作成モードの決定
    switch (disp) {
        case CreationDisposition::CreateNew:
            // ファイルが存在すればエラー (Windows: CREATE_NEW)
            flags |= (O_CREAT | O_EXCL);
            break;
        case CreationDisposition::CreateAlways:
            // 既存なら上書き、なければ作成 (Windows: CREATE_ALWAYS)
            flags |= (O_CREAT | O_TRUNC);
            break;
        case CreationDisposition::OpenExisting:
            // 既存ファイルを開く。なければエラー (Windows: OPEN_EXISTING)
            // 何も追加しない
            break;
        case CreationDisposition::OpenAlways:
            // 既存なら開く、なければ作成 (Windows: OPEN_ALWAYS)
            flags |= O_CREAT;
            break;
        case CreationDisposition::TruncateExisting:
            // 既存を開いてサイズ0にする。なければエラー (Windows: TRUNCATE_EXISTING)
            // POSIXでは O_TRUNC 単体での動作は「既存があれば切り詰め」
            flags |= O_TRUNC;
            break;
    }

    return flags;
}
