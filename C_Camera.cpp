#include "stdafx.h"
#include "C_Camera.h"


C_Camera::C_Camera()
{
	this->CameraReset();
}

GLvoid C_Camera::CameraZoom(unsigned char t)
{
	m_mtxLocal.r1.z += (t * Move_Factor);
}

GLvoid C_Camera::CameraMove(unsigned char t)
{
	char sign = 1;
	if (t & 1) {
		sign *= -1;
	}
	switch (t) {
	case 0:
	case 1:
		m_mtxLocal.r1.x += sign * Move_Factor;
		m_mtxLocal.r2.x += sign * Move_Factor;
		break;
	case 2:
	case 3:
		m_mtxLocal.r1.y += sign * Move_Factor;
		m_mtxLocal.r2.y += sign * Move_Factor;
		break;

	}
}

GLvoid C_Camera::CameraRotate(unsigned char t)
{
	char sign = 1;
	if (t & 1) {
		sign *= -1;
	}
	switch (t) {
	case 0:
	case 1:
		RotateAngle.y += sign * ROTATE_FACTOR;
		break;
	case 2:
	case 3:
		RotateAngle.x += sign * ROTATE_FACTOR;
		break;
	case 4:
	case 5:
		RotateAngle.z += sign * ROTATE_FACTOR;
		break;
	}
}

GLvoid C_Camera::CameraPos()
{
}

GLvoid C_Camera::CameraReset()
{
	RotateAngle = Vector3D{ 0.f, 0.f, 0.f };
	m_mtxLocal.r1 = Vector3D{ 0.f, 0.f, 15.f };
	m_mtxLocal.r2 = Vector3D{ 0.f, 0.f, -1.f };
	m_mtxLocal.r3 = Vector3D{ 0.f, 1.f, 0.f };
}


C_Camera::~C_Camera()
{

}
