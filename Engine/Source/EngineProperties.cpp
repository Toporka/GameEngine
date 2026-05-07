#include "EngineProperties.h"

EngineProperties::EngineProperties() {}

EngineProperties* EngineProperties::GetEngineProperties()
{
	static EngineProperties engineProperties;
	return &engineProperties;
}