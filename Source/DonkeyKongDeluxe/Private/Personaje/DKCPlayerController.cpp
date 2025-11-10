// RUTA: Source/DonkeyKongDeluxe/Private/Personaje/DKCPlayerController.cpp

#include "Personaje/DKCPlayerController.h"
#include "UObject/ConstructorHelpers.h" // Para FClassFinder
#include "Blueprint/UserWidget.h" // Para CreateWidget
#include "UI/DKCHud.h" // Nuestra clase de widget C++

ADKCPlayerController::ADKCPlayerController()
{


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

	if (HUDWidgetClass)
	{

		HUDWidgetInstance = CreateWidget<UDKCHud>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}
}