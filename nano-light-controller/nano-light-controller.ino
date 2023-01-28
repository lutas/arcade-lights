#include "lightManager.h"

LightManager lights;

bool on;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  // lights = new LightManager();
  lights.init();

  on = true;
}

void loop()
{
  // put your main code here, to run repeatedly:
  on = !on;

  for (int i = 0; i < lights.numLights(); ++i)
  {
    lights.setLight(i, on);
  }
  delay(3000);
}
