# Build
>RunScript (Blender)
```
GLB
KeyFrame
```
>Gen (Linux)
```bash
run/config
run/config-gen
cmake -DCMAKE_BUILD_TYPE=Debug -B build-debug -S .
run/gdb
```
>Linux
```bash
run/lib-wayland
run/shader-vulkan
run/config
run/config-linux
```
>Compile (Linux-Release)
```bash
cmake -DCMAKE_BUILD_TYPE=Release -B build-release -S .
cmake --build build-release
```
>Compile (Linux-Debug)
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build-debug -S .
cmake --build build-debug
```
>Debug (Linux)
```bash
run/gdb
```
>Android
```bash
run/android-tool
run/android-ffmpeg
run/config
run/config-android
run/android-apk
```
>Run/Log (Android)
```bash
adb shell am start -n com.nali.smallpointer/android.app.NativeActivity
adb shell cat storage/emulated/0/Android/data/com.nali.smallpointer/save/log.dat
```
