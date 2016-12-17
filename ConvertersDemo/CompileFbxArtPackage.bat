FbxConverter space_frigate.fbx --no-verbose
FbxConverter astroboy.fbx --no-verbose
FbxConverter buggy.fbx --no-verbose
FbxConverter warbear.fbx --no-verbose
FbxConverter SimplePyramid.fbx --no-verbose

VitorToLgeConverter humanoid2.fbx humanoid
VitorToLgeConverter teddy_TGA.fbx teddy

MetaAppender space_frigate.vrt -t Vertices -n space_frigate
MetaAppender space_frigate.tri -t Triangles -n space_frigate
MetaAppender space_frigate.tex -t Texture -n space_frigate
MetaAppender space_frigate.sph -t BoundingSphere -n space_frigate

MetaAppender astroboy.vrt -t Vertices -n astroboy
MetaAppender astroboy.tri -t Triangles -n astroboy
MetaAppender astroboy.tex -t Texture -n astroboy
MetaAppender astroboy.sph -t BoundingSphere -n astroboy

MetaAppender buggy.vrt -t Vertices -n buggy
MetaAppender buggy.tri -t Triangles -n buggy
MetaAppender buggy.tex -t Texture -n buggy
MetaAppender buggy.sph -t BoundingSphere -n buggy

MetaAppender warbear.vrt -t Vertices -n warbear
MetaAppender warbear.tri -t Triangles -n warbear
MetaAppender warbear.tex -t Texture -n warbear
MetaAppender warbear.sph -t BoundingSphere -n warbear

MetaAppender SimplePyramid.vrt -t Vertices -n pyramid
MetaAppender SimplePyramid.tri -t Triangles -n pyramid
MetaAppender SimplePyramid.tex -t Texture -n pyramid
MetaAppender SimplePyramid.sph -t BoundingSphere -n pyramid

MetaAppender teddy.vrt -t Vertices -n teddy_tga
MetaAppender teddy.tri -t Triangles -n teddy_tga
MetaAppender teddy.anim -t Animation -n teddy_tga

MetaAppender humanoid.vrt -t Vertices -n humanoid
MetaAppender humanoid.tri -t Triangles -n humanoid
MetaAppender humanoid.anim -t Animation -n humanoid

DataPackager game_resources.lgepkg -n resources -v 1.0