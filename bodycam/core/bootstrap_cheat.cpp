#include "bootstrap_cheat.h"

void core::c_cheat_bootstrap::run( )
{
	core::logger->alloc_console( "bodycam" );
	L_INFO( "attached" );

	game::hooked->apply( );
}