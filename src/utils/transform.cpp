#include "transform.h"

Transform::Transform() :
	position_(0.0f, 0.0f, 0.0f),
	rotation_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f)
{
	bx::mtxIdentity(matrix_);
}

void Transform::SetPosition(float x, float y, float z)
{
	position_ = { x, y, z };
	UpdateMatrix();
}

void Transform::SetRotation(float yaw, float pitch, float roll)
{
	rotation_ = { pitch, yaw, roll };
	UpdateMatrix();
}

void Transform::SetScale(float x, float y, float z)
{
	scale_ = { x ,y, z };
	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	bx::mtxIdentity(matrix_);

	// Create individual matrices
	float rot[16], scl[16], trans[16], temp[16];

	bx::mtxRotateXYZ(rot, rotation_.x, rotation_.y, rotation_.z);
	bx::mtxScale(scl, scale_.x, scale_.y, scale_.z);
	bx::mtxTranslate(trans, position_.x, position_.y, position_.z);

	// Combine transforms: M = T * R * S
	bx::mtxMul(temp, rot, scl);     // temp = R * S
	bx::mtxMul(matrix_, trans, temp); // M = T * (R * S)
}
