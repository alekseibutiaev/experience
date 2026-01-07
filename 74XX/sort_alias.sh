#!/bin/bash
set -x
while IFS= read -r line
do
  R=`echo ${line} | grep ALIAS`
  if [ -z "${R}" ]
  then
    echo ${line}
  else
    R1=`echo ${R} | tr -s ' ' '\n' | sort | grep -v "ALIAS" | tr -s '\n' ' '`
    echo "ALIAS ${R1}"
  fi
done < ${1}

