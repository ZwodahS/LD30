WARNING= -Wextra -Wno-switch -Wno-sign-compare -Wno-missing-braces -Wno-unused-parameter
OPTIMIZE= -fno-exceptions

TARGET=notHack
BIN=bin

BOOST=-l boost_system -l boost_filesystem
SFML=-framework sfml-graphics -framework sfml-system -framework sfml-window

OBJDIR=obj

vpath %.cpp game/
vpath %.hpp game/
vpath %.cpp game/ui
vpath %.hpp game/ui
vpath %.cpp game/objects
vpath %.hpp game/objects
vpath %.cpp zf/
vpath %.hpp zf/

vpath %.o $(OBJDIR)/

CXX=clang++ ${WARNING} -std=c++11 ${OPTIMIZE}

cppfiles=$(shell find . -name "*.cpp" -exec basename {} \;)
hppfiles=$(shell find . -name "*.hpp" -exec basename {} \;)
objs=$(patsubst %, $(OBJDIR)/%, $(cppfiles:.cpp=.o))

all: $(BIN)/$(TARGET)

$(BIN)/$(TARGET) : $(objs)
	$(CXX) -o $(BIN)/$(TARGET) $(OBJDIR)/*.o $(SFML) # $(BOOST)

$(OBJDIR)/%.o : %.cpp $(hppfiles)
	$(CXX) -c -o $@ $<

clean:
	rm -f obj/*.o
	rm -f $(BIN)/$(TARGET)

remake:
	make clean
	make all

debug:
	@echo $(cppfiles)
	@echo $(hppfiles)

.PHONY: clean remake debug
