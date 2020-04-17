#include <Arduino.h>
#include <LuaWrapper.h>
#include <esptag-mesh.h>

ESPtagMesh Tagmesh;

void setup()
{
  // Start serial
  Serial.begin(115200);
}

void loop()
{
  // Update mesh network
  Tagmesh.update();
}