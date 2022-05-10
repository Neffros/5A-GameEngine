#include "../headers/RTTI.h";

using namespace GameEngine;

template <class Base>
RTTI<Base>::RTTI<Base>(const char* type, const RTTI<Base>& parent): _parent(parent), _type(type) { }

template <class Base>
bool RTTI<Base>::IsExactlyA(const RTTI<Base>& other) const
{
	return this->_type == other->_type;
}

template <class Base>
bool RTTI<Base>::IsA(const RTTI<Base>& other) const
{
	RTTI<Base>& current = other;

	while (current != RTTI<Base>::Default) {
		if (this->IsExactlyA(current))
			return true;

		current = current._parent;
	}

	return false;
}
