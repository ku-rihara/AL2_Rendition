#pragma once

struct Vector2 {
	float x;
	float y;
	
};

struct Vector2i {
	int intx;
	int inty;
};

struct Vertex {
	Vector2 LeftTop;
	Vector2 RightTop;
	Vector2 LeftBottom;
	Vector2 RightBottom;
};

struct Matrix3x3 {

	float m[3][3];
};

struct SE {
	int handle;
	int voiceHandle;
	bool isStart;
};

struct GH {
	int Handle;
};

