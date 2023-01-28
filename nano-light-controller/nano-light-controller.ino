#include "lightManager.h"
#include "comms.h"

IEntity** pEntities;

bool on;

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

  on = true;
}

void loop()
{
  // put your main code here, to run repeatedly:
  on = !on;  
  
  int numEntities = sizeof(*pEntities) / sizeof(IEntity*);
  for (int i = 0; i < numEntities; ++i) {

    pEntities[i]->update(0);
  }
  
  delay(3000);
}
