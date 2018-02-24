python ./pyToExe.py py2exe
copy config.json ..\exeFile
xcopy template ..\exeFile\template /e
pause
