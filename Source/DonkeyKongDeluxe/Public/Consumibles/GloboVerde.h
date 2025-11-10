// RUTA: Source/DonkeyKongDeluxe/Public/Consumibles/GloboVerde.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GloboVerde.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DONKEYKONGDELUXE_API AGloboVerde : public AActor
{
	GENERATED_BODY()

public:
	AGloboVerde();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	USphereComponent* ColisionEsfera;
	UPROPERTY()
	UStaticMeshComponent* MeshGlobo;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};