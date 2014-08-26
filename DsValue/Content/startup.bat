cls
@ECHO OFF
CLS
color 0a
Title Distributed Lottery System
set datadir=-datadir=%CD%\dspay
set defalutflag=-server=1 -rpcuser=dspay -rpcpassword=admin
set genflag=-gen=0

if exist dspayd.exe (
	if exist dspayKey.dat (
	echo dspayKey.dat is ok 
	goto copy
	) ELSE (
	echo dspayKey.dat missing 
	goto check
	)
) else (
	echo dspayd.exe missing
	goto check
)



:check
set /p choice=         Enter to [Exit] 
goto EX


:copy
MD %CD%\dspay
COPY dspayKey.dat %CD%\dspay
COPY bitcoin.conf %CD%\dspay

:menu
cls
echo.
echo                  [Main Menu]  
echo         =================================
echo.		
echo         1.Minning Configure
echo         2.Start Node
echo         3.Stop Node
echo         4.Get Info
echo         z.Exit
echo.	
echo         =================================      
:cl
echo.
set /p choice=         Enter to Next 
if /i "%choice%"=="1" goto s0
if /i "%choice%"=="2" goto s1
if /i "%choice%"=="3" goto s2
if /i "%choice%"=="4" goto s3
if /i "%choice%"=="z" goto EX
goto menu

:s0
cls
echo.
echo.
echo         =========================================
echo.
echo         ============Minning Configure============
echo         1.With Minning
echo         2.Without Minning     
echo.
echo         =========================================
echo.       
set /p choice=         Enter to [Main Menu] 
if /i "%choice%"=="1" set genflag=-gen=1 &goto menu
if /i "%choice%"=="2" set genflag=-gen=0 &goto menu
goto s0


:s1
START cmd /k "%CD%\dspayd.exe %datadir% %defalutflag% %genflag%"
goto menu

:s2
%CD%\dspayd.exe %datadir% %defalutflag% stop
goto menu

:s3
cls
%CD%\dspayd.exe %datadir% %defalutflag% getinfo
set /p choice=         Enter to [Main Menu] 
goto menu


:EX
exit