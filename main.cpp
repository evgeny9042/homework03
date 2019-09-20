
#include "factorial.h"
#include "my_list.h"
#include "my_allocator.h"

#include <map>
#include <algorithm>
#include <iostream>

int main(int argc, char const *argv[])
{
  // функция для вывода значений из ассоциативного контейнера
  auto print_map = [] (auto &map) {
    std::for_each(map.cbegin(), map.cend(), [] (const std::pair<int, int>&p) {
      std::cout << p.first << "->" << p.second << std::endl;
    });
  };

  // ассоциативный контейнер с стандартным аллокатороам
  std::map<int, int> map1;
  for ( int i = 0; i < 10; i++ ) {
    map1.insert(std::pair<int, int>(i, my_lib::factorial(i)));
  }
  std::cout << "map with standart allocator:" << std::endl;
  print_map(map1);

  // ассоциативный контейнер с моим аллокатороам
  std::map<int, int, std::less<int>, my_lib::my_allocator<std::pair<const int, int>>> map2;
  for (  int i = 0; i < 10; i++ ) {
    map2.insert(std::pair<int, int>(i, my_lib::factorial(i)));
  }  
  std::cout << "map with my_allocator:" << std::endl;
  print_map(map2);  


  // функция вывода значений из моего контейнера
  auto print_list = [] (auto &list) {
    auto it = list.get_iterator();
    while ( it.has_next() ) {
      std::cout << it.get() << " ";
    }
    std::cout << std::endl;
  };

  // мой контейнер с стандартным аллокатором
  my_lib::my_list<int, std::allocator<int>> list1;
  for ( int i = 0; i < 10; i++ ) {
    list1.push_back(i);
  }

  std::cout << "my list with std allocator:" << std::endl;
  print_list(list1);

  // мой контейнер с моим аллокатором
  my_lib::my_list<int, my_lib::my_allocator<int>> list2;
  for ( int i = 0; i < 10; i++ ) {
    list2.push_back(i);
  }
  
  std::cout << "my list with my_allocator:" << std::endl;
  print_list(list2);

	return 0;
}
