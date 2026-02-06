@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

::Engilsh text which inludes the searching text
%PROGRAM% "EugeneOnegin.txt" "I write to you" > %OUT% || goto err
fc %OUT% EugeneOnegin-out.txt || goto err

::Engilsh text which doesn't inlude the searching text
%PROGRAM% "Quote.txt" "Can I write to you" > %OUT% || goto err
fc %OUT% Quote-out.txt || goto err

::Russian text which includes the searching text
%PROGRAM% "RussianQuote.txt" "жизнь" > %OUT% || goto err
fc %OUT% RussianQuote-out.txt || goto err


echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1