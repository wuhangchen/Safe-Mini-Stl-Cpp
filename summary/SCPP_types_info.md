## 总结———scpp_types.hpp 
毫无疑问，使用未初始化的变量是一种隐含的错误，可是在大多数的内置类型中，我们都会隐藏的发生这种错误。因此，在此头文件中，实现了对C++内置类型的重定义，尤其在类的设计中，不要使用内置类型，根本原因是因为内置类型没有构造函数。  
所以在此头文件中设计了一个模板类来完成相应的工作。  
```c++
template<typename T>
class TNumber {
public:
	TNumber(const T& x=0)
		: data_(x) {
	}

	operator T () const { return data_; }

	TNumber& operator = (const T& x) {
		data_ = x;
		return *this;
	}

	// postfix operator x++
	TNumber operator ++ (int) {
		TNumber<T> copy(*this);
		++data_;
		return copy;
	}

	// prefix operator ++x
	TNumber& operator ++ () {
		++data_;
		return *this;
	}

	TNumber& operator += (T x) {
		data_ += x;
		return *this;
	}

	TNumber& operator -= (T x) {
		data_ -= x;
		return *this;
	}

	TNumber& operator *= (T x) {
		data_ *= x;
		return *this;
	}

	TNumber& operator /= (T x) {
		SCPP_TEST_ASSERT(x!=0, "Attempt to divide by 0");
		data_ /= x;
		return *this;
	}

	T operator / (T x) 
	{
		SCPP_TEST_ASSERT(x!=0, "Attempt to divide by 0");
		return data_ / x;
	}

private:
	T data_;
};  
```  
同时该类中的构造函数并没有申明为explicit。这是有意为之。此类中的下一个函数是operator T(),它允许将这个类的实例隐式的转换对应的内置类型，其中定义的重载操作符这没有什么好讲的。  
```c++  
typedef long long int64;
typedef unsigned long long unsigned64;

typedef		TNumber<int>		Int;
typedef		TNumber<unsigned>		Unsigned;
typedef		TNumber<int64>		Int64;
typedef		TNumber<unsigned64>	Unsigned64;
typedef		TNumber<float>		Float;
typedef		TNumber<double>		Double;
typedef		TNumber<char>		Char;  
```  
类的最后针对bool类型进行特化版本的设计。  
1. 相比较于bool类型，它被初始化为false。采取的标准来源于STL的标准之一。  
2. 它具有<<操作符，打印出False和True。显得更为清晰。  
3. 同时还会有额外的类型安全。