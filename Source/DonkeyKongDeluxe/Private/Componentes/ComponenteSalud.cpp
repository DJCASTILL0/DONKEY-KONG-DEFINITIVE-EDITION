// RUTA: Source/DonkeyKongDeluxe/Private/Componentes/ComponenteSalud.cpp

#include "Componentes/ComponenteSalud.h"

UComponenteSalud::UComponenteSalud()
{
	PrimaryComponentTick.bCanEverTick = false;
	SaludMaxima = 3.0f;
	SaludActual = SaludMaxima;
}


void UComponenteSalud::BeginPlay()
{
	Super::BeginPlay();
	EnSaludCambiada.Broadcast(SaludActual);
}


void UComponenteSalud::RecibirDanio(float DanioAplicado)
{
	if (SaludActual <= 0.0f)
	{
		return;
	}

	SaludActual = FMath::Clamp(SaludActual - DanioAplicado, 0.0f, SaludMaxima);
	EnSaludCambiada.Broadcast(SaludActual);

	UE_LOG(LogTemp, Warning, TEXT("%s recibio danio. Salud restante: %f"), *GetOwner()->GetName(), SaludActual);

	if (SaludActual <= 0.0f)
	{
		EnMuerte.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("%s ha muerto!"), *GetOwner()->GetName());
	}
}