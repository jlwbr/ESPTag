#ifndef DISCOVERY_H
#define DISCOVERY_H

#include "Arduino.h"

struct Lobby
{
    int ID;
    Player players[128];
};

struct Player
{
    String uid;
    String name;
};

struct DiscoveryLobbys
{
    int ID;
    String GameMode;
};


class Discovery
{
public:
    Discovery();
    DiscoveryLobbys GetLobbys();
    bool ConnectToLobby(int ID);
    Lobby GetCurrentLobby();
    bool KillDiscovery();
};
#endif
