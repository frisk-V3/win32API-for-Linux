package;

@:include("Handle.h") // ヘッダーファイル名を指定（実際のファイル名に合わせてください）
@:native("HandleKind")
@:enum
extern abstract HandleKind(Int) {
    @:native("HandleKind::Process") var Process;
    @:native("HandleKind::Thread") var Thread;
    @:native("HandleKind::Event") var Event;
    @:native("HandleKind::Mutex") var Mutex;
    @:native("HandleKind::Semaphore") var Semaphore;
}

@:include("Handle.h")
@:native("HandleEntry")
@:structAccess // 構造体としてスタック上で扱うための指定
extern class HandleEntry {
    @:native("kind") var kind:HandleKind;
    @:native("object") var object:cpp.Pointer<Void>;
    
    // C++側でデフォルトコンストラクタが必要な場合
    @:native("HandleEntry")
    static function create():HandleEntry;
}
