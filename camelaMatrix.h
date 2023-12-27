#pragma once

#include"struct.h"

class CamelaMatrix {
public:

	Vector2 pos_;
	Vector2 zoomLevel_;
	Matrix3x3 worldMatrix_;
	Matrix3x3 viewMatrix_;
	Matrix3x3 orthoMatrix_;
	Matrix3x3 viewportMatrix_;

public:

	CamelaMatrix();
	void MakeCamelaMatrix();

	//getter
	Matrix3x3 GetWorldMatrix()const { return worldMatrix_; }
	Matrix3x3 GetViewMatrix()const { return viewMatrix_; }
	Matrix3x3 GetOrthoMatrix()const { return orthoMatrix_; }
	Matrix3x3 GetViewportMatrix()const { return viewportMatrix_; }
	Vector2 GetPos()const { return pos_; }
	Vector2 GetZoomLevel()const { return zoomLevel_; }

	//setter
	void SetPosX(float posX) { this->pos_.x=posX; }
	void SetPosY(float posY) { this->pos_.y = posY; }
	void SetZoomLevelX(float Zoom) { this->zoomLevel_.x = Zoom; }
	void SetZoomLevelY(float Zoom) { this->zoomLevel_.y = Zoom; }

};
