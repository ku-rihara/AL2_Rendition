#pragma once

#include"struct.h"

Vector2 LeftTopMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2 LeftBottomMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2 RightTopMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2 RightBottomMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2i fitMapSize(Vector2 worldPos, Vector2 oldWorldPos, float mapSize);

Vector2 normalize(Vector2 pos);

float MAX(float a, float b);

void newDrawQuad(Vertex VerTex, float startx, float starty, float DrawWidth, float DrawHeigth, int Handle, int Color);

float RightSide(float PosX, float SizeX);

float LeftSide(float PosX, float SizeX);

float UpSide(float PosY, float SizeY);

float LowerSide(float PosY, float SizeY);