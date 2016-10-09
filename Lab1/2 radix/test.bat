set PROGRAM="%~1"

rem Пустой source notation
set TEST_NUMBER=1
%PROGRAM% "" "16" 42 >NUL
if NOT ERRORLEVEL 1 goto err

rem Пустой destination notation
set TEST_NUMBER=2
%PROGRAM% 10 "" 42 >NUL
if NOT ERRORLEVEL 1 goto err

rem Пустой value
set TEST_NUMBER=3
%PROGRAM% 10 16 >NUL
if NOT ERRORLEVEL 1 goto err

rem Нижняя граница notation
set TEST_NUMBER=4
%PROGRAM% 1 16 0 >NUL
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 2 16 0101 >NUL
if ERRORLEVEL 1 goto err

%PROGRAM% 10 1 0 >NUL
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 10 2 0101 >NUL
if ERRORLEVEL 1 goto err

rem Верхняя граница notation
set TEST_NUMBER=5
%PROGRAM% 37 10 42 >NUL
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 36 10 42 >NUL
if ERRORLEVEL 1 goto err

%PROGRAM% 10 37 42 >NUL
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 10 36 42 >NUL
if ERRORLEVEL 1 goto err

rem Нулевое значение
set TEST_NUMBER=6
%PROGRAM% 10 16 0 >"%TEMP%\Empty.txt"
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\Empty.txt" "test\Empty.txt" >NUL
if ERRORLEVEL 1 goto err

rem Отрицательное значение
set TEST_NUMBER=7
%PROGRAM% 15 35 "-abda123" >"%TEMP%\Negative.txt"
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\Negative.txt" "test\Negative.txt" >NUL
if ERRORLEVEL 1 goto err

rem Положительное значение с унарным плюсом
set TEST_NUMBER=8
%PROGRAM% 15 35 "+abda123" >"%TEMP%\Positive.txt"
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\Positive.txt" "test\Positive.txt" >NUL
if ERRORLEVEL 1 goto err

rem Из большего основания в меньшее
set TEST_NUMBER=9
%PROGRAM% 36 2 "hEllO" >"%TEMP%\MaxToMin.txt"
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\MaxToMin.txt" "test\MaxToMin.txt" >NUL
if ERRORLEVEL 1 goto err

rem Из меньшего основания в большее
set TEST_NUMBER=10
%PROGRAM% 2 36 0101001111010110100000010100101 >"%TEMP%\MinToMax.txt"
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\MinToMax.txt" "test\MinToMax.txt" >NUL
if ERRORLEVEL 1 goto err

rem Из decimal основания
set TEST_NUMBER=11
%PROGRAM% 10 16 29397875 >"%TEMP%\Decimal.txt"
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\Decimal.txt" "test\Decimal.txt" >NUL
if ERRORLEVEL 1 goto err

rem Одно и то же основание
set TEST_NUMBER=12
%PROGRAM% 16 16 "DEADBEEF" >"%TEMP%\Same.txt"
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\Same.txt" "test\Same.txt" >NUL
if ERRORLEVEL 1 goto err

rem Значение не соответствует исходной системе счисления
set TEST_NUMBER=13
%PROGRAM% 8 16 18 >NUL
if NOT ERRORLEVEL 1 goto err

rem >INTMAX при чтении строки
set TEST_NUMBER=14
%PROGRAM% 10 16 2147483648 >NUL
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 10 16 2147483647 >NUL
if ERRORLEVEL 1 goto err

rem <INTMIN при чтении строки
set TEST_NUMBER=15
%PROGRAM% 10 10 -2147483649 >NUL
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 10 16 -2147483648 >NUL
if ERRORLEVEL 1 goto err

rem >INTMAX при конвертации
set TEST_NUMBER=16
%PROGRAM% 36 16 "HELLOYESTHISISDOG" >NUL
if NOT ERRORLEVEL 1 goto err

:ok
echo Testing SUCCEED
exit 0

:err
echo Testing FAILED at %TEST_NUMBER% testcase
exit 1