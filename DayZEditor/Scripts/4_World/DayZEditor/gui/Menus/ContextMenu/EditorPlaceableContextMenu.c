class EditorPlaceableContextMenu: EditorContextMenu
{
	void EditorPlaceableContextMenu(float x, float y, EditorPlaceableItem context)
	{
		EditorLog.Trace("EditorPlacedContextMenu");
		
		/*if (context.GetTemplateController().Favorite) {
			m_Editor.CommandManager[EditorRemoveFromFavoritesCommand].SetData(new Param1<EditorPlaceableItem>(context));
			AddMenuButton(m_Editor.CommandManager[EditorRemoveFromFavoritesCommand]);
		} else {
			m_Editor.CommandManager[EditorAddToFavoritesCommand].SetData(new Param1<EditorPlaceableItem>(context));
			AddMenuButton(m_Editor.CommandManager[EditorAddToFavoritesCommand]);
		}*/
		
		AddMenuButton(m_Editor.CommandManager[EditorLootEditorCommand]);
		
		m_Editor.CommandManager[EditorCopyPlaceableToClipboard].SetData(new Param1<EditorPlaceableItem>(context));
		AddMenuButton(m_Editor.CommandManager[EditorCopyPlaceableToClipboard]);
		
		AddMenuDivider();
		
		// Virtual Folder options - show Add or Remove based on current state
		string existingFolder = EditorVirtualFolderManager.GetInstance().GetItemFolder(context);
		
		if (existingFolder != string.Empty)
		{
			// Remove
			EditorCommand removeCmd = m_Editor.CommandManager.Get(EditorRemoveFromVirtualFolderCommand);
			if (!removeCmd) {
				removeCmd = m_Editor.CommandManager.RegisterCommand(EditorRemoveFromVirtualFolderCommand);
			}
			removeCmd.SetData(new Param1<EditorPlaceableItem>(context));
			AddMenuButton(removeCmd);
		}
		else
		{
			// Add
			EditorCommand addCmd = m_Editor.CommandManager.Get(EditorAddToVirtualFolderCommand);
			if (!addCmd) {
				addCmd = m_Editor.CommandManager.RegisterCommand(EditorAddToVirtualFolderCommand);
			}
			addCmd.SetData(new Param1<EditorPlaceableItem>(context));
			AddMenuButton(addCmd);
		}
	}
}