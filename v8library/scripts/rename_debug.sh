#!/bin/bash
#set -x

v8source=${1}

for f in `grep --exclude-dir=.git -Rle "#include \"src/debug" ${v8source}`
do
#  echo ${f}
  mv ${f}{,.back}
  cat ${f}.back | sed 's/src\/debug/src\/Debug/g' > ${f}
  rm ${f}.back
done

pushd ${v8source}/src
mv {d,D}ebug
popd

