cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project ("Wolfenstein3D" LANGUAGES CXX)
FILE(
	COPY "${CMAKE_CURRENT_SOURCE_DIR}/images"
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)
FILE(
	COPY "${CMAKE_CURRENT_SOURCE_DIR}/fonts"
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)
set(
	HEADERS
    "src/Animation/Animation.h"
	"src/Constants/game_settings.h"
	"src/Constants/ray_cast_settings.h"
	"src/Constants/texture_settings.h"
	"src/ConstantShootingAnimation/ConstantShootingAnimation.h"
	"src/ContinuousShootingAnimation/ContinuousShootingAnimation.h"
	"src/EndingGameState/EndingGameState.h"
	"src/Game/Game.h"
	"src/GameData/GameData.h"
	"src/GameLogic/GameLogic.h"
	"src/GameState/GameState.h"
	"src/Object/Object.h"
	"src/Objects/Objects.h"
	"src/Player/Player.h"
	"src/PlayingGameState/PlayingGameState.h"
	"src/RenderableObject/RenderableObject.h"
	"src/RenderableObjects/RenderableObjects.h"
	"src/ResourceManager/ResourceManager.h"
	"src/ShootingAnimation/ShootingAnimation.h"
	"src/StartingGameState/StartingGameState.h"
	"src/Walls/Walls.h"
	"src/Weapon/Weapon.h"
	"src/Weapons/Weapons.h"
	"src/WorldMap/WorldMap.h"
	"src/PickableItem/PickableItem.h"
	"src/PickableHealth/PickableHealth.h"
	"src/PickableWeapon/PickableWeapon.h"
	"src/PickableScore/PickableScore.h"
	"src/NotPickableItem/NotPickableItem.h"
	"src/SS/SS.h"
	"src/Enemy/Enemy.h"
	"src/Enemies/Enemies.h"
)
set(
	SOURCE_CPP
    "src/Animation/Animation.cpp"
	"src/ConstantShootingAnimation/ConstantShootingAnimation.cpp"
	"src/ContinuousShootingAnimation/ContinuousShootingAnimation.cpp"
	"src/EndingGameState/EndingGameState.cpp"
	"src/Game/Game.cpp"
	"src/GameLogic/GameLogic.cpp"
	"src/GameState/GameState.cpp"
	"src/Object/Object.cpp"
	"src/Objects/Objects.cpp"
	"src/Player/Player.cpp"
	"src/PlayingGameState/PlayingGameState.cpp"
	"src/RenderableObjects/RenderableObjects.cpp"
	"src/ResourceManager/ResourceManager.cpp"
	"src/ShootingAnimation/ShootingAnimation.cpp"
	"src/StartingGameState/StartingGameState.cpp"
	"src/Walls/Walls.cpp"
	"src/Weapon/Weapon.cpp"
	"src/Weapons/Weapons.cpp"
	"src/WorldMap/WorldMap.cpp"
	"src/PickableItem/PickableItem.cpp"
	"src/PickableHealth/PickableHealth.cpp"
	"src/PickableWeapon/PickableWeapon.cpp"
	"src/PickableScore/PickableScore.cpp"
	"src/NotPickableItem/NotPickableItem.cpp"
	"src/SS/SS.cpp"
	"src/Enemy/Enemy.cpp"
	"src/Enemies/Enemies.cpp"
)
set(
	SOURCE_EXE
	"src/Main/Main.cpp"
)
add_executable(Wolfenstein ${HEADERS} ${SOURCE_CPP} ${SOURCE_EXE})
set(SFML_STATIC_LIBRARIES TRUE)
if(MINGW)
	set(SFML_DIR "C:/Libs/SFML-2.5.1/lib/cmake/SFML")
elseif(MSVC)
	set(SFML_DIR "C:/Libs/SFML-x64/SFML-2.5.1/lib/cmake/SFML")
endif()
find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)
target_link_libraries(Wolfenstein sfml-system sfml-window sfml-graphics)