#include <Windows.h>
#include <iostream>

#define BUTTON_CLICK 1

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void encode_func(char *, int, char *);


void AddControls(HWND);

HWND hName;
HWND hPass;
HWND hResult;
HWND hButton;
HICON hIcon;
int music_wav;
HDC hEdit;
int hIdent;
HBRUSH hbr;

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    WNDCLASSA wc = {0};

    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = GetModuleHandleA(0);
    wc.lpszClassName = "myWindowClass";
    wc.lpfnWndProc = WindowProcedure;
    wc.hIcon = static_cast<HICON>(LoadImage(GetModuleHandleA(0), MAKEINTRESOURCE(1336), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));
    wc.hbrBackground = CreateSolidBrush(RGB(255, 242, 204));

    if (!RegisterClassA(&wc)) {
        DWORD dw = GetLastError();
        //std::cout << dw << std::endl;
        return -1;
    }
    
    CreateWindowA("myWindowClass", "Crackme", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, 
                    NULL, NULL, NULL);
    
    MSG msg = {0};
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    } 
    
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:
            switch (wParam) {
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
            music_wav = PlaySound(MAKEINTRESOURCE(1556), GetModuleHandleA(NULL), SND_LOOP | SND_RESOURCE | SND_ASYNC);
            //hIcon = LoadIcon(NULL, IDI_SHIELD); 
            SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            AddControls(hWnd);

            //hBGcolor = GetDC(hWnd);
            //tst = SetBkColor(hBGcolor, RGB(0, 0, 0));

            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcA(hWnd, msg, wParam, lParam);
    }
    return 0;
}

void AddControls(HWND hWnd) {

    CreateWindowA("testclass", "My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL,
        NULL, NULL, NULL);


    CreateWindowA("Static", "Enter you name here: ", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 95, 100, 45,
                    hWnd, NULL, NULL, NULL);
    hName = CreateWindowA("Edit", "...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 120, 100, 100, 25,
                    hWnd, NULL, NULL, NULL);

    CreateWindowA("Static", "Enter you pass here: ", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 145, 100, 40,
                    hWnd, NULL, NULL, NULL);
    hPass = CreateWindowA("Edit", "...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 120, 150, 100, 25,
                    hWnd, NULL, NULL, NULL);


    hResult = CreateWindowA("Edit", "...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 120, 220, 300, 200,
                    hWnd, NULL, NULL, NULL);


    //BS_OWNERDRAW SS_NOTIFY
    //del BS_OWNERDRAW and button will work simplier
    hButton = CreateWindowA("Button", "Run", WS_VISIBLE | WS_CHILD, 10, 205, 100, 50,
                    hWnd, (HMENU)BUTTON_CLICK, NULL, NULL);
    
}

void encode_func(CHAR *name, int len, CHAR *out_array) {

    for (int i = 0; i < len; i++) {
        out_array[i] = (char)((int)name[i] + 1);
    }
}