#pragma once

#include"struct.h"

class Camela {
public:

	//Pos,ZoomLevel
	Vector2 pos_;
	Vector2 zoomLevel_;

	//Matrix
	Matrix3x3 worldMatrix_;
	Matrix3x3 viewMatrix_;
	Matrix3x3 orthoMatrix_;
	Matrix3x3 viewportMatrix_;

	Easing zoomOut_;
	Easing zoomIn_;

public:

	Camela();
	void MakeCamelaMatrix();
	void ZoomOut();
	void ZoomIn();

	//getter
	Matrix3x3 GetWorldMatrix()const { return worldMatrix_; }
	Matrix3x3 GetViewMatrix()const { return viewMatrix_; }
	Matrix3x3 GetOrthoMatrix()const { return orthoMatrix_; }
	Matrix3x3 GetViewportMatrix()const { return viewportMatrix_; }
	Vector2 GetPos()const { return pos_; }
	Vector2 GetZoomLevel()const { return zoomLevel_; }
	bool GetIsZoomOut()const { return zoomOut_.isEasing; }

	//setter
	void SetPosX(float posX) { this->pos_.x=posX; }
	void SetPosY(float posY) { this->pos_.y = posY; }
	void SetZoomLevelX(float Zoom) { this->zoomLevel_.x = Zoom; }
	void SetZoomLevelY(float Zoom) { this->zoomLevel_.y = Zoom; }
	void SetIsZoomOut(bool isZoom) { this->zoomOut_.isEasing=isZoom; }
	void SetZoomOutPuls(float zoomPuls) { this->zoomOut_.easingPlus = zoomPuls; }
	void SetIsZoomIn(bool isZoom) { this->zoomIn_.isEasing = isZoom; }
	void SetZoomInPuls(float zoomPuls) { this->zoomIn_.easingPlus = zoomPuls; }

};
