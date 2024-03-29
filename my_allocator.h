
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
  my_allocator()  {        
    m_preallocated = reinterpret_cast<T*>(std::malloc(m_size * sizeof(T)));  
  };
  /// �����������
  template<class U>
  my_allocator( my_allocator<U> &another) noexcept {       
    std::cout << "my_allocator( my_allocator<U> &another)" << std::endl;
  };
  /// ����������
  ~my_allocator() {
    free(m_preallocated);
  }

  /// ��� �������� ������� ���� ����������
  template<typename U>
  struct rebind {
  using other = my_allocator<U>;
  };

  /// ������� ������
  T * allocate(size_t n)
  {        
    if ( m_current_indx + n > m_size ) {
      std::cout << "m_current_indx + n > m_size" << std::endl;      
      throw std::bad_alloc();
    } 
    T* cur_ptr = m_preallocated;
    cur_ptr += m_current_indx;
    m_current_indx += n;
    return cur_ptr;
  }

  /// ���������� ������
  void deallocate(T * p, size_t n)
  {    
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

private:
  T *m_preallocated{nullptr};
  size_t m_size{15};
  size_t m_current_indx{0};
};

}