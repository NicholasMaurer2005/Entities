#pragma once

#include <glm/glm.hpp>
#include <span>

#include "SpritePipeline.h"



class Renderer
{
public:

	//	Public Definitions

	using SpriteDrawData = SpritePipeline::DrawData;



private:

	//	Private Methods

	SpritePipeline m_spritePipeline;



public:

	//	Public Methods
	
	//renderer
	void draw() const noexcept;

	void submit(std::span<const SpriteDrawData> sprites) noexcept;



	//setters
	void resize(float width, float height) const noexcept;
};

