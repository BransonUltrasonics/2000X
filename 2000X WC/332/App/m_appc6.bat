ECHO OFF
rem Batch file to create the application part of the 2000X series software
rem using PVCS version Manager and Configuration Builder
rem
rem     file name : m_appc6.bat
rem     Created 5/8/96 by Guy Vandevoordt
rem     Modified 12/1/10 by BEKymer
rem
rem    1) Modified to run on Citrix 5 when the version manager
rem       archive is on Citrix 6.
rem    2) This will call make_appc6 which has been modified to only
rem       compile and not 'get' any files.
rem    3) To use this file you must manually 'get' ALL the files needed
rem       to do a full compile.
rem
rem
rem
rem
rem
rem #####################################################################
ECHO ON

set LABEL=%2

cd %1:\pss\bsp\src

rem This used to call m_bspc.bat.  It only executed one line.
rem @call m_bspc
rem That line is now included here.

c:\progra~1\pvcs\cb\nt\build.exe -script make_bspc6 


cd %1:\332\app
c:\progra~1\pvcs\cb\nt\build.exe -script make_appc6 

rem this is for 2-flash build
c:\progra~1\estii\convert rom.elf -a %label%-1.bin -l 0x000000 -u 0x0FFFFF
