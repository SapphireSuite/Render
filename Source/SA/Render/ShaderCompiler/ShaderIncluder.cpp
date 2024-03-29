// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include "ShaderIncluder.hpp"

#include <algorithm>

#include <SA/Collections/Debug>

namespace SA::RND
{
	ShaderIncluder::ShaderIncluder(CComPtr<IDxcUtils> _utils) :
		mUtils{_utils}
	{
	}

	HRESULT STDMETHODCALLTYPE ShaderIncluder::LoadSource(_In_z_ LPCWSTR _pFilename,
				_COM_Outptr_result_maybenull_ IDxcBlob **_ppIncludeSource)
	{
		std::wstring filename = _pFilename;

		// Already included?
		if(includedFiles.find(filename) != includedFiles.end())
		{
			*_ppIncludeSource = nullptr;
			return S_OK;
		}

		CComPtr<IDxcBlobEncoding> encoding;
		const HRESULT hr = mUtils->LoadFile(_pFilename, nullptr, &encoding);

		if(SUCCEEDED(hr))
		{
			includedFiles.emplace(std::move(filename));
			*_ppIncludeSource = encoding.Detach();
		}
		else
		{
			SA_LOG((L"Failed to open included file {%1}!", filename.c_str()), Error, SA.Render.ShaderCompiler.Includer);
			*_ppIncludeSource = nullptr;
		}

		return hr;
	}

	HRESULT ShaderIncluder::QueryInterface(REFIID riid, void **ppvObject)
	{
		(void)riid;
		(void)ppvObject;

		return S_FALSE;
	}

	ULONG ShaderIncluder::AddRef() { return 0; }
	ULONG ShaderIncluder::Release() { return 0; }
}
