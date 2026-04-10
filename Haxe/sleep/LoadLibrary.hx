package LoadLibraryW;

class LoadLibrary {
    public static function load(path:String):cpp.Pointer<Void> {
        return untyped __cpp__("LoadLibraryW({0})", path);
    }
}
