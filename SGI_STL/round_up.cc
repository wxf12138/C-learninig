#include <iostream>
#include <cstddef>
enum { _ALIGN = 8 };
static size_t
_S_round_up(size_t __bytes) 
  { return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); }



/* 
    byte 1                 = 0000 0000 0000 0000 0000 0000 0000 0001
    byte 9                 = 0000 0000 0000 0000 0000 0000 0000 1001
    (size_t) _ALIGN-1) =     0000 0000 0000 0000 0000 0000 0000 0111
    ~((size_t) _ALIGN - 1) = 1111 1111 1111 1111 1111 1111 1111 1000
*/
int main()
{
    std::cout << _S_round_up(1) << std::endl;
    std::cout << _S_round_up(9) << std::endl;
}