// RUTA: Source/DonkeyKongDeluxe/Public/Enemigos/ZingerPatrulladorVertical.h
#pragma once

#include "CoreMinimal.h"
#include "Enemigos/ZingerBase.h"
#include "ZingerPatrulladorVertical.generated.h"

UCLASS()
class DONKEYKONGDELUXE_API AZingerPatrulladorVertical : public AZingerBase
{
	GENERATED_BODY()

public:
	AZingerPatrulladorVertical();

	// Anulamos (Override) el Tick C++ para nuestra IA vertical
	virtual void Tick(float DeltaTime) override;

protected:
	// Anulamos (Override) BeginPlay para iniciar el timer C++
	virtual void BeginPlay() override;

	// Variables C++ puras
	float TiempoCambioDireccion;
	float VelocidadVertical;
	float DireccionVertical;

	// Timer C++
	FTimerHandle TimerHandle_CambioDireccion;

	// Callback C++ del Timer
	void InvertirDireccionVertical();
};