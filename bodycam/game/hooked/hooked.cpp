#include "hooked.h"

using PostRender_t = void( __thiscall* )( SDK::UObject*, SDK::UObject* );
PostRender_t o_PostRender;
void hk_PostRender( SDK::UObject* ViewportClient, SDK::UCanvas* Canvas )
{
	features::esp->process( Canvas );
}

void game::c_hooked::apply( )
{
	MH_Initialize( );

	const SDK::UGameViewportClient* local_viewport_client = SDK::UWorld::GetWorld( )->OwningGameInstance->LocalPlayers[ 0 ]->ViewportClient;
	void* const postrender = reinterpret_cast< void** >( local_viewport_client->VTable )[ 115 ];
	MH_CreateHook( postrender, &hk_PostRender, reinterpret_cast< void** >( &o_PostRender ) );

	MH_EnableHook( MH_ALL_HOOKS );
}