
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
  my_allocator()  {    
    //m_preallocated = reinterpret_cast<T*>(std::malloc(m_size * sizeof(T)));  
  };
  /// Конструктор
  template<class U>
  my_allocator( my_allocator<U> &another) noexcept {
    //m_preallocated = reinterpret_cast<T*>(std::malloc(m_size * sizeof(T)));
  };
  /// Деструктор
  ~my_allocator() {
    //std::free(m_preallocated);
  }

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
    /*if ( m_current_indx == m_size - 1 ) {
      throw std::bad_alloc();
    } 
    T* cur_ptr = reinterpret_cast<T*>(m_preallocated);
    cur_ptr += m_current_indx;
    m_current_indx++;
    return cur_ptr;*/
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

//private:
//  T *m_preallocated{nullptr};
//  int m_size{10};
//  int m_current_indx{0};
};

}