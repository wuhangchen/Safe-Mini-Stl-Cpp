## 总结————scpp_vector.hpp  
整个vector的设计没有什么大的巧妙的设计，仅仅只是公有继承于STL中的容器。  
可以简述的是唯一的就是运算符重载的设计，这涉及到cpp的哲学思维——模仿，上层的运算符（经过重载的）模拟的的底层（原生）的运算符。在上层的实现中，需要更多的考虑底层的实现。  
```c++  
T& operator [] (size_type index) {
		SCPP_TEST_ASSERT(index < std::vector<T>::size(),
			"Index " << index << " must be less than "
			<< std::vector<T>::size());
		return std::vector<T>::operator[](index);
	}

	const T& operator [] (size_type index) const {
		SCPP_TEST_ASSERT(index < std::vector<T>::size(),
			"Index " << index << " must be less than "
			<< std::vector<T>::size());
		return std::vector<T>::operator[](index);
	}  
```  
重载的运算符并没有什么可以值得注意的，唯一的注意的需要是调用了之前实现的安全检测的宏定义，然后就转调用STL中对应的方法。operator[]还针对const object与matable object来进行重载。