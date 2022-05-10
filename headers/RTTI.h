#pragma once

#include <string>

namespace GameEngine
{
	class DefaultRTTI {};
	
	template <class Base>
	class RTTI
	{
	public:
		static RTTI<DefaultRTTI> Default;
	protected:
		const RTTI<Base>& _parent;
		std::string _type;
	public:
		RTTI(const char* type, const RTTI<Base>& parent);

		bool IsA(const RTTI<Base>& other) const;
		bool IsExactlyA(const RTTI<Base>& other) const;
	};

#define RTTI_DECLARATION(Base) \
	static RTTI<Base> Type;
#define RTTI_DEFINITION(Base, Parent) \
	RTTI<DefaultRTTI> RTTI<Base>::Default("", RTTI<Base>::Default); \
	RTTI<Base> Base::Type("#Base", Parent::rtti);
#define RTTI_DEFINITION_BASE(Base) \
	RTTI<DefaultRTTI> RTTI<Base>::Default("", RTTI<Base>::Default); \
	RTTI<Base> Base::Type("#Base", RTTI<Base>::Default);
}