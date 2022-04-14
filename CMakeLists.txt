cmake_minimum_required( VERSION 3.6 )
project(mfx)

include(CMakeDependentOption)

set (MSDK_PATH "/home/berkay/Downloads/mediasdk_installation/MediaSDK")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (CMAKE_BUILD_TYPE release)
#setting builder root which contains find cmakes. 
set (BUILDER_ROOT "${MSDK_PATH}/builder")

#Setting API
set (CMAKE_MFX_HOME "${MSDK_PATH}/api")

#Set MFX_HOME DIR

set ( MFX_HOME ${MSDK_PATH})

option ( ENABLE_OPENCL "Build targets dependent on OpenCL?" ON )

option ( ENABLE_ALL "Enable all dpenedencies and features?" ON )

if ( CMAKE_SYSTEM_NAME MATCHES Linux)
    option( ENABLE_X11_DRI3 ${ENABLE_ALL})
    option( ENABLE_WAYLAND ${ENABLE_ALL})
endif()

option( ENABLE_TEXTLOG ${ENABLE_ALL})
option( ENABLE_STAT ${ENABLE_ALL})
option ( BUILD_RUNTIME ON)
cmake_dependent_option(BUILD_SAMPLES "Build samples?" ON "BUILD_DISPATCHER" OFF )

include( ${BUILDER_ROOT}/FindOpenCL.cmake )
include( ${BUILDER_ROOT}/FindFunctions.cmake )
include( ${BUILDER_ROOT}/FindMFX.cmake )
include( ${BUILDER_ROOT}/FindGlobals.cmake )
include( ${BUILDER_ROOT}/FindPackages.cmake )
include( ${BUILDER_ROOT}/FindInternals.cmake )
include( ${BUILDER_ROOT}/FindITT.cmake )
include( ${BUILDER_ROOT}/ConfTargets.cmake )


if (PKG_LIBDRM_FOUND)
    set(DEPENDENCIES libdrm)
    add_subdirectory(${CMAKE_HOME_DIRECTORY}/common)
    add_subdirectory(${CMAKE_HOME_DIRECTORY}/decode_vpp)
    
endif()
