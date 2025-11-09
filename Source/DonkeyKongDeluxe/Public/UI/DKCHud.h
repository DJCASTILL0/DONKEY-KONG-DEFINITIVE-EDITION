// RUTA: Source/DonkeyKongDeluxe/Public/UI/DKCHud.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DKCHud.generated.h"

// Declaraciones anticipadas
class UComponenteSalud;
class UComponenteInventario;
class UTextBlock;

UCLASS()
class DONKEYKONGDELUXE_API UDKCHud : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	// --- Componentes Vinculados (BindWidget) ---
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextoSalud;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextoBananas;

	// (NUEVO)
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextoVidas;

private:
	// --- Observadores (Punteros) ---
	UPROPERTY()
	UComponenteSalud* ComponenteSaludObservado;
	UPROPERTY()
	UComponenteInventario* ComponenteInventarioObservado;

	// --- Callbacks de Salud ---
	UFUNCTION()
	void AlSaludCambiar(float SaludActual);
	void ActualizarTextoSalud(float SaludActual);

	// --- Callbacks de Bananas ---
	UFUNCTION()
	void AlBananasCambiar(int TotalBananas);
	void ActualizarTextoBananas(int TotalBananas);

	// --- Callbacks de Vidas (NUEVO) ---
	UFUNCTION()
	void AlVidasCambiar(int TotalVidas);
	void ActualizarTextoVidas(int TotalVidas);
};