#!/bin/bash
#set -x

v8source=${1}

for f in `grep -Rle "#include \"testing/gtest/include/gtest/gtest_prod.h\"" ${v8source}`
do
#  echo ${f}
  mv ${f}{,.back}
  cat ${f}.back | sed 's/testing\/gtest\/include\///g' > ${f}
  rm ${f}.back
done
