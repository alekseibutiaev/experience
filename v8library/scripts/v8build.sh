#!/bin/bash
set -x

v8source=${1}
depot_tools=${2}
export PATH=${depot_tools}:${PATH}
cd ${v8source}
[ -d v8 ] && gclient sync || fetch v8

#cd v8
#cat tools/dev/gm.py | sed "s/is_component_build\ =\ false/is_component_build\ =\ true/g" > tools/dev/gm.so.py
#chmod 755 tools/dev/gm.so.py
#tools/dev/gm.so.py x64.release.check

