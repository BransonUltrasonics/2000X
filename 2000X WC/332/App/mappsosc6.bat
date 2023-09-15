
echo  Drive %1:\ will be used for source files.


set PSS_ROOT=%1:\pss
set DRIVE=%1
md %DRIVE%:\332
md %DRIVE%:\332\app
md %DRIVE%:\332\inc
md %DRIVE%:\temp
md %PSS_ROOT%
md %PSS_ROOT%\bsp
md %PSS_ROOT%\bsp\src
md %PSS_ROOT%\configs
md %PSS_ROOT%\configs\std
md %PSS_ROOT%\include
md %PSS_ROOT%\sys
md %PSS_ROOT%\sys\libc
md %PSS_ROOT%\sys\os

rem set LABEL=-
set DOTEST=xq
set PERSONAL_DIR=%DRIVE%:/332/inc
set PSS_BSP=%PSS_ROOT%/bsp
rem PATH=%PATH%;d:\SWLab\pvcs\nt;d:\SWLab\pvcs\cb\nt
set TEMP=%DRIVE%:\temp
set TMP=%DRIVE%:\temp
set TMPDIR=%DRIVE%:\temp


echo  To compile type "m_appc6 %DRIVE% 'label'"
echo  where 'label' is the version label you checked out.
