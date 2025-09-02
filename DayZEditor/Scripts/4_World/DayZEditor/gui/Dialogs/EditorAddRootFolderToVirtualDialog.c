class EditorAddRootFolderToVirtualDialog: EditorDialogBase
{
    string NewFolderName;
    string SelectedFolder;
    
    protected string m_RootFolderPath;
    
    void EditorAddRootFolderToVirtualDialog(string title, string rootFolderPath)
    {
        m_RootFolderPath = rootFolderPath;
        
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
        if (dialog_result == DialogResult.OK && m_RootFolderPath)
        {
            string folderName = NewFolderName;
            if (!folderName || folderName.Trim() == "")
            {
                folderName = SelectedFolder;
            }
            
            if (!folderName || folderName.Trim() == "")
            {
                array<string> pathParts = new array<string>();
                m_RootFolderPath.Split("/", pathParts);
                string lastFolder = pathParts[pathParts.Count() - 1];
                folderName = "RootFolders_" + lastFolder;
            }
            
            folderName = folderName.Trim();
            EditorVirtualFolderManager.GetInstance().CreateFolder(folderName);
            bool addSuccess = EditorVirtualFolderManager.GetInstance().AddRootFolderToFolder(m_RootFolderPath, folderName);
            
            Editor editor = GetEditor();
            if (editor)
            {
                EditorHud hud = editor.GetEditorHud();
                if (hud)
                {
                    // Show notification
                    string message;
                    if (addSuccess)
                    {
                        message = "Added root folder '" + m_RootFolderPath + "' to '" + folderName + "'";
                    }
                    else
                    {
                        message = "Failed to add root folder '" + m_RootFolderPath + "' to '" + folderName + "'";
                    }
                    hud.CreateNotification(message);
                    
                    hud.RefreshVirtualFoldersWithReload();
                }
            }
        }
        
        super.CloseDialog(dialog_result);
    }
}