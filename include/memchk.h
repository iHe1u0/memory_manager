#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <malloc.h>

#if defined(__GNUC__) || defined(__clang__)
#define KT_NORETURN_ATTRIBUTE __attribute__((noreturn))
#elif defined(_MSC_VER)
#define KT_NORETURN_ATTRIBUTE __declspec(noreturn)
#else
#define KT_NORETURN_ATTRIBUTE
#endif

namespace kt
{
  // for C style
  class memchk
  {
   public:
    explicit memchk(bool is_auto_release = false);
    virtual ~memchk();

   public:
    void* kt_malloc(size_t size) noexcept;  // malloc memory
    KT_NORETURN_ATTRIBUTE void kt_free(void* ptr) noexcept;      // free memory
    KT_NORETURN_ATTRIBUTE void  kt_dump() noexcept;               // check if memory leaked

   private:
    std::map<void*, size_t> __memory_map;  // Save memory address and size

    bool is_auto_release;  // Auto clear memory when exit

   private:
    std::string get_human_readable_size(size_t size) noexcept;

   private:
    template<typename _Ty>
    inline void debug_print(const _Ty& msg, bool newline = true)
    {
#ifdef DEBUG
      std::cout << msg;
      if (newline)
      {
        std::cout << std::endl;
      }
#endif  // DEBUG
    }
  };
}  // namespace kt