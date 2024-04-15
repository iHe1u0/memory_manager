#include <memchk.h>

using kt::memchk;

int main(int, char **)
{
  memchk manager(true);  // auto release memory when exit
  for (size_t i = 1; i < 1e6; i *= 10)
  {
    manager.kt_malloc(i * 1024);
  }

  {
    int *ptr = (int *)manager.kt_malloc(sizeof(manager) * 1);
    manager.kt_free(ptr);
  }

  // c++ style
  {
#define __ENABLE_KT_NEW 1
    int *ptr = new int;
    if (ptr)
    {
      delete ptr;
    }
#undef __ENABLE_KT_NEW
  }

  return 0;
}
