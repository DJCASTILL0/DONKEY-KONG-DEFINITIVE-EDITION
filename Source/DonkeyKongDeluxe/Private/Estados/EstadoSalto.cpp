
#include "Estados/EstadoSalto.h"
#include "Personaje/DKCPlayerCharacter.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Estados/EstadoReposo.h" 

UEstadoSalto::UEstadoSalto() {}

void UEstadoSalto::OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia)
{
	Super::OnEnter(PersonajeReferencia, ActorReferencia);
	UE_LOG(LogTemp, Warning, TEXT("Estado: Entrando en Salto/Caida"));
}

void UEstadoSalto::OnExit()
{
	Super::OnExit();
	UE_LOG(LogTemp, Warning, TEXT("Estado: Saliendo de Salto/Caida"));
}

void UEstadoSalto::TickState(float DeltaTime)
{
	if (Personaje && !Personaje->GetCharacterMovement()->IsFalling())
	{
		Personaje->CambiarEstado(NewObject<UEstadoReposo>(Personaje));
	}
}


void UEstadoSalto::ManejarInputMoverDerecha(float Valor)
{

	if (Personaje && Personaje->GetController() != nullptr && Valor != 0.0f)
	{
		Personaje->AddMovementInput(FVector(0.f, -1.f, 0.f), Valor);
	}
}