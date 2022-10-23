#pragma once

namespace Sea
{
	template<typename K, typename V>
	struct Pair
	{
		Pair(K key, V value) : key(key), value(value) { }
		Pair(const Pair&) = default
		Pair(Pair&&) = default
		~Pair()=default

		K key;
		V value;
	};
}