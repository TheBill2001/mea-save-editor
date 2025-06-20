# SPDX-FileCopyrightText: 2025 Trần Nam Tuấn <tuantran1632001@gmail.com>
# SPDX-License-Identifier: GPL-3.0-only

qt_add_library(mea-save-editor_static STATIC)
ecm_add_qml_module(mea-save-editor_static
    URI thebill2001.measaveeditor
    GENERATE_PLUGIN_SOURCE
    QML_FILES
        qml/Main.qml
    DEPENDENCIES
        org.kde.kirigami
        org.kde.kirigamiaddons.formcard
        org.kde.kirigamiaddons.components
        org.kde.kirigamiaddons.statefulapp
)

target_sources(mea-save-editor_static PRIVATE
    measaveeditorapplication.cpp
    measaveeditorapplication.hpp
    measaveeditorconfig.cpp
    measaveeditorconfig.hpp

    data/measavefile.cpp
    data/measavefile.hpp
    data/measavefileheader.cpp
    data/measavefileheader.hpp
    data/measavefilemanager.cpp
    data/measavefilemanager.hpp
    data/measavefileerror.cpp
    data/measavefileerror.hpp
    data/p_measavefileutils.hpp

    utils/datetime.cpp
    utils/datetime.hpp
    utils/number.hpp
    utils/hashing/djb.hpp
)

target_link_libraries(mea-save-editor_static PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Svg
    Qt6::Widgets

    KF6::I18n
    KF6::I18nQml
    KF6::IconThemes
    KF6::CoreAddons
    KF6::ConfigCore

    KirigamiAddonsStatefulApp

    ZLIB::ZLIB
)
target_include_directories(mea-save-editor_static PUBLIC
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/data"
)

kconfig_add_kcfg_files(mea-save-editor_static GENERATE_MOC measaveeditorconfigbase.kcfgc)

add_executable(mea-save-editor main.cpp)
target_link_libraries(mea-save-editor PUBLIC
    mea-save-editor_static
    mea-save-editor_staticplugin
)
install(TARGETS mea-save-editor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
