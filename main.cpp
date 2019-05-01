#include <windows.h>

using namespace std;

const DWORD DebounceTime = 2000;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

int main()
{
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

    MSG Msg;
    while (GetMessage(&Msg, NULL, 0, 0) != 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    UnhookWindowsHookEx(hook);
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    static DWORD lastTime;
    if ((wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) && nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* kbDllHookStruct = (KBDLLHOOKSTRUCT*)lParam;
        int vkCode = kbDllHookStruct->vkCode;
        DWORD time = kbDllHookStruct->time;

        if (time > lastTime + DebounceTime && vkCode == 0xae)
        {
            Sleep(500);
            keybd_event(0xad, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
            keybd_event(0xad, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
        }

        if (vkCode == 0xae || vkCode == 0xaf)
        {
            lastTime = kbDllHookStruct->time;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
