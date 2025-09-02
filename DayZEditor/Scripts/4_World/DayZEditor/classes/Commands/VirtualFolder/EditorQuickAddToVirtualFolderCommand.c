class EditorQuickAddToVirtualFolderCommand: EditorCommand
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
        
        if (manager.AddItemToLastUsedFolder(m_PlaceableItem, 0))
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
        // Check if theres a last used folder and a selected placeable item
        EditorVirtualFolderManager manager = EditorVirtualFolderManager.GetInstance();
        if (!manager.HasLastUsedFolder())
            return false;
            
        // Check if theres a selected placeable node
        if (EditorListNode.s_SelectedNode && EditorListNode.s_SelectedNode.IsInherited(EditorPlaceableListNode))
            return true;
            
        return false;
    }
}