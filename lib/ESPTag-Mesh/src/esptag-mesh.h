#ifndef ESPTAG_H
#define ESPTAG_H

#include "Arduino.h"
#include "painlessMesh.h"

class ESPtagMesh
{
public:
  ESPtagMesh();
  void connect(String ssid, String password, bool host, uint8_t channel);
  void update();

private:
};
#endif