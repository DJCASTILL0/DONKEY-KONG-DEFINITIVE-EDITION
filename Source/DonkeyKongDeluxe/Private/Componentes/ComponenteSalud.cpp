#include "Componentes/ComponenteSalud.h"
#include "TimerManager.h" 

UComponenteSalud::UComponenteSalud()
{
	PrimaryComponentTick.bCanEverTick = false;

	SaludMaxima = 3.0f;
	SaludActual = SaludMaxima;

	// Invulnerabilidad (Jugador)
	bPuedeSerInvulnerable = false;
	bEsInvulnerable = false;
	DuracionInvulnerabilidad = 3.0f;

	bEsInvencible = false; // Por defecto, los enemigos NO son invencibles
}

void UComponenteSalud::BeginPlay()
{
	Super::BeginPlay();
	EnSaludCambiada.Broadcast(SaludActual);
}

void UComponenteSalud::RecibirDanio(float DanioAplicado)
{
	if (bEsInvencible)
	{
		return; // Ignora todo el daño
	}

	if (bEsInvulnerable)
	{
		return;
	}

	if (SaludActual <= 0.0f)
	{
		return;
	}

	SaludActual = FMath::Clamp(SaludActual - DanioAplicado, 0.0f, SaludMaxima);
	EnSaludCambiada.Broadcast(SaludActual);
	UE_LOG(LogTemp, Warning, TEXT("%s recibio danio. Salud restante: %f"), *GetOwner()->GetName(), SaludActual);

	// 5. Activar Invulnerabilidad (SI PUEDE y si no murió)
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
	// 6. Comprobar si ha muerto
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