@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

::Convert 10111 from 2-notation to 10-notation
%PROGRAM% 2 10 "10111" > %OUT% || goto err
fc %OUT% 2To10For10111-out.txt || goto err

::Convert 23 from 10-notation to 2-notation
%PROGRAM% 10 2 "23" > %OUT% || goto err
fc %OUT% 10To2For23-out.txt || goto err

::Convert -23 from 10-notation to 2-notation
%PROGRAM% 10 2 "-23" > %OUT% || goto err
fc %OUT% 10To2For-23-out.txt || goto err

::Convert 1F from 16-notation to 10-notation
%PROGRAM% 16 10 "1F" > %OUT% || goto err
fc %OUT% 16To10For1F-out.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1