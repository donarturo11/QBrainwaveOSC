#!/usr/bin/env bash
#BASH_ENV=${BASH_ENV:?"BASH_ENV not defined"}

export SCRIPTS_DIR=$(cd $(dirname $0); pwd)

OS_NAME=$(uname -s | tr '[:upper:]' '[:lower:]')
CWD=${CWD:-$(pwd)}
CARCH=$(uname -m)
case $OS_NAME in
  msys*)
    OS_NAME=windows
    PROFILE_NAME=${CARCH}-windows-msvc
    if [[ -z $CHOST ]]; then
      CHOST=${CARCH}-pc-windows-msvc
      TOOLCHAIN=msvc
    fi
    ;;
  mingw*)
    OS_NAME=windows
    if [[ -z $CHOST ]]; then
      CHOST=${CARCH}-w64-mingw32
      TOOLCHAIN=mingw
    fi
    ;;
  darwin)
    OS_NAME=macos
    ;;
esac
export CHOST=${CHOST:-$MACHTYPE}

export ENV_FILE=${ENV_FILE:-$TMPDIR/environment.sh}
echo "" > $ENV_FILE
if [[ -n $GITHUB_TEMP ]]; then
  echo source $SCRIPTS_DIR/gha.bashrc >> $ENV_FILE
fi
echo export ENV_DIR=$TMPDIR/environment.d >> $ENV_FILE
cat >> $TMPDIR/environment.sh << 'EOF'
[[ ! -e $ENV_DIR ]] && mkdir -vp $ENV_DIR
export PKG_ENV=$ENV_DIR/00-pkg-env.sh
export TOOLCHAIN_ENV=$ENV_DIR/10-toolchain-env.sh
export TOOLS_ENV=$ENV_DIR/20-tools-env.sh
export BUILD_ENV=$ENV_DIR/30-build-env.sh
export CMAKE_ENV=$ENV_DIR/40-cmake-env.sh

