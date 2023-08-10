#include <iostream>
#include <type_traits> // std::make_signed_t<>

#include <windows.h>

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode != HC_ACTION) // Nothing to do :(
        return CallNextHookEx(NULL, nCode, wParam, lParam);

    MSLLHOOKSTRUCT *info = reinterpret_cast<MSLLHOOKSTRUCT *>(lParam);

    char const *button_name[] = {"Left", "Right", "Middle", "X"};
    enum
    {
        BTN_LEFT,
        BTN_RIGHT,
        BTN_MIDDLE,
        BTN_XBUTTON,
        BTN_NONE
    } button = BTN_NONE;

    char const *up_down[] = {"up", "down"};
    bool down = false;

    switch (wParam)
    {

    case WM_LBUTTONDOWN:
        down = true;
    case WM_LBUTTONUP:
        button = BTN_LEFT;
        break;
    case WM_RBUTTONDOWN:
        down = true;
    case WM_RBUTTONUP:
        button = BTN_RIGHT;
        break;
    case WM_MBUTTONDOWN:
        down = true;
    case WM_MBUTTONUP:
        button = BTN_MIDDLE;
        break;
    case WM_XBUTTONDOWN:
        down = true;
    case WM_XBUTTONUP:
        button = BTN_XBUTTON;
        break;

    case WM_MOUSEWHEEL:
        // the hi order word might be negative, but WORD is unsigned, so
        // we need some signed type of an appropriate size:
        down = static_cast<std::make_signed_t<WORD>>(HIWORD(info->mouseData)) < 0;
        std::cout << "Mouse wheel scrolled " << up_down[down] << '\n';
        break;
    }

    if (button != BTN_NONE)
    {
        std::cout << button_name[button];
        if (button == BTN_XBUTTON)
            std::cout << HIWORD(info->mouseData);
        std::cout << " mouse button " << up_down[down] << '\n';
    }

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
