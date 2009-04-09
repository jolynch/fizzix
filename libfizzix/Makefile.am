## Process this file with automake to produce Makefile.in
## Modified from a file by Anjuta of the libgen3d library - will *NOT* be overwritten

SUBDIRS=include src

liblibfizzixdocdir = ${prefix}/doc/libfizzix
liblibfizzixdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS\
	TODO

dist-devpak: all
	rm -rf $(PACKAGE)-$(VERSION)
	mkdir $(PACKAGE)-$(VERSION)
	mkdir $(PACKAGE)-$(VERSION)/lib
	mkdir $(PACKAGE)-$(VERSION)/include
	mkdir $(PACKAGE)-$(VERSION)/include/$(PACKAGE)
	if test -f $(PACKAGE).DevPackage; then \
		cp -p $(PACKAGE).DevPackage $(PACKAGE)-$(VERSION); \
	fi
	for header in include/$(PACKAGE)/*.h; do \
		if test -f $$header; then \
			cp -p $$header $(PACKAGE)-$(VERSION)/include/$(PACKAGE); \
		fi \
	done
	if test -f src/.libs/lib$(PACKAGE).a; then \
		cp -p src/.libs/lib$(PACKAGE).a $(PACKAGE)-$(VERSION)/lib; \
		ranlib $(PACKAGE)-$(VERSION)/lib/lib$(PACKAGE).a; \
		chmod 644 $(PACKAGE)-$(VERSION)/lib/lib$(PACKAGE).a; \
	fi
	if test -f README; then \
        	cp -p README $(PACKAGE)-$(VERSION)/README.txt; \
	fi
	if test -f COPYING; then \
        	cp -p COPYING $(PACKAGE)-$(VERSION)/COPYING.txt; \
	fi
	cd $(PACKAGE)-$(VERSION) && tar cfj ../$(PACKAGE)-$(VERSION).DevPak .
	rm -rf $(PACKAGE)-$(VERSION)

EXTRA_BIN_DISTS = dist-devpak

EXTRA_DIST = $(liblibfizzixdoc_DATA)\
	     libfizzix.pc.in\
	     libfizzix-uninstalled.pc.in\
	     libfizzix-env.sh.in\
	     libfizzix.DevPackage.in\
	     liblibfizzix.cbp\
	     liblibfizzix.dev

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfizzix.pc

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done
