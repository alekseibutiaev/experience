#pragma once
#include <stdio.h>
#include "CPtr.h"

class CLogReader
{
public:
  CLogReader(const char* val = "\r\n");
  ~CLogReader();
  bool Open(const char* filename);
  void Close();
  bool SetFilter(const char* buf);
  bool GetNextLine(CPtr& buf, size_t& size);
public:
  static char* NormalizeFilter(const char* ptr);
  static bool IsMach(const char* str, const size_t lstr, const char* ptr/*, const size_t lpattern*/);
private:
  void CloseFile();
private:
  char eos[128];
  size_t eossize;
  FILE* file;
  size_t bufsize;
  size_t tail;
  CPtr intbuf;
  CPtr filter;
private:
  static const size_t bsstep = 1024;
  static const char any_one = '?';
  static const char star = '*';
};
