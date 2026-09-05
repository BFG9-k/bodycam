#pragma once
#include "../includes.h"

namespace core
{
	class c_cheat_bootstrap
	{
	public:
		static void run( );
	};
	inline const std::unique_ptr< c_cheat_bootstrap > bootstrap = std::make_unique< c_cheat_bootstrap >( );
}