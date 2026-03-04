# win32API for Linux（対応 API 一覧）

Linux 上で Win32 API を本気で互換実装するプロジェクト。  
以下は現在実装済みの API と対応ファイル一覧。

## ファイルシステム

| API | 言語 | ファイル |
|------|------|----------|
| CreateFile | C++ | `kernel32.cpp` |
| FindFirstFile / FindNextFile | C++ | `Win32FindApi.cpp` |
| FindFirstFile（Rust版） | Rust | `win_file_iter.rs` |
| CreateDirectoryW | C++ | `win_proc_kill.cpp` |
| CreateDirectoryW（Rust版） | Rust | `win_meta_attr.rs` |

## プロセス管理

| API | 言語 | ファイル |
|------|------|----------|
| CreateProcessW（Rust版） | Rust | `win_proc_wait.rs` |
| TerminateProcess（相当） | C++ | `win_proc_kill.cpp` |

## スレッド

| API | 言語 | ファイル |
|------|------|----------|
| CreateThread | C++ | `win_handle_close.cpp` |
| CreateThread（Rust版） | Rust | `win_thread_join.rs` |
| WaitForSingleObject（Thread版） | Rust | `win_thread_join.rs` |

## 同期オブジェクト

| API | 言語 | ファイル |
|------|------|----------|
| Mutex | C++ | `win_mutex_close.cpp` |
| Event | C++ | `win_event_reset.cpp` |
| Semaphore | C++ | `win_sem_rel.cpp` |

## 時間

| API | 言語 | ファイル |
|------|------|----------|
| Sleep（Rust版） | Rust | `win_perf_inst.rs` |

## エラー処理

| API | 言語 | ファイル |
|------|------|----------|
| GetLastError | C++ | `win_file_open.cpp` |
| GetLastError（Rust版） | Rust | `win_errno_map.rs` |

## 環境変数

| API | 言語 | ファイル |
|------|------|----------|
| GetEnvironmentVariableW | C++ | `win_env_get.cpp` |
| SetEnvironmentVariableW（Rust版） | Rust | `win_env_set.rs` |

## システム情報

| API | 言語 | ファイル |
|------|------|----------|
| GetSystemInfo | C++ | `win_sys_impl.cpp` |
