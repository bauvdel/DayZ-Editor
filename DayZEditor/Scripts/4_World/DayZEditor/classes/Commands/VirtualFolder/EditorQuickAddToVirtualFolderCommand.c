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
        
        if (!m_PlaceableItem)
        {
            return true;
        }
        
        EditorVirtualFolderManager manager = EditorVirtualFolderManager.GetInstance();
        if (!manager.HasLastUsedFolder())
        {
            return true;
        }
        
        if (manager.AddItemToLastUsedFolder(m_PlaceableItem, 0))
        {
            GetEditor().GetEditorHud().RefreshVirtualFolders();
        }
        else
        {
            EditorLog.Error("Failed to add item to last used virtual folder");
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