for _env in $ENV_DIR/*.sh
do
  [[ -f $_env ]] && . $_env
done
EOF
cat $ENV_FILE

source $ENV_FILE

export QT_VERSION_MAJOR=${QT_VERSION_MAJOR:-6}
export PROFILE_NAME=${PROFILE_NAME:-"${OS_NAME}${TOOLCHAIN:+-}${TOOLCHAIN}-${CARCH}"}
export PKGNAME=${PKGNAME:?"PKGNAME is not defined"}
export PKGVERSION=${PKGVERSION:?"PKGVERSION is not defined"}
if [[ -z $BUILD_RELEASE ]]; then
  export PKGREVISION=$(git rev-parse --short HEAD || echo "")
fi
export TAG=${TAG:-"-qt${QT_VERSION_MAJOR}_${PROFILE_NAME}"}
export FULL_PKGNAME="${PKGNAME}-${PKGVERSION}${PKGREVISION:+.$PKGREVISION}${TAG}"

echo PKGNAME=$PKGNAME >> $PKG_ENV
echo PKGVERSION=$PKGVERSION >> $PKG_ENV
echo PKGREVISION=$PKGREVISION >> $PKG_ENV
echo TAG=$TAG >> $PKG_ENV
echo FULL_PKGNAME=$FULL_PKGNAME >> $PKG_ENV
echo export PKGNAME PKGVERSION PKGREVISION TAG FULL_PKGNAME >> $PKG_ENV
source $PKG_ENV

echo export CMAKE_GENERATOR=Ninja >> $CMAKE_ENV
if [[ $OS_NAME =~ macos ]]; then
  echo export CMAKE_INSTALL_PREFIX=\"./\" >> $CMAKE_ENV
else
  echo export CMAKE_INSTALL_PREFIX=_install >> $CMAKE_ENV
fi
_cmake_opts=(
  -DCPACK_PACKAGE_NAME=$PKGNAME
  -DCPACK_PACKAGE_FILE_NAME=$FULL_PKGNAME
  -DCPACK_PACKAGE_VERSION=${PKGVERSION}${PKGREVISION:+.}${PKGREVISION}
  -DCPACK_PACKAGE_VERSION_PATCH=${PKGREVISION}
)
echo export CMAKE_OPTS=\"${_cmake_opts[@]}\" >> $CMAKE_ENV

echo export CHOST=$CHOST >> $BUILD_ENV
echo export QT_VERSION_MAJOR=${QT_VERSION_MAJOR:-6} >> $BUILD_ENV
echo export SOURCE_DIR=${SOURCE_DIR:-$CWD} >> $BUILD_ENV
echo export BUILD_DIR=\${SOURCE_DIR}/build$TAG >> $BUILD_ENV
echo export ARTIFACTS_DIR=\${ARTIFACTS_DIR:-\${BUILD_DIR}.artifacts} >> $BUILD_ENV

if [[ -n $OWNCLOUD_TOKEN ]]; then
  echo export OWNCLOUD_TOKEN=$OWNCLOUD_TOKEN >> $ENV_DIR/owncloud.sh
  echo export OWNCLOUD_ROOT_URL=https://freeshell.de/owncloud/remote.php/webdav >> $ENV_DIR/owncloud.sh
  source $ENV_DIR/owncloud.sh
fi

case $OS_NAME in
windows)
  MSYS_ROOT=${MSYS_ROOT:-/c/msys64}
  PATH="$MSYS_ROOT/usr/bin:$PATH"
  echo "export MSYSTEM=$MSYSTEM" >> $TOOLCHAIN_ENV
  echo "export MSYS2_PATH_TYPE=inherit" >> $TOOLCHAIN_ENV
  echo "export CHERE_INVOKING=1" >> $TOOLCHAIN_ENV
  echo "source /c/msys64/etc/profile" >> $TOOLCHAIN_ENV
  source $TOOLCHAIN_ENV
  pacman -Syuu
  pacman -S pactoys --noconfirm --needed
  #echo "source $TOOLCHAIN_ENV" >> $ENV_FILE
  if [[ "$CHOST" == "x86_64-pc-windows-msvc" ]]; then
    echo "Setup NSIS"
    cd $TMPDIR
    curl -qLO https://sourceforge.net/projects/nsis/files/NSIS%203/3.11/nsis-3.11.zip
    /c/windows/system32/tar.exe -xf nsis-3.11.zip
    echo "export PATH=$PWD/nsis-3.11:\$PATH" >> $ENV_DIR/nsis.sh
    MSVC_ENV=${ENV_DIR}/00-msvc-env.sh
    bash -c "$(curl https://raw.githubusercontent.com/nathan818fr/vcvars-bash/refs/heads/main/vcvarsall.sh)" -- x64 >> $MSVC_ENV
    echo export CC=cl  >> $TOOLCHAIN_ENV
    echo export CXX=cl >> $TOOLCHAIN_ENV
  fi
  ;;
macos)
  BREW_ENV=$ENV_DIR/00-brew.sh
  echo export CMAKE_PREFIX_PATH=\"\${CMAKE_PREFIX_PATH}\${CMAKE_PREFIX_PATH+:}$HOMEBREW_PREFIX\" >> $BREW_ENV
  echo export LC_RPATH=\"${LC_RPATH}${LC_RPATH+:}${HOMEBREW_PREFIX}/lib\" >> $BREW_ENV
  cat $BREW_ENV
  if [[ -n $OWNCLOUD_TOKEN ]]; then
    cd $TMPDIR
    curl -H "Authorization: Basic $OWNCLOUD_TOKEN" -LO $OWNCLOUD_ROOT_URL/CI/macos-codesign/certificates.tar.gz
    tar -xzf certificates.tar.gz
    cd certificates
    export CODESIGN_ENV=$HOME/.codesign-env
    ./install.sh
    echo export CODESIGN_ENV=$CODESIGN_ENV >> $ENV_FILE
    . $CODESIGN_ENV
    echo KEYCHAIN_IDENTITY=$KEYCHAIN_IDENTITY
    echo export CMAKE_OPTS=\"\${CMAKE_OPTS} -DCPACK_BUNDLE_APPLE_CERT_APP=\\\"$KEYCHAIN_IDENTITY\\\"\" >> $CMAKE_ENV
    cat $CMAKE_ENV
  fi
  ;;
linux)
  LINUXDEPLOY_OUTPUT_VERSION=${PKGVERSION}${PKGREVISION:+.}${PKGREVISION}${QT_VERSION_MAJOR:+-qt}${QT_VERSION_MAJOR}
  echo export LINUXDEPLOY_OUTPUT_VERSION=$LINUXDEPLOY_OUTPUT_VERSION >> $ENV_DIR/appimage.sh
  ;;
*)
  ;;
esac
