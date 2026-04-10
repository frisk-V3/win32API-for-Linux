using System;
using System.Runtime.InteropServices;

namespace Win32Like.VirtualAlloc
{
    internal static class VirtualAllocApi
    {
        private const string KERNEL32 = "kernel32.dll";

        public const uint MEM_COMMIT  = 0x1000;
        public const uint MEM_RESERVE = 0x2000;

        [DllImport(KERNEL32, SetLastError = true)]
        public static extern IntPtr VirtualAlloc(
            IntPtr lpAddress,
            uint dwSize,
            uint flAllocationType,
            uint flProtect
        );
    }
}
