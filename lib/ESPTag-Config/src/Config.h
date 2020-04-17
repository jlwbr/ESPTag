#ifndef CONFIG_H
#define CONFIG_H
#include "Arduino.h"

#define CONFIG_FILE "config.json"

enum WeaponType
{
  MANUAL,
  SEMI,
  AUTO
};

struct Team
{
  String TeamName;
  int r;
  int g;
  int b;
};

struct Weapon
{
  String WeaponName;
  WeaponType Type;
  int FireRate;
  int Range;
  int Damage;
  int MagSize;
};

struct GameConfig
{
  String GameType;
  String FriendlyName;
  bool IsTeams;
  Team Teams[32]; // TeamName, R, G, B
  bool TeamSelectable;
  Weapon Weapons[32]; // WeaponName, FireRate, Range, Damage, MagSize
  bool WeaponSelectable;
};

struct PlayConfig
{
  String ssid;
  String password;
  uint8_t channel;
  String MeshState;
  String GameState;
};

extern PlayConfig PConfig;
extern GameConfig GConfig;

// class Config
// {
// public:
//   void setGConfig(GameConfig _GConfig)
//   {
//     GConfig = _GConfig;
//   }
//   GameConfig getGConfig()
//   {
//     return GConfig;
//   }
//   void setPConfig(PlayConfig _PConfig)
//   {
//     PConfig = _PConfig;
//   }
//   PlayConfig getPConfig()
//   {
//     return PConfig;
//   }
//   Config();
//   ~Config();
// };
#endif