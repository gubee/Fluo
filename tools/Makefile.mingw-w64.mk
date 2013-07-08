
CC := $(MINGW_W64_TOOLCHAIN_PATH)/bin/i686-w64-mingw32-gcc
CXX := $(MINGW_W64_TOOLCHAIN_PATH)/bin/i686-w64-mingw32-g++
AR := $(MINGW_W64_TOOLCHAIN_PATH)/bin/i686-w64-mingw32-ar
RANLIB := $(MINGW_W64_TOOLCHAIN_PATH)/bin/i686-w64-mingw32-ranlib
LD := $(MINGW_W64_TOOLCHAIN_PATH)/bin/i686-w64-mingw32-ld
LINK := $(MINGW_W64_TOOLCHAIN_PATH)/bin/i686-w64-mingw32-g++

OUTDIR ?=
MODE ?=
TARGET ?=

BUILDDIR := $(OUTDIR)/mingw-w64.$(MODE)

DEFINES.debug := \
	'-DENABLE_DEBUGGER_SUPPORT' \
	'-DV8_TARGET_ARCH_IA32' \
	'-DDEBUG' \
	'-DENABLE_DISASSEMBLER' \
	'-DV8_ENABLE_CHECKS' \
	'-DOBJECT_PRINT' \
	'-DVERIFY_HEAP' \
	'-DENABLE_EXTRA_CHECKS'

DEFINES.release := \
	'-DENABLE_DEBUGGER_SUPPORT' \
	'-DV8_TARGET_ARCH_IA32'

CFLAGS.debug := \
	-O0 \
	-g3 \
	-c \
	-Wall \
	-Wendif-labels \
	-Wnon-virtual-dtor \
	-W \
	-Wno-unused-local-typedefs \
	-Wno-unused-parameter \
	-fno-rtti \
	-fno-exceptions \
	-fno-threadsafe-statics \
	-fno-strict-aliasing \
	-fvisibility-inlines-hidden \
	-fmessage-length=0

CFLAGS.release := \
	-O3 \
	-c \
	-Wall \
	-Wendif-labels \
	-Wnon-virtual-dtor \
	-W \
	-Wno-unused-local-typedefs \
	-Wno-unused-parameter \
	-fno-rtti \
	-fno-exceptions \
	-fno-threadsafe-statics \
	-fno-strict-aliasing \
	-fvisibility-inlines-hidden \
	-fmessage-length=0

OBJS.v8_base.ia32 := \
	$(BUILDDIR)/obj.target/v8_base.ia32/accessors.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/allocation.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/api.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/arguments.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/assembler.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ast.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/atomicops_internals_x86_gcc.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/bignum-dtoa.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/bignum.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/bootstrapper.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/builtins.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/cached-powers.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/checks.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/circular-queue.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/code-stubs.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/code-stubs-hydrogen.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/codegen.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/compilation-cache.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/compiler.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/contexts.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/conversions.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/counters.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/cpu-profiler.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/data-flow.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/date.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/dateparser.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/debug-agent.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/debug.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/deoptimizer.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/disassembler.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/diy-fp.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/dtoa.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/elements-kind.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/elements.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/execution.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/extensions/externalize-string-extension.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/extensions/gc-extension.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/extensions/statistics-extension.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/factory.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/fast-dtoa.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/fixed-dtoa.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/flags.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/frames.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/full-codegen.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/func-name-inferrer.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/gdb-jit.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/global-handles.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/handles.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/heap-profiler.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/heap-snapshot-generator.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/heap.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/hydrogen-environment-liveness.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/hydrogen-instructions.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/hydrogen.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/hydrogen-gvn.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ic.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/incremental-marking.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/interface.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/interpreter-irregexp.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/isolate.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/jsregexp.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/lithium-allocator.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/lithium.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/liveedit.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/log-utils.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/log.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/mark-compact.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/marking-thread.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/messages.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/objects-debug.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/objects-printer.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/objects-visiting.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/objects.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/once.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/optimizing-compiler-thread.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/parser.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/preparse-data.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/preparser.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/prettyprinter.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/profile-generator.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/property.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/regexp-macro-assembler-irregexp.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/regexp-macro-assembler-tracer.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/regexp-macro-assembler.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/regexp-stack.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/rewriter.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/runtime-profiler.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/runtime.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/safepoint-table.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/sampler.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/scanner-character-streams.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/scanner.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/scopeinfo.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/scopes.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/serialize.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/snapshot-common.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/spaces.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/store-buffer.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/string-search.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/string-stream.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/strtod.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/stub-cache.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/sweeper-thread.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/token.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/transitions.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/type-info.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/types.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/typing.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/unicode.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/utils.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/v8-counters.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/v8.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/v8conversions.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/v8threads.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/v8utils.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/variables.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/version.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/zone.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/assembler-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/builtins-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/code-stubs-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/codegen-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/cpu-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/debug-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/deoptimizer-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/disasm-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/frames-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/full-codegen-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/ic-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/lithium-codegen-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/lithium-gap-resolver-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/lithium-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/macro-assembler-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/regexp-macro-assembler-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/ia32/stub-cache-ia32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/platform-win32.o \
	$(BUILDDIR)/obj.target/v8_base.ia32/win32-math.o
	
