#pragma once

#include <list>

namespace Sea
{
	template<typename E>
	using List = std::list<E>;
	
	class Lists
	{
	public:
		template<typename E>
		static bool Contains(List<E> list, E element)
		{
			return std::find(list.begin(), list.end(), element) != list.end();
		}

	};



}