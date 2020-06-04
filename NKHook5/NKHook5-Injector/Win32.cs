using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NKHook5_Injector
{
    public class Win32
    {
        [DllImport("user32.dll")]
        public static extern int GetWindowText(IntPtr hWnd, StringBuilder text, int count);
        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        public static extern UIntPtr VirtualAllocEx(
            IntPtr hProcess,
            UIntPtr lpAddress,
            uint dwSize,
            uint flAllocationType,
            uint flProtect
        );
        [DllImport("kernel32.dll")]
        public static extern bool WriteProcessMemory(
            IntPtr hProcess,
            UIntPtr lpBaseAddress,
            string lpBuffer,
            UIntPtr nSize,
            out IntPtr lpNumberOfBytesWritten
        );
        [DllImport("kernel32.dll", CharSet = CharSet.Ansi, ExactSpelling = true)]
        public static extern UIntPtr GetProcAddress(
            IntPtr hModule,
            string procName
        );
        [DllImport("kernel32")]
        public static extern IntPtr CreateRemoteThread(
            IntPtr hProcess,
            IntPtr lpThreadAttributes,
            uint dwStackSize,
            UIntPtr lpStartAddress, // raw Pointer into remote process  
            UIntPtr lpParameter,
            uint dwCreationFlags,
            out IntPtr lpThreadId
        );
        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr GetModuleHandle(
            string lpModuleName
        );
        [DllImport("kernel32", SetLastError = true, ExactSpelling = true)]
        internal static extern Int32 WaitForSingleObject(
            IntPtr handle,
            Int32 milliseconds
        );
        [DllImport("kernel32.dll")]
        public static extern Int32 CloseHandle(
            IntPtr hObject
        );
        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        public static extern bool VirtualFreeEx(
            IntPtr hProcess,
            UIntPtr lpAddress,
            UIntPtr dwSize,
            uint dwFreeType
        );
        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(
            UInt32 dwDesiredAccess,
            bool bInheritHandle,
            Int32 dwProcessId
        );
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern int LoadString(IntPtr hInstance, uint uID, StringBuilder lpBuffer, int nBufferMax);
        [DllImport("kernel32.dll", EntryPoint = "LoadLibrary", SetLastError = true)]
        public static extern IntPtr LoadLibrary(string lpFileName);
        [DllImport("advapi32.dll")]
        public static extern IntPtr GetNamedSecurityInfo(string pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, out IntPtr ppsidOwner, out IntPtr ppsidGroup, out IntPtr ppDacl, out IntPtr ppSacl, out IntPtr ppSecurityDescriptor);
        [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern int SetEntriesInAcl(int cCountOfExplicitEntries, ref EXPLICIT_ACCESS pListOfExplicitEntries, IntPtr OldAcl, out IntPtr NewAcl);
        [DllImport("advapi32.dll", CharSet = CharSet.Auto)]
        public static extern uint SetNamedSecurityInfo(string pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, IntPtr psidOwner, IntPtr psidGroup, IntPtr pDacl, IntPtr pSacl);
        [DllImport("advapi32.dll", CharSet = CharSet.Unicode, EntryPoint = "ConvertStringSidToSidW", ExactSpelling = true, SetLastError = true)]
        public static extern IntPtr ConvertStringSidToSid(string sid, out IntPtr sidP);
        [DllImport("kernel32", SetLastError = true)]
        public static extern int VirtualProtectEx(IntPtr hProcess, IntPtr lpAddress, int dwSize, Int64 flNewProtect, ref Int64 lpflOldProtect);

        public enum SE_OBJECT_TYPE
        {
            SE_UNKNOWN_OBJECT_TYPE = 0,
            SE_FILE_OBJECT,
            SE_SERVICE,
            SE_PRINTER,
            SE_REGISTRY_KEY,
            SE_LMSHARE,
            SE_KERNEL_OBJECT,
            SE_WINDOW_OBJECT,
            SE_DS_OBJECT,
            SE_DS_OBJECT_ALL,
            SE_PROVIDER_DEFINED_OBJECT,
            SE_WMIGUID_OBJECT,
            SE_REGISTRY_WOW64_32KEY
        }
        [Flags]
        public enum SECURITY_INFORMATION : uint
        {
            OWNER_SECURITY_INFORMATION = 0x00000001,
            GROUP_SECURITY_INFORMATION = 0x00000002,
            DACL_SECURITY_INFORMATION = 0x00000004,
            SACL_SECURITY_INFORMATION = 0x00000008,
            UNPROTECTED_SACL_SECURITY_INFORMATION = 0x10000000,
            UNPROTECTED_DACL_SECURITY_INFORMATION = 0x20000000,
            PROTECTED_SACL_SECURITY_INFORMATION = 0x40000000,
            PROTECTED_DACL_SECURITY_INFORMATION = 0x80000000
        }
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode, Pack = 0)] //Platform independent 32 & 64 bit - use Pack = 0 for both platforms
        public struct EXPLICIT_ACCESS
        {
            public uint grfAccessPermissions;
            public uint grfAccessMode;
            public uint grfInheritance;
            public TRUSTEE Trustee;
        }

        public enum MULTIPLE_TRUSTEE_OPERATION
        {
            NO_MULTIPLE_TRUSTEE,
            TRUSTEE_IS_IMPERSONATE
        }

        public enum TRUSTEE_FORM
        {
            TRUSTEE_IS_SID,
            TRUSTEE_IS_NAME,
            TRUSTEE_BAD_FORM,
            TRUSTEE_IS_OBJECTS_AND_SID,
            TRUSTEE_IS_OBJECTS_AND_NAME
        }

        public enum TRUSTEE_TYPE
        {
            TRUSTEE_IS_UNKNOWN,
            TRUSTEE_IS_USER,
            TRUSTEE_IS_GROUP,
            TRUSTEE_IS_DOMAIN,
            TRUSTEE_IS_ALIAS,
            TRUSTEE_IS_WELL_KNOWN_GROUP,
            TRUSTEE_IS_DELETED,
            TRUSTEE_IS_INVALID,
            TRUSTEE_IS_COMPUTER
        }

        //Platform independent (32 & 64 bit) - use Pack = 0 for both platforms. IntPtr works as well.
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto, Pack = 0)]
        public struct TRUSTEE : IDisposable
        {
            public IntPtr pMultipleTrustee;
            public MULTIPLE_TRUSTEE_OPERATION MultipleTrusteeOperation;
            public TRUSTEE_FORM TrusteeForm;
            public TRUSTEE_TYPE TrusteeType;
            private IntPtr ptstrName;

            void IDisposable.Dispose()
            {
                if (ptstrName != IntPtr.Zero) Marshal.Release(ptstrName);
            }

            public IntPtr Name;
        }

        [Flags]
        public enum ThreadAccess : int
        {
            TERMINATE = (0x0001),
            SUSPEND_RESUME = (0x0002),
            GET_CONTEXT = (0x0008),
            SET_CONTEXT = (0x0010),
            SET_INFORMATION = (0x0020),
            QUERY_INFORMATION = (0x0040),
            SET_THREAD_TOKEN = (0x0080),
            IMPERSONATE = (0x0100),
            DIRECT_IMPERSONATION = (0x0200)
        }

        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenThread(ThreadAccess dwDesiredAccess, bool bInheritHandle, uint dwThreadId);
        [DllImport("kernel32.dll")]
        public static extern uint SuspendThread(IntPtr hThread);
        [DllImport("kernel32.dll")]
        public static extern int ResumeThread(IntPtr hThread);
        public static void SuspendProcess(int pid)
        {
            var process = Process.GetProcessById(pid); // throws exception if process does not exist

            foreach (ProcessThread pT in process.Threads)
            {
                IntPtr pOpenThread = OpenThread(ThreadAccess.SUSPEND_RESUME, false, (uint)pT.Id);

                if (pOpenThread == IntPtr.Zero)
                {
                    continue;
                }

                SuspendThread(pOpenThread);

                CloseHandle(pOpenThread);
            }
        }
        public static void ResumeProcess(int pid)
        {
            var process = Process.GetProcessById(pid);

            if (process.ProcessName == string.Empty)
                return;

            foreach (ProcessThread pT in process.Threads)
            {
                IntPtr pOpenThread = OpenThread(ThreadAccess.SUSPEND_RESUME, false, (uint)pT.Id);

                if (pOpenThread == IntPtr.Zero)
                {
                    continue;
                }

                var suspendCount = 0;
                do
                {
                    suspendCount = ResumeThread(pOpenThread);
                } while (suspendCount > 0);

                CloseHandle(pOpenThread);
            }
        }
    }
}