OBJS.v8_nosnapshot := \
	$(BUILDDIR)/obj.target/v8_nosnapshot/libraries.o \
	$(BUILDDIR)/obj.target/v8_nosnapshot/experimental-libraries.o \
	$(BUILDDIR)/obj.target/v8_nosnapshot/snapshot-empty.o

OBJS.v8_snapshot := \
	$(BUILDDIR)/obj.target/v8_snapshot/libraries.o \
	$(BUILDDIR)/obj.target/v8_snapshot/experimental-libraries.o \
	$(BUILDDIR)/obj.target/v8_snapshot/snapshot.o
	
DIRS.v8_base.ia32 := \
	obj.target obj.target/v8_base.ia32 obj.target/v8_base.ia32/extensions obj.target/v8_base.ia32/ia32

DIRS.v8_nosnapshot := \
	obj.target obj.target/v8_nosnapshot obj obj/gen

DIRS.v8_snapshot := \
	obj.target obj.target/v8_snapshot obj obj/gen

CFLAGS := $(CFLAGS.$(MODE))
DEFINES := $(DEFINES.$(MODE))

all: prerequisite $(BUILDDIR)/lib$(TARGET).a

prerequisite: $(DIRS.$(TARGET))
	
obj.target obj.target/v8_base.ia32 obj.target/v8_base.ia32/extensions obj.target/v8_base.ia32/ia32 obj.target/v8_nosnapshot obj.target/v8_snapshot obj obj/gen:
	@mkdir -p $(BUILDDIR)/$@

$(BUILDDIR)/lib$(TARGET).a: $(OBJS.$(TARGET))
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Archiver'
	$(AR) -r $@ $(OBJS.$(TARGET)) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

$(BUILDDIR)/obj.target/v8_base.ia32/%.o: ./src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX) $(CFLAGS) $(DEFINES) -I./src -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(BUILDDIR)/obj.target/v8_nosnapshot/%.o: $(BUILDDIR)/obj/gen/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX) $(CFLAGS) $(DEFINES) -I./src -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(BUILDDIR)/obj.target/v8_nosnapshot/%.o: ./src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX) $(CFLAGS) $(DEFINES) -I./src -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(BUILDDIR)/obj.target/v8_snapshot/%.o: $(BUILDDIR)/obj/gen/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX) $(CFLAGS) $(DEFINES) -I./src -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(BUILDDIR)/obj/gen/libraries.cc:
	@python ./tools/js2c.py $@ CORE off ./src/runtime.js ./src/v8natives.js ./src/array.js ./src/string.js ./src/uri.js ./src/math.js ./src/messages.js ./src/apinatives.js ./src/debug-debugger.js ./src/mirror-debugger.js ./src/liveedit-debugger.js ./src/date.js ./src/json.js ./src/regexp.js ./src/macros.py

$(BUILDDIR)/obj/gen/experimental-libraries.cc:
	@python ./tools/js2c.py $@ EXPERIMENTAL off ./src/macros.py ./src/symbol.js ./src/proxy.js ./src/collection.js ./src/object-observe.js ./src/arraybuffer.js ./src/typedarray.js ./src/generator.js
	
$(BUILDDIR)/obj/gen/snapshot.cc: 
	"$(OUTDIR)/ia32.$(MODE)/mksnapshot.ia32" --log-snapshot-positions --logfile "$(BUILDDIR)/obj/gen/snapshot.log" "$(BUILDDIR)/obj/gen/snapshot.cc"
