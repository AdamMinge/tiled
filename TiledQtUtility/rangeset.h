/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <map>
/*-----------------------------------------------------------------------------------------------------------*/
#define RANGESET_ITERATOR(NAME, ITERATOR, TYPE)									\
class NAME : public std::map<TYPE, TYPE>::##ITERATOR							\
{																				\
public:																			\
	NAME() = default;															\
	explicit NAME(const typename std::map<TYPE, TYPE>::##ITERATOR& iter)		\
	: std::map<TYPE, TYPE>::##ITERATOR(iter) {}									\
																				\
	TYPE first() const { return (*this)->first; }								\
	TYPE last() const { return (*this)->second; }								\
	TYPE length() const { return last() - first() + 1;}							\
};																				
/*-----------------------------------------------------------------------------------------------------------*/
template<typename TYPE, typename = std::enable_if_t<std::is_integral<TYPE>::value>>
class RangeSet final
{
public:
	RANGESET_ITERATOR(ConstIterator, const_iterator, TYPE)
	RANGESET_ITERATOR(ConstReverseIterator, const_reverse_iterator, TYPE)

public:
	RangeSet() = default;
	~RangeSet() = default;

	RangeSet(const RangeSet&) = default;
	RangeSet(RangeSet&&) = default;

	RangeSet& operator=(const RangeSet&) = default;
	RangeSet& operator=(RangeSet&&) = default;

	void insert(TYPE value);

	ConstIterator begin() const;
	ConstIterator end() const;

	ConstReverseIterator rbegin() const;
	ConstReverseIterator rend() const;

	bool isEmpty() const;

private:
	std::map<TYPE, TYPE> mMap;
};
/*-----------------------------------------------------------------------------------------------------------*/
template <typename TYPE, typename U>
void RangeSet<TYPE, U>::insert(TYPE value)
{
	if (mMap.empty()) 
	{
		mMap.insert(std::make_pair(value, value));
		return;
	}

	auto it = mMap.lower_bound(value);
	auto begin = mMap.begin();
	auto end = mMap.end();

	if (it == end) 
	{
		--it;

		if (it->second >= value) return;
		if (++it->second == value) return;

		--it->second;

		mMap.insert(it, std::make_pair(value, value));
		return;
	}

	if (it->first == value) return;

	if (it->first == value + 1) 
	{
		auto prev = it;
		if (it != begin)
		{
			--prev;
			if (prev->second == value - 1) 
			{
				prev->second = it->second;
				mMap.erase(it);
				return;
			}
		}

		mMap.insert(prev, std::make_pair(value, it->second));
		mMap.erase(it);
		return;
	}

	if (it != begin) 
	{
		--it;
		if (it->second == value - 1) 
		{
			++it->second;
			return;
		}
	}

	mMap.insert(it, std::make_pair(value, value));
}
/*-----------------------------------------------------------------------------------------------------------*/
template <typename TYPE, typename U>
typename RangeSet<TYPE, U>::ConstIterator RangeSet<TYPE, U>::begin() const
{
	return ConstIterator(mMap.begin());
}
/*-----------------------------------------------------------------------------------------------------------*/
template <typename TYPE, typename U>
typename RangeSet<TYPE, U>::ConstIterator RangeSet<TYPE, U>::end() const
{
	return ConstIterator(mMap.end());
}
/*-----------------------------------------------------------------------------------------------------------*/
template <typename TYPE, typename U>
typename RangeSet<TYPE, U>::ConstReverseIterator RangeSet<TYPE, U>::rbegin() const
{
	return ConstReverseIterator(mMap.rbegin());
}
/*-----------------------------------------------------------------------------------------------------------*/
template <typename TYPE, typename U>
typename RangeSet<TYPE, U>::ConstReverseIterator RangeSet<TYPE, U>::rend() const
{
	return ConstReverseIterator(mMap.rend());
}
/*-----------------------------------------------------------------------------------------------------------*/
template <typename TYPE, typename U>
bool RangeSet<TYPE, U>::isEmpty() const
{
	return mMap.empty();
}
/*-----------------------------------------------------------------------------------------------------------*/

