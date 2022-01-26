#include <Windows.h>
#include <iostream>

#define BUTTON_CLICK 1

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void encode_func(char *, int, char *);


void AddControls(HWND);

HWND hName;
HWND hPass;
HWND hResult;
HICON hIcon;


int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    WNDCLASSA wc = {0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = GetModuleHandleA(0);
    wc.lpszClassName = "myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassA(&wc)) {
        DWORD dw = GetLastError();
        //std::cout << dw << std::endl;
        return -1;
    }
    
    CreateWindowA("myWindowClass", "My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, 
                    NULL, NULL, NULL);
    
    MSG msg = {0};
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    } 
    
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND:
            switch (wp) {
                case BUTTON_CLICK:
                    int name_len = GetWindowTextLengthA(hName);
                    int pass_len = GetWindowTextLengthA(hPass);
                    if (name_len != pass_len) {
                        SetWindowTextA(hResult, "name and pass should have the same length");
                        break;
                    }
                    char *name = new char[name_len];
                    char *pass = new char[name_len];
                    GetWindowTextA(hName, name, name_len+1);
                    GetWindowTextA(hPass, pass, name_len+1);

                    char *result = new char[name_len];
                    encode_func(name, name_len, result);
                    if (!strncmp(result, pass, name_len)) {
                        SetWindowTextA(hResult, "Well, you win!");
                    } else {
                        SetWindowTextA(hResult, "Nope, you lose!");
                    }
                    break;

            }
            break;
        case WM_CREATE:
            hIcon = LoadIcon(NULL, IDI_SHIELD); 
            SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            AddControls(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcA(hWnd, msg, wp, lp);
    }
    return 0;
}

void AddControls(HWND hWnd) {
    CreateWindowA("Static", "Enter you name here: ", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 100, 100, 50, 
                    hWnd, NULL, NULL, NULL);
    hName = CreateWindowA("Edit", "...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 120, 100, 100, 25,
                    hWnd, NULL, NULL, NULL);

    CreateWindowA("Static", "Enter you pass here: ", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 150, 100, 50, 
                    hWnd, NULL, NULL, NULL);
    hPass = CreateWindowA("Edit", "...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 120, 150, 100, 25,
                    hWnd, NULL, NULL, NULL);


    hResult = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY, 120, 220, 300, 200, 
                    hWnd, NULL, NULL, NULL);



    CreateWindowA("Button", "Run", WS_VISIBLE | WS_CHILD, 10, 205, 100, 50,
                    hWnd, (HMENU)BUTTON_CLICK, NULL, NULL);
    
}

void encode_func(CHAR *name, int len, CHAR *out_array) {

    for (int i = 0; i < len; i++) {
        out_array[i] = (char)((int)name[i] + 1);
    }
}