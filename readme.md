#Sprite3d
*by Hapax (August 2015)*
(http://github.com/Hapaxia)

For use with [SFML](http://sfml-dev.org) (v2).

Originally planned to be a part of a drawables module in the [Hx](http://github.com/Hapaxia/Hx) library, this follow-up to [SpinningCard](https://github.com/Hapaxia/SpinningCard), which has been completely rewritten from scratch, has been re-routed to a life of independence!

This is a drawable class for use with SFML. It works in a similar way to a SFML standard Sprite (it has many of the same methods plus it's derived from both sf::Transformable and sf::Drawable). This class, however, has the ability to rotate around all three axis (the standard Sprite only rotates around the z axis).

Since it can rotate and show its back face, the class allows you to supply a secondary texture which it displays instead when the back is visible.

Click this image to see a video that shows an early test example:
[![Example Video](http://img.youtube.com/vi/EAPDIlVEMKA/0.jpg)](http://www.youtube.com/watch?v=EAPDIlVEMKA)

Note that the texture is still subject to the same mapping problems evident in [SpinningCard](https://github.com/Hapaxia/SpinningCard) where it shows that distorting a quad doesn't interpolate the texture correctly.
As in [SpinningCard](https://github.com/Hapaxia/SpinningCard), this object can, instead of being created using a quad (or two triangles), be created using more triangles to reduce the size - and therefore the distortions in the textures - of the triangles. Sprite3d creates a triangle strip that alternates across each row of quads. The number of triangles is determined by the Mesh Density and the Subdivision level (see below).

<<<<<<< HEAD
The texture distortions are more visible depending on the apparent depth of the 3D effect. This amount can be changed by setting its **depth**, which is a _float_. The higher the value, the greater the apparent depth but with more visible texture distortion; the lower the value, the flatter the apparent depth but with less visible texture distortion. The default depth value is 10.
=======
The texture distortions are more visible depending on the apparent depth of the 3D effect. This amount can be changed by setting its **depth**, which is a _float_. The higher the value, the greater the depth but with more visible texture distortion; the lower the value, the lessser the depth but with less visible texture distortion. The default depth value is 8 (this is approximately equal to the depth shown in the example video)
>>>>>>> origin/master

To combat the texture distortion evident when a non-affine transformation (three dimensional rotation is a non-affine transformation as the edges stop being parallel) is applied to a quad, there are three features in Sprite3d that alter the mesh (size and number of triangles).

1. *Mesh Density*
This is how many points are used per dimension, not including the edges.
For example, if the mesh is created from 5x5 points, that's 5 points per dimension - 3 points per dimension, not including the edges.
So, a mesh density of 3 would give you a mesh created from 5x5 points (a single quad is 2x2 points; 5x5 points creates 4x4 quads)

2. *Subdivision level*
This is very similar to Mesh Density. It changes how many points are used for the mesh.
Each subdivision divides each quad in the mesh into four quads.
e.g.:
1 quad that is subdivided once becomes 4 quads,
1 quad that is subdivided twice becomes 16 quads,
etc.

<<<<<<< HEAD
3. *Dynamic Subdivision*
When enabled, Dynamic Subdivision changes the subdivision level automatically based on the most extreme angle. That is, the greatest rotation angle of pitch and yaw (around the x and y axes respectively). The range of subdivision can be specified; the default range is 1 to 4.
Example:
Using the default range, if pitch and yaw are both 0 (object is _flat_), the subdivision level would be 1, whereas if pitch _or_ yaw is close to 90°, the subdivision level would be 3. Subdivision level 2 would be used if the most extreme angle was not almost 90° but was not almost flat.
The range is interpolated linearly so (in the case of the default range) from 0° _up to_ 30° the subdivision level would be 1, from 30° _up to_ 60° degrees it would be 2, from 60° _up to_ 90° it would be 3, and _at_ 90° it would be 4.

Note: if you used Sprite3d in its previous form, the interface may be slightly different. The main interface should be compatible and most of the changes to the interface are simply additional methods.

=======
>>>>>>> origin/master
There is a [thread dedicated to this class](http://en.sfml-dev.org/forums/index.php?topic=18698) on the SFML wiki forum.

[Hapax's SFML Forum profile](http://en.sfml-dev.org/forums/index.php?action=profile;u=13086)
