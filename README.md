cross compile for windows:
[mingw.cmake](https://gist.github.com/peterspackman/8cf73f7f12ba270aa8192d6911972fe8)
```
mkdir windows-build
cd windows-build
cmake -DCMAKE_TOOLCHAIN_FILE=~/mingw-w64-x86_64.cmake ..
make OpenGLCustomTest -j4
wine OpenGLCustomTest.exe
# wine will be missing dlls: /usr/lib/gcc/x86_64-w64-mingw32/7.3-win32/
```