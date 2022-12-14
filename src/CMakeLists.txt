cmake_minimum_required(VERSION 3.20)
project(src)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(src main.cpp MainWindow.cpp MainWindow.h widgets/GraphicsListWidget.cpp
        widgets/GraphicsListWidget.h widgets/other/StyleSheetsHelper.h widgets/PlotArea.cpp
        widgets/PlotArea.h widgets/buttons/IconsButton.cpp widgets/buttons/IconsButton.h
        widgets/GraphicsItem.cpp widgets/GraphicsItem.h resources.qrc widgets/buttons/CustomButton.h
        external/QCustomPlot/qcustomplot.cpp external/QCustomPlot/qcustomplot.h external/parser/muParser.cpp
        external/parser/muParser.h external/parser/muParserBase.cpp external/parser/muParserBase.h external/parser/muParserBytecode.cpp
        external/parser/muParserBytecode.h external/parser/muParserCallback.cpp external/parser/muParserCallback.h
        external/parser/muParserComplex.cpp external/parser/muParserComplex.h external/parser/muParserDef.h
        external/parser/muParserDLL.cpp external/parser/muParserDLL.h external/parser/muParserError.cpp
        external/parser/muParserError.h external/parser/muParserFixes.h
        external/parser/muParserInt.cpp
        external/parser/muParserInt.h
        external/parser/muParserStack.h
        external/parser/muParserTest.cpp
        external/parser/muParserTest.h
        external/parser/muParserToken.h
        external/parser/muParserTokenReader.cpp
        external/parser/muParserTokenReader.h)
target_link_libraries(src
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
#        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
