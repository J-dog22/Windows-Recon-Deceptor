@ECHO OFF
REM This batch script will restore the Image File Execution Options registry keys that intercept the execution of a program.
reg delete "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\Net.exe" /f
reg delete "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\whoami.exe" /f
reg delete "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\ipconfig.exe" /f
Echo "Original Keys Restored!"