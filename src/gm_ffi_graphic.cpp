#include "gm2.h"

namespace gm
{
	void InitGraphic(lua_State* L)
	{
		lua_pushlightuserdata(L, roundedRectangleRGBA);
		lua_setglobal(L,"roundedRectangleRGBA");
		lua_pushlightuserdata(L, roundedBoxRGBA);
		lua_setglobal(L, "roundedBoxRGBA");
		lua_pushlightuserdata(L, circleRGBA);
		lua_setglobal(L, "circleRGBA");
		lua_pushlightuserdata(L, filledCircleRGBA);
		lua_setglobal(L, "filledCircleRGBA");
		lua_pushlightuserdata(L, arcRGBA);
		lua_setglobal(L, "arcRGBA");
		lua_pushlightuserdata(L, ellipseRGBA);
		lua_setglobal(L, "ellipseRGBA");
		lua_pushlightuserdata(L, filledEllipseRGBA);
		lua_setglobal(L, "filledEllipseRGBA");
		lua_pushlightuserdata(L, pieRGBA);
		lua_setglobal(L, "pieRGBA");
		lua_pushlightuserdata(L, filledPieRGBA);
		lua_setglobal(L, "filledPieRGBA");
		lua_pushlightuserdata(L, trigonRGBA);
		lua_setglobal(L, "trigonRGBA");
		lua_pushlightuserdata(L, filledTrigonRGBA);
		lua_setglobal(L, "filledTrigonRGBA");
		lua_pushlightuserdata(L, aalineRGBA);
		lua_setglobal(L, "aalineRGBA");
		lua_pushlightuserdata(L, filledTrigonRGBA);
		lua_setglobal(L, "filledTrigonRGBA");
		lua_pushlightuserdata(L, thickLineRGBA);
		lua_setglobal(L, "thickLineRGBA");
		lua_pushlightuserdata(L, aacircleRGBA);
		lua_setglobal(L, "aacircleRGBA");
		lua_pushlightuserdata(L, aaellipseRGBA);
		lua_setglobal(L, "aaellipseRGBA");
		lua_pushlightuserdata(L, aatrigonRGBA);
		lua_setglobal(L, "aatrigonRGBA");
	}
}