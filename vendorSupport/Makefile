TOP=../
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================


ifeq (x86_64, $(findstring x86_64, $(T_A)))
LIB_INSTALLS    += ../lib/libst_if_client.a
LIB_INSTALLS    += ../lib/libst_if_common.a
LIB_INSTALLS    += ../lib/libstdatastore.a
LIB_INSTALLS    += ../lib/libstutil.a
endif

ifeq (x86_64-debug, $(findstring x86_64-debug, $(T_A)))
LIB_INSTALLS    += ../lib/libst_if_client.a
LIB_INSTALLS    += ../lib/libst_if_common.a
LIB_INSTALLS    += ../lib/libstdatastore.a
LIB_INSTALLS    += ../lib/libstutil.a
endif


#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

