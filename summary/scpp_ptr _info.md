## 总结———scpp_ptr 
毫无疑问，导致程序崩溃的最最要的原因就是试图解引用NULL指针，前面我们实现的引用型指针和作用域型指针能够提供了运行时期的诊断功能。  
但是我们不想使用智能指针的时候如何处理呢？于是我们自己实现了一个。    
此模板指针Ptr<T>具有下面特性。
1. 它并不拥有对象的所有权。
2. 默认情况下，初始化为NULL。  
3. 提供了运行期间的诊断功能，
```c++  
#include "scpp_assert.hpp"

namespace scpp {

// Template pointer, does not take ownership of an object.
template <typename T>
class Ptr {
  public:

	explicit Ptr(T* p = NULL)
	: ptr_(p) {
	}

	T* Get() const {						
		return ptr_;
	}

	Ptr<T>& operator=(T* p) {
		ptr_ = p;
		return *this;
	}

	T* operator->() const {						
		SCPP_TEST_ASSERT(ptr_ != NULL, "Attempt to use operator -> on NULL pointer.");
		return ptr_;
	}

	T& operator* () const { 
		SCPP_TEST_ASSERT(ptr_ != NULL, "Attempt to use operator * on NULL pointer.");
		return *ptr_;
	}

private:
	T*	ptr_;
};

} // namespace scpp
  
```