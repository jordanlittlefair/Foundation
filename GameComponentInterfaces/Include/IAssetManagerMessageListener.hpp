#pragma once

#ifndef _GAMECOMPONENTINTERFACES_IASSETMANAGERMESSAGELISTENER_HPP_
#define _GAMECOMPONENTINTERFACES_IASSETMANAGERMESSAGELISTENER_HPP_

namespace Fnd
{
namespace GameComponentInterfaces
{
class IGraphics;

class IAssetManagerMessageListener
{
	public:

		virtual Fnd::GameComponentInterfaces::IGraphics* GetGraphics() = 0;
};

}
}

#endif