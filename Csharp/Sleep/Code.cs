using System;
using System.Runtime.InteropServices;

namespace Win32Like.SleepApi
{
    internal static class Native
    {
        private const string KERNEL32 = "kernel32.dll";

        // --- 1: Sleep ---
        [DllImport(KERNEL32)]
        public static extern void Sleep(uint dwMilliseconds);

        // --- 2: GetTickCount ---
        [DllImport(KERNEL32)]
        public static extern uint GetTickCount();

        // --- 3: QueryPerformanceCounter ---
        [DllImport(KERNEL32)]
        public static extern bool QueryPerformanceCounter(out long lpPerformanceCount);

        // --- 4: QueryPerformanceFrequency（おまけ） ---
        [DllImport(KERNEL32)]
        public static extern bool QueryPerformanceFrequency(out long lpFrequency);
    }

    // C#側のラッパ（Win32っぽい）
    public static class SleepApi
    {
        public static void SleepMs(uint ms)
        {
            Native.Sleep(ms);
        }

        public static uint TickCount()
        {
            return Native.GetTickCount();
        }

        public static double HighPrecisionTime()
        {
            Native.QueryPerformanceFrequency(out long freq);
            Native.QueryPerformanceCounter(out long counter);

            return (double)counter / freq;
        }
    }
}
