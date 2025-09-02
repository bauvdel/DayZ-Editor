class EditorVirtualFolderUIManager
{
    protected EditorHud m_EditorHud;
    protected Editor m_Editor;
    protected EditorHudController m_TemplateController;
    
    protected ref array<ref EditorVirtualFolderListNode> m_VirtualFolderNodes = {};
    protected ref EditorFolderListNode m_VirtualFoldersRoot;
    
    void EditorVirtualFolderUIManager(EditorHud editorHud)
    {
        m_EditorHud = editorHud;
        m_Editor = editorHud.GetEditor();
        m_TemplateController = editorHud.GetTemplateController();
    }
    
    void ~EditorVirtualFolderUIManager()
    {
        ClearVirtualFolderNodes();
    }
    
    array<ref EditorVirtualFolderListNode> GetVirtualFolderNodes()
    {
        return m_VirtualFolderNodes;
    }
    
    EditorFolderListNode GetVirtualFoldersRoot()
    {
        return m_VirtualFoldersRoot;
    }
    
    // Compatibility methods for code that still references the old member variables
    ref array<ref EditorVirtualFolderListNode> GetVirtualFolderNodesRef()
    {
        return m_VirtualFolderNodes;
    }
    
    ref EditorFolderListNode GetVirtualFoldersRootRef()
    {
        return m_VirtualFoldersRoot;
    }
    
    void LoadVirtualFolders()
    {
        // Suppress folder collapse during virtual folder operations to prevent slowdown
        m_EditorHud.SetSuppressFolderCollapse(true);
        
        // No need to rebuild - the initial tree was already built with virtual folder filtering
        
        // Clear existing virtual folder nodes
        ClearVirtualFolderNodes();
        
        // Remove existing virtual folders root
        ClearVirtualFoldersRoot();
        
        EditorVirtualFolderManager folderManager = EditorVirtualFolderManager.GetInstance();
        array<string> folderNames = folderManager.GetFolderNames();
        
        if (folderNames.Count() == 0)
        {
            // Re-enable folder collapse
            m_EditorHud.SetSuppressFolderCollapse(false);
            return;
        }
        
        // Create Virtual Folders root node
        CreateVirtualFoldersRoot();
        
        // Hide original items that are now in virtual folders BEFORE creating virtual folder contents
        HideVirtualizedItems();
        
        // Create virtual folder nodes
        foreach (string folderName: folderNames)
        {
            EditorVirtualFolderData folderData = folderManager.GetFolder(folderName);
            if (folderData && !folderData.IsEmpty())
            {
                EditorVirtualFolderListNode newVirtualFolderNode = new EditorVirtualFolderListNode(folderName, folderData);
                
                m_VirtualFoldersRoot.InsertChild(newVirtualFolderNode);
                m_VirtualFolderNodes.Insert(newVirtualFolderNode);
                
                // Add virtual folder itself to searchable nodes so it gets filtered during search
                m_EditorHud.GetSearchableListNodes().Insert(newVirtualFolderNode);
                
                // Add to folder depth system (this was missing!)
                if (!m_EditorHud.GetFolderNodesByDepth()[1])
                    m_EditorHud.GetFolderNodesByDepth()[1] = {};
                m_EditorHud.GetFolderNodesByDepth()[1].Insert(newVirtualFolderNode);
                
                // Add to folder nodes collection (this was missing!)
                m_EditorHud.GetFolderNodes()["virtual_folder_" + folderName] = newVirtualFolderNode;
            }
        }
        
        // Re-enable folder collapse
        m_EditorHud.SetSuppressFolderCollapse(false);
    }
    
    void RefreshVirtualFolders()
    {
        // Clear any stale selection to prevent crashes
        m_EditorHud.ClearSelection();
        
        // Suppress folder collapse during refresh
        m_EditorHud.SetSuppressFolderCollapse(true);
        
        // Rebuild the base folder tree to restore any items removed from virtual folders
        m_EditorHud.RebuildBaseFolderTree();
        
        // Load virtual folders with restored base tree
        LoadVirtualFolders();
        
        // Re-enable folder collapse
        m_EditorHud.SetSuppressFolderCollapse(false);
    }
    
    void RefreshVirtualFoldersWithHiding()
    {
        // Use this only when we actually need to hide/restore items
        EditorLog.Info("RefreshVirtualFoldersWithHiding called - using full refresh");
        
        // Clear any stale selection to prevent crashes
        m_EditorHud.ClearSelection();
        
        // Suppress folder collapse during refresh
        m_EditorHud.SetSuppressFolderCollapse(true);
        
        // For more complex changes, do full reload
        if (ShouldUseFullReload())
        {
            RefreshVirtualFoldersWithReload();
        }
        else
        {
            // Hide items and refresh folder contents
            HideVirtualizedItems();
            
            // Refresh virtual folder contents
            foreach (EditorVirtualFolderListNode folderNode: m_VirtualFolderNodes)
            {
                if (folderNode)
                    folderNode.RefreshContents();
            }
            
            // Re-enable folder collapse
            m_EditorHud.SetSuppressFolderCollapse(false);
        }
    }
    
    void RestoreItemsRemovedFromVirtualFolders()
    {
        // Simple but effective approach: check if any items need restoration
        // and if so, trigger a full reload to ensure everything is properly restored
        EditorVirtualFolderManager folderManager = EditorVirtualFolderManager.GetInstance();
        array<ref EditorPlaceableItem> allPlaceableObjects = m_Editor.GetPlaceableObjects();
        
        bool needsReload = false;
        
        foreach (EditorPlaceableItem placeableItem: allPlaceableObjects)
        {
            string currentFolder = folderManager.GetItemFolder(placeableItem);
            if (currentFolder == string.Empty)
            {
                // This item is no longer in any virtual folder, check if it needs to be restored
                if (!IsItemVisibleInternal(placeableItem))
                {
                    needsReload = true;
                    break;
                }
            }
        }
        
        if (needsReload)
        {
            LoadVirtualFolders();
            // Stop here since LoadVirtualFolders already handles everything
        }
    }
    
    void HideVirtualizedItems()
    {
        EditorVirtualFolderManager folderManager = EditorVirtualFolderManager.GetInstance();
        
        // Get all virtualized items first (more efficient than checking each item individually)
        array<ref EditorPlaceableItem> virtualizedItems = new array<ref EditorPlaceableItem>();
        array<ref EditorPlaceableItem> allPlaceableObjects = m_Editor.GetPlaceableObjects();
        
        foreach (EditorPlaceableItem placeableItem: allPlaceableObjects)
        {
            string virtualFolderName = folderManager.GetItemFolder(placeableItem);
            if (virtualFolderName != string.Empty)
            {
                virtualizedItems.Insert(placeableItem);
            }
        }
        
        // Hide virtualized items efficiently
        HideItemsInBulkInternal(virtualizedItems);
    }
    
    void RefreshVirtualFoldersWithReload()
    {
        // Clear any stale selection to prevent crashes
        m_EditorHud.ClearSelection();
        
        // Rebuild the base folder tree to restore any items removed from virtual folders
        m_EditorHud.RebuildBaseFolderTree();
        
        // Use this for major changes that require full reload (like new folder creation)
        LoadVirtualFolders();
    }
    
    bool HasVirtualFolderMatches(string searchText, bool favoriteToggle)
    {
        bool hasMatches = false;
        
        foreach (EditorVirtualFolderListNode virtualFolderNode: m_VirtualFolderNodes)
        {
            bool hasMatchingChildren = false;
            foreach (EditorListNode childNode: virtualFolderNode.ChildrenItems)
            {
                if (childNode.FilterType(searchText, favoriteToggle))
                {
                    hasMatchingChildren = true;
                    break;
                }
            }
            
            if (hasMatchingChildren)
            {
                virtualFolderNode.SetCollapsed(false);
                hasMatches = true;
            }
        }
        
        // Expand Virtual Folders root if any virtual folders have matches
        if (hasMatches && m_VirtualFoldersRoot)
        {
            m_VirtualFoldersRoot.SetCollapsed(false);
        }
        else if (hasMatches && !m_VirtualFoldersRoot)
        {
            EditorLog.Warning("Virtual Folders root is null during search expansion");
        }
        
        return hasMatches;
    }
    
    bool HasShortSearchVirtualFolderMatches(bool favoriteToggle)
    {
        bool hasMatches = false;
        
        foreach (EditorVirtualFolderListNode virtualFolderNode: m_VirtualFolderNodes)
        {
            bool hasMatchingChildren = false;
            foreach (EditorListNode childNode: virtualFolderNode.ChildrenItems)
            {
                if (childNode.FilterType("", favoriteToggle))
                {
                    GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(virtualFolderNode.SetCollapsed, 0, 0, false);
                    hasMatchingChildren = true;
                    break;
                }
            }
            
            if (hasMatchingChildren)
            {
                hasMatches = true;
            }
        }
        
        // Expand Virtual Folders root if any virtual folders have matches
        if (hasMatches && m_VirtualFoldersRoot)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_VirtualFoldersRoot.SetCollapsed, 0, 0, false);
        }
        else if (hasMatches && !m_VirtualFoldersRoot)
        {
            EditorLog.Warning("Virtual Folders root is null during short search expansion");
        }
        
        return hasMatches;
    }
    
    int CollapseAllVirtualFolders()
    {
        int foldersCollapsed = 0;
        
        // Check all virtual folders
        foreach (EditorVirtualFolderListNode vfNode: m_VirtualFolderNodes)
        {
            if (vfNode && !vfNode.IsCollapsed())
            {
                vfNode.SetCollapsed(true);
                foldersCollapsed++;
            }
        }
        
        // Check Virtual Folders root
        if (m_VirtualFoldersRoot && !m_VirtualFoldersRoot.IsCollapsed())
        {
            m_VirtualFoldersRoot.SetCollapsed(true);
            foldersCollapsed++;
        }
        
        return foldersCollapsed;
    }
    
    protected void ClearVirtualFolderNodes()
    {
        foreach (EditorVirtualFolderListNode existingNode: m_VirtualFolderNodes)
        {
            if (existingNode)
                existingNode.GetLayoutRoot().Unlink();
        }
        m_VirtualFolderNodes.Clear();
    }
    
    protected void ClearVirtualFoldersRoot()
    {
        if (m_VirtualFoldersRoot)
        {
            m_VirtualFoldersRoot.GetLayoutRoot().Unlink();
            m_EditorHud.GetFolderNodes().Remove("virtual_folders_root");
            if (m_EditorHud.GetFolderNodesByDepth()[0])
                m_EditorHud.GetFolderNodesByDepth()[0].RemoveItem(m_VirtualFoldersRoot);
            m_VirtualFoldersRoot = null;
        }
    }
    
    protected void CreateVirtualFoldersRoot()
    {
        m_VirtualFoldersRoot = new EditorFolderListNode("Virtual Folders");
        m_TemplateController.LeftContent.Insert(m_VirtualFoldersRoot);
        
        // Add to folder depth system
        if (!m_EditorHud.GetFolderNodesByDepth()[0])
            m_EditorHud.GetFolderNodesByDepth()[0] = {};
        m_EditorHud.GetFolderNodesByDepth()[0].Insert(m_VirtualFoldersRoot);
        m_EditorHud.GetFolderNodes()["virtual_folders_root"] = m_VirtualFoldersRoot;
    }
    
    protected bool ShouldUseFullReload()
    {
        // Logic to determine if full reload is needed
        // For now, use simpler refresh unless we detect major changes
        return false;
    }
    
    protected void HideItemsInBulkInternal(array<ref EditorPlaceableItem> items)
    {
        // Efficiently hide multiple items
        foreach (EditorPlaceableItem placeableItem: items)
        {
            // Find and hide the placeable item nodes
            string model_name = placeableItem.GetModelName();
            if (model_name && model_name != "bmp" && model_name != "bmp.p3d")
            {
                if (m_EditorHud.GetFolderNodes().Contains(model_name))
                {
                    EditorListNode modelNode = m_EditorHud.GetFolderNodes()[model_name];
                    if (modelNode && modelNode.IsInherited(EditorPlaceableListNode))
                    {
                        modelNode.GetLayoutRoot().Show(false);
                    }
                }
            }
            else
            {
                // For class-based items, find in searchable nodes
                string itemType = placeableItem.Type;
                
                foreach (EditorListNode searchableNode: m_EditorHud.GetSearchableListNodes())
                {
                    if (searchableNode.IsInherited(EditorPlaceableListNode))
                    {
                        EditorPlaceableListNode placeableNode = EditorPlaceableListNode.Cast(searchableNode);
                        if (placeableNode)
                        {
                            EditorPlaceableItem nodeItem = placeableNode.GetPlaceableItem();
                            if (nodeItem && nodeItem.Type == itemType)
                            {
                                placeableNode.GetLayoutRoot().Show(false);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    
    protected bool IsItemVisibleInternal(EditorPlaceableItem placeableItem)
    {
        // Check if an item is currently visible in the UI
        string model_name = placeableItem.GetModelName();
        if (model_name && model_name != "bmp" && model_name != "bmp.p3d")
        {
            if (m_EditorHud.GetFolderNodes().Contains(model_name))
            {
                EditorListNode modelNode = m_EditorHud.GetFolderNodes()[model_name];
                if (modelNode && modelNode.IsInherited(EditorPlaceableListNode))
                {
                    return modelNode.GetLayoutRoot().IsVisible();
                }
            }
        }
        else
        {
            // For class-based items, find in searchable nodes
            string itemType = placeableItem.Type;
            
            foreach (EditorListNode searchableNode: m_EditorHud.GetSearchableListNodes())
            {
                if (searchableNode.IsInherited(EditorPlaceableListNode))
                {
                    EditorPlaceableListNode placeableNode = EditorPlaceableListNode.Cast(searchableNode);
                    if (placeableNode)
                    {
                        EditorPlaceableItem nodeItem = placeableNode.GetPlaceableItem();
                        if (nodeItem && nodeItem.Type == itemType)
                        {
                            return placeableNode.GetLayoutRoot().IsVisible();
                        }
                    }
                }
            }
        }
        return false;
    }
}