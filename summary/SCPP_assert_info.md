## 总结————scpp_assert.hpp
如何定义一个宏来诊断缺陷，在scpp_assert.hpp中定义如下宏定义：
该宏定义很简单，没有什么可以说的，  
```c++  
// Permanent sanity check macro.
#define SCPP_ASSERT(condition, msg)                 \
    if(!(condition)) {                              \
        std::ostringstream s;                       \
        s << msg;                                   \
        SCPP_AssertErrorHandler(                    \
            __FILE__, __LINE__, s.str().c_str() );  \
	}
```  
同是在同文件中申明一个断言错误处理函数SCPP_AssertErrorHandler()，它的实现在对应的cpp文件，如下所示：  
```c++  
void SCPP_AssertErrorHandler(const char* file_name,
							 unsigned line_number,
							 const char* message) {
	// This is a good place to put your debug breakpoint:
	// You can also add writing of the same info into a log file if appropriate.
	
#ifdef SCPP_THROW_EXCEPTION_ON_BUG
	throw scpp::ScppAssertFailedException(file_name, line_number, message);
#else
	cerr << message << " in file " << file_name << " #" << line_number << endl << flush;
	// Terminate application
	exit(1);
#endif
}
```  
该函数取决于SCPP_THROW_EXCEPTION_ON_BUG是否定义。这没有什么可以说的。
以及该文件申明与定义了异常类`ScppAssertFailedException : public std::exception`公有继承与`exception`。
