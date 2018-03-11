## 总结———scpp_refcountptr.hpp   
针对内存泄漏，C++有专门的范式来解决，以及特定的RAII机制来描绘，C++03标准中将资源放进对象中，在C++11标准使用智能指针来管理内存。针对现有标准，我在此实现的C++11标准类似的引用计数指针。  
此种指针有一个非常形象的说法，最后一个离开屋子的人负责关灯。  
```c++  
namespace scpp {

// Reference-counting pointer.  Takes ownership of an object.  Can be copied.
template <typename T>
class RefCountPtr {
  public:

	explicit RefCountPtr(T* p = NULL) {
		Create(p);	
	}

	RefCountPtr(const RefCountPtr<T>& rhs) {
		Copy(rhs);					
	}

	RefCountPtr<T>& operator=(const RefCountPtr<T>& rhs) {
		if(ptr_ != rhs.ptr_) {
			Kill();
			Copy(rhs);
		}
									
		return *this;
	}

	RefCountPtr<T>& operator=(T* p) {						
		if(ptr_ != p) {
			Kill();
			Create(p);
		}
							
		return *this;
	}

	~RefCountPtr() {							
		Kill();
	}

	T* Get() const { return ptr_; }

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
	int*	count_;

	void Create(T* p) {
		ptr_ = p;
		if(ptr_ != NULL) {
			count_ = new int;
			*count_ = 1;
		} else {
			count_ = NULL;
		}
	}

	void Copy(const RefCountPtr<T>& rhs) {
		ptr_ = rhs.ptr_;
		count_ = rhs.count_;
		if(count_ != NULL)
			++(*count_);
	}

	void Kill() {
		if(count_ != NULL) {
			if(--(*count_) == 0) {
				delete ptr_;
				delete count_;
			}
		}
	}

};
} // namespace scpp  
```  
类中同时提供了拷贝构造函数和赋值操作符，因此毫无疑问可以复制这些指针。当然还有一些缺陷，例如多线程的环境下，有一定的问题。