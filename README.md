# gui_crackme_template
Simple WinAPI GUI template for crackmes

<h2>About</h2>

Every time I want to create a GUI crackme I have to recreate all these long templates of WinAPI calls.<br>
So, I decided to create a simple template for it where you just need to change encode function.<br>

<i>Enjoy</i>

<h2>How to use</h2>

```bash
icon:
windres.exe .\icon.rc -o .\icon.rs

executable:
g++.exe .\main.cpp .\rscs\icon.rs -o .\main -mwindows -static
.\main.exe
```
