#include "src/lights/lightManager.h"
#include "src/messaging/comms.h"

IEntity** pEntities;
unsigned long currentTime = 0;

void setup()
{
  LightManager* pLights = new LightManager();

  static IEntity* pArr[] = { 
    pLights, 
    new Comms(*pLights) 
  }; 
  pEntities = pArr;
  
  int numEntities = sizeof(*pEntities) / sizeof(IEntity*);
  for (int i = 0; i < numEntities; ++i) {
    pEntities[i]->init();
  }

  currentTime = millis();
}

void loop()
{
  unsigned long elapsedTime = millis() - currentTime;
  currentTime = millis();
  
  int numEntities = sizeof(*pEntities) / sizeof(IEntity*);
  for (int i = 0; i < numEntities; ++i) {

    pEntities[i]->update(elapsedTime);
  }
  
  delay(5);
}
