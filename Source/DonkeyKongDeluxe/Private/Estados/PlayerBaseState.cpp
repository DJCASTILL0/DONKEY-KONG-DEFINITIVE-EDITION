
#include "Estados/PlayerBaseState.h"

void UPlayerBaseState::OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia)
{
	Personaje = PersonajeReferencia;
}
void UPlayerBaseState::OnExit() {}
void UPlayerBaseState::TickState(float DeltaTime) {}
void UPlayerBaseState::ManejarInputSalto() {}
void UPlayerBaseState::ManejarInputRodar() {}
bool UPlayerBaseState::EstaAtacando() const { return false; }
void UPlayerBaseState::ManejarInputMoverArriba(float Valor) {}


void UPlayerBaseState::ManejarInputMoverDerecha(float Valor)
{

}