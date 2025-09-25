#!/usr/bin/env bash
ARTIFACTS_DIR=${ARTIFACTS_DIR:-$PWD/out}
APPDIR=${APPDIR:-"$TMPDIR/AppDir"}
[[ ! -d $ARTIFACTS_DIR ]] && mkdir -vp $ARTIFACTS_DIR
cd $TMPDIR
cmake --install $BUILD_DIR --prefix ${APPDIR}/usr
LINUXDEPLOY=$(which linuxdeploy)
if [[ -z "${LINUXDEPLOY}" ]]; then
  echo -e "${LOG_NOTICE}Downloading linux deploy${LOG_RESET}"
  _urls=(
  https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-${HOSTTYPE}.AppImage
  https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-${HOSTTYPE}.AppImage
  https://github.com/linuxdeploy/linuxdeploy-plugin-appimage/releases/download/continuous/linuxdeploy-plugin-appimage-${HOSTTYPE}.AppImage
  )
  for url in ${_urls[@]}; do
    _file=$(basename $url)
    curl -L $url > $TMPDIR/$_file
    chmod +x $TMPDIR/$_file
  done
  LINUXDEPLOY="$TMPDIR/linuxdeploy-${HOSTTYPE}.AppImage"
  export PATH="$TMPDIR:$PATH"
fi

echo -e "${LOG_NOTICE}Linux deploy QT${LOG_RESET}"

cd $TMPDIR
[[ ! -e $TMPDIR/out ]] && mkdir -vp $TMPDIR/out
cd $TMPDIR/out
${LINUXDEPLOY} --appdir=$APPDIR --plugin qt
echo -e "${LOG_NOTICE}Creating AppImage${LOG_RESET}"
${LINUXDEPLOY} --appdir=$APPDIR --output=appimage
find $PWD -iname '*.AppImage'
[[ ! -e $ARTIFACTS_DIR ]] && mkdir $ARTIFACTS_DIR
ls -lah
cp -av *.AppImage $ARTIFACTS_DIR/
cp -a $APPDIR $FULL_PKGNAME
tar -czf $ARTIFACTS_DIR/$FULL_PKGNAME.binary.tar.gz $FULL_PKGNAME
