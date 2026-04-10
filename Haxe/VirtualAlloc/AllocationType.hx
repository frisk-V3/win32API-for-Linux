package VirtualAlloc;

class AllocationType {
    // MEM_* flags for VirtualAlloc

    public static inline var MEM_COMMIT:Int      = 0x1000;
    public static inline var MEM_RESERVE:Int     = 0x2000;
    public static inline var MEM_RESET:Int       = 0x80000;
    public static inline var MEM_LARGE_PAGES:Int = 0x20000000;
    public static inline var MEM_PHYSICAL:Int    = 0x00400000;
    public static inline var MEM_TOP_DOWN:Int    = 0x00100000;

    public static function toString(flags:Int):String {
        var parts:Array<String> = [];
        if ((flags & MEM_COMMIT) != 0) parts.push("COMMIT");
        if ((flags & MEM_RESERVE) != 0) parts.push("RESERVE");
        if ((flags & MEM_RESET) != 0) parts.push("RESET");
        if ((flags & MEM_LARGE_PAGES) != 0) parts.push("LARGE_PAGES");
        if ((flags & MEM_PHYSICAL) != 0) parts.push("PHYSICAL");
        if ((flags & MEM_TOP_DOWN) != 0) parts.push("TOP_DOWN");
        if (parts.length == 0) return "0";
        return parts.join("|");
    }

    public static function hasCommit(flags:Int):Bool {
        return (flags & MEM_COMMIT) != 0;
    }

    public static function hasReserve(flags:Int):Bool {
        return (flags & MEM_RESERVE) != 0;
    }

    public static function isCommitReserve(flags:Int):Bool {
        return hasCommit(flags) && hasReserve(flags);
    }

    public static function addCommit(flags:Int):Int {
        return flags | MEM_COMMIT;
    }

    public static function addReserve(flags:Int):Int {
        return flags | MEM_RESERVE;
    }

    public static function removeCommit(flags:Int):Int {
        return flags & ~MEM_COMMIT;
    }

    public static function removeReserve(flags:Int):Int {
        return flags & ~MEM_RESERVE;
    }

    public static function normalize(flags:Int):Int {
        // とりあえず COMMIT or RESERVE がなければ COMMIT を足す
        if (!hasCommit(flags) && !hasReserve(flags)) {
            flags |= MEM_COMMIT;
        }
        return flags;
    }

    public static function debug(flags:Int):String {
        return "AllocationType(" + toString(flags) + ")";
    }

    public static function defaultCommitReserve():Int {
        return MEM_COMMIT | MEM_RESERVE;
    }

    public static function onlyCommit():Int {
        return MEM_COMMIT;
    }

    public static function onlyReserve():Int {
        return MEM_RESERVE;
    }
}
