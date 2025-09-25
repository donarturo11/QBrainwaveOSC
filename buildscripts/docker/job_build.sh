#!/usr/bin/env bash
THIS_SCRIPT_DIR=$(cd $(dirname $0); pwd)
export SCRIPTS_DIR=$(cd $THIS_SCRIPT_DIR/..; pwd)
TMP=${TMP:-$HOME}
export TMPDIR=$(mktemp -p $TMP -d .job-build-XXXXXXXX)
export BASH_ENV=$TMPDIR/.bashenv

git clone https://github.com/donarturo11/QBrainwaveOSC
cd QBrainwaveOSC
export SOURCE_DIR=$PWD

cat > $BASH_ENV << EOF
  export PKGNAME=QBrainwaveOSC
  export PKGVERSION=$(< ${SOURCE_DIR}/project-version)
  export QT_VERSION_MAJOR=${QT_VERSION_MAJOR:-6}
  export TMPDIR=$TMPDIR
  export SCRIPTS_DIR=$SCRIPTS_DIR
  export ENV_FILE=$TMPDIR/environment.sh
EOF

_SHELL="$(which bash) --noprofile --norc"
$_SHELL $SCRIPTS_DIR/setup_environment.sh
$_SHELL $SCRIPTS_DIR/install_dependencies.sh
$_SHELL $SCRIPTS_DIR/compile.sh
$_SHELL $SCRIPTS_DIR/package.sh
$_SHELL <<'EOF'
   . $ENV_FILE
   ARTIFACTS_NAME=$(basename $ARTIFACTS_DIR)
   cd $ARTIFACTS_DIR/..
   sudo tar -vczf $CONTAINER_TEMP/$ARTIFACTS_NAME.tar.gz $ARTIFACTS_NAME/*
EOF

