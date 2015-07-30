#Sprite3d
*by Hapax (2015)*
(http://github.com/Hapaxia)

For use with [SFML](http://sfml-dev.org) (v2).

Originally planned to be a part of the drawables module in the [Hx](http://github.com/hapaxia/Hx) library, this follow-up to [SpinningCard](https://github.com/Hapaxia/SpinningCard), which has been completely rewritten from scratch, has been re-routed to a life of independence!

This is a drawable class for use with SFML. It works in a similar way to a SFML standard Sprite (it has many of the same methods plus it's derived from both sf::Transformable and sf::Drawable). This class, however, has the ability to rotate around all three axis (the standard Sprite only rotates around the z axis).

Since it can rotate and show its back face, the class allows you to supply a secondary texture which it displays instead when the back is visible.

Note that the texture is still subject to the same mapping problems evident in [SpinningCard](https://github.com/Hapaxia/SpinningCard) where it shows that distorting a quad doesn't interpolate the texture correctly.
As in [SpinningCard](https://github.com/Hapaxia/SpinningCard), this object is, instead of being created using a quad (or two triangles), created using a triangle fan that uses either four or eight (can be chosen) triangles to display to quad. This helps keep certain areas (centre point and centre of edges or just centre point) of the texture in the correct place but still does not distort the texture perfectly.

The texture distortions are more visible depending on the apparent depth of the 3D effect. This amount can be changed. It's called shallowness: the higher the value, the less depth but with less visible texture distortion, whereas the lower the value, the greater the depth but with more visible texture distortion.

This class is a work-in-progress and as such should not be considered complete or final. Some features of the standard sprite are currently missing such as setting custom texture rectangles and getting bounds.

Planned for the future is dynamic splitting of the sprite into multiple quads (triangle pair) to allow how accurate the texture will look by using more vertices.

Due to this currently being unfinished, some of the interface should be expected to change ([that bool](Sprite3d.hpp#L52) will probably disappear, for example). However, the main interface should stay relatively stable since it's designed to be used in the same way that SFML's standard Sprite is used.

The class will be posted to the [SFML Forum's project forum](http://en.sfml-dev.org/forums/index.php?board=10.0) or the [SFML Forum's wiki forum](http://en.sfml-dev.org/forums/index.php?board=11.0) at a later time.

[Hapax's SFML Forum profile](http://en.sfml-dev.org/forums/index.php?action=profile;u=13086)
