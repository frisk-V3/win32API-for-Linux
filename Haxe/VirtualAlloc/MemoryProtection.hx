package VirtualAlloc;

class MemoryProtection {
    // PAGE_* flags for VirtualAlloc

    public static inline var PAGE_NOACCESS:Int          = 0x01;
    public static inline var PAGE_READONLY:Int          = 0x02;
    public static inline var PAGE_READWRITE:Int         = 0x04;
    public static inline var PAGE_WRITECOPY:Int         = 0x08;
    public static inline var PAGE_EXECUTE:Int           = 0x10;
    public static inline var PAGE_EXECUTE_READ:Int      = 0x20;
    public static inline var PAGE_EXECUTE_READWRITE:Int = 0x40;
    public static inline var PAGE_EXECUTE_WRITECOPY:Int = 0x80;

    public static function toString(flags:Int):String {
        var parts:Array<String> = [];
        if ((flags & PAGE_NOACCESS) != 0) parts.push("NOACCESS");
        if ((flags & PAGE_READONLY) != 0) parts.push("READONLY");
        if ((flags & PAGE_READWRITE) != 0) parts.push("READWRITE");
        if ((flags & PAGE_WRITECOPY) != 0) parts.push("WRITECOPY");
        if ((flags & PAGE_EXECUTE) != 0) parts.push("EXECUTE");
        if ((flags & PAGE_EXECUTE_READ) != 0) parts.push("EXECUTE_READ");
        if ((flags & PAGE_EXECUTE_READWRITE) != 0) parts.push("EXECUTE_READWRITE");
        if ((flags & PAGE_EXECUTE_WRITECOPY) != 0) parts.push("EXECUTE_WRITECOPY");
        if (parts.length == 0) return "0";
        return parts.join("|");
    }

    public static function isReadable(flags:Int):Bool {
        return (flags & (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) != 0;
    }

    public static function isWritable(flags:Int):Bool {
        return (flags & (PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) != 0;
    }

    public static function isExecutable(flags:Int):Bool {
        return (flags & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) != 0;
    }

    public static function defaultReadWrite():Int {
        return PAGE_READWRITE;
    }

    public static function defaultExecReadWrite():Int {
        return PAGE_EXECUTE_READWRITE;
    }

    public static function debug(flags:Int):String {
        return "MemoryProtection(" + toString(flags) + ")";
    }

    public static function makeReadOnly(flags:Int):Int {
        flags &= ~PAGE_READWRITE;
        flags |= PAGE_READONLY;
        return flags;
    }

    public static function makeReadWrite(flags:Int):Int {
        flags &= ~PAGE_READONLY;
        flags |= PAGE_READWRITE;
        return flags;
    }

    public static function makeExecutable(flags:Int):Int {
        if (!isExecutable(flags)) {
            flags |= PAGE_EXECUTE_READ;
        }
        return flags;
    }

    public static function clearExecute(flags:Int):Int {
        flags &= ~PAGE_EXECUTE;
        flags &= ~PAGE_EXECUTE_READ;
        flags &= ~PAGE_EXECUTE_READWRITE;
        flags &= ~PAGE_EXECUTE_WRITECOPY;
        return flags;
    }
}
