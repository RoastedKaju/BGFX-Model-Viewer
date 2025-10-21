#include "renderable.h"

#include <SDL3/SDL.h>

Renderable::Renderable(const std::shared_ptr<Model> model)
{
	model_ = model;
}

void Renderable::Draw(const uint8_t view_id) const
{
	if (!model_)
	{
		SDL_Log("Model not valid for this renderable\n");
		return;
	}

	model_->Draw(transform_ ,view_id);
}