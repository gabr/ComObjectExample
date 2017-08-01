@echo off

REM set up environment
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\vcvars32.bat"

REM create necessary folders
if not exist ".\bin" mkdir ".\bin"

REM set path to compiler
set compiler="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\cl.exe"

REM compile
%compiler% src\*.c             ^
           /nologo             ^
           /Fo: .\bin\         ^
           /Fe: .\bin\main.exe ^
           /Fd: .\bin\         ^
           /EHsc               ^
           /W4                 ^
           /WX                 ^
           /Zi

REM arguments explanation:
REM /Fo   - output path for .obj files
REM /Fe   - output path for .exe files
REM /Fd   - output path for .pdb files
REM /EHsc - turns on automatic exception handling (compiler is angry if not set)
REM # /Wall - shows ALL ALL warnings
REM /Wn   - show level n warnings
REM /WX   - turns warnings into errors
REM /Zi   - additional informations for compiler

if NOT ERRORLEVEL 1 (
    .\bin\main.exe
)

