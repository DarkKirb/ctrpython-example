# TARGET #

TARGET := 3DS
LIBRARY := 0

ifeq ($(TARGET),$(filter $(TARGET),3DS WIIU))
    ifeq ($(strip $(DEVKITPRO)),)
        $(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro")
    endif
endif

# COMMON CONFIGURATION #

NAME := Build Template

BUILD_DIR := build
OUTPUT_DIR := output
INCLUDE_DIRS := include
SOURCE_DIRS := source

EXTRA_OUTPUT_FILES :=

LIBRARY_DIRS := $(PWD)
LIBRARIES := python

BUILD_FLAGS := -I$(DEVKITPRO)/portlibs/armv6k/include/python3.6m
BUILD_FLAGS_CC := -Wno-unused -Wno-unused-variable
BUILD_FLAGS_CXX :=
RUN_FLAGS :=

VERSION_MAJOR := 0
VERSION_MINOR := 0
VERSION_MICRO := 0

# 3DS/Wii U CONFIGURATION #

ifeq ($(TARGET),$(filter $(TARGET),3DS WIIU))
    TITLE := $(NAME)
    DESCRIPTION := Build template.
    AUTHOR := Steveice10
endif

# 3DS CONFIGURATION #

ifeq ($(TARGET),3DS)
	APP_ROMFS=romfs/
    LIBRARY_DIRS += $(DEVKITPRO)/libctru
    LIBRARIES += ctru

    PRODUCT_CODE := CTR-P-TEMP
    UNIQUE_ID := 0xF8000

    CATEGORY := Application
    USE_ON_SD := true

    MEMORY_TYPE := Application
    SYSTEM_MODE := 64MB
    SYSTEM_MODE_EXT := Legacy
    CPU_SPEED := 268MHz
    ENABLE_L2_CACHE := true

    ICON_FLAGS :=

    ROMFS_DIR :=
    BANNER_AUDIO := meta/audio_3ds.wav
    BANNER_IMAGE := meta/banner_3ds.png
    ICON := meta/icon_3ds.png
    LOGO :=
endif

# Wii U CONFIGURATION #

ifeq ($(TARGET),WIIU)
    LIBRARY_DIRS +=
    LIBRARIES +=

    LONG_DESCRIPTION := Build template.
    ICON := meta/icon_wiiu.png
endif

# INTERNAL #

include buildtools/make_base
