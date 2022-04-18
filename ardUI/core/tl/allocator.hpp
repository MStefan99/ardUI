//
// Created by MStefan99 on 16.4.22.
//

#ifndef ARDUI_ALLOCATOR_HPP
#define ARDUI_ALLOCATOR_HPP

#include "platform.h"


#if !USE_NEW

#include <cstdlib>

#endif


namespace tl {
	template <class T>
	class allocator {
	public:
		allocator() = default;
		~allocator() = default;

		T* allocate(unsigned int n = 1);
		void deallocate(T* p, unsigned int n = 1);

		template <class U, class... Args>
		void construct(U* p, Args& ... args);
		template <class U>
		void destroy(U* p);
	};


	#if USE_NEW


	template <class T>
	T* allocator<T>::allocate(unsigned int n) {
		return static_cast<T*>(::operator new(sizeof(T) * n));
	}


	template <class T>
	void allocator<T>::deallocate(T* p, unsigned int n) {
		::operator delete(p);
	}


	#else


	template <class T>
	T* allocator<T>::allocate(unsigned int n) {
		return static_cast<T*>(std::malloc(sizeof(T) * n));
	}


	template <class T>
	void allocator<T>::deallocate(T* p, unsigned int) {
		std::free(p);
	}


	#endif


	template <class T>
	template <class U, class... Args>
	void allocator<T>::construct(U* p, Args& ...args) {
		::new((void*)p) U(args...);
	}


	template <class T>
	template <class U>
	void allocator<T>::destroy(U* p) {
		p->~U();
	}
}

#endif //ARDUI_ALLOCATOR_HPP
