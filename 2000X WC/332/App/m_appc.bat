ECHO OFF
rem Batch file to create the application part of the 1000 series software
rem using PVCS version Manager and Configuration Builder
rem
rem     file name : m_app.bat
rem     Created 5/8/96 by Guy Vandevoordt
rem    updated for citrix 2
rem #####################################################################
ECHO ON
cd l:\pss\bsp\src
@call m_bspc
cd \332\app
c:\progra~1\pvcs\cb\nt\build.exe -script make_app 

rem this is for 2-flash build
c:\progra~1\estii\convert rom.elf -a %label%-1.bin -l 0x000000 -u 0x0FFFFF
