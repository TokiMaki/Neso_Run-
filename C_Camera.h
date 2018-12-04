#pragma once
#pragma once
#include "Run_Time_Framework.h"

#define Move_Factor 0.5f
#define ROTATE_FACTOR 5.f

struct Vector3D {
	float x;
	float y;
	float z;

	Vector3D operator += (const Vector3D other) {
		x += other.x;
		y += other.y;
		z += other.z;
	}
};

struct Matrix3x3 {
	Vector3D r1, r2, r3;
};

class C_Camera
{
private:
	Vector3D RotateAngle;
	Matrix3x3 m_mtxLocal;

public:
	C_Camera();
	~C_Camera();

	GLvoid CameraZoom(unsigned char t);
	GLvoid CameraMove(unsigned char t);
	GLvoid CameraRotate(unsigned char t);
	GLvoid CameraPos();
	GLvoid CameraLook();
	GLvoid CameraReset();

	Vector3D GetCameraRotate() const { return RotateAngle; }
	Vector3D GetCameraPos() const { return m_mtxLocal.r1; }
	Vector3D GetCameraLook() const { return m_mtxLocal.r2; }
	Vector3D GetCameraUp() const { return m_mtxLocal.r3; }

	GLvoid SetCameraRotate(Vector3D other) { RotateAngle = other; };
	GLvoid SetCameraPos(Vector3D other) { m_mtxLocal.r1 = other; };
	GLvoid SetCameraLook(Vector3D other) { m_mtxLocal.r2 = other; };
	GLvoid SetCameraUp(Vector3D other) { m_mtxLocal.r3 = other; };
};

