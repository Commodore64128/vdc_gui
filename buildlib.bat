SETLOCAL ENABLEDELAYEDEXPANSION

set TARGET=c128
set OBJECT=vdc_gui.o
set LIBRARY=c128.lib
set OUTLIB=vdc_gui.lib

set COMPILER=cc65
set ASSEMBLER=ca65
set LINKER=ld65

del .\obj\*.o
del .\obj\*.sc
del .\obj\*.map
del .\obj\*.lbl

cd src

REM: Compile each .C file into assembler.
for /f %%a IN ('dir /b *.c') do %COMPILER% -g -O -I J:\Software\Emulation\Commodore\Development\cc65\include -t %TARGET% %%a -o ..\obj\%%~na.s

cd ..\obj

REM: Assemble each .S file an object file.
for /f %%a IN ('dir /b *.s') do %ASSEMBLER% %%a
for /f %%a IN ('dir /b *.s') do %ASSEMBLER% -t %TARGET% %%a -o %%~na.o

REM: Link all the .O files together
REM: set FILES=
REM: for /f %%a IN ('dir /b *.o') do set FILES=!FILES! %%a
REM: %LINKER% -t %TARGET% -Ln output.lbl -m output.map -o  %OBJECT% %FILES% %LIBRARY%

REM: Create a library
set FILES=
for /f %%a IN ('dir /b *.o') do set FILES=!FILES! %%a
ar65 r  %OUTLIB% %FILES%

REM: Clean up
cd ..
del .\lib\%OBJECT%
del .\include\*.h

copy .\obj\%OUTLIB% .\lib\
copy .\src\*.h .\include\*.h
