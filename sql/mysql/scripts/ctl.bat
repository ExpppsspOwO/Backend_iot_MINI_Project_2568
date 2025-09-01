@echo off
rem START or STOP Services
rem ----------------------------------
rem Check if argument is STOP or START

if not ""%1"" == ""START"" goto stop


"D:\iot_byoak_js\sql\mysql\bin\mysqld" --defaults-file="D:\iot_byoak_js\sql\mysql\bin\my.ini" --standalone
if errorlevel 1 goto error
goto finish

:stop
cmd.exe /C start "" /MIN call "D:\iot_byoak_js\sql\killprocess.bat" "mysqld.exe"

if not exist "D:\iot_byoak_js\sql\mysql\data\%computername%.pid" goto finish
echo Delete %computername%.pid ...
del "D:\iot_byoak_js\sql\mysql\data\%computername%.pid"
goto finish


:error
echo MySQL could not be started

:finish
exit
