@echo off
set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"
set TEMP_INPUT="%TEMP%\input.txt"

::Normal test
%PROGRAM% "test1.txt" "test1-out.txt" > %OUT% || goto err
fc test1-out.txt test1-answer.txt || goto err

::Full filling
%PROGRAM% "full.txt" "full-out.txt" > %OUT% || goto err
fc full-out.txt full-answer.txt || goto err

%PROGRAM% "test2.txt" "test2-out.txt" > %OUT% || goto err
fc test2-out.txt test2-answer.txt || goto err

%PROGRAM% "test4.txt" "test4-out.txt" > %OUT% || goto err
fc test4-out.txt test4-answer.txt || goto err

::Help
%PROGRAM% -h > %OUT% || goto err

::File redirection
%PROGRAM% < test1.txt > test-stdin1.txt || goto err
fc test-stdin1.txt test1-answer.txt || goto err
echo STDIN Test 1: PASS

(
echo ###############
echo ########     #####
echo   ######          ####
echo #####      O     ####
echo ####################
) > test-input3.txt

type test-input3.txt | %PROGRAM% > test-stdin3.txt
if %errorlevel% neq 0 (
    echo ERROR: Program returned error code %errorlevel%
    goto err
)

(
echo ###############
echo ########.....#####
echo   ######..........####
echo #####......O.....####
echo ####################
) > test-expected3.txt

fc /b test-stdin3.txt test-expected3.txt

comp /M test-stdin3.txt test-expected3.txt


if %errorlevel% equ 0 (
    echo.
    echo STDIN Test 2: PASS
) else (
    echo.
    echo STDIN Test 2: FAILED
    goto err
)

::Without start points
(
echo ####
echo #  #
echo #  #
echo ####
) | %PROGRAM% > test4-stdin.txt

find "ERROR" test4-stdin.txt > nul
if %errorlevel% equ 0 goto err
echo STDIN Test 3: PASS

::Too big image
(
echo #####################################################################################################
echo O
) | %PROGRAM% > test5-stdin.txt || echo STDIN Test 4: PASS

::Dont need to feel

echo All tests passed!
exit /B 0

:err
echo
echo Program testing failed
exit /B 1