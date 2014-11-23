#Foundation

##Game Engine and Tools

An *(over)*-ambitious project to create an experimental, cross-plaftorm game engine. 

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
 
###Documentation 

Run 'Doc/GenerateDocumentation' to generate the documentation using [Doxygen](www.doxygen.org).

* Note: Documentation is incomplete.

___

###Build/Run TestApp

A sample application (TestApp) is provided in the repository and can be found in *Foundation/TestApp*. 

* Note: The model's textures are not provided (to keep the repository size down).

####Build

All projects require Visual Studio 2012 to build (untested in later versions).

To build this application:

1. Build the *DirectX11ShaderCompiler* solution (in Release).
2. Build the *Game* solution (in Release).
3. Run *CopyDLLs.bat* in the root directory.
4. Run *Configure_Win32.bat* in *Foundation\Configure*.
5. Run *DirectX11ShaderCompiler.exe* in *Foundation*.

You have now built the Foundation Game Engine and TestApp.

####Run

To use the TestApp, run *Launcher.exe* in *Foundation\TestApp*.

___

###Customisation and Creating Games

Customisation is very limited at the moment and there is no GUI world editor, only *.xml* files.

####Changing the world

To customise the TestApp's world, you can edit the *Foundation\TestApp\Resources\Worlds\sponza_test.xml* file. This defines the *Entities* in the world by their *Components* (data), *Nodes* and *Scripts* (behaviour). There is no documentation around this as it should (and will) be handled by a UI, but the existing *Entities* and definition files in *EntitySystemGenerator\Resources* should be enough to make simple worlds.

Scripting is not really supported yet-  there are only 2 'mock' scripts hard coded into the engine; *CameraAnimationScript* and *OculusCameraAnimationScript* to handle camera movement.

Any new models added to the TestApp should be placed in *Foundation\TestApp\Resources\Assets\Models*. They should also be defined in *sponza_test_assets.xml*, and be given unique names.

####Enabling Oculus Rift support

To enable the Oculus Rift in the TestApp, open *Foundation\TestApp\ApplicationSettings.xml* and find the *Graphics* node, then set the *enable_vr* attribute to true.
* The default free moving camera will probably make you sick with this turned on. To enable a more stable camera, open *sponza_test.xml* and find the 'Camera' Entity's *Scripts* node, and replace 'CameraAnimationScript' with 'OculusCameraAnimationScript'. This camera is always upright and works better with the Oculus Rift's head tracking.
