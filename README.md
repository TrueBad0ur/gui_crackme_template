# gui_crackme_template
Simple WinAPI GUI template for crackmes

<h2>About</h2>

Every time I want to create a GUI crackme I have to recreate all these long templates of WinAPI calls.<br>
So, I decided to create a simple template for it where you just need to change encode function.<br>

<i>Enjoy</i>

<h2>How to use</h2>

<h4>MinGW way:</h4>

```bash
icon:
windres.exe .\rscs\icon.rc -o .\rscs\icon.rs

executable:
g++.exe .\main.cpp .\rscs\icon.rs -o .\main -mwindows -static
.\main.exe
```


<h4>Microsoft way:</h4>

```bash
rc.exe .\rscs\icon.rc
cl.exe .\test.cpp /link .\rscs\icon.res User32.lib
```
