using System;
using System.Runtime.InteropServices;

namespace Win32Like.CreateFileW
{
    internal static class FileHandle
    {
        private const string KERNEL32 = "kernel32.dll";

        [DllImport(KERNEL32, SetLastError = true)]
        public static extern bool CloseHandle(IntPtr hObject);

        public static void Close(IntPtr handle)
        {
            if (handle != IntPtr.Zero)
            {
                CloseHandle(handle);
            }
        }
    }
}
