#include <unistd.h>
#include <sys/utsname.h>
#include <fstream>
#include <string>
#include <cstring>

#define PROCESSOR_ARCHITECTURE_INTEL   0
#define PROCESSOR_ARCHITECTURE_ARM     5
#define PROCESSOR_ARCHITECTURE_AMD64   9
#define PROCESSOR_ARCHITECTURE_ARM64   12

void GetSystemInfo(SYSTEM_INFO* info) {
    if (!info) return;

    std::memset(info, 0, sizeof(SYSTEM_INFO));

    // --- 1. アーキテクチャ判定 ---
    struct utsname un;
    uname(&un);
    std::string arch = un.machine;

    if (arch == "x86_64") {
        info->wProcessorArchitecture = PROCESSOR_ARCHITECTURE_AMD64;
    } else if (arch == "i386" || arch == "i686") {
        info->wProcessorArchitecture = PROCESSOR_ARCHITECTURE_INTEL;
    } else if (arch == "aarch64") {
        info->wProcessorArchitecture = PROCESSOR_ARCHITECTURE_ARM64;
    } else if (arch.find("arm") == 0) {
        info->wProcessorArchitecture = PROCESSOR_ARCHITECTURE_ARM;
    } else {
        info->wProcessorArchitecture = PROCESSOR_ARCHITECTURE_INTEL;
    }

    // --- 2. ページサイズ ---
    info->dwPageSize = sysconf(_SC_PAGESIZE);

    // --- 3. CPU 数 ---
    info->dwNumberOfProcessors = sysconf(_SC_NPROCESSORS_ONLN);

    // --- 4. アドレス空間の最小/最大 ---
    // /proc/self/maps の最初と最後のアドレスを読む
    {
        std::ifstream maps("/proc/self/maps");
        std::string line;
        uintptr_t minAddr = (uintptr_t)-1;
        uintptr_t maxAddr = 0;

        while (std::getline(maps, line)) {
            uintptr_t start, end;
            if (sscanf(line.c_str(), "%lx-%lx", &start, &end) == 2) {
                if (start < minAddr) minAddr = start;
                if (end > maxAddr) maxAddr = end;
            }
        }

        info->lpMinimumApplicationAddress = (LPVOID)minAddr;
        info->lpMaximumApplicationAddress = (LPVOID)maxAddr;
    }

    // --- 5. AllocationGranularity ---
    info->dwAllocationGranularity = 65536; // 64KB（Windows 固定値）

    // --- 6. ProcessorLevel / Revision ---
    {
        std::ifstream cpuinfo("/proc/cpuinfo");
        std::string line;
        int model = 0, stepping = 0;

        while (std::getline(cpuinfo, line)) {
            if (line.find("model\t") != std::string::npos) {
                sscanf(line.c_str(), "model\t: %d", &model);
            }
            if (line.find("stepping") != std::string::npos) {
                sscanf(line.c_str(), "stepping\t: %d", &stepping);
            }
        }

        info->wProcessorLevel = model;
        info->wProcessorRevision = stepping;
    }

    // --- 7. ActiveProcessorMask ---
    info->dwActiveProcessorMask = (1ULL << info->dwNumberOfProcessors) - 1;
}
