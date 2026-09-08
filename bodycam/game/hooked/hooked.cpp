#include "hooked.h"

using PostRender_t = void( __thiscall* )( SDK::UObject*, SDK::UObject* );
PostRender_t o_PostRender;
void hk_PostRender( SDK::UObject* ViewportClient, SDK::UCanvas* Canvas )
{
  SDK::UWorld* const World = SDK::UWorld::GetWorld( );
  if ( !World ) 
    return;

  SDK::UGameInstance* const GameInstance = World->OwningGameInstance;
  if ( !GameInstance || !GameInstance->LocalPlayers[ 0 ] ) 
    return;

  SDK::APlayerController* const PlayerController = GameInstance->LocalPlayers[ 0 ]->PlayerController;
  if ( !PlayerController )
    return;

  for ( const auto& current_actor : World->PersistentLevel->Actors )
  {
    if ( !current_actor )
      continue;

    if ( !current_actor->IsA( SDK::ABodycamCharacter::StaticClass( ) ) )
      continue;

    SDK::ABodycamCharacter* const NPC = static_cast< SDK::ABodycamCharacter* >( current_actor );
    if ( !NPC )
      continue;

    if ( !NPC->IsCharacterAlive( ) )
      continue;

    if ( NPC == PlayerController->AcknowledgedPawn )
      continue;

    const SDK::FVector actor_location = current_actor->K2_GetActorLocation( );

    const SDK::FVector top_world = { actor_location.X, actor_location.Y, actor_location.Z + 85.f };
    const SDK::FVector bottom_world = { actor_location.X, actor_location.Y, actor_location.Z - 85.f };

    const SDK::FVector top_screen = Canvas->K2_Project( top_world ); 
    const SDK::FVector bottom_screen = Canvas->K2_Project( bottom_world );

    if ( top_screen.Z > 0.f && bottom_screen.Z > 0.f )
    {
      const float height = bottom_screen.Y - top_screen.Y;
      const float width = height / 1.8f;

      const SDK::FVector2D box_position = { top_screen.X - ( width / 2.0f ), top_screen.Y };
      const SDK::FVector2D box_size = { width, height };

      Canvas->K2_DrawBox( box_position, box_size, 1.5f, SDK::FLinearColor{ 1.f, 1.f, 1.f, 1.f } );
    }
  }
}

void game::c_hooked::apply( )
{
	MH_Initialize( );

	const SDK::UGameViewportClient* local_viewport_client = SDK::UWorld::GetWorld( )->OwningGameInstance->LocalPlayers[ 0 ]->ViewportClient;
	void* const postrender = reinterpret_cast< void** >( local_viewport_client->VTable )[ 115 ];
	MH_CreateHook( postrender, &hk_PostRender, reinterpret_cast< void** >( &o_PostRender ) );

	MH_EnableHook( MH_ALL_HOOKS );
}