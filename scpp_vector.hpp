/*
 
 If you feel your use of code examples falls outside fair use or the
 permission given above, feel free to contact us at 1714593434@Outlook.com.
 
*/

#ifndef __SCPP_VECTOR_HPP_INCLUDED__
#define __SCPP_VECTOR_HPP_INCLUDED__

#include <vector>
#include "scpp_assert.hpp"


namespace scpp {
	
// Wrapper around std::vector, has temporary sanity checks in the operators [].
template <typename T>
class vector : public std::vector<T> {
 public:
	typedef unsigned size_type;	
	
	// Most commonly used constructors:
	explicit vector( size_type n = 0  )
	: std::vector<T>(n)
	{}
	
	vector( size_type n, const T& value )
	: std::vector<T>(n, value)
	{}

	template <class InputIterator> vector ( InputIterator first, InputIterator last )
	: std::vector<T>(first, last)
	{}
	
	// Note: we do not provide a copy-ctor and assignment operator.
	// we rely on default versions of these methods generated by the compiler.
	
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
};
} // namespace scpp


template <typename T>
inline
std::ostream& operator << (std::ostream& os, const scpp::vector<T>& v) {
	for(unsigned i=0; i<v.size(); ++i) {
		os << v[i];
		if( i + 1 < v.size() )
			os << " ";
	}
	return os;
}

#endif // __SCPP_VECTOR_HPP_INCLUDED__