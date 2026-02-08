@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

::===================Positive======================

::Convert 10111 from 2-notation to 10-notation
%PROGRAM% 2 10 "10111" > %OUT% || goto err
fc %OUT% 2To10For10111-out.txt || goto err

::Convert 23 from 10-notation to 2-notation
%PROGRAM% 10 2 "23" > %OUT% || goto err
fc %OUT% 10To2For23-out.txt || goto err

::Convert +23 from 10-notation to 2-notation
%PROGRAM% 10 2 "+23" > %OUT% || goto err
fc %OUT% 10To2For23-out.txt || goto err

::Convert -23 from 10-notation to 2-notation
%PROGRAM% 10 2 "-23" > %OUT% || goto err
fc %OUT% 10To2For-23-out.txt || goto err

::Convert 1F from 16-notation to 10-notation
%PROGRAM% 16 10 "1F" > %OUT% || goto err
fc %OUT% 16To10For1F-out.txt || goto err

::Convert  2 147 483 647 from 10-notation to 2-notation
%PROGRAM% 10 2 "2147483647" > %OUT% || goto err
fc %OUT% 10To2ForMaxInt-out.txt || goto err

::Convert  -2 147 483 647 from 10-notation to 2-notation
%PROGRAM% 10 2 "-2147483647" > %OUT% || goto err
fc %OUT% 10To2ForMinInt-out.txt || goto err

::Convert Z from 36-notation to 2-notation
%PROGRAM% 36 2 "Z" > %OUT% || goto err
fc %OUT% 36To2ForZ-out.txt || goto err

::Convert 100011 from 2-notation to 36-notation
%PROGRAM% 2 36 "100011" > %OUT% || goto err
fc %OUT% 2To36For100011-out.txt || goto err

::===================Negative======================

::Empty input radixs
%PROGRAM% 2 "" "100011" > %OUT% || echo Test passed 0

::Too few arguments
%PROGRAM% 2 "100011" > %OUT% || echo Test passed 1

::Too many arguments
%PROGRAM% 2 "100011" 2 4 2 > %OUT% || echo Test passed 2

::Radix overflow
%PROGRAM% 2 40 "100011" > %OUT% || echo Test passed 3

::Radix underflow
%PROGRAM% 1 35 "100011" > %OUT% || echo Test passed 4

::Empty value
%PROGRAM% 2 10 "" > %OUT% || echo Test passed 5

::Uknown value
%PROGRAM% 2 10 "10?" > %OUT% || echo Test passed 6

::Value overflow
%PROGRAM% 10 2 "12345678910111213" > %OUT% || echo Test passed 7

::Value doesn't match with source radix
%PROGRAM% 2 10 "123" > %OUT% || echo Test passed 8

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1