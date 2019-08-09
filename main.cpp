
#include "factorial.h"
#include "my_list.h"
#include "my_allocator.h"

#include <map>
#include <algorithm>
#include <iostream>

int main(int argc, char const *argv[])
{
  std::map<int, int> map1;
  for ( unsigned int i = 0; i < 10; i++ ) {
    map1.insert(std::pair<int, int>(i, my_lib::factorial(i)));
  }

  std::map<int, int, std::less<int>, my_lib::my_allocator<std::pair<const int, int>>> map2;
  for ( unsigned int i = 0; i < 10; i++ ) {
    map2.insert(std::pair<int, int>(i, my_lib::factorial(i)));
  }

  auto print_map = [] (auto &map) {    
    std::for_each(map.cbegin(), map.cend(), [] (const std::pair<int, int>&p) {
      std::cout << p.first << "->" << p.second << std::endl;
    });
  };

  std::cout << "map with standart allocator:" << std::endl;
  print_map(map1);
  std::cout << "map with my_allocator:" << std::endl;
  print_map(map2);  


  my_lib::my_list<int, my_lib::my_allocator<int>> list;
  list.push_back(1);
  list.push_back(42);

  std::cout << "my list with my_allocator:" << std::endl;
  auto it = list.get_iterator();
  while(it.has_next()) {
    std::cout << it.get();
  }

	return 0;
}
