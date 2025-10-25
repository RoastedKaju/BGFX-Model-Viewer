#include "camera.h"
#include "transform.h"

Camera::Camera()
	: position_(0.0f, 5.0f, 10.0f),
	up_(0.0f, 1.0f, 0.0f),
	forward_(0.0f, 0.0f, -1.0f),
	right_(1.0f, 0.0f, 0.0f)
{
	bx::mtxIdentity(view_);
	bx::mtxIdentity(proj_);
	projection_type_ = ProjectionType::Perspective;

	SetPerspective(bx::toRad(90.0f), 800.0f / 600.0f, 0.1f, 500.0f);
}

void Camera::SetPerspective(float fov, float aspect, float near, float far)
{
	projection_type_ = ProjectionType::Perspective;
	bx::mtxProj(proj_, fov, aspect, near, far, bgfx::getCaps()->homogeneousDepth);
}

void Camera::SetOrthographic(float left, float right, float bottom, float top, float near, float far)
{
	projection_type_ = ProjectionType::Orthographic;
	bx::mtxOrtho(proj_, left, right, bottom, top, near, far, 0.0f, bgfx::getCaps()->homogeneousDepth);
}

void Camera::SetPosition(const bx::Vec3& pos)
{
	position_ = pos;
}

const float* Camera::GetViewMatrix()
{
	const bx::Vec3 at = bx::add(position_, forward_);
	bx::mtxLookAt(view_, position_, at, up_);
	return view_;
}

const float* Camera::GetProjectionMatrix() const
{
	return proj_;
}