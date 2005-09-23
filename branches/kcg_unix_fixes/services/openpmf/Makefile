
.NOTPARALLEL:

SUBDIRS = openpmf_ccm_PEP_ManagerImpl_SERVANT \
	openpmf_ccm_PEP_ManagerImpl \


all: MakeComponentVars $(SUBDIRS:%=%-all)

clean: $(SUBDIRS:%=%-clean)


%-all: %
	$(MAKE) -C $< all


MakeComponentVars:
	cp ${QEDO}/etc/MakeComponentVars .

%-clean: %
	$(MAKE) -C $< clean

package: all
	$(MAKE) -C openpmf_ccm_PEP_ManagerImpl package

distclean: clean
	rm -f MakeComponentVars

install: package $(SUBDIRS:%=%-install)

%-install: %
	$(MAKE) -C $< install
