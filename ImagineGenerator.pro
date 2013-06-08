isEmpty(PREFIX):PREFIX=/usr/local

QT += core gui widgets xml script

HEADERS += \
    model/pointtype.h \
    model/componenttype.h \
    version.h \
    renderer/scriptablecalculator.h \
    renderer/colorcalculator.h \
    renderer/imaginerender.h \
    gui/canvas.h \
    gui/window.h \
    renderer/renderthread.h \
    gui/renderwaitdialog.h \
    gui/exportsize.h \
    model/layer.h \
    gui/layersettings.h \
    storage/storageerror.h \
    storage/projectstorage.h \
    gui/about.h \
    renderer/scriptapi.h

SOURCES += \
    main.cpp \
    renderer/scriptablecalculator.cpp \
    renderer/colorcalculator.cpp \
    renderer/imaginerender.cpp \
    gui/canvas.cpp \
    gui/window.cpp \
    renderer/renderthread.cpp \
    gui/renderwaitdialog.cpp \
    gui/exportsize.cpp \
    model/layer.cpp \
    gui/layersettings.cpp \
    storage/storageerror.cpp \
    storage/projectstorage.cpp \
    gui/about.cpp \
    renderer/scriptapi.cpp

FORMS += \
    gui/renderwaitdialog.ui \
    gui/exportsize.ui \
    gui/layersettings.ui \
    gui/about.ui

TARGET = "imagine-generator"

win32:TARGET = "imagine"

target.path=$${PREFIX}/bin
INSTALLS+=target

icon16.path=$${PREFIX}/share/icons/hicolor/16x16/apps/
icon16.files+=icons/16x16/imaginegenerator.png
INSTALLS+=icon16

icon22.path=$${PREFIX}/share/icons/hicolor/22x22/apps/
icon22.files+=icons/22x22/imaginegenerator.png
INSTALLS+=icon22

icon24.path=$${PREFIX}/share/icons/hicolor/24x24/apps/
icon24.files+=icons/24x24/imaginegenerator.png
INSTALLS+=icon24

icon32.path=$${PREFIX}/share/icons/hicolor/32x32/apps/
icon32.files+=icons/32x32/imaginegenerator.png
INSTALLS+=icon32

icon48.path=$${PREFIX}/share/icons/hicolor/48x48/apps/
icon48.files+=icons/48x48/imaginegenerator.png
INSTALLS+=icon48

icon256.path=$${PREFIX}/share/icons/hicolor/256x256/apps/
icon256.files+=icons/256x256/imaginegenerator.png
INSTALLS+=icon256

desktopfile.path=$${PREFIX}/share/applications/
desktopfile.files+=resources/imaginegenerator.desktop
INSTALLS+=desktopfile

translations.path=$${PREFIX}/share/imaginegenerator/translations/
translations.files+=*.qm
INSTALLS+=translations

ICON = resources/icon.ico

RESOURCES += \
    resources/resources.qrc

TRANSLATIONS += \
    Russian.ts
