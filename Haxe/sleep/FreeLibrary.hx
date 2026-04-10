package LoadLibraryW;

class FreeLibrary {
    public static function free(module:cpp.Pointer<Void>):Bool {
        return untyped __cpp__("FreeLibrary({0})", module);
    }
}
