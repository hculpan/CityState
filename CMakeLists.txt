cmake_minimum_required(VERSION 3.12)

project(CityState)

set(SOURCE
    src/Button.cpp
    src/Component.cpp
    src/FontManager.cpp
    src/Game.cpp
    src/MainWindow.cpp
    src/TextOutput.cpp
    src/Window.cpp
    src/terrain/BaseTerrain.cpp
    src/terrain/UnknownTerrain.cpp
    src/main.cpp
)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
#find_path(SDL2_TTF_DIR SDL_ttf.h PATHS /Library/Frameworks/SDL2_image.framework/Headers)
#find_path(SDL2_IMAGE_DIR NAMES SDL_image.h)

if (APPLE)
    set(SDL2_TTF_DIR /Library/Frameworks/SDL2_ttf.framework/Headers)
    set(SDL2_IMAGE_DIR /Library/Frameworks/SDL2_image.framework/Headers)
endif()

find_library(SDL2_LIBRARY NAME SLD2)
find_library(SDL2_IMAGE_LIB NAME SLD2_image)

message(${SDL2_TTF_DIR})
message(${SDL2_IMAGE_DIR})

if (NOT SDL2_LIBRARY)
    if (APPLE)
        set(SDL2_LIBRARY /Library/Frameworks/SDL2.framework/Versions/Current/SDL2)
    endif()
endif()

if (NOT SDL2_TTF_LIB)
    if (APPLE)
        set(SDL2_TTF_LIB /Library/Frameworks/SDL2_ttf.framework/Versions/Current/SDL2_ttf)
    endif()
endif()

if (NOT SDL2_IMAGE_LIB)
    if (APPLE)
        set(SDL2_IMAGE_LIB /Library/Frameworks/SDL2_image.framework/Versions/Current/SDL2_image)
    endif()
endif()

add_executable(CityState ${SOURCE})

if (APPLE)
    set_target_properties(CityState PROPERTIES MACOSX_BUNDLE TRUE)
endif()

target_include_directories (
    CityState
    PUBLIC
    ${SDL2_INCLUDE_DIR}
    ${SDL2_TTF_DIR}
    ${SDL2_IMAGE_DIR}
)

target_link_libraries (
    CityState 
    PUBLIC
    ${SDL2_LIBRARY}
    ${SDL2_TTF_LIB}
    ${SDL2_IMAGE_LIB}   
)

target_compile_features(CityState PRIVATE cxx_lambda_init_captures)

