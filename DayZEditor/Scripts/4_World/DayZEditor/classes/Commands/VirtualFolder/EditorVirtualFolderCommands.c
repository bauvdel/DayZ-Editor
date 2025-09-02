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
            return true;
        }
            
        EditorVirtualFolderManager manager = EditorVirtualFolderManager.GetInstance();
        string folderName = manager.GetItemFolder(m_PlaceableItem);
        if (folderName == string.Empty)
        {
            return true;
        }
        
        // Check if this item belongs to a root folder
        string rootFolderPath = manager.GetItemRootFolder(m_PlaceableItem, folderName);
        if (rootFolderPath != string.Empty)
        {
            // Item belongs to a root folder - show special dialog
            EditorRemoveRootFolderFromVirtualDialog dialog = new EditorRemoveRootFolderFromVirtualDialog("Remove Root Folder", m_PlaceableItem, folderName, rootFolderPath);
            
            if (!dialog)
            {
                EditorLog.Error("Root folder removal dialog creation failed");
            }
        }
        else
        {
            // Item was individually added - remove normally
            EditorHud hud = GetEditor().GetEditorHud();
            string message;
            
            if (manager.RemoveItemFromFolder(m_PlaceableItem))
            {
                // Show success notification
                if (hud)
                {
                    message = "Removed '" + m_PlaceableItem.Name + "' from '" + folderName + "'";
                    hud.CreateNotification(message);
                }
                
                if (!manager.IsBatchMode())
                {
                    GetEditor().GetEditorHud().RefreshVirtualFoldersWithReload();
                }
            }
            else
            {
                // Show error notification
                if (hud)
                {
                    message = "Failed to remove '" + m_PlaceableItem.Name + "' from virtual folder";
                    hud.CreateNotification(message);
                }
            }
        }
        
        return true;
    }
    
    override string GetName()
    {
        return "Remove from Folder";
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