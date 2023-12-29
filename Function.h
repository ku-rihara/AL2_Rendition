#pragma once

#include"struct.h"

Vector2 LeftTopMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2 LeftBottomMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2 RightTopMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2 RightBottomMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2i fitMapSize(Vector2 worldPos, Vector2 oldWorldPos, float mapSize);

Vector2 normalize(Vector2 pos);

Vector2 normalize(Vector2 objPos1, Vector2 objPos2);

float Distance(Vector2 posA, Vector2 posB);

float MAX(float a, float b);

int MAX(int a, int b);

void newDrawQuad(Vertex VerTex, float startx, float starty, float DrawWidth, float DrawHeigth, int Handle, int Color);

float RightSide(float PosX, float SizeX);

float LeftSide(float PosX, float SizeX);

float UpSide(float PosY, float SizeY);

float LowerSide(float PosY, float SizeY);

bool isBoxColligion(Vector2 obj1_LeftTop, Vector2  obj1_RightBottom, Vector2 obj2_LeftTop, Vector2 obj2_RightBottom);
