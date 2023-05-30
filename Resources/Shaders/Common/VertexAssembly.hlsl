// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_VERTEX_ASSEMBLY_GUARD
#define SAPPHIRE_RENDER_SHADER_VERTEX_ASSEMBLY_GUARD

namespace SA
{
	struct VertexAssembly
	{
		float3 position : POSITION;

	#if SA_HAS_NORMAL

		float3 normal : NORMAL;

	#endif

	#if SA_HAS_TANGENT

		float3 tangent : TANGENT;

	#endif

	#if SA_HAS_BITANGENT

		float3 bitangent : BITANGENT;

	#endif

	#if SA_HAS_UV

		float2 uv : TEXCOORD;

	#elif SA_HAS_COLOR

		float4 color : COLOR;

	#endif
	};
}

#endif // SAPPHIRE_RENDER_SHADER_VERTEX_ASSEMBLY_GUARD