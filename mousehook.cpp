#include <iostream>
#include <type_traits> // std::make_signed_t<>

#include <windows.h>

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode != HC_ACTION) // Nothing to do :(
        return CallNextHookEx(NULL, nCode, wParam, lParam);

    MSLLHOOKSTRUCT *info = reinterpret_cast<MSLLHOOKSTRUCT *>(lParam);
    if (wParam == WM_XBUTTONDOWN)
    {
        if (HIWORD(info->mouseData) == 1)
        {
            keybd_event(VK_CONTROL, 0, 0, 0);               // 模拟按下 Ctrl 键
            keybd_event('T', 0, 0, 0);                      // 模拟按下 A 键
            keybd_event('T', 0, KEYEVENTF_KEYUP, 0);        // 模拟松开 A 键
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // 模拟松开 Ctrl 键
        }
        else if (HIWORD(info->mouseData) == 2)
        {
            keybd_event(VK_CONTROL, 0, 0, 0);               // 模拟按下 Ctrl 键
            keybd_event('W', 0, 0, 0);                      // 模拟按下 A 键
            keybd_event('W', 0, KEYEVENTF_KEYUP, 0);        // 模拟松开 A 键
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // 模拟松开 Ctrl 键
        }
        return 1; // 返回 1，表示事件已经被处理
    }
    if (wParam == WM_XBUTTONUP)
        return 1; // 返回 1，表示事件已经被处理
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
HHOOK hook = NULL;

BOOL WINAPI ctrl_handler(DWORD dwCtrlType)
{
    if (hook)
    {
        std::cout << "Unhooking " << hook << '\n';
        UnhookWindowsHookEx(hook);
        hook = NULL; // ctrl_handler might be called multiple times
        std::cout << "Bye :(";
        std::cin.get(); // gives the user 5 seconds to read our last output
    }

    return TRUE;
}

int main()
{
    SetConsoleCtrlHandler(ctrl_handler, TRUE);
    hook = SetWindowsHookExW(WH_MOUSE_LL, MouseHookProc, nullptr, 0);

    if (!hook)
    {
        std::cerr << "SetWindowsHookExW() failed. Bye :(\n\n";
        return EXIT_FAILURE;
    }

    std::cout << "Hook set: " << hook << '\n';
    GetMessageW(nullptr, nullptr, 0, 0);
}
