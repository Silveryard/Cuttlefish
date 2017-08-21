/*
 * Copyright 2017 Aaron Barany
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cuttlefish/Config.h>
#include <memory>
#include <vector>

namespace cuttlefish
{

class Image;
class Texture;

class Converter
{
public:
	using FaceImageList = std::vector<Image>;
	using DepthImageList = std::vector<FaceImageList>;
	using MipImageList = std::vector<DepthImageList>;

	using TextureData = std::vector<std::uint8_t>;
	using FaceTextureList = std::vector<TextureData>;
	using DepthTextureList = std::vector<FaceTextureList>;
	using MipTextureList = std::vector<DepthTextureList>;

	static bool convert(const Texture& texture, MipImageList& images, MipTextureList& textureData,
		unsigned int threadCount);

	explicit Converter(const Image& image)
		: m_image(&image)
	{
	}

	virtual ~Converter() = default;

	const Image& getImage() const {return *m_image;}

	std::vector<std::uint8_t>& data() {return m_data;}
	const std::vector<std::uint8_t>& data() const {return m_data;}

	virtual unsigned int jobsX() const = 0;
	virtual unsigned int jobsY() const = 0;
	virtual void process(unsigned int x, unsigned int y) = 0;

private:
	const Image* m_image;
	std::vector<std::uint8_t> m_data;
};

} // namespace cuttlefish
