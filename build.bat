IF NOT EXIST build (
    mkdir build
    ECHO Build directory created.
) ELSE (
    ECHO Build already exists.
)

REM Compile all .c files in src and src/backend directories
cl.exe /c src\*.c /Fo:build\
cl.exe /c src\backend\*.c /Fo:build\

REM Link object files to create catfourm.exe
cl.exe /Fe:build\catfourm.exe build\*.obj

REM ...existing code...
