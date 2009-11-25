# **********************************************************************
#
# Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

top_srcdir	= ..\..

!include $(top_srcdir)\config\Make.rules.mak

SUBDIRS		= proxy \
		  operations \
		  exceptions \
		  ami \
		  info \
		  inheritance \
		  facets \
		  objects \
		  faultTolerance \
		  location \
		  adapterDeactivation \
		  slicing \
		  gc \
		  checksum \
		  hold \
		  custom \
		  binding \
		  retry \
		  timeout \
		  servantLocator \
		  interceptor \
		  stringConverter \
		  background \
		  udp \
		  defaultServant \
		  threadPoolPriority

!if "$(CPP_COMPILER)" != "VC60"
SUBDIRS		= $(SUBDIRS) \
		  stream
!endif

$(EVERYTHING)::
	@for %i in ( $(SUBDIRS) ) do \
	    @echo "making $@ in %i" && \
	    cmd /c "cd %i && $(MAKE) -nologo -f Makefile.mak $@" || exit 1
