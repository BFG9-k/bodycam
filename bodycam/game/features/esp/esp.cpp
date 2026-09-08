#include "esp.h"

void features::c_esp::process( SDK::UCanvas* Canvas )
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

    const SDK::FVector actor_location = current_actor->RootComponent->RelativeLocation;

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

      if ( NPC->PlayerState )
      {
        const SDK::FString player_name = NPC->PlayerState->GetPlayerName( );

        const SDK::FVector2D text_postition = { top_screen.X, top_screen.Y - 15.f };
        const SDK::FLinearColor text_color = { 1.f, 1.f, 1.f, 1.f };

        Canvas->K2_DrawText( SDK::UEngine::GetEngine( )->SmallFont, player_name, text_postition, { 1.f, 1.f }, text_color, 0.f, { 0.f, 0.f, 0.f, 1.f }, { 1.f, 1.f }, true, false, true, { 0.f, 0.f, 0.f, 1.f } );
      }

      if ( NPC->CharacterSet )
      {
        const float current_hp = NPC->CharacterSet->Health.CurrentValue;
        const float max_hp = NPC->CharacterSet->MaxHealth.CurrentValue;
        
        float hp_percentage = current_hp / max_hp; hp_percentage = max( 0.0f, min( 1.0f, hp_percentage ) );

        SDK::FLinearColor fill_color;
        if ( hp_percentage > 0.5f )
          fill_color = { 1.0f - ( hp_percentage - 0.5f ) * 2.0f, 1.0f, 0.0f, 1.0f };
        else
          fill_color = { 1.0f, hp_percentage * 2.0f, 0.0f, 1.0f };

        Canvas->K2_DrawLine( { box_position.X - 4.0f, box_position.Y }, { box_position.X - 4.0f, box_position.Y + box_size.Y }, 2.0f, { 0.2f, 0.2f, 0.2f, 1.0f} );     
  
        const float fill_height = ( ( box_position.Y + box_size.Y ) - box_position.Y ) * hp_percentage;
        Canvas->K2_DrawLine( { box_position.X - 4.0f, ( box_position.Y + box_size.Y ) - fill_height }, { box_position.X - 4.0f, box_position.Y + box_size.Y }, 2.0f, fill_color );
      }
    }
  }
}