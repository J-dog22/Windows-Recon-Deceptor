@ECHO OFF
REM This batch script will modify the Image File Execution Options registry keys to intercept the execution of a program.
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\Net.exe" /v Debugger /d "C:\Users\IEUser\Desktop\repos\Net\x64\Debug\Deceptive_Net.exe" /f
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\whoami.exe" /v Debugger /d "C:\Users\IEUser\Desktop\repos\whoami\x64\Debug\Deceptive_whoami.exe" /f
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\ipconfig.exe" /v Debugger /d "C:\Users\IEUser\Desktop\repos\ipconfig\x64\Debug\Deceptive_ipconfig.exe" /f
Echo "Keys Modified!"
