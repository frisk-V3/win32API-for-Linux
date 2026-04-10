using System.Runtime.InteropServices;

namespace Win32Like.SleepApi
{
    internal static class HighPrecisionTimer
    {
        private const string KERNEL32 = "kernel32.dll";

        [DllImport(KERNEL32)]
        public static extern bool QueryPerformanceCounter(out long lpPerformanceCount);

        [DllImport(KERNEL32)]
        public static extern bool QueryPerformanceFrequency(out long lpFrequency);
    }
}
