#include <memchk.h>
#include <sstream>

namespace kt
{
  memchk::memchk(bool is_auto_release) : is_auto_release(is_auto_release)
  {
    std::ios_base::sync_with_stdio(false);
  }

  memchk::~memchk()
  {
    if (is_auto_release && !__memory_map.empty())
    {
      for (auto it = __memory_map.begin(); it != __memory_map.end();)
      {
        if (it->first != nullptr)
        {
          std::free(it->first);
          it = __memory_map.erase(it);
        }
        else
        {
          ++it;
        }
      }
    }

    kt_dump();
  }

  void* memchk::kt_malloc(size_t size) noexcept
  {
    void* ptr = std::malloc(size);
    if (ptr == nullptr)
    {
      return nullptr;
    }
    __memory_map[ptr] = size;
    return ptr;
  }

  void memchk::kt_free(void* ptr) noexcept
  {
    if (ptr != nullptr && !__memory_map.empty())
    {
      auto address = __memory_map.find(ptr);
      if (address != __memory_map.end())
      {
        std::free(ptr);
        __memory_map.erase(ptr);
      }
    }
  }

  void memchk::kt_dump() noexcept
  {
    if (!__memory_map.empty())
    {
      size_t leak_size = 0;
      std::cout << __memory_map.size() << " times memory leak found:" << std::endl;
      for (auto& _mem : __memory_map)
      {
        std::cout << "  Address: " << _mem.first << "  Size: " << get_human_readable_size(_mem.second) << std::endl;
        leak_size += _mem.second;
      }
      debug_print("All leakd memory size: " + get_human_readable_size(leak_size));
    }
    else
    {
      debug_print("Not found memory leak, all memory free.");
    }
  }

  std::string memchk::get_human_readable_size(size_t size) noexcept
  {
    const char* units[] = { "Bytes", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
    const int   num_units = sizeof(units) / sizeof(units[0]);

    int    unit_index = 0;
    double size_d = static_cast<double>(size);

    while (size_d >= 1024 && unit_index < num_units - 1)
    {
      size_d /= 1024;
      ++unit_index;
    }

    std::stringstream ss{};
    ss << size_d << " " << units[unit_index];
    return ss.str();
  }

}  // namespace kt

#if defined(__ENABLE_KT_NEW)
void* operator new(size_t size)
{
  void* ptr = std::malloc(size);
  if (ptr == nullptr)
  {
    throw std::bad_alloc();  // throw exception when malloc failed
  }
  return ptr;
}

void operator delete(void* ptr) noexcept
{
  if (ptr != nullptr)
  {
    std::free(ptr);
  }
}
#endif  // #if defined(__ENABLE_KT_NEW)
