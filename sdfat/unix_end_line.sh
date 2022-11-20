#/bin/bash

for i in `find ./ -name "*.h" -o -name "*.c"`; do
  o=${i}.bck; mv -v ${i} ${o}; cat ${o} | tr -d '\r' > ${i};
done
rm -v `find ./ -name "*.bck"`

