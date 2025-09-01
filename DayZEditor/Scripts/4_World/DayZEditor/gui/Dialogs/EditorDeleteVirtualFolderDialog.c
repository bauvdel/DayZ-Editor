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
        string confirmMessage = string.Format("Are you sure you want to delete the virtual folder '%1'?\n\nThis will remove the folder and all its contents from the Virtual Folders list.", folderName);
        AddContent(new MessageBoxPrefab(confirmMessage));
    }
    
    override void CloseDialog(DialogResult dialog_result = DialogResult.Cancel)
    {
        if (dialog_result == DialogResult.Yes && m_VirtualFolderNode)
        {
            m_VirtualFolderNode.DeleteVirtualFolder();
        }
        
        super.CloseDialog(dialog_result);
    }
}