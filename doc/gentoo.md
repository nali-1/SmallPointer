# Gentoo Linux
>[Handbook](https://wiki.gentoo.org/wiki/Handbook)

>/etc/portage/make.conf
```bash
USE="-elogind -fonts builtin server icu sound-server pipewire-alsa alsa pipewire ffmpeg extra kms drm vaapi dvd cdda cups bluetooth dbus udev usb opus ogg vorbis x264 xvid theora vpx postproc gif jpeg2k jpeg jpegxl webp lcms pango svg tiff truetype harfbuzz xml postscript vulkan layers opengl gles2 egl wayland X gtk text"
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
sudo run/pack-clean
run/vi-gen
run/hp-gen
run/foot-gen
```
>Kernel
```bash
run/kernel-check
run/kernel-default [major.minor.patch/0.0.0]
run/kernel-build-new [major.minor.patch/0.0.0] [jobs/0]
run/kernel-build-old2new [old -> major.minor.patch/0.0.0] [new -> major.minor.patch/0.0.0] [jobs/0]
run/kernel-clean [major.minor.patch/0.0.0]
```
>Misc
```bash
run/hp
```
