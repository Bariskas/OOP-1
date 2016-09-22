set PROGRAM="%~1"

rem Пустой параметр входного файла
set TEST_NUMBER=1
%PROGRAM% "" %TEMP%\output.txt "source" "target" >NUL
if NOT ERRORLEVEL 1 goto err

rem Пустой параметр выходного файла
set TEST_NUMBER=2
%PROGRAM% "test\test.txt" "" "source" "target" >NUL
if NOT ERRORLEVEL 1 goto err

rem Пустая параметр поиска подстроки
set TEST_NUMBER=3
%PROGRAM% "test\test.txt" %TEMP%\output.txt "" "target" >NUL
if NOT ERRORLEVEL 1 goto 

rem Несуществующий входной файл
set TEST_NUMBER=4
%PROGRAM% "notExist.txt" %TEMP%\output.txt "source" "target" >NUL
if NOT ERRORLEVEL 1 goto err

rem Ошибка записи файла
set TEST_NUMBER=5
%PROGRAM% "test\test.txt" %PROGRAM% "source" "target" >NUL
if NOT ERRORLEVEL 1 goto err

rem Пустой входной файл
set TEST_NUMBER=6
%PROGRAM% "test\empty.txt" %TEMP%\empty.txt "source" "target" >NUL
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\empty.txt" "test\empty.txt" >NUL
if ERRORLEVEL 1 goto err

rem Пустые строки в файле
set TEST_NUMBER=7
%PROGRAM% "test\empty_lines.txt" %TEMP%\empty_lines.txt "source" "target" >NUL
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\empty_lines.txt" "test\empty_lines_out.txt" >NUL
if ERRORLEVEL 1 goto err

rem Файл без искомой строки
set TEST_NUMBER=8
%PROGRAM% "test\test.txt" "%TEMP%\test.txt" "source" "target" >NUL
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\test.txt" "test\test.txt" >NUL
if ERRORLEVEL 1 goto err

rem Замена на пустую строку
set TEST_NUMBER=9
%PROGRAM% "test\test.txt" "%TEMP%\test.txt" "jumps" "" >NUL
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\test.txt" "test\test_out.txt" >NUL
if ERRORLEVEL 1 goto err

rem Тест многократных вхожений
set TEST_NUMBER=10
%PROGRAM% "test\multiply.txt" "%TEMP%\multiply.txt" "ma" "mama" >NUL
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\multiply.txt" "test\multiply_out.txt" >NUL
if ERRORLEVEL 1 goto err

rem Файл с несколькими вхождениями искомой строки
set TEST_NUMBER=11
%PROGRAM% "test\some.txt" "%TEMP%\some.txt" "test" "shmest" >NUL
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\some.txt" "test\some_out.txt" >NUL
if ERRORLEVEL 1 goto err

rem Файл, состоящий из одной, искомой подстроки
set TEST_NUMBER=12
%PROGRAM% "test\one.txt" "%TEMP%\one.txt" "first" "second" >NUL
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\one.txt" "test\one_out.txt" >NUL
if ERRORLEVEL 1 goto err

rem Многострочный файл
set TEST_NUMBER=13
%PROGRAM% "test\multiline.txt" "%TEMP%\multiline.txt" " one " "two" >NUL
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\multiline.txt" "test\multiline_out.txt" >NUL
if ERRORLEVEL 1 goto err



echo Testing SUCCEED
exit 0

:err
echo Testing FAILED at %TEST_NUMBER% testcase
exit 1