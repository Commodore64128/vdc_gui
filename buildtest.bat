set TARGET=c128
set LIBRARY=c128.lib

set CSRC=test.c
set ASRC=test.s
set OBJECT=test.o
set OUTPUT=test.prg

set COMPILER=cc65
set ASSEMBLER=ca65
set LINKER=ld65

del %ASRC%
del %OBJECT%
del %OUTPUT%

%COMPILER% %CSRC% -t %TARGET% -I .\include\  -o %ASRC%
%ASSEMBLER% %ASRC% -t %TARGET% -I .\include\  -o %OBJECT%
%LINKER% -t %TARGET% -L .\lib\  %OBJECT% vdc_gui.lib %LIBRARY% -o %OUTPUT%

del %ASRC%
del %OBJECT%
