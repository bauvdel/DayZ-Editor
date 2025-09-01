class EditorVirtualFolderData
{
    string Name;
    ref array<string> ClassNames = new array<string>();      // types
    ref array<string> ModelPaths = new array<string>();      // .p3d files with paths
    ref array<string> RootFolders = new array<string>();     // entire root folders (prefix)
    
    void EditorVirtualFolderData(string name = "")
    {
        Name = name;
    }
    
    bool AddClassName(string className)
    {
        if (ClassNames.Find(className) == -1)
        {
            ClassNames.Insert(className);
            return true;
        }
        return false;
    }
    
    bool AddModelPath(string modelPath)
    {
        if (ModelPaths.Find(modelPath) == -1)
        {
            ModelPaths.Insert(modelPath);
            return true;
        }
        return false;
    }
    
    bool AddRootFolder(string rootFolder)
    {
        if (RootFolders.Find(rootFolder) == -1)
        {
            RootFolders.Insert(rootFolder);
            return true;
        }
        return false;
    }
    
    bool RemoveClassName(string className)
    {
        int index = ClassNames.Find(className);
        if (index != -1)
        {
            ClassNames.Remove(index);
            return true;
        }
        return false;
    }
    
    bool RemoveModelPath(string modelPath)
    {
        int index = ModelPaths.Find(modelPath);
        if (index != -1)
        {
            ModelPaths.Remove(index);
            return true;
        }
        return false;
    }
    
    bool RemoveRootFolder(string rootFolder)
    {
        int index = RootFolders.Find(rootFolder);
        if (index != -1)
        {
            RootFolders.Remove(index);
            return true;
        }
        return false;
    }
    
    bool ContainsClassName(string className)
    {
        return ClassNames.Find(className) != -1;
    }
    
    bool ContainsModelPath(string modelPath)
    {
        return ModelPaths.Find(modelPath) != -1;
    }
    
    bool ContainsRootFolder(string rootFolder)
    {
        return RootFolders.Find(rootFolder) != -1;
    }
    
    bool ContainsItemByData(string itemType, string modelPath, string itemPath)
    {
        // Check if item's type is in class names
        if (ContainsClassName(itemType))
            return true;
            
        // Check if item's model path is in model paths
        if (modelPath != string.Empty && ContainsModelPath(modelPath))
            return true;
            
        // Check if item belongs to any of the root folders
        
        foreach (string rootFolder: RootFolders)
        {
            // Normalize root folder path separators (both forward and backslash versions)
            string normalizedRootFolder = rootFolder;
            normalizedRootFolder.ToLower();
            string backslashRootFolder = rootFolder;
            backslashRootFolder.Replace("/", "\\");
            backslashRootFolder.ToLower();
            
            // Check both itemPath (config path) and modelPath (file path) for root folder matching
            if (itemPath != string.Empty)
            {
                string lowerItemPath = itemPath;
                lowerItemPath.ToLower();
                if (lowerItemPath.Contains(normalizedRootFolder) || lowerItemPath.Contains(backslashRootFolder))
                {
                    return true;
                }
            }
                
            if (modelPath != string.Empty)
            {
                string lowerModelPath = modelPath;
                lowerModelPath.ToLower();
                if (lowerModelPath.Contains(normalizedRootFolder) || lowerModelPath.Contains(backslashRootFolder))
                {
                    return true;
                }
            }
                
            // Also check if the item type contains the root folder (for p3d files)
            if (itemType != string.Empty)
            {
                string lowerItemType = itemType;
                lowerItemType.ToLower();
                if (lowerItemType.Contains(normalizedRootFolder) || lowerItemType.Contains(backslashRootFolder))
                {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    bool IsEmpty()
    {
        return ClassNames.Count() == 0 && ModelPaths.Count() == 0 && RootFolders.Count() == 0;
    }
    
    void Clear()
    {
        ClassNames.Clear();
        ModelPaths.Clear();
        RootFolders.Clear();
    }
}