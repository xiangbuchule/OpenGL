@echo off
@REM 跳过函数
goto:skipFunction
@REM 删除目录
:deleteDirectory
    if "%~n1"=="%~2" (
        echo delete : "%~1"
        rd /s /q "%~1"
    )
goto:EOF
@REM 清理目录
:cleanDirectory
    for /f %%i in (' dir /a:d-h /b %1 ') do (
        call:deleteDirectory "%~dp0%1\%%i" "bin"
    )
goto:EOF
@REM 清理LearnOpenGL目录
:cleanLearnOpenGLDirectory
    @REM 清理LearnOpenGL目录
    for /f %%i in (' dir /s /a:d-h /b .\LearnOpenGL ') do (
        @REM 删除bin install目录
        call:deleteDirectory "%%i" "bin"
        call:deleteDirectory "%%i" "install"
    )
goto:EOF
@REM 清理其他目录
:cleanOthersDirectory
    set param=%*
    @REM 遍历清理参数目录
    for %%i in (%param%) do (
        call:cleanDirectory %%~i
    )
goto:EOF
@REM 清理项目根目录
:cleanRootDirectory
    for /f %%i in (' dir /a:d-h /b ') do (
        call:deleteDirectory %%~fi "build"
    )
goto:EOF
:skipFunction
@REM 设置当前路径
set nowPath=%cd%
@REM 进入该脚本路径
cd /d %~dp0
@REM 获取脚本参数
set commandParam=%1
@REM 判断参数
if /i "%commandParam%" == "" (
    call:cleanLearnOpenGLDirectory
    call:cleanOthersDirectory "ThirdParty"
    call:cleanRootDirectory
)
if /i "%commandParam%" == "all" (
    call:cleanLearnOpenGLDirectory
    call:cleanOthersDirectory "ThirdParty"
    call:cleanRootDirectory
)
if /i "%commandParam%" == "LearnOpenGL" (
    call:cleanLearnOpenGLDirectory
)
if /i "%commandParam%" == "ThirdParty" (
    call:cleanLearnOpenGLDirectory
    call:cleanOthersDirectory "ThirdParty"
)
@REM cd还原回去原来的路径
cd /d %nowPath%