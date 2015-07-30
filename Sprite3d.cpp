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

#include "Sprite3d.hpp"

namespace sf
{

Sprite3d::Sprite3d(const bool centralizeEdges) :
m_compactTransformMatrix(5, 0.f),
m_numberOfVertices(centralizeEdges ? 10u : 6u),
m_points(m_numberOfVertices),
m_vertices(m_numberOfVertices),
m_pTexture(nullptr),
m_pBackTexture(nullptr),
m_pitch(0.f),
m_yaw(0.f),
m_shallowness(1200.f),
m_center(),
m_origin()
{
}

Sprite3d::Sprite3d(const sf::Texture& texture, const bool centralizeEdges) :
m_compactTransformMatrix(5, 0.f),
m_numberOfVertices(centralizeEdges ? 10u : 6u),
m_points(m_numberOfVertices),
m_vertices(m_numberOfVertices),
m_pTexture(nullptr),
m_pBackTexture(nullptr),
m_pitch(0.f),
m_yaw(0.f),
m_shallowness(1200.f),
m_center(),
m_origin()
{
	setTexture(texture);
}

Sprite3d::Sprite3d(const sf::Texture& texture, const sf::Texture& backTexture, const bool centralizeEdges) :
m_compactTransformMatrix(5, 0.f),
m_numberOfVertices(centralizeEdges ? 10u : 6u),
m_points(m_numberOfVertices),
m_vertices(m_numberOfVertices),
m_pTexture(nullptr),
m_pBackTexture(nullptr),
m_pitch(0.f),
m_yaw(0.f),
m_shallowness(1200.f),
m_center(),
m_origin()
{
	setTexture(texture);
	setBackTexture(backTexture);
}

void Sprite3d::setTexture(const sf::Texture& texture)
{
	m_pTexture = &texture;

	sf::Vector2f size = sf::Vector2f(texture.getSize());
	m_center = size / 2.f;

	if (m_numberOfVertices == 10)
	{
		// 10 vertices
		m_vertices[0].texCoords = m_center;
		m_vertices[1].texCoords = { 0.f, 0.f };
		m_vertices[2].texCoords = { m_center.x, 0.f };
		m_vertices[3].texCoords = { size.x, 0.f };
		m_vertices[4].texCoords = { size.x, m_center.y };
		m_vertices[5].texCoords = size;
		m_vertices[6].texCoords = { m_center.x, size.y };
		m_vertices[7].texCoords = { 0.f, size.y };
		m_vertices[8].texCoords = { 0.f, m_center.y };
		m_vertices[9].texCoords = m_vertices[1].texCoords;
	}
	else if (m_numberOfVertices == 6)
	{
		// 6 vertices
		m_vertices[0].texCoords = m_center;
		m_vertices[1].texCoords = { 0.f, 0.f };
		m_vertices[2].texCoords = { size.x, 0.f };
		m_vertices[3].texCoords = size;
		m_vertices[4].texCoords = { 0.f, size.y };
		m_vertices[5].texCoords = m_vertices[1].texCoords;
	}

	for (unsigned int v = 0; v < m_numberOfVertices; ++v)
	{
		m_points[v] = { m_vertices[v].texCoords.x, m_vertices[v].texCoords.y, 0.f };
	}
}

void Sprite3d::setBackTexture(const sf::Texture& texture)
{
	m_pBackTexture = &texture;
}

void Sprite3d::setColor(const sf::Color& color)
{
	for (auto& vertex : m_vertices)
		vertex.color = color;
}

sf::Color Sprite3d::getColor() const
{
	return m_vertices[0].color;
}

void Sprite3d::setPitch(float pitch)
{
	m_pitch = pitch;
	while (m_pitch > 180.f)
		m_pitch -= 360.f;
	while (m_pitch < -180.f)
		m_pitch += 360.f;
}

void Sprite3d::setYaw(float yaw)
{
	m_yaw = yaw;
	while (m_yaw > 180.f)
		m_yaw -= 360.f;
	while (m_yaw < -180.f)
		m_yaw += 360.f;
}

void Sprite3d::setRoll(float roll)
{
	//this->setRotation(roll);
	Transformable::setRotation(roll); // sf::Transformable::setRotation(roll);
}

void Sprite3d::setRotation(float rotation)
{
	setRoll(rotation);
}

void Sprite3d::setRotation(sf::Vector3f rotation)
{
	setPitch(rotation.x);
	setYaw(rotation.y);
	setRoll(rotation.z);
}

void Sprite3d::setShallowness(float shallowness)
{
	m_shallowness = shallowness;
}

float Sprite3d::getShallowness() const
{
	return m_shallowness;
}

const sf::Texture* Sprite3d::getTexture() const
{
	return m_pTexture;
}

void Sprite3d::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_pTexture != nullptr)
	{
		prepareVertices();

		states.texture = m_pTexture;
		states.transform *= getTransform();

		bool useBack = false;
		if (m_pitch < -90.f || m_pitch > 90.f)
			useBack = true;
		if (m_yaw < -90.f || m_yaw > 90.f)
			useBack = !useBack;

		if (useBack && m_pBackTexture != nullptr)
			states.texture = m_pBackTexture;

		target.draw(&m_vertices[0], m_numberOfVertices, sf::PrimitiveType::TrianglesFan, states);
	}
}

void Sprite3d::prepareVertices() const
{
	m_origin = { this->getOrigin().x, this->getOrigin().y, 0.f };
	const float radiansFromDegreesMultiplier = 0.0174532925f; // pi / 180;
	const float pitchInRadians = m_pitch * radiansFromDegreesMultiplier;
	const float yawInRadians = m_yaw * radiansFromDegreesMultiplier;
	
	const float cosPitch = cos(pitchInRadians);
	const float sinPitch = sin(pitchInRadians);
	const float cosYaw = cos(yawInRadians);
	const float sinYaw = sin(yawInRadians);

	/*******************************************************
	*          Pitch and Yaw combined matrix               *
	*                                                      *
	*  cosYaw,  sinPitch * sinYaw, -cosPitch * sinYaw, 0,  *
	*  0,       cosPitch,           sinPitch,          0,  *
	*  sinYaw, -sinPitch * cosYaw,  cosPitch * cosYaw, 0,  *
	*  0,       0,                  0,                 1   *
	*******************************************************/

	m_compactTransformMatrix = { cosYaw, sinYaw, sinPitch * sinYaw, cosPitch, -sinPitch * cosYaw }; // only the five used elements

	for (unsigned int v = 0; v < m_numberOfVertices; ++v)
	{
		sf::Vector3f point = m_points[v];
		
		point -= m_origin;
		point =
		{
			m_compactTransformMatrix[0] * point.x + m_compactTransformMatrix[2] * point.y,
			                                        m_compactTransformMatrix[3] * point.y,
			m_compactTransformMatrix[1] * point.x + m_compactTransformMatrix[4] * point.y
		}; // apply rotations
		point *= m_shallowness / (m_shallowness + point.z); // apply depth
		point += m_origin;
		
		m_vertices[v].position = sf::Vector2f(point.x, point.y);
	}
}

} // namespace sf
