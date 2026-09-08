#include "bootstrap_cheat.h"

void core::c_cheat_bootstrap::run( )
{
#ifdef _DEBUG
	core::logger->alloc_console( "bodycam" );
	L_INFO( "attached" );
#endif
	game::hooked->apply( );
}