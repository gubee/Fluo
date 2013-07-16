
TOOLCHAIN :=
TOOLCHAIN_PREFIX :=
TARGET := 
SOURCEDIRS :=
OUTDIR :=
OBJDIR := 
MODE :=
ARCH :=
OBJS :=
DEFINES :=
CFLAGS :=
CXXFLAGS :=
INCLUDES :=

CC := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)gcc
CXX := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)g++
AR := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)ar
RANLIB := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)ranlib
LD := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)ld
LINK := $(TOOLCHAIN)/bin/$(TOOLCHAIN_PREFIX)g++

DEFINES.debug :=

DEFINES.release :=

CFLAGS.debug := $(ARCH)
CFLAGS.debug += \
	-O0 \
	-g3 \
	-c \
	-Wall \
	-Wendif-labels \
	-W \
	-Wno-unused-local-typedefs \
	-Wno-unused-parameter \
	-Wno-strict-overflow \
	-fno-strict-aliasing \
	-fmessage-length=0

CFLAGS.release := $(ARCH)
CFLAGS.release += \
	-O3 \
	-c \
	-Wall \
	-Wendif-labels \
	-W \
	-Wno-unused-local-typedefs \
	-Wno-unused-parameter \
	-Wno-strict-overflow \
	-fno-strict-aliasing \
	-fmessage-length=0

CXXFLAGS.debug := $(CFLAGS.debug)
CXXFLAGS.debug += \
	-Wnon-virtual-dtor \
	-fno-rtti \
	-fno-exceptions \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden

CXXFLAGS.release := $(CFLAGS.release)
CXXFLAGS.release += \
	-Wnon-virtual-dtor \
	-fno-rtti \
	-fno-exceptions \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden

DEFINES += $(DEFINES.$(MODE))
CFLAGS += $(CFLAGS.$(MODE))
CXXFLAGS += $(CXXFLAGS.$(MODE))
INCLUDES += -I $(TOOLCHAIN)/include

define OBJECTRULE
$$(OUTDIR)/$$(OBJDIR)/%.o: $(1)/%.c
	$$(CC) $$(CFLAGS) $$(DEFINES) $$(INCLUDES) -o "$$@" "$$<"
	@echo ' '

$$(OUTDIR)/$$(OBJDIR)/%.o: $(1)/%.cpp
	$$(CXX) $$(CXXFLAGS) $$(DEFINES) $$(INCLUDES) -o "$$@" "$$<"
	@echo ' '

$$(OUTDIR)/$$(OBJDIR)/%.o: $(1)/%.cc
	$$(CXX) $$(CXXFLAGS) $$(DEFINES) $$(INCLUDES) -o "$$@" "$$<"
	@echo ' '
endef

$(foreach source, $(SOURCEDIRS), $(eval $(call OBJECTRULE, $(source))))

.PHONY: all check prerequisite

all: prerequisite $(OUTDIR)/lib$(TARGET).a
	
check:
	@echo 'TOOLCHAIN=$(TOOLCHAIN)'
	@echo 'TOOLCHAIN_PREFIX=$(TOOLCHAIN_PREFIX)'
	@echo 'TARGET=$(TARGET)'
	@echo 'SOURCEDIRS=$(SOURCEDIRS)'
	@echo 'OUTDIR=$(OUTDIR)'
	@echo 'OBJDIR=$(OBJDIR)'
	@echo 'MODE=$(MODE)'
	@echo 'ARCH=$(ARCH)'
	@echo 'DEFINES=$(DEFINES)'
	@echo 'CFLAGS=$(CFLAGS)'
	@echo 'CXXFLAGS=$(CXXFLAGS)'
	@echo 'INCLUDES=$(INCLUDES)'
	@echo ' '
	
prerequisite:
	$(shell mkdir -p $(OUTDIR)/$(OBJDIR))
	$(foreach each, $(dir $(addprefix $(OUTDIR)/$(OBJDIR)/, $(OBJS))), $(shell mkdir -p $(each)))

$(OUTDIR)/lib$(TARGET).a: $(addprefix $(OUTDIR)/$(OBJDIR)/, $(OBJS))
	$(AR) -r $@ $(addprefix $(OUTDIR)/$(OBJDIR)/, $(OBJS))
	@echo ' '

