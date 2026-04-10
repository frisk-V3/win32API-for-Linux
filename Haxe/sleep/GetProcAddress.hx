package LoadLibraryW;

class GetProcAddress {
    public static function get(module:cpp.Pointer<Void>, name:String):cpp.Pointer<Void> {
        return untyped __cpp__("GetProcAddress({0}, {1})", module, name);
    }
}
