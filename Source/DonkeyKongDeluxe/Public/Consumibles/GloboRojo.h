// RUTA: Source/DonkeyKongDeluxe/Public/Consumibles/GloboRojo.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GloboRojo.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DONKEYKONGDELUXE_API AGloboRojo : public AActor
{
	GENERATED_BODY()

public:
	AGloboRojo();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	USphereComponent* ColisionEsfera;
	UPROPERTY()
	UStaticMeshComponent* MeshGlobo;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};