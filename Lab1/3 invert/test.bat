set PROGRAM="%~1"

rem Запуск без аргумента
set TEST_NUMBER=1
%PROGRAM% >NUL
if NOT ERRORLEVEL 1 goto err

rem Пустой аргумент
set TEST_NUMBER=2
%PROGRAM% "" >NUL
if NOT ERRORLEVEL 1 goto err

rem Ошибка чтения файла
set TEST_NUMBER=3
%PROGRAM% %PROGRAM% >NUL
if NOT ERRORLEVEL 1 goto err

rem Пустой файл
set TEST_NUMBER=4
%PROGRAM% "test\Empty.txt" >NUL
if NOT ERRORLEVEL 1 goto err

rem Матрица с ненулевым определителем
set TEST_NUMBER=5
%PROGRAM% "test\Normal.txt" > %TEMP%\Normal.txt
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\Normal.txt" "test\Normal_out.txt" >NUL
if ERRORLEVEL 1 goto err

rem Вырожденная матрица
set TEST_NUMBER=6
%PROGRAM% "test\Singular.txt" >NUL
if NOT ERRORLEVEL 1 goto err

rem Невалидные символы в файле
set TEST_NUMBER=7
%PROGRAM% "test\Wrong.txt" >NUL
if NOT ERRORLEVEL 1 goto err

rem Матрица меньшей размерности
set TEST_NUMBER=8
%PROGRAM% "test\Less.txt" >NUL
if NOT ERRORLEVEL 1 goto err
%PROGRAM% "test\Less1.txt" >NUL
if NOT ERRORLEVEL 1 goto err

rem Матрица большей размерности
set TEST_NUMBER=9
%PROGRAM% "test\More.txt" >NUL
if NOT ERRORLEVEL 1 goto err
%PROGRAM% "test\More1.txt" >NUL
if NOT ERRORLEVEL 1 goto err


:ok
echo Testing SUCCEED
exit 0

:err
echo Testing FAILED at %TEST_NUMBER% testcase
exit 1