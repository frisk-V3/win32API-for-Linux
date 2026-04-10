namespace Win32Like.VirtualAlloc
{
    internal static class MemoryProtection
    {
        public const uint PAGE_NOACCESS          = 0x01;
        public const uint PAGE_READONLY          = 0x02;
        public const uint PAGE_READWRITE         = 0x04;
        public const uint PAGE_EXECUTE           = 0x10;
        public const uint PAGE_EXECUTE_READ      = 0x20;
        public const uint PAGE_EXECUTE_READWRITE = 0x40;
    }
}
