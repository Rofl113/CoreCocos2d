#pragma once
#include <cassert>
#include <type_traits>
#include <forward_list>



namespace cocos2d { class Ref; }


template<class T>
class PtrCocos2d
{
	using TypeCocosBase = cocos2d::Ref;

public:
	PtrCocos2d() noexcept : px( 0 )
	{
		static_assert(std::is_base_of<cocos2d::Ref, T>::value, "Should be child of cocos2d::Ref");
	}

	template<typename ... Args>
	static PtrCocos2d<T> create(Args&& ... args)
	{
		static_assert(std::is_base_of<cocos2d::Ref, T>::value, "Should be child of cocos2d::Ref");
		return T::create(std::forward<Args>(args)...);
		// no retain()!
	}

	PtrCocos2d(T* p) noexcept: px( p )
	{
		if (px) px->retain();
	}

	PtrCocos2d(PtrCocos2d const& rhs, bool add_ref = false): px( rhs.px )
	{
		if (px and add_ref) px->retain();
	}

	template<class U>
	PtrCocos2d(PtrCocos2d<U> const& rhs): px( rhs.get() )
	{
		if (px) px->retain();
	}

	~PtrCocos2d()
	{
		if (px) px->release();
	}

	PtrCocos2d(PtrCocos2d&& rhs) noexcept : px( rhs.px )
	{
		rhs.px = nullptr;
	}

	PtrCocos2d& operator=(PtrCocos2d&& rhs) noexcept
	{
		PtrCocos2d(static_cast<PtrCocos2d&&>(rhs)).swap(*this);
		return *this;
	}

	PtrCocos2d& operator=(PtrCocos2d const& rhs)
	{
		PtrCocos2d(rhs).swap(*this);
		return *this;
	}

	PtrCocos2d& operator=(T* rhs)
	{
		PtrCocos2d(rhs).swap(*this);
		return *this;
	}

	void reset() noexcept
	{
		PtrCocos2d().swap(*this);
	}

	void reset(T* rhs)
	{
		PtrCocos2d(rhs).swap( *this );
	}

	void reset(T* rhs, bool add_ref)
	{
		PtrCocos2d(rhs, add_ref).swap(*this);
	}

	T* get() const noexcept
	{
		return px;
	}

	T& operator*() const
	{
		assert(px);
		return *px;
	}

	T* operator->() const
	{
		assert(px);
		return px;
	}

	operator bool () const noexcept
	{
		return px != 0;
	}

	inline bool operator==(PtrCocos2d<T> const& b) const
	{
		return px == b.get();
	}

	inline bool operator!=(PtrCocos2d<T> const& b) const
	{
		return px != b.get();
	}

private:
	void swap(PtrCocos2d& rhs) noexcept
	{
		T* tmp = px;
		px = rhs.px;
		rhs.px = tmp;
	}

	T* px;
};
