// RUTA: Source/DonkeyKongDeluxe/Private/Estrategias/DiddyKongStrategy.cpp

#include "Estrategias/DiddyKongStrategy.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Estados/EstadoRodarTierra.h"

void UDiddyKongStrategy::AjustarParametrosMovimiento()
{
	if (Personaje)
	{
		// Los valores C++ de Diddy
		Personaje->GetCharacterMovement()->MaxWalkSpeed = 600.f;
		Personaje->GetCharacterMovement()->JumpZVelocity = 700.f;
		Personaje->GetCharacterMovement()->AirControl = 0.5f;
		UE_LOG(LogTemp, Warning, TEXT("Estrategia C++: Cambiado a Diddy Kong (Velocidad: 600)"));
	}
}


void UDiddyKongStrategy::AplicarMallaEAnimacion(ADKCPlayerCharacter* PersonajeReferencia)
{
	if (PersonajeReferencia)
	{
		PersonajeReferencia->GetMesh()->SetSkeletalMesh(PersonajeReferencia->GetMallaDiddy());
		PersonajeReferencia->GetMesh()->SetAnimInstanceClass(PersonajeReferencia->GetAnimClassDiddy());
	}
}

void UDiddyKongStrategy::EjecutarRodar(ADKCPlayerCharacter* PersonajeReferencia)
{
	if (PersonajeReferencia && PersonajeReferencia->GetCharacterMovement()->IsMovingOnGround())
	{
		UE_LOG(LogTemp, Warning, TEXT("Estrategia C++: Ejecutando Voltereta de Diddy Kong."));
		PersonajeReferencia->CambiarEstado(NewObject<UEstadoRodarTierra>(PersonajeReferencia));
	}
}