class EditorDeleteVirtualFolderDialog: EditorDialogBase
{
    protected EditorVirtualFolderListNode m_VirtualFolderNode;
    
    void EditorDeleteVirtualFolderDialog(string title, EditorVirtualFolderListNode virtualFolderNode)
    {
        m_VirtualFolderNode = virtualFolderNode;
        
        BuildContent();
        AddButton(DialogResult.Yes);
        AddButton(DialogResult.Cancel);
    }
    
    override string GetLayoutFile()
    {
        return "DayZEditor/gui/Layouts/dialogs/DialogBase.layout";
    }
    
    protected void BuildContent()
    {
        string folderName = m_VirtualFolderNode.GetFolderName();
        string confirmMessage = string.Format("Are you sure you want to delete the virtual folder '%1'?\n\nThis will remove the folder and all its contents from the Virtual Folders list. This may take a moment.", folderName);
        AddContent(new MessageBoxPrefab(confirmMessage));
    }
    
    override void CloseDialog(DialogResult dialog_result = DialogResult.Cancel)
    {
        if (dialog_result == DialogResult.Yes && m_VirtualFolderNode)
        {
            string folderName = m_VirtualFolderNode.GetFolderName();
            bool deleteSuccess = EditorVirtualFolderManager.GetInstance().DeleteFolder(folderName);
            
            if (deleteSuccess)
            {
                // Remove from UI manually since we're calling manager directly
                if (m_VirtualFolderNode.GetListParent())
                {
                    m_VirtualFolderNode.GetListParent().ChildrenItems.RemoveItem(m_VirtualFolderNode);
                }
                m_VirtualFolderNode.GetLayoutRoot().Unlink();
            }
            
            // Show notification and refresh UI
            Editor editor = GetEditor();
            if (editor)
            {
                EditorHud hud = editor.GetEditorHud();
                if (hud)
                {
                    string message;
                    if (deleteSuccess)
                    {
                        message = "Deleted virtual folder '" + folderName + "'";
                        // Refresh the virtual folders UI to show changes
                        hud.RefreshVirtualFoldersWithReload();
                    }
                    else
                    {
                        message = "Failed to delete virtual folder '" + folderName + "'";
                    }
                    hud.CreateNotification(message);
                }
            }
        }
        
        super.CloseDialog(dialog_result);
    }
}