using System;
using System.Runtime.InteropServices;

namespace Win32Like.CreateProcessW
{
    internal static class CreateProcessApi
    {
        private const string KERNEL32 = "kernel32.dll";

        [DllImport(KERNEL32, CharSet = CharSet.Unicode, SetLastError = true)]
        public static extern bool CreateProcessW(
            string lpApplicationName,
            string lpCommandLine,
            IntPtr lpProcessAttributes,
            IntPtr lpThreadAttributes,
            bool bInheritHandles,
            uint dwCreationFlags,
            IntPtr lpEnvironment,
            string lpCurrentDirectory,
            ref STARTUPINFO si,
            out PROCESS_INFORMATION pi
        );
    }
}
