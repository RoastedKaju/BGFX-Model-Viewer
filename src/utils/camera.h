#ifndef CAMERA_H_
#define CAMERA_H_

#include <bgfx/bgfx.h>
#include <bx/math.h>

class Camera
{
public:
	enum class ProjectionType { Perspective, Orthographic };

	Camera();
	~Camera() = default;

	// Projection
	void SetPerspective(float fov, float aspect, float near, float far);
	void SetOrthographic(float left, float right, float bottom, float top, float near, float far);

	void SetPosition(const bx::Vec3& pos);

	const float* GetViewMatrix();
	const float* GetProjectionMatrix() const;

private:
	bx::Vec3 position_;
	bx::Vec3 up_;
	bx::Vec3 forward_;
	bx::Vec3 right_;

	float view_[16];
	float proj_[16];

	ProjectionType projection_type_;
};

#endif // !CAMERA_H_
