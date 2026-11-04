@echo off
setlocal

cmake -S "%~dp0" -B "%~dp0build" -A x64
if errorlevel 1 exit /b 1

cmake --build "%~dp0build" --config Release --parallel 4
if errorlevel 1 exit /b 1

echo.
echo Build complete. VST3 bundle:
echo %~dp0build\RedSignal_artefacts\Release\VST3\RED SIGNAL.vst3

echo.
echo Copy the entire "RED SIGNAL.vst3" folder. Do not copy only the internal binary.
endlocal
