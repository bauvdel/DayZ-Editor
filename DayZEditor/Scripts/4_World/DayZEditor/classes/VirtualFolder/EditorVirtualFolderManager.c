class EditorVirtualFolderManager
{
    protected static ref EditorVirtualFolderManager s_Instance;
    protected ref EditorVirtualFolderConfig m_Config;
    protected string m_LastUsedFolder;
    
    void EditorVirtualFolderManager()
    {
        m_Config = GetEditorVirtualFolderConfig();
    }
    
    static EditorVirtualFolderManager GetInstance()
    {
        if (!s_Instance)
            s_Instance = new EditorVirtualFolderManager();
        return s_Instance;
    }
    
    bool CreateFolder(string folderName)
    {
        if (m_Config.VirtualFolders.Contains(folderName))
            return false;
            
        // Use the user-provided folderName as both the key and the Name field
        EditorVirtualFolderData newFolder = new EditorVirtualFolderData(folderName);
        m_Config.VirtualFolders[folderName] = newFolder;
        m_Config.Save();
        return true;
    }
    
    bool DeleteFolder(string folderName)
    {
        if (!m_Config.VirtualFolders.Contains(folderName))
            return false;
            
        m_Config.VirtualFolders.Remove(folderName);
        m_Config.Save();
        return true;
    }
    
    EditorVirtualFolderData GetFolder(string folderName)
    {
        if (m_Config.VirtualFolders.Contains(folderName))
            return m_Config.VirtualFolders[folderName];
        return null;
    }
    
    array<string> GetFolderNames()
    {
        array<string> folderNames = new array<string>();
        foreach (string folderName, EditorVirtualFolderData folderData: m_Config.VirtualFolders)
        {
            folderNames.Insert(folderName);
        }
        return folderNames;
    }
    
    string GetItemFolder(EditorPlaceableItem placeableItem)
    {
        if (!placeableItem)
            return string.Empty;
            
        string itemType = placeableItem.Type;
        string modelPath = placeableItem.GetModelName();
        string itemPath = placeableItem.Path;
        
        foreach (string folderName, EditorVirtualFolderData folderData: m_Config.VirtualFolders)
        {
            if (folderData.ContainsItemByData(itemType, modelPath, itemPath))
                return folderName;
        }
        
        return string.Empty;
    }
    
    bool AddItemToFolder(EditorPlaceableItem placeableItem, string folderName, int addType)
    {
        if (!placeableItem || folderName == string.Empty)
            return false;
            
        EditorVirtualFolderData folderData = GetFolder(folderName);
        if (!folderData)
            return false;
        
        bool success = false;
        switch (addType)
        {
            case 0: // Class Name
                success = folderData.AddClassName(placeableItem.Type);
                break;
            case 1: // Model Path
                success = folderData.AddModelPath(placeableItem.GetModelName());
                break;
            case 2: // Root Folder
                success = folderData.AddRootFolder(placeableItem.Path);
                break;
        }
        
        if (success)
        {
            m_LastUsedFolder = folderName;
            m_Config.Save();
            return true;
        }
        
        return false;
    }
    
    bool RemoveItemFromFolder(EditorPlaceableItem placeableItem)
    {
        if (!placeableItem)
            return false;
            
        string folderName = GetItemFolder(placeableItem);
        if (folderName == string.Empty)
            return false;
            
        EditorVirtualFolderData folderData = GetFolder(folderName);
        if (!folderData)
            return false;
        
        bool success = false;
        string itemType = placeableItem.Type;
        string modelPath = placeableItem.GetModelName();
        string itemPath = placeableItem.Path;
        
        // Try to remove from all possible categories
        if (folderData.ContainsClassName(itemType))
            success = folderData.RemoveClassName(itemType) || success;
        if (folderData.ContainsModelPath(modelPath))
            success = folderData.RemoveModelPath(modelPath) || success;
        if (folderData.ContainsRootFolder(itemPath))
            success = folderData.RemoveRootFolder(itemPath) || success;
        
        if (success)
        {
            m_Config.Save();
            return true;
        }
        
        return false;
    }
    
    bool AddRootFolderToFolder(string rootFolderPath, string virtualFolderName)
    {
        if (!rootFolderPath || !virtualFolderName)
            return false;
            
        EditorVirtualFolderData folderData = GetFolder(virtualFolderName);
        if (!folderData)
            return false;
            
        if (folderData.AddRootFolder(rootFolderPath))
        {
            m_LastUsedFolder = virtualFolderName;
            m_Config.Save();
            return true;
        }
        
        return false;
    }
    
    array<ref EditorPlaceableItem> GetItemsInFolder(string virtualFolderName)
    {
        array<ref EditorPlaceableItem> folderItems = new array<ref EditorPlaceableItem>();
        
        if (!virtualFolderName)
            return folderItems;
            
        EditorVirtualFolderData folderData = GetFolder(virtualFolderName);
        if (!folderData)
            return folderItems;
        
        // Get all placeable objects and filter for this virtual folder
        EditorObjectManagerModule objectManager = GetEditor().GetObjectManager();
        if (!objectManager)
            return folderItems;
            
        array<ref EditorPlaceableItem> allPlaceableObjects = objectManager.GetPlaceableObjects();
        
        foreach (EditorPlaceableItem placeableItem: allPlaceableObjects)
        {
            if (folderData.ContainsItemByData(placeableItem.Type, placeableItem.GetModelName(), placeableItem.Path))
            {
                folderItems.Insert(placeableItem);
            }
        }
        
        return folderItems;
    }
    
    string GetLastUsedFolder()
    {
        return m_LastUsedFolder;
    }
    
    bool HasLastUsedFolder()
    {
        return m_LastUsedFolder != string.Empty && m_Config.VirtualFolders.Contains(m_LastUsedFolder);
    }
    
    bool AddItemToLastUsedFolder(EditorPlaceableItem placeableItem, int addType = 0)
    {
        if (!HasLastUsedFolder())
            return false;
            
        return AddItemToFolder(placeableItem, m_LastUsedFolder, addType);
    }
}