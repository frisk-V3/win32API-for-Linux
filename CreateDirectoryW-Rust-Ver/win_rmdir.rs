use std::fs;
use std::path::Path;

/// ディレクトリを削除する。中身があっても再帰的に削除を行う。
pub fn remove_directory(path: &str) -> bool {
    let path = Path::new(path);
    
    // 存在しない場合は、目的を達成している（削除の必要がない）ため true とみなす設計もあるが、
    // ここでは「削除操作の成否」を厳密に返す。
    if !path.exists() {
        return false;
    }

    // remove_dir_all は Windows において、中身があるディレクトリを
    // 下位層から順に効率よく削除する。
    fs::remove_dir_all(path).is_ok()
}
