# Makefile for generating a VisImageUtil25_Test library using Emscripten.
#
# build with       emmake make
#

# For placing path overrides.. this path is hidden from git
-include Makefile.local

LATEST =  lib
STABLE =  lib
PYTHON=$(ENV) python
VERSION := stable
BUILD := debug

ifeq ($(BUILD), debug)
	OPTS = -O0 -g2
	LINK_OPTS = -g4  --llvm-lto 0 -s NO_BROWSER=1 -s ASSERTIONS=2 --closure 0  -s DEMANGLE_SUPPORT=1 
else
	OPTS = -Os
	LINK_OPTS =  -O3 --llvm-lto 1 -s NO_BROWSER=1  --closure 1  --js-transform "python bundle.py"
endif

ifeq ($(VERSION), latest)
	ACTIVE = $(LATEST)
	OBJECTS = \
	$(ACTIVE)/Box2D/Dynamics/Joints/b2MotorJoint.bc
else ifeq ($(VERSION), stable)
	ACTIVE = $(STABLE)
else
	ACTIVE = $(VERSION)
endif

OBJECTS += \
$(ACTIVE)/CImageUtil/CImageUtil.bc \
$(ACTIVE)/CImageUtil/CImageUtilHtml5.bc \
$(ACTIVE)/CImageUtil/CBase64.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/INFOLIBJPEG.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcapimin.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcmainct.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdapimin.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdhuff.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdtrans.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jmemmgr.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcapistd.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcmarker.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdapistd.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdinput.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jerror.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jmemnobs.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcarith.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcmaster.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdarith.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdmainct.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jfdctflt.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jccoefct.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcomapi.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdatadst.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdmarker.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jfdctfst.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jpegtran.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jccolor.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcparam.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdatasrc.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdmaster.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jfdctint.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jquant1.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcdctmgr.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcprepct.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdcoefct.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdmerge.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jidctflt.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jquant2.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jchuff.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcsample.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdcolor.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdpostct.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jidctfst.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jutils.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jcinit.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/cdjpeg.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/transupp.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jctrans.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jddctmgr.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jdsample.bc \
$(ACTIVE)/CImageUtil/INFOLIBJPEG/jidctint.bc

all: remove visTest.js
	@echo $(ACTIVE)"_"$(BUILD)".js is ready"

%.bc: %.c
	$(CXX) $(OPTS) -I$(ACTIVE) $< -o $@

visTest.bc: $(OBJECTS)
	$(CXX) $(OPTS) -I$(ACTIVE) -o $@ $(OBJECTS)

visTest_glue.cpp: $(ACTIVE).idl
	$(PYTHON) $(EMSCRIPTEN)/tools/webidl_binder.py $(ACTIVE).idl visTest_glue

visTest_glue.h: visTest_glue.cpp

visTest.js: visTest.bc visTest_glue.cpp visTest_glue.h
	$(CXX) $(LINK_OPTS) -I$(ACTIVE) -s EXPORT_BINDINGS=1 -O1 -s RESERVED_FUNCTION_POINTERS=20 --post-js visTest_glue.js --memory-init-file 0 -s NO_EXIT_RUNTIME=1 glue_stub.cpp $< -o build/$(ACTIVE)_$(BUILD).js

clean: remove
	rm -f $(OBJECTS)
	
remove:
	rm -f visTest.bc visTest_bindings.cpp visTest_bindings.bc visTest.clean.h visTest_glue.js visTest_glue.cpp WebIDLGrammar.pkl parser.out

