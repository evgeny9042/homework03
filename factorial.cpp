
#include <vector>
#include "factorial.h"

namespace my_lib {
	
int factorial(int n)
{
  static std::vector<unsigned int> v(2, 1);
  if ( v.size() > n )
    return v[n];
  for ( auto i = v.size(); i <= n; i++ ) {
    v.push_back(i * v[i - 1]);
  }
  return v[n];
}

}
