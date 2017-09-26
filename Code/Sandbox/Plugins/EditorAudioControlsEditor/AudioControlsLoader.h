// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "AudioAssets.h"

namespace ACE
{
class CAudioAssetsManager;

class CAudioControlsLoader
{
public:

	CAudioControlsLoader(CAudioAssetsManager* pAssetsManager);
	std::set<string> GetLoadedFilenamesList();
	void             LoadAll();
	void             LoadControls();
	void             LoadScopes();
	EErrorCode       GetErrorCodeMask() const { return m_errorCodeMask; }

private:

	using SwitchStates = std::vector<const char*>;

	void           LoadAllLibrariesInFolder(string const& folderPath, string const& level);
	void           LoadControlsLibrary(XmlNodeRef pRoot, string const& filepath, string const& level, string const& filename, uint version);
	CAudioControl* LoadControl(XmlNodeRef pNode, Scope scope, uint version, CAudioAsset* pParentItem);

	void           LoadPreloadConnections(XmlNodeRef pNode, CAudioControl* pControl, uint version);
	void           LoadConnections(XmlNodeRef root, CAudioControl* pControl);

	void           CreateDefaultControls();
	void           CreateDefaultSwitch(CAudioAsset* pLibrary, const char* szExternalName, const char* szInternalName, SwitchStates const& states);

	void           LoadScopesImpl(string const& path);

	void           LoadEditorData(XmlNodeRef pEditorDataNode, CAudioAsset* pRootItem);
	void           LoadAllFolders(XmlNodeRef pRootFoldersNode, CAudioAsset* pParentItem);
	void           LoadFolderData(XmlNodeRef pRootFoldersNode, CAudioAsset* pParentItem);

	CAudioAsset*   AddUniqueFolderPath(CAudioAsset* pParent, QString const& path);

	static string const ms_controlsLevelsFolder;
	static string const ms_levelsFolder;
	// TODO: Move these strings to Utils

	CAudioAssetsManager* m_pAssetsManager;
	std::set<string>     m_loadedFilenames;
	EErrorCode           m_errorCodeMask;
};
} // namespace ACE
