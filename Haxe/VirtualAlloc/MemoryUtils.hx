package VirtualAlloc;

import cpp.Pointer;

class MemoryUtils {
    // 高レベルなユーティリティ：確保＋解放＋ログ

    public static function allocBuffer(size:Int, label:String):Pointer<Void> {
        var flags = AllocationType.defaultCommitReserve();
        var protect = MemoryProtection.defaultReadWrite();
        var ptr = VirtualAlloc.alloc(null, size, flags, protect);
        VirtualAlloc.debugPrint(ptr, label);
        if (VirtualAlloc.isNull(ptr)) {
            logError("allocBuffer failed: " + label + " size=" + size);
        }
        return ptr;
    }

    public static function allocExecBuffer(size:Int, label:String):Pointer<Void> {
        var flags = AllocationType.defaultCommitReserve();
        var protect = MemoryProtection.defaultExecReadWrite();
        var ptr = VirtualAlloc.alloc(null, size, flags, protect);
        VirtualAlloc.debugPrint(ptr, label);
        if (VirtualAlloc.isNull(ptr)) {
            logError("allocExecBuffer failed: " + label + " size=" + size);
        }
        return ptr;
    }

    public static function freeBuffer(ptr:Pointer<Void>, label:String):Bool {
        var ok = VirtualFree.freeAndLog(ptr, label);
        if (!ok) {
            logError("freeBuffer failed: " + label);
        }
        return ok;
    }

    public static function reallocBuffer(
        oldPtr:Pointer<Void>,
        oldSize:Int,
        newSize:Int,
        label:String
    ):Pointer<Void> {
        var newPtr = allocBuffer(newSize, label + "_realloc");
        if (!VirtualAlloc.isNull(oldPtr) && !VirtualAlloc.isNull(newPtr)) {
            var copySize = oldSize < newSize ? oldSize : newSize;
            VirtualAlloc.copyMemory(newPtr, oldPtr, copySize);
            freeBuffer(oldPtr, label + "_old");
        }
        return newPtr;
    }

    public static function fillWithPattern(ptr:Pointer<Void>, size:Int, value:Int, label:String):Void {
        if (VirtualAlloc.isNull(ptr)) {
            logError("fillWithPattern: NULL ptr (" + label + ")");
            return;
        }
        VirtualAlloc.fillPattern(ptr, size, value);
    }

    public static function writeString(ptr:Pointer<Void>, text:String, label:String):Void {
        if (VirtualAlloc.isNull(ptr)) {
            logError("writeString: NULL ptr (" + label + ")");
            return;
        }
        #if cpp
        untyped __cpp__(
            "{ char* p = (char*){0}; const char* s = {1}; while (*s) *p++ = *s++; *p = 0; }",
            ptr,
            text
        );
        #end
    }

    public static function readCString(ptr:Pointer<Void>, max:Int):String {
        if (VirtualAlloc.isNull(ptr)) return "";
        #if cpp
        return untyped __cpp__(
            "({ \
                char* p = (char*){0}; \
                int n = {1}; \
                std::string s; \
                while (n-- > 0 && *p) { s.push_back(*p++); } \
                ::String(s.c_str()); \
            })",
            ptr,
            max
        );
        #else
        return "";
        #end
    }

    public static function logInfo(msg:String):Void {
        #if cpp
        untyped __cpp__(
            "printf(\"[VirtualAlloc/Info] %s\\n\", {0});",
            msg
        );
        #end
    }

    public static function logError(msg:String):Void {
        #if cpp
        untyped __cpp__(
            "fprintf(stderr, \"[VirtualAlloc/Error] %s\\n\", {0});",
            msg
        );
        #end
    }

    public static function dumpBytes(ptr:Pointer<Void>, size:Int, label:String):Void {
        if (VirtualAlloc.isNull(ptr)) {
            logError("dumpBytes: NULL ptr (" + label + ")");
            return;
        }
        #if cpp
        untyped __cpp__(
            "{ \
                unsigned char* p = (unsigned char*){0}; \
                int n = {1}; \
                printf(\"[VirtualAlloc/Dump] %s: \", {2}); \
                for (int i = 0; i < n; ++i) { \
                    printf(\"%02X \", p[i]); \
                } \
                printf(\"\\n\"); \
            }",
            ptr,
            size,
            label
        );
        #end
    }
}
