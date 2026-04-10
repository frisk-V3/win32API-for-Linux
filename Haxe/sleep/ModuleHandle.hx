package LoadLibraryW;

class ModuleHandle {
    public static function nullHandle():cpp.Pointer<Void> {
        return untyped __cpp__("(HMODULE)0");
    }
}
