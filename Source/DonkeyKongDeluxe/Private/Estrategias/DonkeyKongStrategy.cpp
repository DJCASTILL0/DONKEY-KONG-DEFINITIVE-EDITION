// RUTA: Source/DonkeyKongDeluxe/Private/Estrategias/DonkeyKongStrategy.cpp

#include "Estrategias/DonkeyKongStrategy.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Estados/EstadoRodarTierra.h" 

void UDonkeyKongStrategy::AjustarParametrosMovimiento()
{
	if (Personaje)
	{
		// Los valores C++ de Donkey Kong
		Personaje->GetCharacterMovement()->MaxWalkSpeed = 500.f;
		Personaje->GetCharacterMovement()->JumpZVelocity = 650.f;
		Personaje->GetCharacterMovement()->AirControl = 0.2f;
		UE_LOG(LogTemp, Warning, TEXT("Estrategia C++: Cambiado a Donkey Kong (Velocidad: 500)"));
	}
}

// (CORREGIDO) Nombre del parámetro C++
void UDonkeyKongStrategy::AplicarMallaEAnimacion(ADKCPlayerCharacter* PersonajeReferencia)
{
	if (PersonajeReferencia)
	{
		// Usamos el 'PersonajeReferencia' que viene de la función
		PersonajeReferencia->GetMesh()->SetSkeletalMesh(PersonajeReferencia->GetMallaDonkey());
		PersonajeReferencia->GetMesh()->SetAnimInstanceClass(PersonajeReferencia->GetAnimClassDonkey());
	}
}

void UDonkeyKongStrategy::EjecutarRodar(ADKCPlayerCharacter* PersonajeReferencia)
{
	if (PersonajeReferencia && PersonajeReferencia->GetCharacterMovement()->IsMovingOnGround())
	{
		UE_LOG(LogTemp, Warning, TEXT("Estrategia C++: Ejecutando Roll de Donkey Kong."));
		PersonajeReferencia->CambiarEstado(NewObject<UEstadoRodarTierra>(PersonajeReferencia));
	}
}