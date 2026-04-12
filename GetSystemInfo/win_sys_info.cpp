#include <cstdint>
#include <type_traits>

// Windows API互換の型定義（Windows.hを含まない場合用）
using WORD = uint16_t;
using DWORD = uint32_t;
using LPVOID = void*;
using DWORD_PTR = uintptr_t;

struct SYSTEM_INFO {
    // アーキテクチャ定数の定義
    enum ProcessorArch : WORD {
        Arch_AMD64   = 9,
        Arch_ARM     = 5,
        Arch_ARM64   = 12,
        Arch_IA64    = 6,
        Arch_Intel   = 0,
        Arch_Unknown = 0xFFFF
    };

    union {
        DWORD dwOemId;
        struct {
            WORD wProcessorArchitecture;
            WORD wReserved;
        };
    };
    DWORD     dwPageSize;
    LPVOID    lpMinimumApplicationAddress;
    LPVOID    lpMaximumApplicationAddress;
    DWORD_PTR dwActiveProcessorMask;
    DWORD     dwNumberOfProcessors;
    DWORD     dwProcessorType;
    DWORD     dwAllocationGranularity;
    WORD      wProcessorLevel;
    WORD      wProcessorRevision;

    // ヘルパーメソッド: アーキテクチャを列挙型で安全に取得
    ProcessorArch GetArchitecture() const {
        return static_cast<ProcessorArch>(wProcessorArchitecture);
    }

    // デフォルト初期化（ゼロ埋め）を保証
    SYSTEM_INFO() : dwOemId(0), dwPageSize(0), lpMinimumApplicationAddress(nullptr), 
                    lpMaximumApplicationAddress(nullptr), dwActiveProcessorMask(0), 
                    dwNumberOfProcessors(0), dwProcessorType(0), dwAllocationGranularity(0), 
                    wProcessorLevel(0), wProcessorRevision(0) {}
};

// バイナリレイアウトが標準のSYSTEM_INFOと一致するかチェック
static_assert(sizeof(SYSTEM_INFO) >= 36, "Size mismatch");
static_assert(std::is_standard_layout<SYSTEM_INFO>::value, "Must be standard layout");
