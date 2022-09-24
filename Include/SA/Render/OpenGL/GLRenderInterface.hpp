#pragma once

#ifndef SA_RENDER_GL_RENDER_INTERFACE_GUARD
#define SA_RENDER_GL_RENDER_INTERFACE_GUARD

#include <SA/Render/Base/ARenderInterface.hpp>

namespace SA
{
	namespace GL
	{
		class RenderInterface : public ARenderInterface
		{
		public:
			void Create(AWindowInterface* _win_intf = nullptr) override final;
			void Destroy() override final;

			void Clear() override final;
		};
	}
}

#endif // SA_RENDER_GL_RENDER_INTERFACE_GUARD
