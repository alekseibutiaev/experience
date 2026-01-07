#include <windows.h>
#include <string.h>
#include "CLogReader.h"

CLogReader::CLogReader(const char* val)
  : eossize(strlen(val))
  , file(0)
  , bufsize(bsstep)
{
  strcpy_s(eos, sizeof(eos), val);
}

CLogReader::~CLogReader() {
  Close();
}

bool CLogReader::Open(const char* filename) {
  CloseFile();
  if (0 != fopen_s(&file, filename, "r"))
    return false;
  if (0 == intbuf.Get())
  {
    CPtr tmp(static_cast<char*>(malloc(bufsize)));
    // check buffer and read 
    if (0 != tmp.Get() && 0 == (tail = fread_s(tmp.Get(), bufsize, 1, bufsize, file))) {
      CloseFile();
      return false;
    }
    intbuf.Swap(tmp);
  }
  return false;
}

void CLogReader::Close() {
  CloseFile();
}

bool CLogReader::SetFilter(const char* buf) {
  CPtr tmp(NormalizeFilter(buf));
  filter.Swap(tmp);
  return 0 != filter.Get();
}

bool CLogReader::GetNextLine(CPtr& buf, size_t& size) {
  while (0 == feof(file) && 0 == ferror(file)) {
    size_t strsize = 0;
    char* ibuf = intbuf.Get();
    // find end of string
    while (char* es = strstr(ibuf, eos)) {
      strsize = es - ibuf;
      tail -= (strsize + eossize);
      //make null terminate string
      memset(es, 0, eossize);
      if (IsMach(ibuf, strsize, filter.Get())) {
        // check size of output buffer
        if (size < strsize) {
          // realloc 
          size = (strsize / bsstep + 1) * bsstep;
          CPtr tmp(static_cast<char*>(malloc(size)));
          tmp.Swap(buf);
        }
        //copy mached string to result
        strncpy_s(buf.Get(), size, ibuf, strsize);
        // copy unprocessed symbol (tail) to start of buffer
        strncpy_s(intbuf.Get(), bufsize, es + eossize, bufsize - strsize);
        return true;
      }
      else
        // copy unprocessed symbol (tail) to start of buffer
        strncpy_s(intbuf.Get(), bufsize, es + eossize, bufsize - strsize);
    }
    // check long string
    if (bufsize == tail) {
      // string is to long. reolatate input buffer;
      bufsize += bsstep;
      CPtr tmp(static_cast<char*>(malloc(bufsize)));
      strncpy_s(tmp.Get(), bufsize, intbuf.Get(), bufsize);
      intbuf.Swap(tmp);
    }
    // read next data;
    if (size_t read = fread_s(intbuf.Get() + tail, bufsize - tail, 1, bufsize - tail, file))
      tail += read;
  }
  return false;
}

char* CLogReader::NormalizeFilter(const char* ptr) {
  const size_t lptr = strlen(ptr);
  if (char* ret = static_cast<char*>(malloc(lptr + 1))) {
    memset(ret, 0, lptr + 1);
    size_t ridx = 0;
    for (size_t pidx = 0; pidx < lptr; ++pidx)
      if (star != ptr[pidx]) {
        if (star == ret[ridx])
          ++ridx;
        ret[ridx++] = ptr[pidx];
      }
      else
        ret[ridx] = ptr[pidx];
    return ret;
  }
  else
    return ret;
}

bool CLogReader::IsMach(const char* str, const size_t lstr, const char* ptr/*, const size_t lpattern*/) {
  if (0 == str || 0 == lstr || 0 == ptr/* || 0 == lpattern*/) {
    // wrong parameters
    return false;
  }
  size_t sidx = 0;
  const char* tptr = ptr;
  // checkc begin of string
  if (any_one != *ptr && star != *ptr && str[sidx] != *ptr)
    return false;
  bool ret = false;
  for (; sidx < lstr; ) {
    //    printf("[%c]  [%c]\r\n", *ptr, str[sidx]);
    if (any_one == *ptr) {
      ++sidx;
      ++ptr;
      continue;
    }
    else if (star == *ptr) {
      // next str symbol
      ++sidx;
      // check next str symbol with next patern symbol.
      if (str[sidx] == ptr[1]) {
        // if this is same take next patern symbol
        // store tail off pattern
        tptr = ptr;
        ++ptr;
      }
      else if (0 == ptr[1])
        // reach end of patterm
        break;
    }
    else if (str[sidx] == *ptr) {
      ret = true;
      ++sidx;
      ++ptr;
    }
    else {
      ret = false;

      // if strin can has pattern aggain return to tail of pattern
      if (strlen(tptr) - 1 <= lstr - sidx)
        ptr = tptr;
      else
        break;
    }
  }
  // end of string
  if (sidx == lstr && 0 < strlen(ptr))
    ret = false;
  return ret;
}

void CLogReader::CloseFile() {
  if (file) {
    fclose(file);
    file = 0;
  }
}
