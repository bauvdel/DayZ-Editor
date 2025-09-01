class EditorAddToVirtualFolderCommand: EditorCommand
{
    protected override bool Execute(Class sender, CommandArgs args)
    {
        super.Execute(sender, args);
        
        EditorPlaceableItem m_PlaceableItem = null;
        Param1<EditorPlaceableItem> p1 = Param1<EditorPlaceableItem>.Cast(GetData());
        if (p1) {
            m_PlaceableItem = p1.param1;
        }
        
        if (!m_PlaceableItem)
        {
            return true;
        }
        
        EditorAddToVirtualFolderDialog dialog = new EditorAddToVirtualFolderDialog("Add to Virtual Folder", m_PlaceableItem);
        
        if (!dialog)
        {
            return true;
        }
        
        return true;
    }
    
    override string GetName()
    {
        return "Add to Virtual Folder";
    }
    
    override string GetIcon()
    {
        return "set:solid image:folder_plus";
    }
}

class EditorDeleteVirtualFolderCommand: EditorCommand
{
    protected override bool Execute(Class sender, CommandArgs args)
    {
        super.Execute(sender, args);
        
        EditorVirtualFolderListNode m_VirtualFolderNode = null;
        Param1<EditorVirtualFolderListNode> p1 = Param1<EditorVirtualFolderListNode>.Cast(GetData());
        if (p1) {
            m_VirtualFolderNode = p1.param1;
        }
        
        if (!m_VirtualFolderNode)
        {
            return true;
        }
        
        EditorDeleteVirtualFolderDialog deleteDialog = new EditorDeleteVirtualFolderDialog("Delete Virtual Folder", m_VirtualFolderNode);
        
        if (!deleteDialog)
        {
            return true;
        }
        
        return true;
    }
    
    override string GetName()
    {
        return "Delete Virtual Folder";
    }
    
    override string GetIcon()
    {
        return "set:solid image:trash";
    }
}

class EditorRemoveFromVirtualFolderCommand: EditorCommand
{
    protected override bool Execute(Class sender, CommandArgs args)
    {
        super.Execute(sender, args);
        
        EditorPlaceableItem m_PlaceableItem = null;
        
        // Try to get from context menu data first
        Param1<EditorPlaceableItem> p1 = Param1<EditorPlaceableItem>.Cast(GetData());
        if (p1) {
            m_PlaceableItem = p1.param1;
        }
        
        // If no context menu data, try to get from selected node
        if (!m_PlaceableItem && EditorListNode.s_SelectedNode)
        {
            if (EditorListNode.s_SelectedNode.IsInherited(EditorPlaceableListNode))
            {
                EditorPlaceableListNode placeableNode = EditorPlaceableListNode.Cast(EditorListNode.s_SelectedNode);
                if (placeableNode)
                {
                    m_PlaceableItem = placeableNode.GetPlaceableItem();
                }
            }
        }
        
        if (!m_PlaceableItem)
        {
            EditorLog.Warning("No placeable item selected for RemoveFromVirtualFolderCommand");
            return true;
        }
            
        string folderName = EditorVirtualFolderManager.GetInstance().GetItemFolder(m_PlaceableItem);
        if (folderName == string.Empty)
        {
            EditorLog.Warning("Item is not in any virtual folder");
            return true;
        }
        
        if (EditorVirtualFolderManager.GetInstance().RemoveItemFromFolder(m_PlaceableItem))
        {
            // When removing items, we need full reload to restore them to original locations
            GetEditor().GetEditorHud().RefreshVirtualFoldersWithReload();
        }
        else
        {
            EditorLog.Error("Failed to remove item from virtual folder");
        }
        
        return true;
    }
    
    override string GetName()
    {
        return "Remove from Virtual Folder";
    }
    
    override string GetIcon()
    {
        return "set:solid image:folder_minus";
    }
    
    override ShortcutKeys GetShortcut()
    {
        return { KeyCode.KC_R };
    }
    
    override bool CanExecute()
    {
        // Check if there's a selected placeable node
        if (EditorListNode.s_SelectedNode && EditorListNode.s_SelectedNode.IsInherited(EditorPlaceableListNode))
        {
            EditorPlaceableListNode placeableNode = EditorPlaceableListNode.Cast(EditorListNode.s_SelectedNode);
            if (placeableNode)
            {
                EditorPlaceableItem item = placeableNode.GetPlaceableItem();
                if (item)
                {
                    // Check if the item is actually in a virtual folder
                    string folderName = EditorVirtualFolderManager.GetInstance().GetItemFolder(item);
                    return folderName != string.Empty;
                }
            }
        }
        
        return false;
    }
}

class EditorAddRootFolderToVirtualCommand: EditorCommand
{
    protected override bool Execute(Class sender, CommandArgs args)
    {
        super.Execute(sender, args);
        
        
        // Get the folder node
        EditorListNode folderNode = null;
        Param1<EditorListNode> p1 = Param1<EditorListNode>.Cast(GetData());
        if (p1) {
            folderNode = p1.param1;
        }
        
        if (!folderNode)
        {
            EditorLog.Warning("No folder node provided to AddRootFolderToVirtualCommand");
            return true;
        }
        
        // Get folder name from the node
        string folderName = "";
        
        if (folderNode.IsInherited(EditorFolderListNode)) {
            EditorFolderListNode folderListNode = EditorFolderListNode.Cast(folderNode);
            if (folderListNode) {
                folderName = folderListNode.GetFullFolderPath();
            }
        }
        
        folderName = folderName.Trim();
        
        if (folderName == "" || folderName.Contains("("))
        {
            return true;
        }
        
        // Check if this root folder is already assigned to a virtual folder
        EditorVirtualFolderConfig config = GetEditorVirtualFolderConfig();
        if (config && config.VirtualFolders)
        {
            foreach (string vfName, EditorVirtualFolderData vfData : config.VirtualFolders)
            {
                if (vfData.RootFolders.Find(folderName) != -1)
                {
                    EditorLog.Warning("Root folder already assigned: " + folderName + " in " + vfName);
                    return true;
                }
            }
        }
        
        // Show dialog for folder selection
        EditorAddRootFolderToVirtualDialog dialog = new EditorAddRootFolderToVirtualDialog("Add Root Folder to Virtual Folder", folderName);
        
        if (!dialog)
        {
            return true;
        }
        
        
        return true;
    }
    
    override string GetName()
    {
        return "Add to Virtual Folder";
    }
    
    override string GetIcon()
    {
        return "set:solid image:folder_plus";
    }
}