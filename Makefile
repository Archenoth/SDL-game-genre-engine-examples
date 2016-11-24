SIDESCROLLER_SRC=sidescroller.c
TOPVIEW_SRC=topview.c

SIDESCROLLER_OUT=sidescroller
TOPVIEW_OUT=topview

FLAGS=-Wall `sdl2-config --libs --cflags`

.PHONY: check-syntax clean help

all: $(SIDESCROLLER_OUT) $(TOPVIEW_OUT)

sidescroller: $(SIDESCROLLER_SRC)
	$(CC) $(SIDESCROLLER_SRC) $(FLAGS) -o $@

topview: $(TOPVIEW_SRC)
	$(CC) $(TOPVIEW_SRC) $(FLAGS) -o $@


clean:
	-$(RM) $(SIDESCROLLER_OUT)
	-$(RM) $(TOPVIEW_OUT)

help:
	@echo Make rules
	@echo $(SIDESCROLLER_OUT)		Builds Linux Binary for the sidescroller engine
	@echo $(TOPVIEW_OUT)		Builds Linux Binary for the topview engine
	@echo all			Builds all Binaries
	@echo clean			Removes built binaries
	@echo check-syntax	Checks the syntax of the source files

check-syntax:
	-$(CC) $(SIDESCROLLER_SRC) $(FLAGS) -o null -Wall
	-$(CC) $(TOPVIEW_SRC) $(FLAGS) -o null -Wall
	-$(RM) null
