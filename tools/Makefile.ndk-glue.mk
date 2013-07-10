
TOOLCHAIN :=
TOOLCHAIN_PREFIX := 
OUTDIR :=
MODE :=
ARCH :=
INCLUDES := -I $(TOOLCHAIN)/include

CC := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)gcc
CXX := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)g++
AR := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)ar
RANLIB := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)ranlib
LD := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)ld
LINK := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)g++

DEFINES.debug :=

DEFINES.release :=

CFLAGS.debug := \
	-O0 \
	-g3 \
	-c \
	-Wall \
	-Wendif-labels \
	-W \
	-Wno-unused-local-typedefs \
	-Wno-unused-parameter \
	-fno-strict-aliasing \
	-fmessage-length=0 \
	-march=${ARCH}

CFLAGS.release := \
	-O3 \
	-c \
	-Wall \
	-Wendif-labels \
	-W \
	-Wno-unused-local-typedefs \
	-Wno-unused-parameter \
	-fno-strict-aliasing \
	-fmessage-length=0 \
	-march=${ARCH}
	
DEFINES := $(DEFINES.$(MODE))
CFLAGS := $(CFLAGS.$(MODE))

all: $(OUTDIR)/libndk-glue.a

$(OUTDIR)/libndk-glue.a: $(OUTDIR)/android_native_app_glue.o
	$(AR) -r $@ $< $(LIBS)

$(OUTDIR)/android_native_app_glue.o: $(ANDROID_NDK)/sources/android/native_app_glue/android_native_app_glue.c
	@mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o $@ $<

