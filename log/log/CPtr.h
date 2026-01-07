#pragma once
class CPtr
{
public:
  CPtr(char* ptr = 0);
  ~CPtr();
  char* Get();
  void Swap(CPtr& val);
private:
  char* m_ptr;
};

