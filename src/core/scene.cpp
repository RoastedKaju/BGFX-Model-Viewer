#include "scene.h"

void Scene::AddRenderable(const std::shared_ptr<Renderable>& renderable)
{
	renderables_.push_back(renderable);
}

void Scene::RemoveRenderable(const std::shared_ptr<Renderable>& renderable)
{
	renderables_.erase(std::remove(renderables_.begin(), renderables_.end(), renderable), renderables_.end());
}

void Scene::Draw(const uint8_t view_id) const
{
	for (const auto& renderable : renderables_)
	{
		renderable->Draw(view_id);
	}
}

void Scene::Update(float delta_time)
{

}