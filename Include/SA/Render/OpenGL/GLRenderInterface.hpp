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
			void Create() override final;
			void Destroy() override final;
		};
	}
}

#endif // SA_RENDER_GL_RENDER_INTERFACE_GUARD
