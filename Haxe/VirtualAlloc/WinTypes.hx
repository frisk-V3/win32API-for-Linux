package VirtualAlloc;

import cpp.Pointer;

typedef LPVOID  = Pointer<Void>;
typedef SIZE_T  = Int;
typedef DWORD   = Int;
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
        return untyped __cpp__(
            "({ char buf[32]; sprintf(buf, \"%p\", {0}); ::String(buf); })",
            ptr
        );
        #else
        return "ptr";
        #end
    }

    public static function debugPtr(label:String, ptr:Pointer<Void>):Void {
        #if cpp
        untyped __cpp__(
            "printf(\"[WinTypes] %s = %p\\n\", {0}, {1});",
            label,
            ptr
        );
        #end
    }

    public static function debugBool(label:String, v:BOOL):Void {
        #if cpp
        untyped __cpp__(
            "printf(\"[WinTypes] %s = %s\\n\", {0}, {1} ? \"TRUE\" : \"FALSE\");",
            label,
            v
        );
        #end
    }

    public static function debugDword(label:String, v:DWORD):Void {
        #if cpp
        untyped __cpp__(
            "printf(\"[WinTypes] %s = %u\\n\", {0}, (unsigned int){1});",
            label,
            v
        );
        #end
    }

    public static function zeroPtr():Pointer<Void> {
        return cast 0;
    }

    public static function isNull(ptr:Pointer<Void>):Bool {
        return ptr == null || ptr == cast 0;
    }

    public static function notNull(ptr:Pointer<Void>):Bool {
        return !isNull(ptr);
    }

    public static function ensureNotNull(ptr:Pointer<Void>, msg:String):Pointer<Void> {
        if (isNull(ptr)) {
            #if cpp
            untyped __cpp__(
                "fprintf(stderr, \"[WinTypes] NULL pointer: %s\\n\", {0});",
                msg
            );
            #end
        }
        return ptr;
    }

    public static function ptrEquals(a:Pointer<Void>, b:Pointer<Void>):Bool {
        return a == b;
    }

    public static function ptrNotEquals(a:Pointer<Void>, b:Pointer<Void>):Bool {
        return a != b;
    }
}
