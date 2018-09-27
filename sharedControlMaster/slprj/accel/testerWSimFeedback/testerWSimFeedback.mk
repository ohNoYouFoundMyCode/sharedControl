# Copyright 1994-2017 The MathWorks, Inc.
#
# File    : accel_unix.tmf   
#
# Abstract:
#	Accelerator template makefile for building a UNIX-based,
#       generated mex-file of Simulink model using generated C code.
#
# 	This makefile attempts to conform to the guidelines specified in the
# 	IEEE Std 1003.2-1992 (POSIX) standard. It is designed to be used
#       with GNU Make which is located in matlabroot/rtw/bin.
#
# 	Note that this template is automatically customized by the build 
#       procedure to create "<model>.mk"
#
#       The following defines can be used to modify the behavior of the
#	build:
#
#         MEX_OPTS       - User specific mex options.
#	  OPT_OPTS       - Optimization options. Default is -O.
#	  USER_SRCS      - Additional user sources, such as files needed by
#			   S-functions.
#	  USER_INCLUDES  - Additional include paths
#			   (i.e. USER_INCLUDES="-Iwhere-ever -Iwhere-ever2")
#       To enable debugging:
#         set DEBUG_BUILD = 1 below, which will trigger MEX_OPTS=-g and
#          LDFLAGS += -g (may vary with compiler version, see compiler doc) 
#
#       This template makefile is designed to be used with a system target
#       file that contains 'rtwgensettings.BuildDirSuffix' see accel.tlc

#------------------------ Macros read by make_rtw ------------------------------
#
# The following macros are read by the build procedure:
#
#  MAKECMD         - This is the command used to invoke the make utility
#  HOST            - What platform this template makefile is targeted for
#                    (i.e. PC or UNIX)
#  BUILD           - Invoke make from the build procedure (yes/no)?
#  SYS_TARGET_FILE - Name of system target file.

MAKECMD         = /usr/local/MATLAB/R2018a/bin/glnxa64/gmake
HOST            = UNIX
BUILD           = yes
SYS_TARGET_FILE = accel.tlc
COMPILER_TOOL_CHAIN = unix

# Opt in to simplified format by specifying compatible Toolchain
TOOLCHAIN_NAME = ["Clang v3.1 | gmake (64-bit Mac)", \
             "GNU gcc/g++ v4.4.x | gmake (64-bit Linux)"]

#---------------------- Tokens expanded by make_rtw ----------------------------
#
# The following tokens, when wrapped with "|>" and "<|" are expanded by the
# build procedure.
#
#  MODEL_NAME      - Name of the Simulink block diagram
#  MODEL_MODULES   - Any additional generated source modules
#  MAKEFILE_NAME   - Name of makefile created from template makefile <model>.mk
#  MATLAB_ROOT     - Path to where MATLAB is installed.
#  S_FUNCTIONS_LIB - List of S-functions libraries to link.
#  SOLVER          - Solver source file name
#  NUMST           - Number of sample times
#  TID01EQ         - yes (1) or no (0): Are sampling rates of continuous task
#                    (tid=0) and 1st discrete task equal.
#  NCSTATES        - Number of continuous states
#  COMPUTER        - Computer type. See the MATLAB computer command.
#  MEXEXT          - extension that a mex file has. See the MATLAB mexext 
#                    command
#  BUILDARGS       - Options passed in at the command line.

MODEL              = testerWSimFeedback
MODULES            = rtGetInf.c rtGetNaN.c rt_nonfinite.c testerWSimFeedback_acc.c testerWSimFeedback_acc_data.c
MAKEFILE           = testerWSimFeedback.mk
MATLAB_ROOT        = /usr/local/MATLAB/R2018a
ALT_MATLAB_ROOT    = /usr/local/MATLAB/R2018a
MASTER_ANCHOR_DIR  = 
START_DIR          = /home/transmogrifier/Programming/sharedControl/sharedControlMaster
S_FUNCTIONS_LIB    = 
SOLVER             = 
NUMST              = 2
TID01EQ            = 1
NCSTATES           = 6
MEM_ALLOC          = RT_STATIC
COMPUTER           = GLNXA64
MEXEXT             = mexa64
BUILDARGS          =  COMBINE_OUTPUT_UPDATE_FCNS=0 INCLUDE_MDL_TERMINATE_FCN=1 MULTI_INSTANCE_CODE=0 ISPROTECTINGMODEL=NOTPROTECTING
PURIFY             = 0
MODELREFS          = 
SHARED_SRC         = 
SHARED_SRC_DIR     = 
SHARED_BIN_DIR     = 
SHARED_LIB         = 
TARGET_LANG_EXT    = c
OPTIMIZATION_FLAGS = -O0 -fPIC -DNDEBUG
ADDITIONAL_LDFLAGS = 
INTERLEAVED_COMPLEX_FLAGS = -R2018a
DEFINES_CUSTOM     = 

