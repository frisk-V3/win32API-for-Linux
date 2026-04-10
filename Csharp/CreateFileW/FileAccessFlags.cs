namespace Win32Like.CreateFileW
{
    internal static class FileAccessFlags
    {
        public const uint GENERIC_READ  = 0x80000000;
        public const uint GENERIC_WRITE = 0x40000000;

        public const uint FILE_SHARE_READ  = 0x00000001;
        public const uint FILE_SHARE_WRITE = 0x00000002;

        public const uint CREATE_NEW        = 1;
        public const uint CREATE_ALWAYS     = 2;
        public const uint OPEN_EXISTING     = 3;
        public const uint OPEN_ALWAYS       = 4;
        public const uint TRUNCATE_EXISTING = 5;

        public const uint FILE_ATTRIBUTE_NORMAL = 0x00000080;
    }
}
