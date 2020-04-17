#include "LuaWrapper.h"
#include "Config.h"
/*

Define functions available to lua config system

*/

extern "C"
{
  static int lua_wrapper_init(lua_State *lua)
  {
    // Set max allowed variables and check type
    lua_settop(lua, 1);
    luaL_checktype(lua, 1, LUA_TTABLE);

    // Get gameinfo
    lua_getfield(lua, 1, "GameType");         // -5
    lua_getfield(lua, 1, "FriendlyName");     // -4
    lua_getfield(lua, 1, "IsTeams");          // -3
    lua_getfield(lua, 1, "TeamSelectable");   // -2
    lua_getfield(lua, 1, "WeaponSelectable"); // -1

    // Set Gameconfig
    GConfig.GameType = String(luaL_checkstring(lua, -5));
    GConfig.FriendlyName = String(luaL_checkstring(lua, -4));
    GConfig.IsTeams = lua_toboolean(lua, -3);
    GConfig.TeamSelectable = lua_toboolean(lua, -2);
    GConfig.WeaponSelectable = lua_toboolean(lua, -1);

    lua_pop(lua, 5);

    return 0;
  }

  static int lua_wrapper_teams(lua_State *lua)
  {
    int n = lua_gettop(lua); /* number of arguments */
    int i;
    if (sizeof(GConfig.Teams) <= sizeof(GConfig.Teams) + n)
    {
      for (i = 1; i <= n; i++)
      {
        luaL_checktype(lua, i, LUA_TTABLE);
        lua_getfield(lua, 1, "Teamname"); // -4
        lua_getfield(lua, 1, "r");        // -3
        lua_getfield(lua, 1, "g");        // -2
        lua_getfield(lua, 1, "b");        // -1

        // Add team
        GConfig.Teams[n - i].TeamName = String(luaL_checkstring(lua, -4));
        GConfig.Teams[n - i].r = luaL_checknumber(lua, -3);
        GConfig.Teams[n - i].g = luaL_checknumber(lua, -2);
        GConfig.Teams[n - i].b = luaL_checknumber(lua, -1);

        lua_pop(lua, -4);
      }
    }
    else
    {
      return luaL_error(lua, "No space for Team");
    }

    return 0;
  }

  static int lua_wrapper_weapons(lua_State *lua)
  {
    int n = lua_gettop(lua); /* number of arguments */
    int i;
    if (sizeof(GConfig.Weapons) <= sizeof(GConfig.Weapons) + n)
    {
      for (i = 1; i <= n; i++)
      {
        luaL_checktype(lua, i, LUA_TTABLE);
        lua_getfield(lua, 1, "WeaponName"); // -6
        lua_getfield(lua, 1, "Type");       // -5
        lua_getfield(lua, 1, "FireRate");   // -4
        lua_getfield(lua, 1, "Range");      // -3
        lua_getfield(lua, 1, "Damage");     // -2
        lua_getfield(lua, 1, "MagSize");    // -1

        GConfig.Weapons[n - i].WeaponName = String(luaL_checkstring(lua, -6));
        GConfig.Weapons[n - i].FireRate = luaL_checknumber(lua, -5);
        GConfig.Weapons[n - i].Type = (WeaponType)luaL_checknumber(lua, -3);
        GConfig.Weapons[n - i].Range = luaL_checknumber(lua, -3);
        GConfig.Weapons[n - i].Damage = luaL_checknumber(lua, -2);
        GConfig.Weapons[n - i].MagSize = luaL_checknumber(lua, -1);

        lua_pop(lua, -6);
      }
    }
    else
    {
      return luaL_error(lua, "No space for Weapon");
    }

    return 0;
  }

  static int lua_wrapper_print(lua_State *L)
  {
    int n = lua_gettop(L); /* number of arguments */
    int i;
    lua_getglobal(L, "tostring");
    for (i = 1; i <= n; i++)
    {
      const char *s;
      size_t l;
      lua_pushvalue(L, -1); /* function to be called */
      lua_pushvalue(L, i);  /* value to print */
      lua_call(L, 1, 1);
      s = lua_tolstring(L, -1, &l); /* get result */
      if (s == NULL)
        return luaL_error(L, "'tostring' must return a string to 'print'");
      if (i > 1)
        Serial.write("\t");
      Serial.write(s);
      lua_pop(L, 1); /* pop result */
    }
    Serial.println();
    return 0;
  }
}

LuaWrapper::LuaWrapper()
{
  _state = luaL_newstate();

  luaopen_base(_state);
  luaopen_table(_state);
  luaopen_string(_state);
  luaopen_math(_state);

  lua_register(_state, "print", lua_wrapper_print);
  lua_register(_state, "init", lua_wrapper_init);
  lua_register(_state, "teams", lua_wrapper_teams);
  lua_register(_state, "weapons", lua_wrapper_weapons);
}

void LuaWrapper::Lua_register(const String name, const lua_CFunction function)
{
  lua_register(_state, name.c_str(), function);
}

int LuaWrapper::Lua_get_event(int argno)
{
  int event;
  lua_pushvalue(_state, argno);
  lua_gettable(_state, lua_upvalueindex(1));
  event = lua_tonumber(_state, -1);
  lua_pop(_state, 1);
  if (lua_isnil(_state, event))
  {
    luaL_error(_state, "This event is not defined");
  }
  return event;
}
