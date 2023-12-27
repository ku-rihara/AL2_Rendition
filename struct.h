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

struct Easing {
	bool isEasing;
	float easingTime;
	float easingCoolTime;
	float easingPlus;
	bool isEasingEnd;
	bool easingRock;
	bool isBack;
	int easingCount;
};

	struct SE {
		int handle;
		int voiceHandle;
		bool isStart;
	};

	struct GH {
		int Handle;
	};