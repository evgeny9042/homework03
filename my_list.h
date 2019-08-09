//#include <string>
//#include <vector>

namespace my_lib {

 // мой контейнер
template <typename T, typename Allocator >
class my_list
{
private:
  struct list_node
  {
    list_node(T &&data) : value(std::forward<T>(data)) {};
    list_node* next{nullptr};
    T value;
  };  
  // в первый раз написал такую штуку! Круто!
  using list_node_allocator = typename Allocator::template rebind<list_node>::other;

public: 
  class iterator
  {
    iterator(my_list *list) : current(list->head) {}
  public:
    T& get() {
      T& value = current->value;
      current = current->next;
      return value;
    };
    bool has_next() const {
      return current != nullptr;
    }  
  private:
    list_node* current{nullptr};
    friend my_list;
  };
  
  /// Конструктор
  my_list() noexcept {};
  /// Деструктор
  ~my_list() noexcept {};
  
  void push_back(T &&d)
  {
    list_node *node = allocator.allocate(1);
    allocator.construct(node, std::forward<T>(d));   
    if ( head == nullptr ) {
      head = node;
      tail = node;
      return;
    }
    tail->next = node;
    tail = node;
  }

  iterator get_iterator() {
    iterator it(this);
    return it;
  }

private:
  list_node_allocator allocator;
  list_node* head{nullptr};
  list_node* tail{nullptr};
};

}