@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

::Invert matrix 3x3 with determinant != 0
%PROGRAM% "Matrix1.txt" > %OUT% || goto err
fc %OUT% Matrix1-out.txt || goto err

::Help menu
%PROGRAM% "-h" > %OUT% || goto err
fc %OUT% HelpMenu-out.txt || goto err

::Matrix 3x2
%PROGRAM% "Matrix3x2.txt" > %OUT% || goto err
fc %OUT% Matrix3x2-out.txt || goto err

::The Identity Matrix
%PROGRAM% "TheIdentityMatrix.txt" > %OUT% || goto err
fc %OUT% TheIdentityMatrix-out.txt || goto err

::Without arguments
(echo 1 2 3 & echo 4 5 6 & echo 7 9 9) | %PROGRAM% > %OUT% || goto err
fc %OUT% MatrixWithoutArguments-out.txt || goto err

::Matrix 3x3 with non number arguments
%PROGRAM% "MatrixNan.txt" > %OUT% || goto err
fc %OUT% MatrixNan-out.txt || goto err

::Empty file
%PROGRAM% "Empty.txt" > %OUT% || goto err
fc %OUT% Empty-out.txt || goto err

::Invert the matrix 3x3 with the determinant = 0 and separator in a form of space(not a tab, as usual)
%PROGRAM% "MatrixWithZeroDeterminant.txt" > %OUT% || goto err
fc %OUT% MatrixWithZeroDeterminant-out.txt || goto err

::Doesn't existing file
%PROGRAM% "Empt.txt" > %OUT% || echo Test passed 0

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1