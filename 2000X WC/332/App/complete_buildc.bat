rem Change over to Citrix 2 
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\app\m_appc.bav(L:\332\app\m_appc.bat)
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\app\make_app.__v(L:\332\app\make_app) 
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\os\libsys.a_v(%PSS_ROOT%\sys\os\libsys.a)
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\libc\libprepc.a_v(%PSS_ROOT%\sys\libc\libprepc.a)
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\std\config.mkv(%PSS_ROOT%\configs\std\config.mk9)
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\bsp\rom.lnv(%PSS_ROOT%\bsp\rom.lnk)
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\bsp\bsp.mkv(%PSS_ROOT%\bsp\bsp.mk)
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\bsp\src\m_bspc.bav(%PSS_ROOT%\bsp\src\m_bspc.bat)
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\bsp\src\make_bsp.__v(%PSS_ROOT%\bsp\src\make_bsp)

rem this is special for iotest332.* that doesn't get checked out otherwise
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\app\iotest332.c-arc(L:\332\app\iotest332.c)
get  -U -v%LABEL%  D:\swlab\vmdb\2000Series\inc\iotest332.h-arc(L:\332\inc\iotest332.h)

m_appc.bat     


