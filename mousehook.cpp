#include <iostream>
#include <type_traits>  // std::make_signed_t<>

#include <windows.h>
#include <chrono>
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
        int zDelta = GET_WHEEL_DELTA_WPARAM(((MSLLHOOKSTRUCT*)lParam)->mouseData);
        // std::cout << zDelta << std::endl;
        // 左上角
        if (info->pt.x < 150 && info->pt.y < 150) {
            // 旧的方法
            // auto start = std::chrono::high_resolution_clock::now();
            // INPUT input = {0};
            // input.type = INPUT_KEYBOARD;
            // if (zDelta == 120)
            //     input.ki.wVk = VK_VOLUME_UP;
            // else if (zDelta == -120)
            //     input.ki.wVk = VK_VOLUME_DOWN;
            // SendInput(1, &input, sizeof(INPUT));
            // auto end = std::chrono::high_resolution_clock::now();
            // std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

            INPUT inputs[1] = {};
            ZeroMemory(inputs, sizeof(inputs));

            inputs[0].type = INPUT_KEYBOARD;
            if (zDelta == 120)
                inputs[0].ki.wVk = VK_VOLUME_UP;
            else if (zDelta == -120)
                inputs[0].ki.wVk = VK_VOLUME_DOWN;

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << L"SendInput failed:"
                          << std::endl;
            }
            return 1;  // 返回 1，表示事件已经被处理
        }
        // 右上角
        else if (info->pt.x > 5013 && info->pt.y < 150) {
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
                std::cout << L"SendInput failed:"
                          << std::endl;
            }
            return 1;  // 返回 1，表示事件已经被处理
        }
        // 上
        else if (info->pt.y < 150) {
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
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            return 1;  // 返回 1，表示事件已经被处理
        }
    }

    else if (wParam == WM_RBUTTONDOWN) {
        // 左上角
        if (info->pt.x < 9 && info->pt.y < 9) {
            rDown = true;
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));

            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LSHIFT;
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = VK_F5;
            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            return 1;
        }
        // 左中
        else if (info->pt.x < 9 && info->pt.y < 2800) {
            rDown = true;
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));

            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LCONTROL;
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = 'X';
            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            return 1;
        }
        // 右上角 X按钮
        else if (info->pt.x > 5028 && info->pt.y < 56) {
            rDown = true;
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));

            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LCONTROL;
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = 'V';
            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            return 1;
        }
    }

    else if (wParam == WM_RBUTTONUP && rDown) {
        rDown = false;
        return 1;
    }

    else if (wParam == WM_MBUTTONDOWN) {
        // 右上角 X按钮
        if (info->pt.x > 5028 && info->pt.y < 56) {
            mDown = true;
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
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            return 1;
        }
        // // 右下角
        // else if (info->pt.x > 5111 && info->pt.y > 2800) {
        //     mDown = true;
        //     INPUT inputs[4] = {};
        //     ZeroMemory(inputs, sizeof(inputs));

        //     inputs[0].type = INPUT_KEYBOARD;
        //     inputs[0].ki.wVk = VK_LCONTROL;
        //     inputs[1].type = INPUT_KEYBOARD;
        //     inputs[1].ki.wVk = 'S';
        //     inputs[2] = inputs[1];
        //     inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
        //     inputs[3] = inputs[0];
        //     inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

        //     UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        //     if (uSent != ARRAYSIZE(inputs)) {
        //         std::cout << "SendInput failed:"
        //                   << std::endl;
        //     }
        //     return 1;
        // }
        // 左下角
        else if (info->pt.x < 9 && info->pt.y > 2800) {
            mDown = true;
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
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            return 1;
        }
        // 左中
        else if (info->pt.x < 9 && info->pt.y > 66) {
            mDown = true;
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));

            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LCONTROL;
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = 'D';
            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            return 1;
        }
    }

    else if (wParam == WM_MBUTTONUP && mDown) {
        mDown = false;
        return 1;
    }

    else if (wParam == WM_XBUTTONDOWN) {
        // 右上角 X按钮
        if (info->pt.x > 5028 && info->pt.y < 56) {
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));

            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LCONTROL;

            inputs[1].type = INPUT_KEYBOARD;
            if (HIWORD(info->mouseData) == 1)
                inputs[1].ki.wVk = 'C';
            else if (HIWORD(info->mouseData) == 2)
                inputs[1].ki.wVk = 'F';

            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            xDown = true;
            return 1;
        }
        // 上
        else if (info->pt.x > 66 && info->pt.y < 66) {
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));

            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_LCONTROL;

            inputs[1].type = INPUT_KEYBOARD;
            if (HIWORD(info->mouseData) == 1)
                inputs[1].ki.wVk = 'T';
            else if (HIWORD(info->mouseData) == 2)
                inputs[1].ki.wVk = 'W';

            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            xDown = true;
            return 1;
        }
        // 左下角
        else if (info->pt.x < 95 && info->pt.y > 2809) {
            INPUT inputs[4] = {};
            ZeroMemory(inputs, sizeof(inputs));

            inputs[0].type = INPUT_KEYBOARD;
            inputs[1].type = INPUT_KEYBOARD;
            if (HIWORD(info->mouseData) == 1) {
                inputs[0].ki.wVk = VK_LMENU;
                inputs[1].ki.wVk = 'Q';
            } else if (HIWORD(info->mouseData) == 2) {
                inputs[0].ki.wVk = VK_LWIN;
                inputs[1].ki.wVk = VK_SNAPSHOT;
            }

            inputs[2] = inputs[1];
            inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
            inputs[3] = inputs[0];
            inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            xDown = true;
            return 1;
        }
        // 左
        else if (info->pt.x < 9 && info->pt.y > 66) {
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
                    std::cout << "SendInput failed:"
                              << std::endl;
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
                    std::cout << "SendInput failed:"
                              << std::endl;
                }
            }
            xDown = true;
            return 1;
        }
        // 中右下
        else if (info->pt.x > 66 || info->pt.y > 66) {
            INPUT inputs[2] = {};
            ZeroMemory(inputs, sizeof(inputs));

            inputs[0].type = INPUT_KEYBOARD;
            if (HIWORD(info->mouseData) == 1)
                inputs[0].ki.wVk = VK_F11;
            else if (HIWORD(info->mouseData) == 2)
                inputs[0].ki.wVk = VK_F12;

            inputs[1] = inputs[0];
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs)) {
                std::cout << "SendInput failed:"
                          << std::endl;
            }
            xDown = true;
            return 1;
        }
        // // 左上角66x66
        // else return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

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
        std::cout << hook << "............Bye" << std::endl;
        hook = NULL;  // ctrl_handler might be called multiple times
        std::cout << hook << "............Bye" << std::endl;
        // std::cin.get(); // gives the user 5 seconds to read our last output
        Sleep(2000);
    }

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
