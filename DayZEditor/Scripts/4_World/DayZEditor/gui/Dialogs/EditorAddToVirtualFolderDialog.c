class EditorAddToVirtualFolderDialog: EditorDialogBase
{
    string NewFolderName;
    string SelectedFolder;
    
    protected EditorPlaceableItem m_PlaceableItem;
    
    void EditorAddToVirtualFolderDialog(string title, EditorPlaceableItem placeableItem)
    {
        m_PlaceableItem = placeableItem;
        
        BuildContent();
        AddButton(DialogResult.OK);
        AddButton(DialogResult.Cancel);
    }
    
    override string GetLayoutFile()
    {
        return "DayZEditor/gui/Layouts/dialogs/DialogBase.layout";
    }
    
    protected void BuildContent()
    {
        GroupPrefab group = new GroupPrefab("Virtual Folders", this, string.Empty);
        
        group.Insert(new EditBoxPrefab("Create Folder", this, "NewFolderName"));
        DropdownListPrefab<string> existing = new DropdownListPrefab<string>("Existing Folders", this, "SelectedFolder"); 
        EditorVirtualFolderConfig config = GetEditorVirtualFolderConfig();
        if (config && config.VirtualFolders)
        {
            foreach (string folderName, EditorVirtualFolderData folderData : config.VirtualFolders)
            {
                if (folderName && folderName.Trim() != "")
                {
                    existing[folderName] = folderName;
                }
            }
        }
        
        group.Insert(existing);
        AddContent(group);
    }
    
    override void CloseDialog(DialogResult dialog_result = DialogResult.Cancel)
    {
        if (dialog_result == DialogResult.OK && m_PlaceableItem)
        {
            string folderName = NewFolderName;
            if (!folderName || folderName.Trim() == "")
            {
                folderName = SelectedFolder;
            }
            
            if (folderName && folderName.Trim() != "")
            {
                folderName = folderName.Trim();
                bool newFolderCreated = EditorVirtualFolderManager.GetInstance().CreateFolder(folderName);
                
                // Add as Class item or Model item based on type
                if (m_PlaceableItem.Type.Contains(".p3d"))
                {
                    EditorVirtualFolderManager.GetInstance().AddItemToFolder(m_PlaceableItem, folderName, 1);
                }
                else
                {
                    EditorVirtualFolderManager.GetInstance().AddItemToFolder(m_PlaceableItem, folderName, 0);
                }
                
                // Refresh UI
                Editor editor = GetEditor();
                if (editor)
                {
                    EditorHud hud = editor.GetEditorHud();
                    if (hud)
                    {
                        if (newFolderCreated)
                        {
                            hud.RefreshVirtualFoldersWithReload();
                        }
                        else
                        {
                            hud.RefreshVirtualFolders();
                        }
                    }
                }
            }
        }
        
        super.CloseDialog(dialog_result);
    }
}