
namespace my_lib {

// мой аллокатор
template<typename T>
struct my_allocator
{

  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using size_type = std::size_t;

  /// Конструктор
  my_allocator() noexcept{};
  /// Конструктор
  template<class U>
  my_allocator(const my_allocator<U>&) noexcept {};
  /// Деструктор
  ~my_allocator() = default;

  /// для создания другого типа аллокатора
  template<typename U>
  struct rebind {
  using other = my_allocator<U>;
  };

  /// выделит память
  T * allocate(size_t n)
  {
    void *p = std::malloc(n * sizeof(T));
    if ( !p ) {
      throw std::bad_alloc();
    }
    return reinterpret_cast<T*>(p);
  }

  /// освободить память
  void deallocate(T * p, size_t n)
  {
    std::free(p);
  }

  /// сконструировать объект
  template<typename U, typename ...Args>
  void construct(U* p, Args &&...args)
  {
    new (p) U(std::forward<Args>(args)...);
  }  

  /// уничтожить объект
  void destroy(T * p)
  {
    p->~T();
  }
};

}