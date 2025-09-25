#!/usr/bin/env bash
export ENV_FILE=${ENV_FILE:-$TMPDIR/environment.sh}
[[ -e $ENV_FILE ]] && . $ENV_FILE
#echo "======="
#cat $BUILD_DIR/CPackConfig.cmake
#echo "======="
ARTIFACTS_DIR=${ARTIFACTS_DIR:-out}
[[ ! -e $ARTIFACTS_DIR ]] && mkdir -vp $ARTIFACTS_DIR
SCRIPTS_DIR=${SCRIPTS_DIR:-$(cd $(dirname $0); pwd)}
echo OSTYPE=$OSTYPE
cd $BUILD_DIR

case $OSTYPE in
linux-*)
  $SCRIPTS_DIR/create_appimage.sh
  ;;
darwin*)
  CODESIGN_ENV=${CODESIGN_ENV:-$HOME/.codesign-env}
  [[ -e $CODESIGN_ENV ]] && . $CODESIGN_ENV
  echo KEYCHAIN_IDENTITY=$KEYCHAIN_IDENTITY
  APP_DIR=QBrainwaveOSC.app
  cd $BUILD_DIR/out/bin
  ls -lah
  cmake --build ${BUILD_DIR} --target deploy || echo "${LOG_WARNING}deploying failed${LOG_RESET}"
  codesign --verbose --remove-signature $APP_DIR || echo "${LOG_WARNING}remove failed${LOG_RESET}"
  codesign --verbose --continue --timestamp --force --deep -s "Developer ID Application: ${KEYCHAIN_IDENTITY}" $APP_DIR && echo "${LOG_NOTICE}Sign succeed${LOG_RESET}" || echo "${LOG_WARNING}Sign failed${LOG_RESET}"
  codesign --verbose --verify --strict $APP_DIR
  bsdtar -vc --format zip -f $ARTIFACTS_DIR/${FULL_PKGNAME}.zip $APP_DIR
  cd $ARTIFACTS_DIR
  cpack --config $BUILD_DIR/CPackConfig.cmake \
	-B $ARTIFACTS_DIR
#  for _dmg in *.dmg; do
#    echo "${LOG_NOTICE}Signing $_dmg${LOG_RESET}"
#    codesign --verbose -f --strict --deep -o runtime --timestamp -s "${KEYCHAIN_IDENTITY}" $_dmg && echo "${LOG_NOTICE}Sign succeed${LOG_RESET}" || echo "${LOG_WARNING}Sign failed${LOG_RESET}"
#    codesign --verbose --verify --strict $_dmg
#    spctl -a -t open --context context:primary-signature -vv $_dmg
#  done
  ;;
*)
  cmake --build ${BUILD_DIR} --target deploy || echo "${LOG_WARNING}deploying failed${LOG_RESET}"
  cpack --config $BUILD_DIR/CPackConfig.cmake \
	-B $ARTIFACTS_DIR
  ;;
esac

cd $ARTIFACTS_DIR
for d in _CPack*;
do
  [[ -e $d ]] && rm -Rf $d && echo "$d removed"
done
find $ARTIFACTS_DIR