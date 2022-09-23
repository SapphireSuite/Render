#pragma once

#ifndef SA_RENDER_VK_RENDER_INTERFACE_GUARD
#define SA_RENDER_VK_RENDER_INTERFACE_GUARD

#include <SA/Render/Base/ARenderInterface.hpp>

#include "VkInstance.hpp"

namespace SA
{
	namespace VK
	{
		class RenderInterface : public ARenderInterface
		{
			Instance mInstance;

		public:
			void Create() override final;
			void Destroy() override final;

			void Clear() override final;
		};
	}
}

#endif // SA_RENDER_VK_RENDER_INTERFACE_GUARD
