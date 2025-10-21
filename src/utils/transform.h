#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <bx/math.h>

class Transform
{
public:
	Transform();

	void SetPosition(float x, float y, float z);
	void SetRotation(float yaw, float pitch, float roll);
	void SetScale(float x, float y, float z);

	inline const float* GetMatrix() const { return matrix_; }
	inline bx::Vec3 GetPosition() const { return position_; }
	inline bx::Vec3 GetRotation() const { return rotation_; }
	inline bx::Vec3 GetScale() const { return scale_; }

private:
	void UpdateMatrix();

	bx::Vec3 position_;
	bx::Vec3 rotation_;
	bx::Vec3 scale_;
	float matrix_[16];
};

#endif // !TRANSFORM_H_