# To enable debugging:
# set DEBUG_BUILD = 1
DEBUG_BUILD        = 0


#--------------------------- Model and reference models -----------------------
MODELLIB                  = testerWSimFeedbacklib.a
MODELREF_LINK_LIBS        = 
MODELREF_INC_PATH         = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
# NONE: standalone, SIM: modelref sim, RTW: modelref coder target
MODELREF_TARGET_TYPE       = NONE

#-- In the case when directory name contains space ---
ifneq ($(MATLAB_ROOT),$(ALT_MATLAB_ROOT))
MATLAB_ROOT := $(ALT_MATLAB_ROOT)
endif

#--------------------------- Tool Specifications -------------------------------
include $(MATLAB_ROOT)/rtw/c/tools/unixtools.mk

CC = $(MATLAB_ARCH_BIN)/mex

#------------------------------ Include Path -----------------------------------
MATLAB_INCLUDES = \
	-I$(MATLAB_ROOT)/simulink/include \
	-I$(MATLAB_ROOT)/extern/include \
	-I$(MATLAB_ROOT)/rtw/c/src

# Additional includes

ADD_INCLUDES = \
	-I$(START_DIR) \
	-I$(START_DIR)/slprj/accel/testerWSimFeedback \


SHARED_INCLUDES =
ifneq ($(SHARED_SRC_DIR),)
SHARED_INCLUDES = -I$(SHARED_SRC_DIR) 
endif

INCLUDES = -I. -I$(RELATIVE_PATH_TO_ANCHOR) $(MATLAB_INCLUDES) $(ADD_INCLUDES) $(USER_INCLUDES) \
	$(MODELREF_INC_PATH) $(SHARED_INCLUDES)

#-------------------------------- Mex Options  ---------------------------------
# General User Options
ifeq ($(DEBUG_BUILD),0)
MEX_OPTS =
else
#   Set OPTS=-g and any additional flags for debugging
MEX_OPTS = -g
LDFLAGS += -g
endif

ifndef MEX_OPT_FILE
MEX_OPT_FILE = 
endif

ifndef OPT_OPTS
OPT_OPTS  = $(DEFAULT_OPT_OPTS)
endif

GCC_WARN_OPTS := 

ifeq ($(COMPUTER),MACI64)
ARCH_LDFLAGS = LDFLAGS='$$LDFLAGS -Wl,-rpath,@loader_path'
else
ARCH_LDFLAGS =
endif

ifneq ($(ADDITIONAL_LDFLAGS),)
MEX_LDFLAGS = CLIBS='$$CLIBS $(ADDITIONAL_LDFLAGS)' 
else
MEX_LDFLAGS =
endif

MEX_FLAGS = $(INTERLEAVED_COMPLEX_FLAGS)

# See rtw/c/tools/unixtools.mk for the definition of GCC_WARN_OPTS
ifeq ($(PURIFY),1)
   MEX_FLAGS += $(DEFINES_CUSTOM) $(MEX_OPTS) -g COPTIMFLAGS="$(GCC_WARN_OPTS) $(ANSI_OPTS)" $(MEX_LDFLAGS) $(MEX_OPT_FILE) 
else
  ifeq ($(MEX_OPTS),-g)
    MEX_FLAGS += -g COPTIMFLAGS="$(GCC_WARN_OPTS) $(ANSI_OPTS)" $(DEFINES_CUSTOM) $(MEX_LDFLAGS) $(MEX_OPT_FILE)
  else
    ifeq ($(OPT_OPTS),-g)
     MEX_FLAGS += $(DEFINES_CUSTOM) $(MEX_OPTS) -g COPTIMFLAGS="$(GCC_WARN_OPTS) $(ANSI_OPTS)" $(MEX_LDFLAGS) $(MEX_OPT_FILE)
    else
       ifneq ($(OPTIMIZATION_FLAGS),)	
           MEX_FLAGS += $(DEFINES_CUSTOM) $(MEX_OPTS) COPTIMFLAGS="$(OPTIMIZATION_FLAGS) $(GCC_WARN_OPTS) $(ANSI_OPTS)" $(MEX_LDFLAGS) $(MEX_OPT_FILE)
       else
           MEX_FLAGS += $(DEFINES_CUSTOM) $(MEX_OPTS) COPTIMFLAGS="$(OPT_OPTS) -DNDEBUG $(GCC_WARN_OPTS) $(ANSI_OPTS)" $(MEX_LDFLAGS) $(MEX_OPT_FILE)
       endif
    endif
  endif
