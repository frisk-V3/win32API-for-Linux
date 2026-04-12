package;

class GetProcAddress {
    public static function get(module:cpp.Pointer<Void>, name:String):cpp.Pointer<Void> {
        return untyped __cpp__("::GetProcAddress((HMODULE){0}, {1})", module, name.__s);
    }
}
