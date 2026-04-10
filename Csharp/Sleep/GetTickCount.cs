using System.Runtime.InteropServices;

namespace Win32Like.SleepApi
{
    internal static class TickApi
    {
        private const string KERNEL32 = "kernel32.dll";

        [DllImport(KERNEL32)]
        public static extern uint GetTickCount();
    }
}
