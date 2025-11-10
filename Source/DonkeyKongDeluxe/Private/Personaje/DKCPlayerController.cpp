// RUTA: Source/DonkeyKongDeluxe/Private/Personaje/DKCPlayerController.cpp

#include "Personaje/DKCPlayerController.h"
#include "UObject/ConstructorHelpers.h" // Para FClassFinder
#include "Blueprint/UserWidget.h" // Para CreateWidget
#include "UI/DKCHud.h" // Nuestra clase de widget C++

ADKCPlayerController::ADKCPlayerController()
{
	// (LA SOLUCI?N C++ PURO)
	// Cargamos la referencia a tu asset de Blueprint reparado

	const TCHAR* RutaHUD = TEXT("/Game/100por100Terminados/WBP_JugadorHUD.WBP_JugadorHUD_C");
	static ConstructorHelpers::FClassFinder<UDKCHud> HUDClassFinder(RutaHUD);

	if (HUDClassFinder.Succeeded())
	{
		HUDWidgetClass = HUDClassFinder.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ADKCPlayerController: ?NO SE PUDO ENCONTRAR WBP_JugadorHUD!"));
	}
}

void ADKCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Si el C++ encontr? la clase en el constructor...
	if (HUDWidgetClass)
	{
		// ...creamos el widget y lo a?adimos a la pantalla.
		HUDWidgetInstance = CreateWidget<UDKCHud>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}
}