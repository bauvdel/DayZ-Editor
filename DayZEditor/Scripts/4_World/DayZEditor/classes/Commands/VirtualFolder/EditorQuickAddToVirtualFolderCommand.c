class EditorQuickAddToVirtualFolderCommand: EditorCommand
{
    protected override bool Execute(Class sender, CommandArgs args)
    {
        super.Execute(sender, args);
        
        EditorPlaceableItem m_PlaceableItem = null;
        
        if (EditorListNode.s_SelectedNode && EditorListNode.s_SelectedNode.IsInherited(EditorPlaceableListNode))
        {
            EditorPlaceableListNode placeableNode = EditorPlaceableListNode.Cast(EditorListNode.s_SelectedNode);
            if (placeableNode)
            {
                m_PlaceableItem = placeableNode.GetPlaceableItem();
            }
        }
        
        // Only use context menu data if there's no UI selection (for context menus)
        if (!m_PlaceableItem)
        {
            Param1<EditorPlaceableItem> p1 = Param1<EditorPlaceableItem>.Cast(GetData());
            if (p1) {
                m_PlaceableItem = p1.param1;
            }
        }
        
        EditorVirtualFolderManager manager = EditorVirtualFolderManager.GetInstance();
        EditorHud hud = GetEditor().GetEditorHud();
        
        if (!m_PlaceableItem)
        {
            if (hud)
            {
                if (!EditorListNode.s_SelectedNode)
                {
                    hud.CreateNotification("Quick Add: No item selected");
                }
                else if (!EditorListNode.s_SelectedNode.IsInherited(EditorPlaceableListNode))
                {
                    hud.CreateNotification("Quick Add: Selected item is not placeable (" + EditorListNode.s_SelectedNode.ClassName() + ")");
                }
                else
                {
                    hud.CreateNotification("Quick Add: Could not get placeable item from selected node");
                }
            }
            return true;
        }
        
        if (!manager.HasLastUsedFolder())
        {
            if (hud)
            {
                hud.CreateNotification("Quick Add: No last used folder available");
            }
            return true;
        }
        
        string lastUsedFolder = manager.GetLastUsedFolder();
        string message;
        
        // Determine add type based on item type (same logic as EditorAddToVirtualFolderDialog)
        int addType = 0; 
        if (m_PlaceableItem.Type.Contains(".p3d"))
        {
            addType = 1;
        }
        
        if (manager.AddItemToLastUsedFolder(m_PlaceableItem, addType))
        {
            // Show success notification
            if (hud)
            {
                message = "Added '" + m_PlaceableItem.Name + "' to '" + lastUsedFolder + "'";
                hud.CreateNotification(message);
            }
            
            if (!manager.IsBatchMode())
            {
                GetEditor().GetEditorHud().RefreshVirtualFolders();
            }
        }
        else
        {
            // Show error notification
            if (hud)
            {
                message = "Failed to add '" + m_PlaceableItem.Name + "' to virtual folder";
                hud.CreateNotification(message);
            }
        }
        
        return true;
    }
    
    override string GetName()
    {
        EditorVirtualFolderManager manager = EditorVirtualFolderManager.GetInstance();
        if (manager.HasLastUsedFolder())
        {
            return "Quick Add to " + manager.GetLastUsedFolder() + "";
        }
        return "Quick Add to Virtual Folder";
    }
    
    override string GetIcon()
    {
        return "set:solid image:bolt";
    }
    
    override ShortcutKeys GetShortcut()
    {
        return { KeyCode.KC_V };
    }
    
    override bool CanExecute()
    {
        // Check if theres a last used folder
        EditorVirtualFolderManager manager = EditorVirtualFolderManager.GetInstance();
        if (!manager.HasLastUsedFolder())
            return false;
        
        // For keyboard shortcuts, always prioritize the UI selection over context data
        if (EditorListNode.s_SelectedNode && EditorListNode.s_SelectedNode.IsInherited(EditorPlaceableListNode))
        {
            EditorPlaceableListNode placeableNode = EditorPlaceableListNode.Cast(EditorListNode.s_SelectedNode);
            if (placeableNode && placeableNode.GetPlaceableItem())
            {
                return true;
            }
        }
        
        // Only use context data if there's no UI selection (for context menus)
        Param1<EditorPlaceableItem> p1 = Param1<EditorPlaceableItem>.Cast(GetData());
        if (p1 && p1.param1) {
            return true;
        }
        
        return false;
    }
}