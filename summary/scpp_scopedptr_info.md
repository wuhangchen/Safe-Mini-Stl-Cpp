## 总结———scpp_scopedptr  
当我们不打算复制智能指针，仅仅是想分配的资源被正确的回收，我们就采用作用域指针。  
```c++  
namespace scpp {

// Scoped pointer, takes ownership of an object, could not be copied.
template <typename T>
class ScopedPtr {
  public:

	explicit ScopedPtr(T* p = NULL)
	: ptr_(p) {
	}

	ScopedPtr<T>& operator=(T* p) {						
		if(ptr_ != p)
		{
			delete ptr_;
			ptr_ = p;
		}
							
		return *this;
	}

	~ScopedPtr() {							
		delete ptr_;
	}

	T* Get() const {						
		return ptr_;
	}

	T* operator->() const
	{						
		SCPP_TEST_ASSERT(ptr_ != NULL, "Attempt to use operator -> on NULL pointer.");
		return ptr_;
	}

	T& operator* () const { 
		SCPP_TEST_ASSERT(ptr_ != NULL, "Attempt to use operator * on NULL pointer.");
		return *ptr_;
	}
	
	// Release ownership of the object to the caller.
	T* Release() {
		T* p = ptr_;
		ptr_ = NULL;
		return p;
	}

private:
	T*	ptr_;

	// Copy is prohibited:
	ScopedPtr(const ScopedPtr<T>& rhs);
	ScopedPtr<T>& operator=(const ScopedPtr<T>& rhs);
};

} // namespace scpp
  
```  
这个类中的技术是很常见了的。