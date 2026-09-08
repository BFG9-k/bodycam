#pragma once
#include "../../includes.h"

namespace game
{
	class c_hooked
	{
	public:
		void apply( );
	};
	inline const std::unique_ptr< c_hooked > hooked = std::make_unique< c_hooked >( );
}