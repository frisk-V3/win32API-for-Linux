#include <string>
#include <cstdint>
#include <vector>

// ご提示いただいた構造体
struct WIN32_FIND_DATAW {
    uint32_t     dwFileAttributes;
    uint64_t     nFileSize;
    std::wstring cFileName;

    // 属性定数の定義（Windows API互換）
    static constexpr uint32_t FILE_ATTRIBUTE_DIRECTORY = 0x00000010;
    static constexpr uint32_t FILE_ATTRIBUTE_NORMAL    = 0x00000080;

    // 便利な判定メソッド
    bool isDirectory() const {
        return (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    }
};

/**
 * データの詰め込みを簡潔にするヘルパー例
 */
WIN32_FIND_DATAW CreateFindData(const std::wstring& name, uint64_t size, bool isDir) {
    return {
        isDir ? WIN32_FIND_DATAW::FILE_ATTRIBUTE_DIRECTORY : WIN32_FIND_DATAW::FILE_ATTRIBUTE_NORMAL,
        size,
        name
    };
}

// 使用例
//void Example() {
  //  std::vector<WIN32_FIND_DATAW> results;

    // リストへの追加が直感的
 //   results.push_back({0x10, 0, L"Documents"});
   // results.push_back({0x80, 1024, L"memo.txt"});

 //   for (const auto& data : results) {
 //       if (data.isDirectory()) {
            // ディレクトリの場合の処理
  //      }
//    }
//}
