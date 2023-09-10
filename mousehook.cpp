#include <windows.h>
#include <chrono>
#include <iostream>
#include <type_traits>  // std::make_signed_t<>
bool rDown = false;
bool mDown = false;
bool xDown = false;
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode != HC_ACTION)  // Nothing to do :(
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    MSLLHOOKSTRUCT* info = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
    if (info == NULL) {
        std::cout << "lParam info 空指针" << std::endl;
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }
    // std::cout << "Mouse position: (" << info->pt.x << ", " << info->pt.y << ")" << std::endl; // 输出鼠标位置
    if (wParam == WM_MOUSEWHEEL) {
        // 获取鼠标滚轮滚动方向
        int zDelta = GET_WHEEL_DELTA_WPARAM(info->mouseData);
        // 左上角
        if (info->pt.x < 9 && info->pt.y < 67) {
            INPUT inputs[1] = {};
            ZeroMemory(inputs, sizeof(inputs));
            inputs[0].type = INPUT_KEYBOARD;
            if (zDelta == 120)
                inputs[0].ki.wVk = VK_VOLUME_UP;
            else if (zDelta == -120)
                inputs[0].ki.wVk = VK_VOLUME_DOWN;
            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << L"SendInput failed:" << std::endl;
            }
            return 1;  // 返回 1，表示事件已经被处理
        }
        // 右上角 X按钮的宽,chrome tab的下边界66以上
        else if (info->pt.x > 5028 && info->pt.y < 67) {
            INPUT inputs[2] = {};
            ZeroMemory(inputs, sizeof(inputs));
            inputs[0].type = INPUT_KEYBOARD;
            if (zDelta == 120)
                inputs[0].ki.wVk = VK_HOME;
            else if (zDelta == -120)
                inputs[0].ki.wVk = VK_END;
            inputs[1] = inputs[0];
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << L"SendInput failed:" << std::endl;
            }
            return 1;  // 返回 1，表示事件已经被处理
        }
        // 上
        else if (info->pt.y < 67) {
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LCONTROL;
            inputs[1].type = INPUT_KEYBOARD;
            if (zDelta == 120)
                inputs[1].ki.wVk = VK_PRIOR;
            else if (zDelta == -120)
                inputs[1].ki.wVk = VK_NEXT;
            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << L"SendInput failed:" << std::endl;
            }
            return 1;  // 返回 1，表示事件已经被处理
        }
    }
    // 右键按下
    else if (wParam == WM_RBUTTONDOWN) {
        // 左上角
        if (info->pt.x < 9 && info->pt.y < 67) {
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LCONTROL;
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = 'F';
            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << L"SendInput failed:" << std::endl;
            }
            rDown = true;
            return 1;
        }
        // 右上角 X按钮的宽,chrome tab的下边界66以上
        else if (info->pt.x > 5028 && info->pt.y < 67) {
            INPUT inputs[2] = {};
            ZeroMemory(inputs, sizeof(inputs));
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_F12;
            inputs[1] = inputs[0];
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << L"SendInput failed:" << std::endl;
            }
            rDown = true;
            return 1;
        }
    }
    //
    else if (wParam == WM_RBUTTONUP && rDown) {
        rDown = false;
        return 1;
    }
    //
    else if (wParam == WM_MBUTTONDOWN) {
        // 左上角
        if (info->pt.x < 9 && info->pt.y < 67) {
            INPUT inputs[6] = {};
            ZeroMemory(inputs, sizeof(inputs));
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LCONTROL;
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = VK_LSHIFT;
            inputs[2].type = INPUT_KEYBOARD;
            inputs[2].ki.wVk = 'T';
            inputs[3] = inputs[2];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[4] = inputs[1];
            inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[5] = inputs[0];
            inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << L"SendInput failed:" << std::endl;
            }
            mDown = true;
            return 1;
        }
        // 右上角 X按钮的宽,chrome tab的下边界66以上
        else if (info->pt.x > 5028 && info->pt.y < 67) {
            INPUT inputs[2] = {};
            ZeroMemory(inputs, sizeof(inputs));
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_F5;
            inputs[1] = inputs[0];
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << L"SendInput failed:" << std::endl;
            }
            mDown = true;
            return 1;
        }
        // 上,chrome tab的下边界66以上
        else if (info->pt.y < 67) {
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LCONTROL;
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = 'W';
            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << L"SendInput failed:" << std::endl;
            }
            mDown = true;
            return 1;
        }
        // 左下角win按钮区域
        else if (info->pt.x < 95 && info->pt.y > 2807) {
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LMENU;
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = VK_TAB;
            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << L"SendInput failed:" << std::endl;
            }
            mDown = true;
            return 1;
        }
    }
    //
    else if (wParam == WM_MBUTTONUP && mDown) {
        mDown = false;
        return 1;
    }
    // x1 x2键 按下
    else if (wParam == WM_XBUTTONDOWN) {
        // 中右
        if (info->pt.x > 94) {
            if (HIWORD(info->mouseData) == 1) {
                INPUT inputs[4] = {};
                ZeroMemory(inputs, sizeof(inputs));
                inputs[0].type = INPUT_KEYBOARD;
                inputs[0].ki.wVk = VK_LCONTROL;
                inputs[1].type = INPUT_KEYBOARD;
                inputs[1].ki.wVk = 'T';
                inputs[2] = inputs[1];
                inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
                inputs[3] = inputs[0];
                inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
                UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                if (uSent != ARRAYSIZE(inputs)) {
                    std::cout << L"SendInput failed:" << std::endl;
                }
            } else if (HIWORD(info->mouseData) == 2) {
                INPUT inputs[2] = {};
                ZeroMemory(inputs, sizeof(inputs));
                inputs[0].type = INPUT_KEYBOARD;
                inputs[0].ki.wVk = VK_F11;
                inputs[1] = inputs[0];
                inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
                UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                if (uSent != ARRAYSIZE(inputs)) {
                    std::cout << L"SendInput failed:" << std::endl;
                }
            }
            xDown = true;
            return 1;
        }
        // 左下角win按钮区域
        else if (info->pt.y > 2807) {
            if (HIWORD(info->mouseData) == 1) {
                INPUT inputs[4] = {};
                ZeroMemory(inputs, sizeof(inputs));
                inputs[0].type = INPUT_KEYBOARD;
                inputs[0].ki.wVk = VK_LCONTROL;
                inputs[1].type = INPUT_KEYBOARD;
                inputs[1].ki.wVk = 'Z';
                inputs[2] = inputs[1];
                inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
                inputs[3] = inputs[0];
                inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
                UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                if (uSent != ARRAYSIZE(inputs)) {
                    std::cout << L"SendInput failed:" << std::endl;
                }
            } else if (HIWORD(info->mouseData) == 2) {
                INPUT inputs[4] = {};
                ZeroMemory(inputs, sizeof(inputs));
                inputs[0].type = INPUT_KEYBOARD;
                inputs[0].ki.wVk = VK_LCONTROL;
                inputs[1].type = INPUT_KEYBOARD;
                inputs[1].ki.wVk = 'Y';
                inputs[2] = inputs[1];
                inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
                inputs[3] = inputs[0];
                inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
                UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                if (uSent != ARRAYSIZE(inputs)) {
                    std::cout << L"SendInput failed:" << std::endl;
                }
            }
            xDown = true;
            return 1;
        }
        // 左边94宽,y为chrome tab的下边界66以下到2807
        else if (info->pt.y > 66) {
            if (HIWORD(info->mouseData) == 1) {
                INPUT inputs[4] = {};
                ZeroMemory(inputs, sizeof(inputs));
                inputs[0].type = INPUT_KEYBOARD;
                inputs[0].ki.wVk = VK_LCONTROL;
                inputs[1].type = INPUT_KEYBOARD;
                inputs[1].ki.wVk = 'H';
                inputs[2] = inputs[1];
                inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
                inputs[3] = inputs[0];
                inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
                UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                if (uSent != ARRAYSIZE(inputs)) {
                    std::cout << L"SendInput failed:" << std::endl;
                }
            } else if (HIWORD(info->mouseData) == 2) {
                INPUT inputs[6] = {};
                ZeroMemory(inputs, sizeof(inputs));
                inputs[0].type = INPUT_KEYBOARD;
                inputs[0].ki.wVk = VK_LCONTROL;
                inputs[1].type = INPUT_KEYBOARD;
                inputs[1].ki.wVk = VK_LSHIFT;
                inputs[2].type = INPUT_KEYBOARD;
                inputs[2].ki.wVk = 'O';
                inputs[3] = inputs[2];
                inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
                inputs[4] = inputs[1];
                inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;
                inputs[5] = inputs[0];
                inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
                UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                if (uSent != ARRAYSIZE(inputs)) {
                    std::cout << L"SendInput failed:" << std::endl;
                }
            }
            xDown = true;
            return 1;
        }
    }
    // x1 x2键 松开,并且之前的按下被拦截
    else if (wParam == WM_XBUTTONUP && xDown) {
        xDown = false;
        return 1;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
HHOOK hook = NULL;
BOOL WINAPI ctrl_handler(DWORD dwCtrlType) {
    if (hook) {
        UnhookWindowsHookEx(hook);
        hook = NULL;  // ctrl_handler might be called multiple times
        return TRUE;
    }
    std::cout << hook << "......Why......Bye...2S" << std::endl;
    Sleep(2000);
    return TRUE;
}
int main() {
    SetConsoleCtrlHandler(ctrl_handler, TRUE);
    hook = SetWindowsHookExW(WH_MOUSE_LL, MouseHookProc, nullptr, 0);
    if (!hook) {
        std::cerr << "SetWindowsHookExW() failed. Bye :(\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "Hook set: " << hook << '\n';
    GetMessageW(nullptr, nullptr, 0, 0);
}
