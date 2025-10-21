#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include <bgfx/bgfx.h>
#include <memory>

#include "graphics/model.h"
#include "utils/transform.h"

class Renderable
{
public:
	Renderable(const std::shared_ptr<Model> model);

	void Draw(const uint8_t view_id = 0) const;

	inline std::shared_ptr<Model> GetModel() const { return model_; }
	inline Transform& GetTransform() { return transform_; }
	inline const Transform& GetTransform() const { return transform_; }

private:
	std::shared_ptr<Model> model_;
	Transform transform_;
};


#endif // !RENDERABLE_H_
