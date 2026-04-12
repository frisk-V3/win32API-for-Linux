package VirtualAlloc;

import cpp.Pointer;

// 型定義の精度を向上
typedef LPVOID  = Pointer<Void>;
typedef SIZE_T  = cpp.SizeT;  // 64bit環境に対応
typedef DWORD   = cpp.UInt32; // WindowsのDWORDは32bit無符号
typedef BOOL    = Int;

class WinTypes {
    public static inline function isTrue(v:BOOL):Bool {
        return v != 0;
    }

    public static inline function isFalse(v:BOOL):Bool {
        return v == 0;
    }

    public static inline function toBool(v:Bool):BOOL {
        return v ? 1 : 0;
    }

    public static function ptrToString(ptr:Pointer<Void>):String {
        #if cpp
        // sprintfを使うより、Haxe内部の16進数変換を使う方が安全です
        return "0x" + StringTools.hex(untyped __cpp__("(size_t){0}", ptr));
        #else
        return "ptr";
        #end
    }

    public static function debugPtr(label:String, ptr:Pointer<Void>):Void {
        #if cpp
        // HaxeのString(label)をCのprintfで使うには .utf8_str() が必要
        untyped __cpp__(
            "printf(\"[WinTypes] %s = %p\\n\", {0}.utf8_str(), {1});",
            label,
            ptr
        );
        #end
    }

    public static function debugBool(label:String, v:BOOL):Void {
        #if cpp
        untyped __cpp__(
            "printf(\"[WinTypes] %s = %s\\n\", {0}.utf8_str(), {1} ? \"TRUE\" : \"FALSE\");",
            label,
            v
        );
        #end
    }

    public static function debugDword(label:String, v:DWORD):Void {
        #if cpp
        untyped __cpp__(
            "printf(\"[WinTypes] %s = %u\\n\", {0}.utf8_str(), (unsigned int){1});",
            label,
            v
        );
        #end
    }

    public static function zeroPtr():Pointer<Void> {
        // C++のnullptrをHaxeのPointerとして取得
        return cpp.Pointer.fromRaw(untyped __cpp__("nullptr"));
    }

    public static function isNull(ptr:Pointer<Void>):Bool {
        if (ptr == null) return true;
        // ポインタの中身が0かどうかを直接チェック
        return untyped __cpp__("{0} == nullptr", ptr);
    }

    public static function notNull(ptr:Pointer<Void>):Bool {
        return !isNull(ptr);
    }

    public static function ensureNotNull(ptr:Pointer<Void>, msg:String):Pointer<Void> {
        if (isNull(ptr)) {
            #if cpp
            untyped __cpp__(
                "fprintf(stderr, \"[WinTypes] NULL pointer: %s\\n\", {0}.utf8_str());",
                msg
            );
            #end
        }
        return ptr;
    }

    public static function ptrEquals(a:Pointer<Void>, b:Pointer<Void>):Bool {
        return untyped __cpp__("{0} == {1}", a, b);
    }

    public static function ptrNotEquals(a:Pointer<Void>, b:Pointer<Void>):Bool {
        return !ptrEquals(a, b);
    }
}
