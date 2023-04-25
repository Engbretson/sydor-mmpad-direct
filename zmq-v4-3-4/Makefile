TOP=../
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

INC += zmq.h
INC +=zmq_utils.h


ifeq (x86_64, $(findstring x86_64, $(T_A)))
LIB_INSTALLS    += ../lib/libzmq.a
LIB_INSTALLS    += ../lib/libzmq.so
LIB_INSTALLS    += ../lib/libzmq.so.5
LIB_INSTALLS    += ../lib/libzmq.so.5.2.5
endif

ifeq (x86_64-debug, $(findstring x86_64-debug, $(T_A)))
LIB_INSTALLS    += ../lib/libzmq.a
LIB_INSTALLS    += ../lib/libzmq.so
LIB_INSTALLS    += ../lib/libzmq.so.5
LIB_INSTALLS    += ../lib/libzmq.so.5.2.5
endif


#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

