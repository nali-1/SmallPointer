# Gentoo Linux
>[Handbook](https://wiki.gentoo.org/wiki/Handbook)

>/etc/portage/make.conf
```bash
USE="qml minizip qt6 -elogind -fonts savedconfig builtin server icu sound-server pipewire-alsa alsa pipewire ffmpeg extra kms drm vaapi dvd cdda cups bluetooth dbus udev usb opus ogg vorbis x264 xvid theora vpx postproc gif jpeg2k jpeg jpegxl webp lcms pango svg tiff truetype harfbuzz xml postscript vulkan layers opengl gles2 egl wayland X gtk text"
INPUT_DEVICES="libinput"
ABI_X86="64"
ACCEPT_LICENSE="*"

#AMD_igpu
VIDEO_CARDS="amdgpu radeon radeonsi"

#NVIDIA_dgpu
VIDEO_CARDS="nouveau nvk zink"

#Intel_igpu
VIDEO_CARDS="intel"
```
>Install Package
```bash
sudo run/pack
run/vi-gen
run/hp-gen
```
>Check Kernel
```bash
ls /usr/src
ls -l /usr/src/linux
ls /lib/modules
cd /usr/src/linux
```
>Set/Default Kernel
```bash
ln -sfn /usr/src/linux-6.17.0 /usr/src/linux
make mrproper
make defconfig
make menuconfig
```
>Update Kernel
```bash
make mrproper
cp /usr/src/linux-6.16.*/.config /usr/src/linux-6.17.0
make oldconfig
```
>Compile/Reinstall Kernel/Modules
```bash
make
make modules_install
cp arch/x86/boot/bzImage /boot/vmlinuz-6.17.0
grub-mkconfig -o /boot/grub/grub.cfg
```
>Clean Kernel
```bash
rm -r /usr/src/linux-6.16.*
rm -r /lib/modules/6.16.*
rm /boot/vmlinuz-6.16.*
```
