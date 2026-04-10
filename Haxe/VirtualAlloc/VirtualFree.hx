package VirtualAlloc;

import cpp.Pointer;

class VirtualFree {
    // Win32 VirtualFree wrapper for Haxe/cpp

    public static inline var MEM_RELEASE:Int = 0x8000;

    public static function free(ptr:Pointer<Void>):Bool {
        if (ptr == null || ptr == cast 0) return false;
        var ok:Bool = untyped __cpp__(
            "VirtualFree({0}, 0, {1})",
            ptr,
            MEM_RELEASE
        );
        return ok;
    }

    public static function freeAndLog(ptr:Pointer<Void>, label:String):Bool {
        if (ptr == null || ptr == cast 0) {
            #if cpp
            untyped __cpp__(
                "printf(\"[VirtualFree] %s = NULL (skip)\\n\", {0});",
                label
            );
            #end
            return false;
        }
        #if cpp
        untyped __cpp__(
            "printf(\"[VirtualFree] %s = %p\\n\", {0}, {1});",
            label,
            ptr
        );
        #end
        return free(ptr);
    }

    public static function freeIfNotNull(ptr:Pointer<Void>):Bool {
        if (ptr == null || ptr == cast 0) return false;
        return free(ptr);
    }

    public static function freeArray(ptrs:Array<Pointer<Void>>):Int {
        var count = 0;
        for (p in ptrs) {
            if (p != null && p != cast 0) {
                if (free(p)) count++;
            }
        }
        return count;
    }

    public static function freeArrayAndLog(ptrs:Array<Pointer<Void>>, label:String):Int {
        var count = 0;
        var index = 0;
        for (p in ptrs) {
            var tag = label + "#" + index;
            if (p != null && p != cast 0) {
                if (freeAndLog(p, tag)) count++;
            }
            index++;
        }
        return count;
    }

    public static function safeRelease(ptrRef:{ var value:Pointer<Void>; }):Bool {
        if (ptrRef.value == null || ptrRef.value == cast 0) return false;
        var ok = free(ptrRef.value);
        if (ok) ptrRef.value = cast 0;
        return ok;
    }

    public static function safeReleaseAndLog(ptrRef:{ var value:Pointer<Void>; }, label:String):Bool {
        if (ptrRef.value == null || ptrRef.value == cast 0) {
            #if cpp
            untyped __cpp__(
                "printf(\"[VirtualFree] %s already NULL\\n\", {0});",
                label
            );
            #end
            return false;
        }
        var ok = freeAndLog(ptrRef.value, label);
        if (ok) ptrRef.value = cast 0;
        return ok;
    }

    public static function isReleased(ptr:Pointer<Void>):Bool {
        return ptr == null || ptr == cast 0;
    }
}
