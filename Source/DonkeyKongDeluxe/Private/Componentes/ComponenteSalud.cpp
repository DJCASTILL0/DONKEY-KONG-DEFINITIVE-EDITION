// RUTA: Source/DonkeyKongDeluxe/Private/Componentes/ComponenteSalud.cpp

#include "Componentes/ComponenteSalud.h"
#include "TimerManager.h" 

UComponenteSalud::UComponenteSalud()
{
	PrimaryComponentTick.bCanEverTick = false;
	SaludMaxima = 10.0f;
	SaludActual = SaludMaxima;
	bPuedeSerInvulnerable = false;
	bEsInvencible = false;
	bEsInvulnerable = false;
	DuracionInvulnerabilidad = 3.0f;
}

void UComponenteSalud::BeginPlay()
{
	Super::BeginPlay();
	EnSaludCambiada.Broadcast(SaludActual);
}

void UComponenteSalud::RecibirDanio(float DanioAplicado)
{
	if (bEsInvencible) return;
	if (bEsInvulnerable) return;
	if (SaludActual <= 0.0f) return;

	SaludActual = FMath::Clamp(SaludActual - DanioAplicado, 0.0f, SaludMaxima);
	EnSaludCambiada.Broadcast(SaludActual);
	UE_LOG(LogTemp, Warning, TEXT("%s recibio danio. Salud restante: %f"), *GetOwner()->GetName(), SaludActual);

	// (NUEVO) Notificamos a los observadores C++ (K. Rool) que hemos sido golpeados
	EnDanoRecibido.Broadcast();

	if (bPuedeSerInvulnerable && SaludActual > 0.0f)
	{
		bEsInvulnerable = true;
		UE_LOG(LogTemp, Warning, TEXT("%s AHORA ES INVULNERABLE."), *GetOwner()->GetName());

		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_Invulnerabilidad,
			this,
			&UComponenteSalud::TerminarInvulnerabilidad,
			DuracionInvulnerabilidad,
			false);
	}
	else if (SaludActual <= 0.0f)
	{
		EnMuerte.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("%s ha muerto!"), *GetOwner()->GetName());
	}
}

void UComponenteSalud::TerminarInvulnerabilidad()
{
	bEsInvulnerable = false;
	UE_LOG(LogTemp, Warning, TEXT("%s YA NO ES INVULNERABLE."), *GetOwner()->GetName());
}