# Cudd stuff:
CUDDVER=cudd-3.0.0
CUDDINC=./$(CUDDVER)/include
# CUDDLIBDIR=./$(CUDDVER)/lib
CUDDLIBDIR=
CUDDLIBS=cudd mtr st util
#ifeq ($(CUDDVER),cudd-2.4.1) # for Cudd 2.4.1, add the "epd" library in LIBS
  CUDDLIBS += epd
#endif
# Compiler options
TARGET = mql
TARGETDB = dbmql
TARGETDDB = ddbmql

CC = gcc -g -Wall $(CDBG) $(CDDBG) -I$(CUDDINC)
CPP = g++ -g -Wall $(CDBG) $(CDDBG) -I$(CUDDINC)
LINK=g++ -g $(CDBG) $(CDDBG)
# LIBS = -L$(CUDDLIBDIR) \
# 	-lm $(patsubst %,-l%,$(CUDDLIBS))
CFLAGS = -I $(CUDDVER)/cudd -I $(CUDDVER)/util -I $(CUDDVER)
LFLAGS = -L $(CUDDVER)/cudd/.libs/ -lcudd -lm
O = o

# Modules:
#TMPFILES = irParse.c irLex.c

PARSE = parse
ANALYSE = analyse

IR_MODULES = $(PARSE)/irCon $(PARSE)/irMain $(PARSE)/irName $(PARSE)/irParse $(PARSE)/irPrintx
INT_MODULES = $(PARSE)/intPds $(PARSE)/intExpr $(PARSE)/intBuild $(PARSE)/intSet
ANALYSE_MODULES = $(ANALYSE)/main  $(ANALYSE)/preAnalysis $(ANALYSE)/printADD $(ANALYSE)/wrapper
ENTROPY_MODULES = $(ANALYSE)/minEntropy $(ANALYSE)/shannonEntropy

MODULES = $(PARSE)/ident $(PARSE)/hash $(IR_MODULES) $(INT_MODULES) $(ANALYSE_MODULES) $(ENTROPY_MODULES)

OBJECTS = $(MODULES:=.$(O))

# Compiling:
##### Use 'make' or 'make mql' for normal mode; Use 'make dbmql' for debug mode

$(TARGETDDB): CDDBG = -Dddb
$(TARGETDDB): CDBG = -Ddb
$(TARGETDB): CDBG = -Ddb
	
$(TARGET): $(OBJECTS)
	$(LINK) $(OBJECTS) -o $@ $(LIBS) $(LFLAGS)
	
$(TARGETDB): $(OBJECTS)
	$(LINK) $(OBJECTS) -o $@ $(LIBS) $(LFLAGS)
	
$(TARGETDDB): $(OBJECTS) 
	$(LINK) $(OBJECTS) -o $@ $(LIBS) $(LFLAGS)

%.$(O): %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.$(O): %.cpp
	$(CPP) -c -o $@ $< $(CFLAGS)

# clean
clean: 
	rm -rf $(TARGET) $(TARGETDB) $(TARGETDDB) \
              core core.* *.$(O) *.output mon.out gmon.out out *.d .deps *~ $(ANALYSE)/*.$(O) $(ANALYSE)/*~ \
              $(PARSE)/core $(PARSE)/core.* $(PARSE)/*.$(O) $(PARSE)/*.output $(PARSE)/mon.out\
              $(PARSE)/gmon.out $(PARSE)/*.d $(PARSE)/*.o $(PARSE)/.deps $(PARSE)/*.dot $(PARSE)/*.pdf $(PARSE)/*~
              
cclean:
	rm -rf $(TARGET) $(TARGETDB) $(TARGETDDB) \
              core core.* *.$(O) *.output mon.out gmon.out out *.d .deps *~ $(ANALYSE)/*.$(O) $(ANALYSE)/*~ \
              $(PARSE)/core $(PARSE)/core.* $(PARSE)/*.$(O) $(PARSE)/*.output $(PARSE)/mon.out\
              $(PARSE)/gmon.out $(PARSE)/*.d $(PARSE)/*.o $(PARSE)/.deps $(PARSE)/*.dot $(PARSE)/*.pdf $(PARSE)/*~\
              $(PARSE)/irLex.c $(PARSE)/irParse.c

# Parsers:
$(PARSE)/irParse.$(O): $(PARSE)/irParse.c $(PARSE)/irLex.c
$(PARSE)/irParse.c: $(PARSE)/irParse.y $(PARSE)/irLex.c
	bison $(PARSE)/irParse.y -p ir -o $@
$(PARSE)/irLex.c: $(PARSE)/irLex.l
	flex -o$@ -Pir $(PARSE)/irLex.l

# Dependencies

%.d: %.c
	$(SHELL) -ec '$(CC) -MM $< | sed '\''s,$*.o,& $@,g'\'' > $@'

DEPS = $(OBJECTS:%.$(O)=%.d)

.deps: $(DEPS)
	echo " " $(DEPS) | \
	sed 's/[ 	][ 	]*/#include /g' | tr '#' '\012' > .deps

#include .deps
