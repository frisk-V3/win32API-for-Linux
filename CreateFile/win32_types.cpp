enum class FileAccess : uint32_t {
    Read       = 0x80000000,
    Write      = 0x40000000,
    ReadWrite  = Read | Write,
};

enum class FileShare : uint32_t {
    None  = 0,
    Read  = 1,
    Write = 2,
};

enum class CreationDisposition : uint32_t {
    CreateNew        = 1,
    CreateAlways     = 2,
    OpenExisting     = 3,
    OpenAlways       = 4,
    TruncateExisting = 5,
};
