if [ -n $1 ] ; then
  for ext in hpp cpp; do
    cp -v CSetClipMode.$ext C$1.$ext
    echo "Copy to C$1.$ext"
    CMD=`echo sed s/SetClipMode/$1/g`
    cat CSetClipMode.$ext | $CMD > C$1.$ext.tmp0;
    FROM=`echo "SetClipMode" | tr [a-z] [A-Z]`
    TO=`echo $1 | tr [a-z] [A-Z]`
    echo $FROM $TO
    CMD=`echo sed s/$FROM/$TO/g`
    cat C$1.$ext.tmp0 | $CMD > C$1.$ext.tmp1;
    DATE=`date +%d\.%m\.%Y`
    CMD=`echo sed s/02\.12\.2009/$DATE/g`
    cat C$1.$ext.tmp1 | $CMD > C$1.$ext;
    rm -rfv C$1.$ext.tmp*
  done
  echo "#include \"C$1.hpp\"" >> op.h
  cat C$1.hpp
  cat C$1.cpp
fi
