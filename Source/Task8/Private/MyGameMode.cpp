#include "MyGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "MyGameState.h"

AMyGameMode::AMyGameMode()
{
    PlayerControllerClass = ASpartaPlayerController::StaticClass();
    DefaultPawnClass = ASpartaCharacter::StaticClass();
    // 우리가 만든 GameState로 설정
    GameStateClass = AMyGameState::StaticClass();

}
