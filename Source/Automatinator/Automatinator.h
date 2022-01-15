// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"

class AUTOMATINATOR_API FAutomatinatorModule : public IModuleInterface {

public:
	void StartupModule();
	void ShutdownModule();
};