// RUTA: Source/DonkeyKongDeluxe/Public/Consumibles/BananaMD.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BananaMD.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DONKEYKONGDELUXE_API ABananaMD : public AActor
{
	GENERATED_BODY()

public:
	ABananaMD();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	USphereComponent* ColisionEsfera;
	UPROPERTY()
	UStaticMeshComponent* MeshBananaMD; // Usamos el mesh de la banana simple

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};