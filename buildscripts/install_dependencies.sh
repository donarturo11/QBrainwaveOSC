#!/usr/bin/env bash
#set -e
export ENV_FILE=${ENV_FILE:-$TMPDIR/environment.sh}
[[ -e $ENV_FILE ]] && . $ENV_FILE
QT_ENV=$ENV_DIR/qt.sh
FFTW_ENV=$ENV_DIR/fftw.sh
SCRIPTS_DIR=${SCRIPTS_DIR:-$(cd $(dirname 0); pwd)}
echo CHOST=$CHOST
if [[ -e $SCRIPTS_DIR/aqt/${CHOST}-qt${QT_VERSION_MAJOR}.sh ]]; then
  . $SCRIPTS_DIR/aqt/${CHOST}-qt${QT_VERSION_MAJOR}.sh
  cd $TMPDIR
  (which aqt &> /dev/null) || python -m pip install aqtinstall
  aqt install-qt -O $(pwd)/qt $AQT_HOST desktop $AQT_VERSION ${AQT_OS}_${AQT_ARCH} -m $AQT_MODULES
  QT_ROOT_DIR=$(pwd)/qt/${AQT_VERSION}/${AQT_ARCH}
  echo "export QT_ROOT_DIR=\"$QT_ROOT_DIR\"" > $QT_ENV
  echo "export PATH=\"\${QT_ROOT_DIR}/bin:\$PATH\"" >> $QT_ENV
  echo "export CMAKE_PREFIX_PATH=\"\${CMAKE_PREFIX_PATH}:\$QT_ROOT_DIR\"" >> $QT_ENV
fi
case $CHOST in
  *-windows-msvc)
    cd $TMPDIR
    mkdir fftw3-lib
    cd fftw3-lib
    curl -LO https://fftw.org/pub/fftw/fftw-3.3.5-dll64.zip
    /c/windows/system32/tar.exe -xf fftw-3.3.5-dll64.zip
    lib /machine:x64 /def:libfftw3-3.def
    FFTW_ROOT_DIR=$(pwd)
    echo "export FFTW_ROOT_DIR=\"$FFTW_ROOT_DIR\"" > $FFTW_ENV
    echo "export CMAKE_PREFIX_PATH=\"\${CMAKE_PREFIX_PATH}\${CMAKE_PREFIX_PATH:+:}\$FFTW_ROOT_DIR\"" >> $FFTW_ENV
    ;;
  *-w64-mingw32)
    pacboy -S --needed --noconfirm \
      toolchain \
      cmake \
      ninja \
      nsis \
      qt${QT_VERSION_MAJOR}-base \
      qt${QT_VERSION_MAJOR}-serialport \
      qt${QT_VERSION_MAJOR}-charts \
      qt${QT_VERSION_MAJOR}-tools \
      gles-headers \
      glew \
      glfw \
      angleproject \
      fftw
    ;;
  *-linux-*)
    DISTRIBUTION_ID=$( . /etc/os-release ; echo $ID )
    case $DISTRIBUTION_ID in
    ubuntu*)
      if [[ $QT_VERSION_MAJOR == 5 ]]; then
        QT_PKGS=(
	  qtbase5-dev
	  libqt5charts5-dev
	  libqt5serialport5-dev
	  qt5-qmake
        )
      else
        QT_PKGS=(
	  qt6-base-dev
	  qt6-base-dev-tools
	  qt6-serialport-dev
	  qt6-charts-dev
	  qt6-connectivity-dev
	  qt6-tools-dev
	  qt6-tools-dev-tools
	  qmake6
        )
      fi
    
      echo "$SUDO_PASS" | sudo -S apt-get update -y
      echo "$SUDO_PASS" | sudo -S apt-get install -y \
        appstream \
        ninja-build \
        cmake-extras \
        libfftw3-dev \
        ${QT_PKGS[@]}
      ;;
    arch*)
      echo "$SUDO_PASS" | sudo -S pacman -Syu --noconfirm
      echo "$SUDO_PASS" | sudo -S pacman -S --noconfirm --needed \
        cmake \
        ninja \
        qt${QT_VERSION_MAJOR}-base \
        qt${QT_VERSION_MAJOR}-serialport \
        qt${QT_VERSION_MAJOR}-charts \
        qt${QT_VERSION_MAJOR}-tools \
        fftw
      ;;
    esac
    ;;
  *-apple-*)
    brew install qt@${QT_VERSION_MAJOR} fftw
    QT_ROOT_DIR=$(brew --prefix qt@${QT_VERSION_MAJOR})
    echo "export QT_ROOT_DIR=\"$QT_ROOT_DIR\"" > $QT_ENV
    echo "export PATH=\"\$PATH:\$QT_ROOT_DIR/bin\"" >> $QT_ENV
    echo "export LC_RPATH=\"\${LC_RPATH}\${LC_RPATH+:}\$QT_ROOT_DIR/lib\"" >> $QT_ENV
    echo "export QT_PLUGIN_PATH=\"\$QT_ROOT_DIR/plugins\""  >> $QT_ENV
    echo "export CMAKE_PREFIX_PATH=\"\${CMAKE_PREFIX_PATH}\${CMAKE_PREFIX_PATH:+:}\$QT_ROOT_DIR\"" >> $QT_ENV
    cat $QT_ENV
    ;;
  *)
    ;;
esac