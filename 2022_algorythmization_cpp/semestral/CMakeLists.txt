cmake_minimum_required(VERSION 3.10)
project(minestream)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra")

add_executable(duelheroes src/Core/main.cpp src/Core/CCommand.cpp src/Core/CCommand.h src/Core/CCommandPlayer.cpp src/Core/CCommandPlayer.h src/Core/CCommandApp.cpp src/Core/CCommandApp.h src/Core/CGame.h src/Core/CGame.cpp src/Core/CApplication.cpp src/Core/CApplication.h src/Core/commands.h src/Core/commands.cpp src/Core/CInterface.cpp src/Core/CInterface.h
        src/Features/CPlayer.cpp src/Features/CPlayer.h src/Features/CPlayerHuman.cpp src/Features/CPlayerHuman.h src/Features/CPlayerAI.cpp src/Features/CPlayerAI.h
        src/Features/CCard.cpp src/Features/CCard.h src/Features/CCardAction.cpp src/Features/CCardAction.h src/Features/CCardCharacter.cpp src/Features/CCardCharacter.h
        src/Features/CEffect.cpp src/Features/CEffect.h src/Features/CEffectAttack.cpp src/Features/CEffectAttack.cpp src/Features/CEffectBuff.cpp src/Features/CEffectBuff.cpp
        src/Core/CCardParser.cpp src/Core/CCardParser.h src/Core/Reader.cpp src/Core/Reader.h)
