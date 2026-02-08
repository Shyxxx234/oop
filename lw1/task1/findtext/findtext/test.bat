@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

::Engilsh text which includes the searching text at the begining
%PROGRAM% "EugeneOnegin.txt" "I write to you" > %OUT% || goto err
fc %OUT% EugeneOnegin-out.txt || goto err

::Engilsh text which doesn't include the searching text
%PROGRAM% "Quote.txt" "Can I write to you" > %OUT% || goto err
fc %OUT% Quote-out.txt || goto err

::Russian text which includes the searching text
%PROGRAM% "RussianQuote.txt" "жизнь" > %OUT% || goto err
fc %OUT% RussianQuote-out.txt || goto err

::Russian text which includes the searching text at the end
%PROGRAM% "RussianQuote.txt" "жизни" > %OUT% || goto err
fc %OUT% RussianQuote-out2.txt || goto err

::Russian text which includes the searching text with several entries
%PROGRAM% "RussianQuoteSeveralEntries.txt" "жизнь" > %OUT% || goto err
fc %OUT% RussianQuoteSeveralEntries-out.txt || goto err

::Russian text which includes the searching text with several entries in one line
%PROGRAM% "RussianQuoteSeveralEntriesInOneLine.txt" "жизнь" > %OUT% || goto err
fc %OUT% RussianQuoteSeveralEntriesInOneLine-out.txt || goto err

::Empty filename
%PROGRAM% "" "жизнь" > %OUT% || echo Test passed

::Empty search text
%PROGRAM% "RussianQuote.txt" "" > %OUT% || echo Test passed

::Too many arguments
%PROGRAM% "RussianQuote.txt" "Hello" "What?" > %OUT% || echo Test passed

::Too few arguments
%PROGRAM% "RussianQuote.txt" > %OUT% || echo Test passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
