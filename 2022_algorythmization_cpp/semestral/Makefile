TARGET=charbjak

CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17
MKDIR=mkdir -p

SOURCE_DIR = src
CORE_SUBDIR = Core
FEATURES_SUBDIR = Features
BUILD_DIR = build

SOURCES = $(wildcard $(SOURCE_DIR)/*/*.cpp)
HEADERS = $(wildcard $(SOURCE_DIR)/*/*.h)

OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)


.PHONY: all
all: compile doc
	@echo "Finished..."


.PHONY: compile
compile: $(TARGET)
	@echo "Compile..."


.PHONY: run
run: $(TARGET)
	./$(TARGET)


$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@


$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(MKDIR) $(BUILD_DIR)/$(CORE_SUBDIR) $(BUILD_DIR)/$(FEATURES_SUBDIR)
	$(CXX) $(CXXFLAGS) $< -c -o $@


doc: Doxyfile README.md $(HEADERS)
	doxygen Doxyfile

EXAMPLES = $(wildcard examples/*)
$(TARGET).zip: README.md zadani.txt prohlaseni.txt Makefile Doxyfile $(HEADERS) $(SOURCES) $(EXAMPLES)
	mkdir -p .archive/$(TARGET)/
	cp -r README.md zadani.txt prohlaseni.txt Makefile Doxyfile src/ examples/ .archive/$(TARGET)/
	cd .archive/; zip -r ../$(TARGET).zip $(TARGET)/
	rm -r .archive/

.PHONY: clean
clean:
	rm -rf $(TARGET) $(TARGET).zip doc/ .archive/ $(BUILD_DIR)/ 2>/dev/null


build/CApplication.o: src/Core/CApplication.cpp src/Core/CApplication.h \
 src/Core/CInterface.h src/Core/CGame.h src/Core/CCommandPlayer.h \
 src/Core/CCommand.h src/Core/../Features/CPlayer.h \
 src/Core/../Features/CCardCharacter.h src/Core/../Features/CCard.h \
 src/Core/../Features/../Core/Reader.h src/Core/../Features/CCardAction.h \
 src/Core/../Features/CEffect.h src/Core/CCommandApp.h \
 src/Core/commands.h
build/CCardParser.o: src/Core/CCardParser.cpp src/Core/CCardParser.h \
 src/Core/../Features/CCard.h src/Core/../Features/../Core/Reader.h \
 src/Core/../Features/CCardCharacter.h src/Core/../Features/CCardAction.h \
 src/Core/../Features/CEffect.h src/Core/../Features/CPlayer.h \
 src/Core/../Features/../Core/CInterface.h \
 src/Core/../Features/CEffectBuff.h src/Core/../Features/CEffectAttack.h
build/CCommand.o: src/Core/CCommand.cpp src/Core/CCommand.h
build/CCommandApp.o: src/Core/CCommandApp.cpp src/Core/CCommandApp.h \
 src/Core/CInterface.h src/Core/CCommand.h
build/CCommandPlayer.o: src/Core/CCommandPlayer.cpp src/Core/CCommandPlayer.h \
 src/Core/CCommand.h src/Core/CGame.h src/Core/../Features/CPlayer.h \
 src/Core/../Features/../Core/CInterface.h \
 src/Core/../Features/CCardCharacter.h src/Core/../Features/CCard.h \
 src/Core/../Features/../Core/Reader.h src/Core/../Features/CCardAction.h \
 src/Core/../Features/CEffect.h
build/CGame.o: src/Core/CGame.cpp src/Core/CGame.h src/Core/CCommandPlayer.h \
 src/Core/CCommand.h src/Core/CInterface.h src/Core/../Features/CPlayer.h \
 src/Core/../Features/CCardCharacter.h src/Core/../Features/CCard.h \
 src/Core/../Features/../Core/Reader.h src/Core/../Features/CCardAction.h \
 src/Core/../Features/CEffect.h src/Core/commands.h \
 src/Core/CCommandApp.h src/Core/../Features/CPlayerHuman.h \
 src/Core/../Features/CPlayerAI.h src/Core/CCardParser.h \
 src/Core/../Features/CEffectBuff.h src/Core/../Features/CEffectAttack.h
build/CInterface.o: src/Core/CInterface.cpp src/Core/CInterface.h
build/Reader.o: src/Core/Reader.cpp src/Core/../Features/CCardAction.h \
 src/Core/../Features/CCard.h src/Core/../Features/../Core/Reader.h \
 src/Core/../Features/CEffect.h src/Core/../Features/CPlayer.h \
 src/Core/../Features/../Core/CInterface.h \
 src/Core/../Features/CCardCharacter.h
build/commands.o: src/Core/commands.cpp src/Core/commands.h \
 src/Core/CCommandApp.h src/Core/CInterface.h src/Core/CCommand.h \
 src/Core/CCommandPlayer.h src/Core/CGame.h \
 src/Core/../Features/CPlayer.h src/Core/../Features/CCardCharacter.h \
 src/Core/../Features/CCard.h src/Core/../Features/../Core/Reader.h \
 src/Core/../Features/CCardAction.h src/Core/../Features/CEffect.h \
 src/Core/CApplication.h src/Core/../Features/CPlayerAI.h \
 src/Core/../Features/CPlayerHuman.h
build/main.o: src/Core/main.cpp src/Core/CApplication.h src/Core/CInterface.h \
 src/Core/CGame.h src/Core/CCommandPlayer.h src/Core/CCommand.h \
 src/Core/../Features/CPlayer.h src/Core/../Features/CCardCharacter.h \
 src/Core/../Features/CCard.h src/Core/../Features/../Core/Reader.h \
 src/Core/../Features/CCardAction.h src/Core/../Features/CEffect.h \
 src/Core/CCommandApp.h src/Core/commands.h
build/CCard.o: src/Features/CCard.cpp src/Features/CCard.h \
 src/Features/../Core/Reader.h
build/CCardAction.o: src/Features/CCardAction.cpp src/Features/CCardAction.h \
 src/Features/CCard.h src/Features/../Core/Reader.h \
 src/Features/CEffect.h src/Features/CPlayer.h \
 src/Features/../Core/CInterface.h src/Features/CCardCharacter.h
build/CCardCharacter.o: src/Features/CCardCharacter.cpp \
 src/Features/CCardCharacter.h src/Features/CCard.h \
 src/Features/../Core/Reader.h
build/CEffect.o: src/Features/CEffect.cpp src/Features/CEffect.h \
 src/Features/CPlayer.h src/Features/../Core/CInterface.h \
 src/Features/CCardCharacter.h src/Features/CCard.h \
 src/Features/../Core/Reader.h src/Features/CCardAction.h
build/CEffectAttack.o: src/Features/CEffectAttack.cpp \
 src/Features/CEffectAttack.h src/Features/CEffect.h \
 src/Features/CPlayer.h src/Features/../Core/CInterface.h \
 src/Features/CCardCharacter.h src/Features/CCard.h \
 src/Features/../Core/Reader.h src/Features/CCardAction.h
build/CEffectBuff.o: src/Features/CEffectBuff.cpp src/Features/CEffectBuff.h \
 src/Features/CEffect.h src/Features/CPlayer.h \
 src/Features/../Core/CInterface.h src/Features/CCardCharacter.h \
 src/Features/CCard.h src/Features/../Core/Reader.h \
 src/Features/CCardAction.h
build/CPlayer.o: src/Features/CPlayer.cpp src/Features/CPlayer.h \
 src/Features/../Core/CInterface.h src/Features/CCardCharacter.h \
 src/Features/CCard.h src/Features/../Core/Reader.h \
 src/Features/CCardAction.h src/Features/CEffect.h
build/CPlayerAI.o: src/Features/CPlayerAI.cpp src/Features/CPlayerAI.h \
 src/Features/CPlayer.h src/Features/../Core/CInterface.h \
 src/Features/CCardCharacter.h src/Features/CCard.h \
 src/Features/../Core/Reader.h src/Features/CCardAction.h \
 src/Features/CEffect.h src/Features/../Core/CGame.h \
 src/Features/../Core/CCommandPlayer.h src/Features/../Core/CCommand.h
build/CPlayerHuman.o: src/Features/CPlayerHuman.cpp src/Features/CPlayerHuman.h \
 src/Features/../Core/CInterface.h src/Features/CPlayer.h \
 src/Features/CCardCharacter.h src/Features/CCard.h \
 src/Features/../Core/Reader.h src/Features/CCardAction.h \
 src/Features/CEffect.h