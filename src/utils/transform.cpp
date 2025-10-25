#include "transform.h"

Transform::Transform()
	: position_{ 0.0f, 0.0f, 0.0f },
	rotation_{ 0.0f, 0.0f, 0.0f },
	scale_{1.0f, 1.0f, 1.0f},
	is_dirty_{true}
{
	bx::mtxIdentity(model_matrix_);
}

void Transform::SetPosition(const bx::Vec3& position)
{
	position_ = position;
	is_dirty_ = true;
	UpdateModelMatrix();
}

void Transform::SetRotation(const bx::Vec3& rotation)
{
	rotation_ = rotation;
	is_dirty_ = true;
	UpdateModelMatrix();
}

void Transform::SetScale(const bx::Vec3& scale)
{
	scale_ = scale;
	is_dirty_ = true;
	UpdateModelMatrix();
}

const float* Transform::GetModelMatrix() const
{
	//if (is_dirty_)
	//{
	//	UpdateModelMatrix();
	//	is_dirty_ = false;
	//}

	return model_matrix_;
}

void Transform::UpdateModelMatrix()
{
	float scale_mtx[16];
	float rotx_mtx[16];
	float roty_mtx[16];
	float rotz_mtx[16];
	float rot_mtx[16];
	float temp_mtx[16];

	// Create scale matrix
	bx::mtxScale(scale_mtx, scale_.x, scale_.y, scale_.z);

	// Create rotation matrices (order: Z * Y * X)
	bx::mtxRotateX(rotx_mtx, rotation_.x);
	bx::mtxRotateY(roty_mtx, rotation_.y);
	bx::mtxRotateZ(rotz_mtx, rotation_.z);

	// Combine rotations
	bx::mtxMul(temp_mtx, rotx_mtx, roty_mtx);
	bx::mtxMul(rot_mtx, temp_mtx, rotz_mtx);

	// Combine scale and rotation
	bx::mtxMul(temp_mtx, scale_mtx, rot_mtx);

	// Apply translation
	bx::mtxTranslate(model_matrix_, position_.x, position_.y, position_.z);

	// Final matrix = Translation * Rotation * Scale
	float final_mtx[16];
	bx::mtxMul(final_mtx, temp_mtx, model_matrix_);
	bx::memCopy(model_matrix_, final_mtx, sizeof(model_matrix_));
}
