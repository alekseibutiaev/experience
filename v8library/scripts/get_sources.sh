#!/bin/bash
set -x

git clone https://chromium.googlesource.com/v8/v8.git v8
git clone https://chromium.googlesource.com/chromium/src/base/trace_event/common.git v8/base/trace_event/common
git clone https://chromium.googlesource.com/chromium/src/third_party/jinja2.git v8/third_party/jinja2

pushd v8
git checkout tags/7.9.200
popd
 
