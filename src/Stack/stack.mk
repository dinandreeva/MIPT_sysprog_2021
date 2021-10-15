all :
% : forward_ # build any target by forwarding to the main makefile
    $(MAKE) -C .. project_dirs=$(notdir ${CURDIR}) $@
.PHONY : forward_
