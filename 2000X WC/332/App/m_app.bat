ECHO OFF
rem Batch file to create the application part of the 1000 series software
rem using PVCS version Manager and Configuration Builder
rem
rem     file name : m_app.bat
rem     Created 5/8/96 by Guy Vandevoordt
rem #####################################################################
ECHO ON
rem @call mappsos.bat
cd l:\pss\bsp\src
@call m_bsp
cd \332\app
c:\pvcs\cb\win95\build.exe -script make_app -Debug -directall debug.txt


