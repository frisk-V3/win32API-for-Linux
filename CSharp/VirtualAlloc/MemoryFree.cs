using System;
using System.Runtime.InteropServices;

namespace Win32Like.VirtualAlloc
{
    internal static class MemoryFree
    {
        private const string KERNEL32 = "kernel32.dll";

        public const uint MEM_RELEASE = 0x8000;

        [DllImport(KERNEL32, SetLastError = true)]
        public static extern bool VirtualFree(
            IntPtr lpAddress,
            uint dwSize,
            uint dwFreeType
        );
    }
}
