#include "Config.h"

PlayConfig PConfig;
GameConfig GConfig;

// #include <ArduinoJson.h>
// #include <SD.h>
// #include <SPI.h>
// Spend a whole evening on this, disabling for now :(
// Config::Config()
// {
//     StaticJsonDocument<8600> doc;
//     File file = SPIFFS.open(CONFIG_FILE, "r");
//     if (!file)
//     {
//         Serial.println("No Config file Exist");
//     }
//     else
//     {
//         size_t size = file.size();
//         if (size == 0)
//         {
//             Serial.println("Config file empty !");
//         }
//         else
//         {
//             std::unique_ptr<char[]> buf(new char[size]);
//             file.readBytes(buf.get(), size);
//             DeserializationError error = deserializeJson(doc, buf.get());
//             if (error)
//             {
//                 Serial.println("Impossible to read JSON file");
//             }
//             else
//             {
//                 // If a PlayConfig Exists, load it
//                 if (doc.containsKey("PlayConfig"))
//                 {
//                     PConfig.ssid = doc["PlayConfig"]["ssid"].as<String>();
//                     PConfig.password = doc["PlayConfig"]["password"].as<String>();
//                     PConfig.channel = doc["PlayConfig"]["channel"];
//                     PConfig.MeshState = doc["PlayConfig"]["MeshState"].as<String>();
//                     PConfig.GameState = doc["PlayConfig"]["GameState"].as<String>();
//                 }

//                 // If a GameConfig Exists, load it
//                 if (doc.containsKey("GameConfig"))
//                 {
//                     GConfig.GameType = doc["GameConfig"]["GameType"].as<String>();
//                     GConfig.FriendlyName = doc["GameConfig"]["FriendlyName"].as<String>();
//                     GConfig.IsTeams = doc["GameConfig"]["IsTeams"];
//                     JsonArray TeamArray = doc["GameConfig"]["Teams"].as<JsonArray>();
//                     // A little hacky but its actually pretty fast so
//                     int i = 0;
//                     for (JsonVariant v : TeamArray)
//                     {
//                         GConfig.Teams[i].TeamName = v["TeamName"].as<String>();
//                         GConfig.Teams[i].r = v["r"];
//                         GConfig.Teams[i].g = v["g"];
//                         GConfig.Teams[i].b = v["b"];
//                         i++;
//                     }
//                     GConfig.TeamSelectable = doc["GameConfig"]["TeamSelectable"].as<String>();
//                     JsonArray WeaponArray = doc["GameConfig"]["Weapons"].as<JsonArray>();
//                     // Again: a little hacky
//                     int k = 0;
//                     for (JsonVariant v : WeaponArray)
//                     {
//                         GConfig.Weapons[i].WeaponName = v["WeaponName"].as<String>();
//                         GConfig.Weapons[i].Type = v["Type"];
//                         GConfig.Weapons[i].FireRate = v["FireRate"];
//                         GConfig.Weapons[i].Range = v["Range"];
//                         GConfig.Weapons[i].Damage = v["Damage"];
//                         GConfig.Weapons[i].MagSize = v["MagSize"];
//                         k++;
//                     }
//                     GConfig.WeaponSelectable = doc["GameConfig"]["WeaponSelectable"].as<String>();
//                 }
//             }
//         }
//         // Close the file
//         file.close();
//     }
// }

// Config::~Config()
// {
//     StaticJsonDocument<8600> doc;
//     JsonObject PlayConfig = doc.createNestedObject("PlayConfig");
//     PlayConfig["ssid"] = PConfig.ssid;
//     PlayConfig["password"] = PConfig.password;
//     PlayConfig["channel"] = PConfig.channel;
//     PlayConfig["MeshState"] = PConfig.MeshState;
//     PlayConfig["GameState"] = PConfig.GameState;

//     JsonObject GameConfig = doc.createNestedObject("GameConfig");
//     GameConfig["GameType"] = GConfig.GameType;
//     GameConfig["FriendlyName"] = GConfig.FriendlyName;
//     GameConfig["IsTeams"] = GConfig.IsTeams;
//     JsonArray TeamArray = GameConfig["Teams"].as<JsonArray>();
//     for (Team v : TeamArray)
//     {
//         JsonObject TeamObject = doc.createNestedObject();
//          TeamObject["TeamName"] = v.TeamName;
//          TeamObject["r"] = v.r;
//          TeamObject["g"] = v.g;
//          TeamObject["b"] = v.b;
//     }
//     GameConfig["TeamSelectable"] = GConfig.TeamSelectable;
//     JsonArray WeaponArray = GameConfig["Weapons"].as<JsonArray>();
//     for (Weapon v : GConfig.Weapons)
//     {
//         JsonObject WeaponObject = doc.createNestedObject();
//         WeaponObject["Type"] = v.Type;
//         WeaponObject["FireRate"] = v.FireRate;
//         WeaponObject["Range"] = v.Range;
//         WeaponObject["Damage"] = v.Damage;
//         WeaponObject["MagSize"] = v.MagSize;
//     }
//     GameConfig["WeaponSelectable"] = GConfig.WeaponSelectable;
// }
