#Foundation

##Game Engine and Tools

An *(over)*ambitious project to create an experimental, cross-plaftorm game engine. 

___

###Features

* Black boxed Game Components (Graphics, Physics, Window etc).
* Component based entity system inspired by [Unity](http://unity3d.com/).
 * EntitySystemGenerator can generate *Components* and *Nodes* from *.xml* files.
 * Allows *Entities* to be defined easily within *.xml* world/level files.
* [Bullet Physics library](http://bulletphysics.org/) used to simulate 3D worlds
 * Currently only supports basic 3D shapes (no mesh collision yet).
* Deferred rendering pipeline, with physically based lighting.
 * Currently only supports DirectX 11.
* DirectInput support for controllers.
* Very basic 'mock' scripting support.
 * An *Entity's* definition can include script names, but these are currently C++ classes, not compiled at runtime.
 * Scripts only have access to their owning *Entity's* data.
* Uses [Assimp](https://github.com/assimp/assimp) to load 3D model files.
* [Oculus Rift](http://www.oculus.com/) support (DK2).

___

###Future features

* OpenGL support.
 * Including Oculus Rift support for OpenGL.
* Sound!
* Improved graphics.
 * HDR, SSAO, FXAA, variance shadow maps, bloom etc.
* Mac and Linux support.
 * Again, including support for Oculus Rift.
* Improved Scripting.
 * More flexible interface.
 * Replace 'mock' C++ scripts with Lua (or potentially another scripting language).
* World Editor.
* Log server (probably as a new project).
 * There was support for this already but it has been removed (need to write a proper client).
 * Write messages, warnings, errors and stats to a server.
 * Web app to query logs- get common errors for different configurations etc.
 * Server in Node js using MongoDB- already have basic implementation.
 
 ___
