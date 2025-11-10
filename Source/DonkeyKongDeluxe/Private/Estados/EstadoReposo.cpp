
#include "Estados/EstadoReposo.h"
#include "Personaje/DKCPlayerCharacter.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Estados/EstadoSalto.h"
#include "Estados/EstadoRodarTierra.h" 

UEstadoReposo::UEstadoReposo() {}

void UEstadoReposo::OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia)
{
	Super::OnEnter(PersonajeReferencia, ActorReferencia);
	UE_LOG(LogTemp, Warning, TEXT("Estado: Entrando en Reposo/Caminando"));
}

void UEstadoReposo::OnExit()
{
	Super::OnExit();
	UE_LOG(LogTemp, Warning, TEXT("Estado: Saliendo de Reposo/Caminando"));
}

void UEstadoReposo::TickState(float DeltaTime)
{
	if (Personaje && Personaje->GetCharacterMovement()->IsFalling())
	{
		Personaje->CambiarEstado(NewObject<UEstadoSalto>(Personaje));
	}
}

void UEstadoReposo::ManejarInputSalto()
{
	if (Personaje)
	{
		Personaje->Jump();
		Personaje->CambiarEstado(NewObject<UEstadoSalto>(Personaje));
	}
}

void UEstadoReposo::ManejarInputRodar()
{
	if (Personaje)
	{
		Personaje->EjecutarRodarAccion();
	}
}


void UEstadoReposo::ManejarInputMoverDerecha(float Valor)
{

	if (Personaje && Personaje->GetController() != nullptr && Valor != 0.0f)
	{
		Personaje->AddMovementInput(FVector(0.f, -1.f, 0.f), Valor);
	}
}