endif

#----------------------------- Source Files -----------------------------------
USER_SRCS =

USER_OBJS       = $(USER_SRCS:.c=.o)
LOCAL_USER_OBJS = $(notdir $(USER_OBJS))

SRCS      = $(MODULES)
SRCS_OBJS = $(addsuffix .o, $(basename $(SRCS)))
OBJS      = $(SRCS_OBJS) $(USER_OBJS)
LINK_OBJS = $(SRCS_OBJS) $(LOCAL_USER_OBJS)

SHARED_SRC := $(wildcard $(SHARED_SRC))
SHARED_OBJS = $(addsuffix .o, $(basename $(SHARED_SRC)))

#-------------------------- Additional Libraries ------------------------------

LIBS =
 
LIBS += $(S_FUNCTIONS_LIB)

ifeq ($(PURIFY),1)
LIBUT = -L$(MATLAB_ROOT)/bin/PURIFY/$(ARCH) -lut
LIBMWMATHUTIL = -L$(MATLAB_ROOT)/bin/PURIFY/$(ARCH) -lmwmathutil
LIBMWSTRINGUTIL = -L$(MATLAB_ROOT)/bin/PURIFY/$(ARCH) -lmwstringutil
else
LIBUT = -L$(MATLAB_ROOT)/bin/$(ARCH) -lut
LIBMWMATHUTIL = -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwmathutil
LIBMWSTRINGUTIL = -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwstringutil
endif

LIBMWIPP = -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwipp

LIBDL = -ldl

LIBM = -lm

MATHLIBS = $(LIBUT) $(LIBMWMATHUTIL) $(LIBMWIPP) $(LIBDL) $(LIBM) $(LIBMWSTRINGUTIL)


ACCELEXTRALIBS += -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwsl_fileio

ACCELEXTRALIBS += -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwsigstream

ACCELEXTRALIBS += -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwsl_AsyncioQueue

ACCELEXTRALIBS += -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwslexec_simbridge

ACCELEXTRALIBS += -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwsimulink

ACCELEXTRALIBS += -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwsl_simtarget_core

ACCELEXTRALIBS += -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwsl_simtarget_instrumentation

ACCELEXTRALIBS += -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwslio_core

ACCELEXTRALIBS += -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwslio_clients


ACCELEXTRALIBS += -L$(MATLAB_ROOT)/bin/$(ARCH) -lmwsl_services

PROGRAM = ../$(MODEL)_acc.$(MEXEXT)

#--------------------------------- Rules --------------------------------------

$(PROGRAM) : $(OBJS) $(SHARED_LIB) $(LIBS)
	@echo "### Linking ..."
	$(CC) $(MEX_FLAGS) -output $(MODEL)_acc $(ARCH_LDFLAGS) -MATLAB_ARCH=$(ARCH) -silent -outdir $(RELATIVE_PATH_TO_ANCHOR) $(LINK_OBJS) $(SHARED_LIB) $(LIBS) $(MATHLIBS) $(ACCELEXTRALIBS)
	@echo "### Created mex file: $(MODEL)_acc.$(MEXEXT)"

%.o : %.c
	$(CC) -c $(MEX_FLAGS) $(INCLUDES) "$<"

%.o : %.cpp
	$(CC) -c $(MEX_FLAGS) $(INCLUDES) "$<"

%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) -c $(MEX_FLAGS) $(INCLUDES) "$<"

%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CC) -c $(MEX_FLAGS) $(INCLUDES) "$<"

%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) -c $(MEX_FLAGS) $(INCLUDES) "$<"
%.o : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) -c $(MEX_FLAGS) $(INCLUDES) "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CC) -c $(MEX_FLAGS) $(INCLUDES) "$<"
%.o : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CC) -c $(MEX_FLAGS) $(INCLUDES) "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) -c $(MEX_FLAGS) $(INCLUDES) "$<"

#------------------------------- Libraries -------------------------------------






clean :
	@echo "### Deleting the objects, libraries and $(PROGRAM)"
	@\rm -f $(wildcard *.o) $(PROGRAM)

#----------------------------- Dependencies -------------------------------

$(OBJS) : $(MAKEFILE) rtw_proj.tmw

$(SHARED_LIB) : $(SHARED_SRC)
	@echo "### Creating $@ "
	cd $(SHARED_BIN_DIR); $(CC) -c $(MEX_FLAGS) $(INCLUDES) $(notdir $?)
	$(AR) ruvs $@ $(SHARED_OBJS)
	@echo "### $@ Created "

