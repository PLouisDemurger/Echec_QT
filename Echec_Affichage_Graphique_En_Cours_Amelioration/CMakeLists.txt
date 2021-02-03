cmake_minimum_required(VERSION 3.10)
project(Echec_Affichage)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

set(affichage_SOURCES main.cpp
        fonction/Jeu.cpp
        fonction/JoueurE.cpp
        fonction/PlateauE.cpp
        fonction/CaseE.cpp
        fonction/PieceE.cpp
        fonction/CoupE.cpp
        fonction/LancementJeu.cpp
        fonction/AffichageCouleurEnCours.cpp)

set(affichage_HEADERS
        header/Jeu.h
        header/JoueurE.h
        header/PlateauE.h
        header/CaseE.h
        header/PieceE.h
        header/CoupE.h
        header/LancementJeu.h
        header/AffichageCouleurEnCours.h)

# set(Qt5_DIR "~/Qt5.14.2/5.14.2/gcc_64/lib/cmake/Qt5")
set(Qt5_DIR "D:/Qt/5.14.2/mingw73_32/lib/cmake/Qt5")

set(CMAKE_PREFIX_PATH  "D:/Qt/5.14.2/mingw73_32/")

set(QT_PLUGIN_PATH "D:/Qt/5.14.2/mingw73_32/bin")

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

include_directories(header)

add_executable(Echec_Affichage
        ${affichage_SOURCES}
        ${affichage_HEADERS})

target_link_libraries(Echec_Affichage Qt5::Core Qt5::Widgets Qt5::Gui)
