// log.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//
// Необходимо написать на чистом С++ класс, умеющий максимально быстро читать
// текстовые лог - файлы огромных размеров(сотни мегабайт, десятки гигабайт)
// и выдавать строки, удовлетворяющие условиям простейшего regexp : 
// (как минимум операторы* и ? , более широкий набор возможностей приветствуется) :
//
// cимвол '*' - последовательность любых символов неограниченной длины;
// cимвол "?" - один любой символ;
// должны корректно отрабатываться маски : *Some*, * Some, Some*, ***** Some*** -нет никаких ограничений на положение * в маске.
//
// Результатом поиска должны быть строки, удовлетворяющие маске.
//
// Например :
//
// Маска * abc* отбирает все строки содержащие abc и начинающиеся и заканчивающиеся любой последовательностью символов.
// Маска abc* отбирает все строки начинающиеся с abc и заканчивающиеся любой последовательностью символов.
// Маска abc ? отбирает все строки начинающиеся с abc и заканчивающиеся любым дополнительным символом.
// Маска abc   отбирает все строки которые равны этой маске.
//

#include <windows.h>
#include <stdio.h>
#include "CLogReader.h"
#include "CPtr.h"


static bool unit_test() {

  const char* patern[] = { "*qwr*", "***qw**qw?***", "**qw**qwa**", "*qwr", "qwr*", "qwr" };
  const char* str[] = { "__qw__qwr__", "_qwr", "qwr_", "qwr" };
  const bool r[4][6] = {
    { true, true, false, false, false, false }, /* 00qw0000qwr0 */
    { false, false, false, true, false, false }, /* _qwr */
    { false, false, false, false, true, false }, /* qwr_ */
    { false, false, false, false, false, true} /* qwr */
  };

  bool ut = true;
  for (size_t s = 0; s < sizeof(str) / sizeof(*str) && ut; ++s) {
    for (size_t p = 0; p < sizeof(patern) / sizeof(*patern) && ut; ++p) {
      CPtr filter = CLogReader::NormalizeFilter(patern[p]);
      const bool res = CLogReader::IsMach(str[s], strlen(str[s]), filter.Get());
      if (res != r[s][p])
        ut = false;
      printf("pattern [%s], string [%s] %s %s %d\r\n", filter.Get(), str[s],
        (res ? "Mach" : "No Mach"), (res == r[s][p] ? "Ok" : "Err"), res);
      continue;
    }
  }
  printf("unit test is %s.\r\n", ut ? "ok" : "error");
  return ut;

}

int main(int ac, char* av[]) {

  if (1 == ac || 3 < ac) {
    unit_test();
    printf("wronr parameters. use %s [filename] [filter]\r\n", strrchr(av[0], '\\') + 1);
    return 1;
  }

  size_t bufsize = 1024;
  CPtr buf(static_cast<char*>(malloc(bufsize)));
  CLogReader lr("\n");
  lr.Open(av[1]);
  lr.SetFilter(av[2]);
  while (lr.GetNextLine(buf, bufsize))
    printf("%s\r\n", buf.Get());

  return 0;
}
