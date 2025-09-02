class EditorRemoveRootFolderFromVirtualDialog: EditorDialogBase
{
    protected EditorPlaceableItem m_PlaceableItem;
    protected string m_VirtualFolderName;
    protected string m_RootFolderPath;
    
    void EditorRemoveRootFolderFromVirtualDialog(string title, EditorPlaceableItem placeableItem, string virtualFolderName, string rootFolderPath)
    {
        m_PlaceableItem = placeableItem;
        m_VirtualFolderName = virtualFolderName;
        m_RootFolderPath = rootFolderPath;
        
        BuildContent();
        AddButton(DialogResult.Yes);
        AddButton(DialogResult.No);
    }
    
    override string GetLayoutFile()
    {
        return "DayZEditor/gui/Layouts/dialogs/DialogBase.layout";
    }
    
    protected void BuildContent()
    {
        GroupPrefab group = new GroupPrefab("Remove Root Folder", this, string.Empty);
        
        string message = string.Format("This item (%1) was added via the root folder:\n\n'%2'\n\nRemoving it will remove the ENTIRE root folder and all its objects from the virtual folder '%3'.\n\nThis will take a few moments. Do you want to proceed?", m_PlaceableItem.Name, m_RootFolderPath, m_VirtualFolderName);
        
        group.Insert(new MessageBoxPrefab(message));
        AddContent(group);
    }
    
    override void CloseDialog(DialogResult dialog_result = DialogResult.No)
    {
        if (dialog_result == DialogResult.Yes)
        {
            EditorVirtualFolderManager manager = EditorVirtualFolderManager.GetInstance();
            EditorVirtualFolderData folderData = manager.GetFolder(m_VirtualFolderName);
            
            if (folderData)
            {
                bool removeSuccess = folderData.RemoveRootFolder(m_RootFolderPath);
                if (removeSuccess)
                {
                    manager.GetConfig().Save();
                    GetEditor().GetEditorHud().RefreshVirtualFoldersWithReload();
                }
                
                // Show notification
                EditorHud hud = GetEditor().GetEditorHud();
                if (hud)
                {
                    string message;
                    if (removeSuccess)
                    {
                        message = "Removed root folder '" + m_RootFolderPath + "' from '" + m_VirtualFolderName + "'";
                    }
                    else
                    {
                        message = "Failed to remove root folder '" + m_RootFolderPath + "' from '" + m_VirtualFolderName + "'";
                    }
                    hud.CreateNotification(message);
                }
            }
        }
        
        super.CloseDialog(dialog_result);
    }
}