#pragma once
#include "../features.h"

namespace features
{
	class c_esp
	{
	public:
		void process( SDK::UCanvas* canvas );
	};
	inline const std::unique_ptr< c_esp > esp = std::make_unique< c_esp >( );
}