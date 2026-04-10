package VirtualAlloc;

import cpp.Pointer;

class VirtualAlloc {
    // Win32 VirtualAlloc wrapper for Haxe/cpp
    // MEM_COMMIT / MEM_RESERVE は別ファイルで定義
    // ここでは実際の呼び出しだけを担当する

    public static function allocCommitReadWrite(size:Int):Pointer<Void> {
        var addr:Pointer<Void> = null;
        var flags = AllocationType.MEM_COMMIT | AllocationType.MEM_RESERVE;
        var protect = MemoryProtection.PAGE_READWRITE;
        addr = alloc(null, size, flags, protect);
        return addr;
    }

    public static function allocExec(size:Int):Pointer<Void> {
        var addr:Pointer<Void> = null;
        var flags = AllocationType.MEM_COMMIT | AllocationType.MEM_RESERVE;
        var protect = MemoryProtection.PAGE_EXECUTE_READWRITE;
        addr = alloc(null, size, flags, protect);
        return addr;
    }

    public static function alloc(
        base:Pointer<Void>,
        size:Int,
        allocType:Int,
        protect:Int
    ):Pointer<Void> {
        // base は通常 null (OS に任せる)
        var result:Pointer<Void> = null;
        result = untyped __cpp__(
            "VirtualAlloc({0}, {1}, {2}, {3})",
            base,
            size,
            allocType,
            protect
        );
        return result;
    }

    public static function isNull(ptr:Pointer<Void>):Bool {
        return ptr == null || ptr == cast 0;
    }

    public static function debugPrint(ptr:Pointer<Void>, label:String):Void {
        #if cpp
        untyped __cpp__(
            "printf(\"[VirtualAlloc] %s = %p\\n\", {0}, {1});",
            label,
            ptr
        );
        #end
    }

    public static function allocAndLog(size:Int, label:String):Pointer<Void> {
        var p = allocCommitReadWrite(size);
        debugPrint(p, label);
        return p;
    }

    public static function allocExecAndLog(size:Int, label:String):Pointer<Void> {
        var p = allocExec(size);
        debugPrint(p, label);
        return p;
    }

    public static function zeroMemory(ptr:Pointer<Void>, size:Int):Void {
        if (isNull(ptr)) return;
        untyped __cpp__(
            "memset({0}, 0, {1});",
            ptr,
            size
        );
    }

    public static function fillPattern(ptr:Pointer<Void>, size:Int, value:Int):Void {
        if (isNull(ptr)) return;
        var v = value & 0xFF;
        untyped __cpp__(
            "memset({0}, {1}, {2});",
            ptr,
            v,
            size
        );
    }

    public static function copyMemory(dst:Pointer<Void>, src:Pointer<Void>, size:Int):Void {
        if (isNull(dst) || isNull(src)) return;
        untyped __cpp__(
            "memcpy({0}, {1}, {2});",
            dst,
            src,
            size
        );
    }

    public static function writeByte(ptr:Pointer<Void>, offset:Int, value:Int):Void {
        if (isNull(ptr)) return;
        untyped __cpp__(
            "((unsigned char*){0})[{1}] = (unsigned char){2};",
            ptr,
            offset,
            value & 0xFF
        );
    }

    public static function readByte(ptr:Pointer<Void>, offset:Int):Int {
        if (isNull(ptr)) return 0;
        return untyped __cpp__(
            "((unsigned char*){0})[{1}]",
            ptr,
            offset
        );
    }

    public static function writeInt(ptr:Pointer<Void>, offset:Int, value:Int):Void {
        if (isNull(ptr)) return;
        untyped __cpp__(
            "((int*){0})[{1}] = (int){2};",
            ptr,
            offset,
            value
        );
    }

    public static function readInt(ptr:Pointer<Void>, offset:Int):Int {
        if (isNull(ptr)) return 0;
        return untyped __cpp__(
            "((int*){0})[{1}]",
            ptr,
            offset
        );
    }
}
