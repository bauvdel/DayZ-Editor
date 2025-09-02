#ifndef COMPONENT_SYSTEM
[RegisterEditorCommand(EditorToggleBatchModeCommand)]
#endif
class EditorToggleBatchModeCommand: EditorCommand
{
    protected override bool Execute(Class sender, CommandArgs args)
    {
        super.Execute(sender, args);
        
        EditorVirtualFolderManager manager = EditorVirtualFolderManager.GetInstance();
        manager.ToggleBatchMode();
        
        // Show notification to user
        EditorHud hud = GetEditor().GetEditorHud();
        if (hud)
        {
            string message;
            if (manager.IsBatchMode())
            {
                message = "Virtual Folder Batch Mode: ON - UI refreshes disabled for faster bulk operations";
            }
            else
            {
                message = "Virtual Folder Batch Mode: OFF - UI refreshed with all changes";
            }
            hud.CreateNotification(message);
        }
        
        return true;
    }
    
    override string GetName()
    {
        return "Batch Mode";
    }
    
    override string GetIcon()
    {
        return "set:solid image:layers";
    }
    
    override LinearColor GetColor()
    {
        return LinearColor.YELLOW;
    }
    
    override bool IsToggled()
    {
        return EditorVirtualFolderManager.GetInstance().IsBatchMode();
    }
    
    override bool CanExecute()
    {
        return true;
    }
}