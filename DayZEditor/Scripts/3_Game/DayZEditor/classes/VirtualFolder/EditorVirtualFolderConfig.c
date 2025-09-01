class EditorVirtualFolderConfig
{
    // Config constants
    // static const bool LOAD_ON_SERVER = true;
    // static const bool LOAD_ON_CLIENT = true;
    
    // Config location
    static const string FOLDER = "$saves:Editor/VirtualFolders";
    static const string FILENAME = "VirtualFolders.json";
    static const string CURRENT_VERSION = "1";
    
    // Config data
    ref map<string, ref EditorVirtualFolderData> VirtualFolders;
    
    void EditorVirtualFolderConfig()
    {
        VirtualFolders = new map<string, ref EditorVirtualFolderData>();
    }
    
    void Load()
    {
        string path = FOLDER + "/" + FILENAME;
        
        SetDefaultValues();
        
        /*if (GetGame().IsClient() && !LOAD_ON_CLIENT)
            return;
            
        if (GetGame().IsDedicatedServer() && !LOAD_ON_SERVER)
            return;
        */
        if (!FileExist(path))
        {
            EditorLog.Info("Virtual Folders config file does not exist, creating default");
            Save();
            return;
        }
        
        JsonFileLoader<EditorVirtualFolderConfig>.JsonLoadFile(path, this);
    }
    
    void Save()
    {
        string path = FOLDER + "/" + FILENAME;
        
        if (!FileExist(FOLDER))
        {
            MakeDirectory(FOLDER);
        }
        
        JsonFileLoader<EditorVirtualFolderConfig>.JsonSaveFile(path, this);
    }
    
    void SetDefaultValues()
    {
        if (!VirtualFolders)
        {
            VirtualFolders = new map<string, ref EditorVirtualFolderData>();
        }
    }
}

static EditorVirtualFolderConfig GetEditorVirtualFolderConfig()
{
    if (!m_EditorVirtualFolderConfig)
    {
        m_EditorVirtualFolderConfig = new EditorVirtualFolderConfig();
        m_EditorVirtualFolderConfig.Load();
    }
    
    return m_EditorVirtualFolderConfig;
}

ref EditorVirtualFolderConfig m_EditorVirtualFolderConfig;