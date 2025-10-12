cmake_minimum_required(VERSION 3.31)

#//.i system
set(ST linux)
#set(ST android)
#set(ST win)

#//.i surface
set(DRM 1)
#set(ASURFACE 1)
#set(WL 1)
#set(X11 1)

#//.i run
set(GEN 1)
set(CLIENT 1)
set(SERVER 1)

#//.i media reader
#set(FFMPEG 1)

#//.i network protocol
set(UDP 1)
#set(TCP 1)

#//.i audio
#set(PIPEWIRE 1)
#set(AAUDIO 1)
#set(OPENAL 1)

#//.i render
set(VK 1)
  set(VK_DEBUG 1)
#set(GL 1)

#//.i input
set(LIBINPUT 1)
#set(WLINPUT 1)
#set(X11INPUT 1)
#set(AINPUT 1)

set(TEST 1)
set(DEBUG 1)

set(PN SmallPointer)
project(${PN} LANGUAGES C)

file(GLOB_RECURSE G_SOURCES src/file/*.c)
list(APPEND SOURCES ${G_SOURCES})

set(TLL m)
file(GLOB_RECURSE G_SOURCES src/math/*.c)
list(APPEND SOURCES ${G_SOURCES})

if(TEST)
  list(APPEND TCD SMPT_CM_TEST)
endif()

if(DEBUG)
  list(APPEND TCD SMPT_CM_DEBUG)

  list(APPEND SOURCES src/debug/debug.c)
endif()

if(GEN)
  list(APPEND TCD SMPT_CM_GEN)

  file(GLOB_RECURSE G_SOURCES src/gen/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  list(APPEND TID ../cgltf)
endif()

list(APPEND SOURCES src/raw/raw.c)
list(APPEND SOURCES src/network/network.c)

if(DRM OR ASURFACE OR WL OR X11)
  list(APPEND SOURCES src/surface/surface.c)
endif()

if(CLIENT)
  list(APPEND TCD SMPT_CM_CLIENT)

  file(GLOB_RECURSE G_SOURCES src/raw/client/*.c)
  list(APPEND SOURCES ${G_SOURCES})
endif()

if(SERVER)
  list(APPEND TCD SMPT_CM_SERVER)

  file(GLOB_RECURSE G_SOURCES src/raw/server/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  file(GLOB_RECURSE G_SOURCES src/entity/server/*.c)
  list(APPEND SOURCES ${G_SOURCES})
endif()

if(FFMPEG)
  list(APPEND TCD SMPT_CM_FFMPEG)

  if(ST STREQUAL "linux")
    list(APPEND TLL
      avcodec
      avformat
      avutil
      swresample
    )
  elseif(ST STREQUAL "android")
    list(APPEND TID ../FFmpeg/android/arm64/include)
    list(APPEND TLL
      ${CMAKE_SOURCE_DIR}/../FFmpeg/android/arm64/lib/libavcodec.so
      ${CMAKE_SOURCE_DIR}/../FFmpeg/android/arm64/lib/libavformat.so
      ${CMAKE_SOURCE_DIR}/../FFmpeg/android/arm64/lib/libavutil.so

      ${CMAKE_SOURCE_DIR}/../FFmpeg/android/arm64/lib/libswresample.so
    )
  endif()

  list(APPEND SOURCES src/ffmpeg/ffmpeg.c)
endif()

if(UDP)
  list(APPEND TCD SMPT_CM_UDP)

  if(CLIENT)
    list(APPEND SOURCES src/network/udp/client/client.c)
  endif()
  if(SERVER)
    list(APPEND SOURCES src/network/udp/server/server.c)
  endif()
elseif(TCP)
  list(APPEND TCD SMPT_CM_TCP)

  if(CLIENT)
    list(APPEND SOURCES src/network/tcp/client/client.c)
  endif()
  if(SERVER)
    list(APPEND SOURCES src/network/tcp/server/server.c)
  endif()
endif()

if(VK)
  list(APPEND TCD SMPT_CM_VK)

  if(ST STREQUAL "linux")
    list(APPEND TLL vulkan)
  elseif(ST STREQUAL "android")
    list(APPEND TLL ${CMAKE_SOURCE_DIR}/../android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/24/libvulkan.so)
  endif()

  file(GLOB_RECURSE G_SOURCES src/render/vk/*.c)
  list(APPEND SOURCES ${G_SOURCES})

  if(VK_DEBUG)
    list(APPEND TCD SMPT_CM_VK_DEBUG)
    list(APPEND SOURCES src/render/vk/debug/debug.c)
  endif()
endif()

if(ST STREQUAL "linux")
  list(APPEND TCD SMPT_CM_ST_LINUX)

  if(DRM)
    list(APPEND TCD SMPT_CM_DRM)
  endif()

  if(LIBINPUT)
    list(APPEND TCD SMPT_CM_LIBINPUT)

    file(GLOB_RECURSE G_SOURCES src/input/libinput/*.c)
    list(APPEND SOURCES ${G_SOURCES})

    list(APPEND TLL
      input
      udev
    )
  endif()

  if(PIPEWIRE)
    list(APPEND TLL pipewire-0.3)
    list(APPEND TID /usr/include/spa-0.2)
    list(APPEND TID /usr/include/pipewire-0.3)
  endif()

  if(WL)
    list(APPEND TCD SMPT_CM_WL)

    if(WLINPUT)
      list(APPEND TCD SMPT_CM_WLINPUT)
    endif()

    list(APPEND TLL
      wayland-client
      wayland-cursor
    )

    file(GLOB_RECURSE G_SOURCES lib/wayland/*.c)
    list(APPEND SOURCES ${G_SOURCES})

    file(GLOB_RECURSE G_SOURCES src/surface/wayland/*.c)
    list(APPEND SOURCES ${G_SOURCES})

    list(APPEND TID lib/wayland)
  endif()

  list(APPEND SOURCES src/src.c)

  add_executable(${PN} ${SOURCES})
elseif(ST STREQUAL "android")
  list(APPEND TCD SMPT_CM_ST_ANDROID)

  #//! audio android
  list(APPEND TLL
    android
    #OpenSLES
  )

  if(AAUDIO)
    list(APPEND TCD SMPT_CM_AAUDIO)
  endif()

  if(ASURFACE)
    list(APPEND TCD SMPT_CM_ASURFACE)

    file(GLOB_RECURSE G_SOURCES src/surface/android/*.c)
    list(APPEND SOURCES ${G_SOURCES})
  endif()

  if(AINPUT)
    list(APPEND TCD SMPT_CM_AINPUT)
  endif()

  add_library(${PN} SHARED ${SOURCES})
endif()

if(TID)
  target_include_directories(${PN} PRIVATE ${TID})
endif()
target_link_libraries(${PN} ${TLL})
target_compile_definitions(${PN} PRIVATE ${TCD})

target_precompile_headers(${PN} PRIVATE src/src.h)
