
namespace my_lib {

// ��� ���������
template<typename T>
struct my_allocator
{

  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using size_type = std::size_t;

  /// �����������
  my_allocator() noexcept{};
  /// �����������
  template<class U>
  my_allocator(const my_allocator<U>&) noexcept {};
  /// ����������
  ~my_allocator() = default;

  /// ��� �������� ������� ���� ����������
  template<typename U>
  struct rebind {
  using other = my_allocator<U>;
  };

  /// ������� ������
  T * allocate(size_t n)
  {
    void *p = std::malloc(n * sizeof(T));
    if ( !p ) {
      throw std::bad_alloc();
    }
    return reinterpret_cast<T*>(p);
  }

  /// ���������� ������
  void deallocate(T * p, size_t n)
  {
    std::free(p);
  }

  /// ��������������� ������
  template<typename U, typename ...Args>
  void construct(U* p, Args &&...args)
  {
    new (p) U(std::forward<Args>(args)...);
  }  

  /// ���������� ������
  void destroy(T * p)
  {
    p->~T();
  }
};

}