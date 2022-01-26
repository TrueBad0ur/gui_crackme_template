#include <Windows.h>
#include <iostream>
#include <string.h>

int main() {

    HRSRC hr;
    HGLOBAL hrd;
    CHAR buff[100];

    hr = FindResource(NULL, MAKEINTRESOURCE(3333), RT_RCDATA);
    //MessageBoxA(NULL, (LPCSTR)hr, (LPCSTR)hr, NULL);
    hrd = LoadResource(NULL, hr);
    int _size = SizeofResource(GetModuleHandleA(NULL), (HRSRC)hrd);

    strcpy(buff, (const char*)hrd);

    if (_size > 0)
        MessageBoxA(NULL, (LPCSTR)"Success", (LPCSTR)"Success", NULL);
    else
        MessageBoxA(NULL, (LPCSTR)"Fail", (LPCSTR)"Fail", NULL);

    return 0;
}