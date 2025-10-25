#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <bx/math.h>

class Transform
{
public:
	Transform();

	void SetPosition(const bx::Vec3& position);
	void SetRotation(const bx::Vec3& rotation);
	void SetScale(const bx::Vec3& scale);

	inline const bx::Vec3& GetPosition() const { return position_; }
	inline const bx::Vec3& GetRotation() const { return rotation_; }
	inline const bx::Vec3& GetScale() const { return scale_; }

	const float* GetModelMatrix() const;

private:
	void UpdateModelMatrix();

	bx::Vec3 position_;
	bx::Vec3 rotation_;
	bx::Vec3 scale_;

	float model_matrix_[16];
	bool is_dirty_;
};

#endif // !TRANSFORM_H_
