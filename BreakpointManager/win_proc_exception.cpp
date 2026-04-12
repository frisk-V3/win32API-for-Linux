package;

import cpp.Pointer;
import cpp.RawPointer;

// WinTypesで定義した型を利用
typedef DWORD = cpp.UInt32;
typedef PVOID = Pointer<Void>;

@:headerCode("#include <windows.h>")
@:include("YourHeaderFile.h") // このC++コードが書かれているファイル名
extern class WinDebugUtils {
    
    /**
     * 例外コードを文字列に変換する
     * C++側で const char* を返しているため、Haxeでは cpp.ConstCharStar として受け取ります
     */
    @:native("GetExceptionCodeString")
    public static function getExceptionCodeString(code:DWORD):cpp.ConstCharStar;

    /**
     * DEBUG_EVENT 構造体から例外アドレスを抽出する
     * 第1引数は DEBUG_EVENT* なので Pointer を使用します
     */
    @:native("GetExceptionAddress")
    public static function getExceptionAddress(pEvent:Pointer<Void>):PVOID;
}
