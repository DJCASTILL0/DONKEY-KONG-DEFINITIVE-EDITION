// RUTA: Source/DonkeyKongDeluxe/Public/Estrategias/DonkeyKongStrategy.h

#pragma once

#include "CoreMinimal.h"
#include "Estrategias/PlayerStrategy.h"
#include "DonkeyKongStrategy.generated.h"

UCLASS()
class DONKEYKONGDELUXE_API UDonkeyKongStrategy : public UPlayerStrategy
{
	GENERATED_BODY()

public:
	virtual void EjecutarRodar(ADKCPlayerCharacter* PersonajeReferencia) override;
	virtual void AjustarParametrosMovimiento() override;
};