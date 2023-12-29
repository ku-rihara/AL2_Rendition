#include<Novice.h>
#include<assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include"Function.h"

Vector2 LeftTopMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size) {

	Vector2 mapnum;

	mapnum.y = ((worldpos.y * zoomScale) - (heigth / 2)) / size;
	mapnum.x = ((worldpos.x * zoomScale) - (width / 2)) / size;

	return mapnum;
}

Vector2 LeftBottomMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size) {

	Vector2 mapnum;

	mapnum.y = ((worldpos.y * zoomScale) + (heigth / 2 - 1)) / size;
	mapnum.x = ((worldpos.x * zoomScale) - (width / 2)) / size;

	return mapnum;
}

Vector2 RightTopMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size) {

	Vector2 mapnum;

	mapnum.y = ((worldpos.y * zoomScale) - (heigth / 2)) / size;
	mapnum.x = ((worldpos.x * zoomScale) + (width / 2 - 1)) / size;

	return mapnum;
}

Vector2 RightBottomMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size) {

	Vector2 mapnum;

	mapnum.y = ((worldpos.y * zoomScale) + (heigth / 2 - 1)) / size;
	mapnum.x = ((worldpos.x * zoomScale) + (width / 2 - 1)) / size;

	return mapnum;
}

Vector2i fitMapSize(Vector2 worldPos, Vector2 oldWorldPos, float mapSize) {
	Vector2i fitMapSizePos;
	Vector2 maxPos;

	maxPos.x = MAX(worldPos.x, oldWorldPos.x);
	maxPos.y = MAX(worldPos.y, oldWorldPos.y);

	fitMapSizePos.intx = int(maxPos.x / (mapSize / 2));
	fitMapSizePos.intx = int(fitMapSizePos.intx * (mapSize / 2));

	fitMapSizePos.inty = int(maxPos.y / (mapSize / 2));
	fitMapSizePos.inty = int(fitMapSizePos.inty * (mapSize / 2));

	return fitMapSizePos;
}

Vector2 normalize(Vector2 pos) {

	Vector2 result;

	float distance = sqrtf(pos.x * pos.x + pos.y * pos.y);

	result.x = pos.x / distance;
	result.y = pos.y / distance;

	return result;
}

Vector2 normalize(Vector2 objPos1, Vector2 objPos2) {

	Vector2 result;
	Vector2 objDistance;

	objDistance.x = objPos1.x - objPos2.x;
	objDistance.y = objPos1.y - objPos2.y;

	float c = sqrtf(objDistance.x * objDistance.x + objDistance.y * objDistance.y);

	result.x = objDistance.x / c;
	result.y = objDistance.y / c;

	return result;
}

float Distance(Vector2 posA, Vector2 posB) {

	float x = posA.x - posB.x;
	float y = posA.y - posB.y;

	return sqrtf(x * x + y *y);
}

float MAX(float a, float b) {

	if (a > b) {
		return	a;
	}

	else {
		return b;
	}
}

int MAX(int a, int b) {

	if (a > b) {
		return	a;
	}

	else {
		return b;
	}
}

void newDrawQuad(Vertex VerTex, float startx, float starty, float DrawWidth, float DrawHeigth, int Handle, int Color) {

	Novice::DrawQuad(int(VerTex.LeftTop.x), int(VerTex.LeftTop.y), int(VerTex.RightTop.x), int(VerTex.RightTop.y), int(VerTex.LeftBottom.x), int(VerTex.LeftBottom.y), int(VerTex.RightBottom.x), int(VerTex.RightBottom.y), int(startx), int(starty), int(DrawWidth), int(DrawHeigth), Handle, Color);
}

float RightSide(float PosX, float SizeX) {
	return PosX + (SizeX / 2 - 1);
}

float LeftSide(float PosX, float SizeX) {
	return PosX - (SizeX / 2);
}

float UpSide(float PosY, float SizeY) {
	return PosY - (SizeY / 2);
}

float LowerSide(float PosY, float SizeY) {
	return PosY + (SizeY / 2 - 1);
}

bool isBoxColligion(Vector2 obj1_LeftTop, Vector2  obj1_RightBottom, Vector2 obj2_LeftTop, Vector2 obj2_RightBottom) {

	if (obj1_LeftTop.x<obj2_RightBottom.x && obj1_RightBottom.x>obj2_LeftTop.x && obj1_LeftTop.y<obj2_RightBottom.y && obj1_RightBottom.y>obj2_LeftTop.y) {
		return true;
	}
	else {
		return false;
	}
}
