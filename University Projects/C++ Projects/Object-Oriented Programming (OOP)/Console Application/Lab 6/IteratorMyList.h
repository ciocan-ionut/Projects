#pragma once

template <typename TElement>
class MyList;

template <typename TElement>
class IteratorMyList
{
	friend class MyList<TElement>;
private:
	const MyList<TElement>& v;
	int poz = 0;

public:
	IteratorMyList(const MyList<TElement>& v) noexcept;

	IteratorMyList(const MyList<TElement>& v, int poz) noexcept;

	bool valid() const;

	TElement& element() const;

	void next();

	TElement& operator*();

	IteratorMyList& operator++();

	bool operator==(const IteratorMyList& ot) noexcept;

	bool operator!=(const IteratorMyList& ot) noexcept;
};

template<typename TElement>
IteratorMyList<TElement>::IteratorMyList(const MyList<TElement>& v) noexcept : v{ v } {}

template<typename TElement>
IteratorMyList<TElement>::IteratorMyList(const MyList<TElement>& v, int poz) noexcept : v{ v }, poz { poz } {}

template<typename TElement>
bool IteratorMyList<TElement>::valid() const
{
	return poz < v.lg;
}

template<typename TElement>
TElement& IteratorMyList<TElement>::element() const
{
	return v.elems[poz];
}

template<typename TElement>
void IteratorMyList<TElement>::next()
{
	poz++;
}

template<typename TElement>
TElement& IteratorMyList<TElement>::operator*()
{
	return element();
}

template<typename TElement>
IteratorMyList<TElement>& IteratorMyList<TElement>::operator++()
{
	next();
	return *this;
}

template<typename TElement>
bool IteratorMyList<TElement>::operator==(const IteratorMyList<TElement>& ot) noexcept
{
	return poz == ot.poz;
}

template<typename TElement>
bool IteratorMyList<TElement>::operator!=(const IteratorMyList<TElement>& ot) noexcept
{
	return !(*this == ot);
}