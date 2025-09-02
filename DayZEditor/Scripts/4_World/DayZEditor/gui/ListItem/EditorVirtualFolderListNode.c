class EditorVirtualFolderListNode: EditorFolderListNode
{
    protected EditorVirtualFolderData m_VirtualFolderData;
    protected bool m_Populated;
    
    void EditorVirtualFolderListNode(string text, EditorVirtualFolderData virtualFolderData)
    {
        m_VirtualFolderData = virtualFolderData;
        
        m_Text = text;
        Text.SetText(text);
        m_Text.ToLower();
        m_LayoutRoot.SetSort(0);
        IconImage.LoadImageFile(0, EDITOR_ICON_FOLDER);
        IconImage.SetColor(0xFF4CAF50);
        
        
        RefreshContents();
    }
    
    EditorVirtualFolderData GetVirtualFolderData()
    {
        return m_VirtualFolderData;
    }
    
    void UpdateDisplayName()
    {
        if (!m_VirtualFolderData)
            return;
        int itemCount = ChildrenItems.Count();
        string displayName = string.Format("%1 (%2)", m_Text, itemCount);
        Text.SetText(displayName);
    }

    void RefreshContents()
    {
        
        if (!m_VirtualFolderData)
            return;
            
        ChildrenItems.Clear();
        
        EditorObjectManagerModule objectManager = GetEditor().GetObjectManager();
        if (!objectManager)
            return;
            
        array<ref EditorPlaceableItem> allPlaceableObjects = objectManager.GetPlaceableObjects();
        int itemCount = 0;
        
        
        foreach (EditorPlaceableItem placeableItem: allPlaceableObjects)
        {
            if (m_VirtualFolderData.ContainsItemByData(placeableItem.Type, placeableItem.GetModelName(), placeableItem.Path))
            {
                itemCount++;
                EditorPlaceableListNode childNode = new EditorPlaceableListNode(placeableItem);
                InsertChild(childNode);
                
                EditorHud hud = GetEditor().GetEditorHud();
                if (hud)
                {
                    hud.AddToSearchableNodes(childNode);
                }
            }
        }
        
        Collapse.Show(itemCount > 0);
        string displayName = string.Format("%1 (%2)", m_Text, itemCount);
        Text.SetText(displayName);
        
    }
    
    override bool OnMouseButtonDown(Widget w, int x, int y, int button)
    {
        return super.OnMouseButtonDown(w, x, y, button);
    }
    
    override bool FilterType(string filter, bool favorites)
    {
        
        if (filter == string.Empty)
            return true;
            
        string folderName = m_Text;
        folderName.ToLower();
        if (folderName.Contains(filter))
        {
            return true;
        }
            
        bool hasMatchingChildren = false;
        foreach (EditorListNode childNode: ChildrenItems)
        {
            bool childMatches = childNode.FilterType(filter, favorites);
            childNode.Show(childMatches);
            
            if (childMatches)
            {
                hasMatchingChildren = true;
            }
        }
        
        
        if (hasMatchingChildren)
        {
            SetCollapsed(false);
        }
        
        return hasMatchingChildren;
    }
    
    void DeleteVirtualFolder()
    {
        EditorVirtualFolderManager.GetInstance().DeleteFolder(m_Text);
        if (GetListParent())
        {
            GetListParent().ChildrenItems.RemoveItem(this);
        }
        
        if (GetLayoutRoot())
            GetLayoutRoot().Unlink();
        
        EditorHud hud = GetEditor().GetEditorHud();
        if (hud)
        {
            hud.RefreshVirtualFoldersWithReload();
        }
    }
    
    string GetFolderName()
    {
        return m_Text;
    }
    
    void ConfirmDeleteVirtualFolder(int result)
    {
        if (result == DialogResult.Yes)
        {
            DeleteVirtualFolder();
        }
    }
}