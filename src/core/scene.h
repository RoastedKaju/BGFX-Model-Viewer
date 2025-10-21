#ifndef SCENE_H_
#define SCENE_H_

#include "utils/renderable.h"

#include <memory>
#include <vector>

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	void AddRenderable(const std::shared_ptr<Renderable>& renderable);
	void RemoveRenderable(const std::shared_ptr<Renderable>& renderable);

	void Draw(const uint8_t view_id = 0) const;

	void Update(float delta_time);

	inline const std::vector<std::shared_ptr<Renderable>> GetRenderables() const { return renderables_; }

private:
	std::vector<std::shared_ptr<Renderable>> renderables_;
};


#endif // !SCENE_H_
