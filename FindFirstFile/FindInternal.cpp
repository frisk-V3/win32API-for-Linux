struct FIND_HANDLE__ {
    DIR* dir;
    std::wstring pattern;
    std::wstring directory;
};
using FIND_HANDLE = FIND_HANDLE__*;
