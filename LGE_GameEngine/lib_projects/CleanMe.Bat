rmdir /S /Q Debug
rmdir /S /Q Release
del /F /S *.sdf
del /F /S /A:H *.suo
del /F /S *.user

rmdir /S /Q MathEngine\MathEngine\Debug
rmdir /S /Q MathEngine\MathEngine\Release
del /F /S MathEngine\MathEngine\*.user

rmdir /S /Q MathEngine\MathEngineTest\Debug
rmdir /S /Q MathEngine\MathEngineTest\Release
del /F /S MathEngine\MathEngineTest\*.user

rmdir /S /Q FileLibrary\FileLib\Debug
rmdir /S /Q FileLibrary\FileLib\Release
del /F /S FileLibrary\FileLib\*.user

rmdir /S /Q FileLibrary\FileLibraryTest\Debug
rmdir /S /Q FileLibrary\FileLibraryTest\Release
del /F /S FileLibrary\FileLibraryTest\*.user