#include <iostream>
#include <cstddef>
class memory_alloc_dispatch
{
    public:
        enum {base = 8};
    private:
        std::byte * heap_first;
        std::byte * heap_end;
        std::size_t heap_size;
    public:
        memory_alloc_dispatch() 
        : heap_first {nullptr},
          heap_end {nullptr},
          heap_size {0}
        {}
        memory_alloc_dispatch(const memory_alloc_dispatch&) = delete;
        memory_alloc_dispatch& operator= (const memory_alloc_dispatch&) = delete;
        ~memory_alloc_dispatch() noexcept
        {
            if (heap_first != heap_end)
                free(heap_first);
            heap_first = nullptr; 
        }
        constexpr int UP_GRAD(int bytesRequired) const
        {return bytesRequired;}  
        std::size_t reallocate(std::size_t bytesRequired)
        {
            heap_first = (std::byte *)malloc(bytesRequired);
            heap_size = bytesRequired;
            heap_end = heap_first + bytesRequired;
            return bytesRequired;
        }

        std::byte * allocMemoryFromPool(std::size_t n)
        {
           if (heap_first == heap_end) {
                if (std::size_t required = reallocate(20 * UP_GRAD(n));
                    required >= n) {
                        std::byte * customRequiredBytes = heap_first;
                        heap_first += UP_GRAD(n);
                        heap_size -= UP_GRAD(n);
                        return customRequiredBytes;   
                } else if (required < n) {
                }
            }
            else if (heap_size < UP_GRAD(n)) {
            }
            else {
                heap_first += UP_GRAD(n);
                heap_size -= UP_GRAD(n);
                return (heap_first - UP_GRAD(n));
            }
        }

        std::byte * first() {return heap_first;}
        std::byte * end() {return heap_end;}
};  // class memory_alloc_dispatch

class A
{
public :
    int d;
    virtual void get() {std::cout << "A\n";}
};

class B : public A
{
public:
    int d2;
 //   using A::get;
   // virtual void get() {std::cout << "B\n";};
};

int main ()
{
    B b;
    b.get();  
    return 0;
}