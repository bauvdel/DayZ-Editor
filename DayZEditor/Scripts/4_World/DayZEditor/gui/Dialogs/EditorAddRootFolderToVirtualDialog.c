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
        GroupPrefab group = new GroupPrefab("Add Root Folder: " + m_RootFolderPath, this, string.Empty);
        
        group.Insert(new EditBoxPrefab("New virtual folder (optional)", this, "NewFolderName"));
        
        DropdownListPrefab<string> existing = new DropdownListPrefab<string>("Existing virtual folders", this, "SelectedFolder");
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
            EditorVirtualFolderManager.GetInstance().AddRootFolderToFolder(m_RootFolderPath, folderName);
            
            Editor editor = GetEditor();
            if (editor)
            {
                EditorHud hud = editor.GetEditorHud();
                if (hud)
                {
                    hud.RefreshVirtualFoldersWithReload();
                }
            }
        }
        
        super.CloseDialog(dialog_result);
    }
}