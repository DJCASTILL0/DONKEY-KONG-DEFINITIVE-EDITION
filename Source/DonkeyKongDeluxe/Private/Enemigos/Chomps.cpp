
#include "Enemigos/Chomps.h"
#include "GameFramework/CharacterMovementComponent.h" // Para la gravedad C++
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"

AChomps::AChomps()
{

	bPatrullaSoloEnAgua = true;


	GetCharacterMovement()->GravityScale = 0.0f;


	const TCHAR* RutaMesh = TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin");
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(RutaMesh);

	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}

}