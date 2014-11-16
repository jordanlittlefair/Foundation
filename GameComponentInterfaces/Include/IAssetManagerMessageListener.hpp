#pragma once

#ifndef _IASSETMANAGERMESSAGELISTENER_HPP_
#define _IASSETMANAGERMESSAGELISTENER_HPP_

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