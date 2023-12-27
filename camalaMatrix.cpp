#include<Novice.h>

#include"Matrix3x3.h"
//class
#include"camelaMatrix.h"

CamelaMatrix::CamelaMatrix() {
	pos_={};
	zoomLevel_ = {1,1};
	 worldMatrix_ = {};
	 viewMatrix_ = {};
	 orthoMatrix_ = {};
	 viewportMatrix_ = {};
 }

void CamelaMatrix::MakeCamelaMatrix() {

	worldMatrix_ = MakeAffineMatrix(zoomLevel_, 0, pos_);
	viewMatrix_ = InverseMatrix(worldMatrix_);
	orthoMatrix_ = MakeOrthographicMatrix(0, 0, 1280, 720);
	viewportMatrix_ = MakeViewwportmatrix(0, 0, 1280, 720);
}