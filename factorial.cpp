
#include <vector>
#include "factorial.h"

namespace my_lib {
	
unsigned int factorial(unsigned int n)
{
  static std::vector<unsigned int> v(2, 1);
  if ( v.size() > n )
    return v[n];
  for ( size_t i = v.size(); i <= n; i++ ) {
    v.push_back(i * v[i - 1]);
  }
  return v[n];
}

}