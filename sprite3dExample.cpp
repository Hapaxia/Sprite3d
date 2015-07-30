#include <SFML/Graphics.hpp>
#include <iostream>

#include "Sprite3d.hpp"

int main()
{
	// set up window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite3d", sf::Style::Default);
	window.setVerticalSyncEnabled(true);

	// load resources (textures and font)
	sf::Texture texture, backTexture;
	if (!texture.loadFromFile("G:/Resource Pool/images/misc/uv map 1.jpg") ||
		!backTexture.loadFromFile("G:/Resource Pool/images/misc/uv map 1 (inv).jpg"))
	{
		std::cerr << "Error loading textures." << std::endl;
		return EXIT_FAILURE; // textures are required for this example. it's pointless carrying on without them
	}
	sf::Font font;
	if (!font.loadFromFile("G:/Resource Pool/fonts/arial.ttf"))
		std::cerr << "Error loading font." << std::endl; // no need to exit if font fails; it will just not show any text

	// text headers
	sf::Text sprite3dText("Sprite3d", font, 48);
	sf::Text spriteText("Sprite", font, 48);
	sprite3dText.setOrigin(sprite3dText.getLocalBounds().left + sprite3dText.getLocalBounds().width / 2.f, 0.f);
	spriteText.setOrigin(spriteText.getLocalBounds().left + spriteText.getLocalBounds().width / 2.f, 0.f);
	sprite3dText.setPosition(sf::Vector2f(window.getSize().x * 0.25f, 0.f));
	spriteText.setPosition(sf::Vector2f(window.getSize().x * 0.75f, 0.f));

	// text shallowness value
	sf::Text shallownessText("Shallowness: ", font, 24);
	sprite3dText.setOrigin(sprite3dText.getLocalBounds().left + sprite3dText.getLocalBounds().width / 2.f, 0.f);
	shallownessText.setOrigin(shallownessText.getLocalBounds().left, shallownessText.getLocalBounds().top + shallownessText.getLocalBounds().height);
	shallownessText.setPosition(sf::Vector2f(0.f, window.getSize().y * 1.f));

	// sprite3d
	sf::Sprite3d sprite3d(texture, backTexture);
	sprite3d.setOrigin(sf::Vector2f(sprite3d.getTexture()->getSize()) / 2.f);
	sprite3d.setPosition(sf::Vector2f(window.getSize().x * 0.25f, window.getSize().y / 2.f));

	// sprite
	sf::Sprite sprite(texture);
	sprite.setOrigin(sf::Vector2f(sprite3d.getTexture()->getSize()) / 2.f);
	sprite.setPosition(sf::Vector2f(window.getSize().x * 0.75f, window.getSize().y / 2.f));

	// clock and pause
	sf::Clock clock;
	bool isPaused{ false };
	float time{ 0.f };

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				// pause/unpause
				if (event.key.code == sf::Keyboard::Space)
				{
					isPaused = !isPaused;
					clock.restart();
				}

				// control shallowness
				else if (event.key.code == sf::Keyboard::Equal)
					sprite3d.setShallowness(sprite3d.getShallowness() + 100.f);
				else if (event.key.code == sf::Keyboard::Dash)
					sprite3d.setShallowness(sprite3d.getShallowness() - 100.f);
				else if (event.key.code == sf::Keyboard::Return)
					std::cout << "shallowness is currently: " << sprite3d.getShallowness() << std::endl;
			}
		}

		// update time
		if (!isPaused)
			time += clock.restart().asSeconds();

		// update sprites
		sprite3d.setRotation({ time * 97.f, time * 42.f, time * 51.f });
		//sprite.setScale({ cos(time * 97.f * 3.141592653f / 180.f), cos(time * 42.f * 3.141592653f / 180.f) });
		sprite.setScale({ cos(time * 42 * 3.141592653f / 180.f), cos(time * 97 * 3.141592653f / 180.f) });
		sprite.setRotation(time * 51.f);
		// other sprite3d rotations for testing
		//sprite3d.setRotation(time * 60.f);
		/*
		sprite3d.setPitch(time * 60.f);
		sprite3d.setYaw(time * 40.f);
		*/
		//sprite3d.setYaw(time * 180.f);

		// update shallowness text
		shallownessText.setString("Shallowness: " + std::to_string(sprite3d.getShallowness()));

		// update display
		window.clear();
		window.draw(sprite);
		window.draw(sprite3d);
		window.draw(spriteText);
		window.draw(sprite3dText);
		window.draw(shallownessText);
		window.display();
	}

	return EXIT_SUCCESS;
}
