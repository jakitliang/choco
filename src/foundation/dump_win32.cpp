//
// Created by jakit on 2023/11/21.
//

#include <Windows.h>
#include <DbgHelp.h>

//
// Usage :
//
// SetUnhandledExceptionFilter(funtion handler)
//

void MakeMinidump(EXCEPTION_POINTERS* e) {
    auto hDbgHelp = LoadLibraryA("dbghelp");

    if (hDbgHelp == nullptr) {
        return;
    }

    auto pMiniDumpWriteDump = (decltype(&MiniDumpWriteDump)) GetProcAddress(hDbgHelp, "MiniDumpWriteDump");

    if (pMiniDumpWriteDump == nullptr) {
        return;
    }

    char name[MAX_PATH];
    {
        auto nameEnd = name + GetModuleFileNameA(GetModuleHandleA(nullptr), name, MAX_PATH);
        SYSTEMTIME t;
        GetSystemTime(&t);
        wsprintfA(nameEnd - strlen(".exe"),
                  "_%4d%02d%02d_%02d%02d%02d.dmp",
                  t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
    }

    auto hFile = CreateFileA(name, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if(hFile == INVALID_HANDLE_VALUE) {
        return;
    }

    MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
    exceptionInfo.ThreadId = GetCurrentThreadId();
    exceptionInfo.ExceptionPointers = e;
    exceptionInfo.ClientPointers = FALSE;

    auto dumped = pMiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            hFile,
            MINIDUMP_TYPE(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory),
            e ? &exceptionInfo : nullptr,
            nullptr,
            nullptr);

    CloseHandle(hFile);
}

LONG CALLBACK UnhandledHandler(EXCEPTION_POINTERS* e) {
    MakeMinidump(e);
    return EXCEPTION_CONTINUE_SEARCH;
}
