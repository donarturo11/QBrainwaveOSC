#!/usr/bin/env bash
DOCKER=${DOCKER:-podman}
IMAGE_TAG="${IMAGE_TAG:-ubuntu-ci}"
CWD=${PWD}
TMP=${TMP:-/var/tmp}
TMPDIR=$(mktemp -p $TMP -d tmp-$(basename $DOCKER)-XXXXXXXX)
chmod -Rv 777 $TMPDIR
THIS_SCRIPT_DIR=$(cd $(dirname $0); pwd)
SCRIPTS_DIR=$(cd $THIS_SCRIPT_DIR/..; pwd)
[[ -n $BUILD_IMAGE ]] && $DOCKER build $THIS_SCRIPT_DIR -t $IMAGE_TAG
_opts=(
  -v $TMPDIR:$TMPDIR
  -v $THIS_SCRIPT_DIR/..:/var/buildscripts
  --rm
  --device /dev/fuse
  --cap-add SYS_ADMIN
  --security-opt apparmor=unconfined
  -e BUILDSCRIPTS_DIR=/var/buildscripts
  -e CONTAINER_TEMP=$TMPDIR
  -e DEBIAN_FRONTEND=noninteractive
  -e CI=true
   $IMAGE_TAG
)

$DOCKER run -e QT_VERSION_MAJOR=6 ${_opts[@]} bash /var/buildscripts/docker/job_build.sh
$DOCKER run -e QT_VERSION_MAJOR=5 ${_opts[@]} bash /var/buildscripts/docker/job_build.sh

#$DOCKER run ${_opts[@]}
