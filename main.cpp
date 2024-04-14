#include <memchk.h>

using kt::memchk;

int main(int, char **)
{
  memchk manager(false);
  for (size_t i = 1; i < 1e6; i *= 10)
  {
    manager.kt_malloc(i * 1024);
  }

  int *ptr = (int *)manager.kt_malloc(sizeof(manager) * 1);
  manager.kt_free(ptr);

  return 0;
}
