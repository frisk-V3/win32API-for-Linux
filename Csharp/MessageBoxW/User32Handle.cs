using System;

namespace Win32Like.MessageBoxW
{
    internal static class User32Handle
    {
        public static IntPtr Null => IntPtr.Zero;

        public static IntPtr DesktopWindow => IntPtr.Zero; 
        // 本来は GetDesktopWindow() だが、MessageBoxW では Zero でOK
    }
}
