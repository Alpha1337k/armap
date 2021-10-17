#ifndef FT_ARMAP_HPP
#define FT_ARMAP_HPP

#include <limits>
#include <iostream>
#include <functional>
#include <vector>

#define VBREF std::vector<std::pair<K, T> >

template <typename K, typename T, class Compare = std::less<K> >
class Armap : public VBREF
{
	public:
		typedef K							        key_type;
		typedef T							        mapped_type;
		typedef std::pair<const K, T> 		        value_type;
		typedef	typename VBREF::iterator I;
	private:
		Compare _cmp;
	public:
		T &operator[](const K &k)
		{
			// std::cout << "size: " << VBREF::size() << std::endl;

			if (VBREF::size() == 0)
			{
				value_type n(k, T());

				VBREF::push_back(n);
				return VBREF::front().second;
			}
			size_t traverser = VBREF::size() / 2;
			I i = VBREF::begin() + traverser;
			I i2;
			traverser /= 2;
			for (; ; traverser /= 2)
			{
				if (traverser == 0)
					traverser = 1;
				// std::cout << "comparing " << i->first << " vs " << k << " traverser: " << traverser << std::endl;
				i2 = i;
				i2++;
				if ((_cmp(i->first, k) && _cmp(k, i2->first)) || (_cmp(i->first, k) && i2 == VBREF::end()) || i2 == VBREF::begin())
					break;
				else if (_cmp(i->first, k)) // k > i
					i += traverser;
				else if (_cmp(k, i->first)) // k < i
					i -= traverser;
				else
					return i->second;
			}
			T t = T();
			// std::cout << "inserting " << k << " before " << i2->first << std::endl;
			return VBREF::insert(i2, std::make_pair<K, T>(k, t))->second;
		}

};

#endif