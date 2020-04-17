#include "Config.h"

#include "esptag-mesh.h"

/*

Define functions for the mesh

*/

painlessMesh mesh;

extern "C"
{
  // Setup Callbacks
  static void receivedCallback(uint32_t from, String &msg)
  {
    Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  }

  static void newConnectionCallback(uint32_t nodeId)
  {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
  }

  static void changedConnectionCallback()
  {
    Serial.printf("Changed connections\n");
  }

  static void nodeTimeAdjustedCallback(int32_t offset)
  {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
  }

  // Setup callbacks using C helper function
  static void setupCallbacks()
  {
    mesh.onReceive(&receivedCallback);
    mesh.onNewConnection(&newConnectionCallback);
    mesh.onChangedConnections(&changedConnectionCallback);
    mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  }
}

ESPtagMesh::ESPtagMesh()
{
  // Setup debugging
  mesh.setDebugMsgTypes(ERROR | STARTUP);
}

void ESPtagMesh::connect(String ssid, String password, bool host, uint8_t channel)
{
  if(PConfig.MeshState == "CONNECTED") {
    mesh.stop();
  };

  PConfig.MeshState == "CONNECTING";
  //Connect to Mesh
  if (host)
  {
    mesh.init(ssid, password, 5555U, WIFI_AP_STA, channel);
    mesh.setRoot(true);
    mesh.setContainsRoot(true);
  }
  else
  {
    mesh.init(ssid, password, 5555U, WIFI_AP_STA, channel);
    mesh.setContainsRoot(true);
  }

  // Setup callbacks
  setupCallbacks();
  PConfig.MeshState == "CONNECTED";
}

void ESPtagMesh::update()
{
  if(PConfig.MeshState == "CONNECTED") {
    mesh.update();
  }
}
