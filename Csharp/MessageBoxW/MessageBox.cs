using System;
using System.Runtime.InteropServices;

namespace Win32Like.MessageBoxW
{
    internal static class MessageBoxApi
    {
        private const string USER32 = "user32.dll";

        [DllImport(USER32, CharSet = CharSet.Unicode)]
        public static extern int MessageBoxW(
            IntPtr hWnd,
            string lpText,
            string lpCaption,
            uint uType
        );
    }
}
