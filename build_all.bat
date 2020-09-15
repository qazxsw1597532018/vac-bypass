@echo off

title Building service...

mkdir build\.service
cd build\.service
cmake -G "Ninja" ../../service/
cmake --build .
copy service.exe ..\service.exe /Y
cd ..\..

title Building loader...

mkdir build\.loader
cd build\.loader
cmake -G "Ninja" ../../loader/
cmake --build .
copy loader.exe ..\loader.exe /Y
cd ..\..

title Building bypass...

mkdir build\.bypass
cd build\.bypass
cmake -G "Ninja" ../../bypass/
cmake --build .
copy vac.dll ..\vac.dll /Y
cd ..\..

title Done!
pause