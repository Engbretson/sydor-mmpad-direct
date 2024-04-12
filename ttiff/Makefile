TOP=../
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================


INC += tinytiff_defs.h
INC += tinytiff_export.h
#INC += tinytiff_tools.hxx
INC += tinytiffreader.h
#INC += tinytiffreader.hxx
INC += tinytiffwriter.h


ifeq (x86_64, $(findstring x86_64, $(T_A)))
LIB_INSTALLS    += ../lib/libTinyTIFFShared_Release.so
LIB_INSTALLS    += ../lib/libTinyTIFFShared_Release.so.3.0.0.0
LIB_INSTALLS    += ../lib/libTinyTIFF_Release.a

endif

ifeq (x86_64-debug, $(findstring x86_64-debug, $(T_A)))
LIB_INSTALLS    += ../lib/libTinyTIFFShared_Release.so
LIB_INSTALLS    += ../lib/libTinyTIFFShared_Release.so.3.0.0.0
LIB_INSTALLS    += ../lib/libTinyTIFF_Release.a

endif


#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

