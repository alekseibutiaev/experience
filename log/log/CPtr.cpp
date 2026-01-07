#include "windows.h"
#include "CPtr.h"

CPtr::CPtr(char* ptr) : m_ptr(ptr) {
}

CPtr::~CPtr() {
  if(m_ptr)
    free(m_ptr);
}

char* CPtr::Get() {
  return m_ptr;
}

void CPtr::Swap(CPtr& val) {
  char* tmp = m_ptr;
  m_ptr = val.m_ptr;
  val.m_ptr = tmp;
}