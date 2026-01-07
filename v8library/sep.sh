#!/bin/bash
set -x

echo ${1}

IN="./v8build/v8_base_without_compiler/api"
OUT="./v8build/v8_base_without_compiler/${1}"

cp -Rv ${IN} ${OUT}
cat ./v8/BUILD.gn | grep "/${1}/" | sed 's/ //g' > ./separator
cat separator | sed 's/"src\//  \$\{v8source\}\//g' | sed 's/\".//g' > tmp
echo -e "set(\${PROJECT_NAME}_headers" >> ${OUT}/CMakeLists.txt
cat tmp | grep "\.h" >> ${OUT}/CMakeLists.txt
echo -e "\n)\nset(\${PROJECT_NAME}_sources" >> ${OUT}/CMakeLists.txt
cat tmp | grep "\.cc" >> ${OUT}/CMakeLists.txt
echo -e ")" >> ${OUT}/CMakeLists.txt


