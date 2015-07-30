//////////////////////////////////////////////////////////////////////////////
//
// Sprite3d
//
// Copyright (c) 2015 M. J. Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgement in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M. J. Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef HAPAX_SFML_SPRITE3D_HPP
#define HAPAX_SFML_SPRITE3D_HPP

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sf
{

class Sprite3d : public sf::Drawable, public sf::Transformable
{
public:
	Sprite3d(bool centralizeEdges = true);
	Sprite3d(const sf::Texture& texture, bool centralizeEdges = true);
	Sprite3d(const sf::Texture& texture, const sf::Texture& backTexture, bool centralizeEdges = true);

	// standard sprite
	const sf::Texture* getTexture() const;
	sf::Color getColor() const;
	void setTexture(const sf::Texture& texture);
	void setColor(const sf::Color& color);

	// back face
	void setBackTexture(const sf::Texture& texture);

	// 3D rotation
	void setPitch(float pitch); // rotation around the x axis
	void setYaw(float yaw);     // rotation around the y axis
	void setRoll(float roll);   // rotation around the z axis (this is the usual 2D rotation)
	void setRotation(float rotation); // supplied as the 3d rotation method overrides the sf::Transformable rotation method
	void setRotation(sf::Vector3f rotation); // set pitch, yaw, and roll at once.

	// 3D setup
	// depth controls the amount of the apparent depth of the 3D effect.
	// higher values give a more extreme depth effect but more visible texture distortion
	// higher values give a more subtle depth effect but less visible texture distortion
	void setDepth(float depth);
	float getDepth() const;

private:
	const unsigned int m_numberOfVertices;

	const float m_depthToShallownessRatio;
	
	float m_pitch;
	float m_yaw;
	float m_depth; // even though m_shallowness is the one that actually gets used internally, this is stored as a form of cache to return through getDepth() to avoid the unnecessary division in a getter
	float m_shallowness;

	const sf::Texture* m_pTexture;
	const sf::Texture* m_pBackTexture;
	std::vector<sf::Vector3f> m_points;
	sf::Vector2f m_center;
	
	mutable sf::Vector3f m_origin;
	mutable std::vector<sf::Vertex> m_vertices;
	mutable std::vector<float> m_compactTransformMatrix;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void prepareVertices() const;
};

} // namespace sf
#endif // HAPAX_SFML_SPRITE3D_HPP
