@echo off
copy 698SP_CL.exe .\dist\
ROBOCOPY attach .\dist\EXE\attach  /E
ROBOCOPY Data .\dist\EXE\Data  /E
copy config.xml .\dist\EXE\ 
cd dist
CALL windeployqt 698SP_CL.exe -release
pause