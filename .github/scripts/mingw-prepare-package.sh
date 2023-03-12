#!/usr/bin/env bash
## Copy to build
# PATH::/mingw64/bin/
export PACKAGE_PATH=./tuningTrainer/tuningTrainer-win/
mkdir -p $PACKAGE_PATH

function installFile(){
    cp -Rv ${1} ${PACKAGE_PATH} || echo "NOT FOUND"
}

installFile ./bin/tuningTrainer.exe
installFile ../src/harpsichord.wav

for i in \
libgcc_s_seh-1.dll \
libwinpthread-1.dll \
libpcre2-16-0.dll \
libpcre-1.dll \
libstdc++-6.dll \
libzstd.dll \
zlib1.dll \
libharfbuzz-0.dll \
libfreetype-6.dll \
libdouble-conversion.dll \
libicuin69.dll \
libicuuc69.dll \
libicudt69.dll \
libbz2-1.dll \
libbrotlidec.dll \
libbrotlicommon.dll \
libpng16-16.dll \
libglib-2.0-0.dll \
libintl-8.dll \
libiconv-2.dll \
libgraphite2.dll \
libmd4c.dll \
Qt5Core.dll \
Qt5Gui.dll \
Qt5Widgets.dll
do installFile /mingw64/bin/${i}

done

installFile /mingw64/share/qt5/plugins/platforms
installFile /mingw64/share/qt5/plugins/styles

