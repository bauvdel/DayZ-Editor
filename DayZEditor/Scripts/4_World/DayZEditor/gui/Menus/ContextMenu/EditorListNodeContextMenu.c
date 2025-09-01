class EditorListNodeContextMenu: EditorContextMenu
{
	void EditorListNodeContextMenu(float x, float y, notnull EditorListNode context)
	{
		m_Editor.CommandManager[EditorExpandAllCommand].SetData(new Param1<EditorListNode>(context));
		m_Editor.CommandManager[EditorCollapseAllCommand].SetData(new Param1<EditorListNode>(context));
		
		AddMenuButton(m_Editor.CommandManager[EditorExpandAllCommand]);
		AddMenuButton(m_Editor.CommandManager[EditorCollapseAllCommand]);
		
		if (!context.IsInherited(EditorVirtualFolderListNode))
		{
			EditorCommand addRootCmd = m_Editor.CommandManager.Get(EditorAddRootFolderToVirtualCommand);
			if (!addRootCmd) {
				addRootCmd = m_Editor.CommandManager.RegisterCommand(EditorAddRootFolderToVirtualCommand);
			}
			addRootCmd.SetData(new Param1<EditorListNode>(context));
			
			AddMenuDivider();
			AddMenuButton(addRootCmd);
		}
		else
		{
			EditorVirtualFolderListNode virtualFolderNode = EditorVirtualFolderListNode.Cast(context);
			if (virtualFolderNode)
			{
				AddMenuDivider();
				
				m_Editor.CommandManager[EditorDeleteVirtualFolderCommand].SetData(new Param1<EditorVirtualFolderListNode>(virtualFolderNode));
				AddMenuButton(m_Editor.CommandManager[EditorDeleteVirtualFolderCommand]);
			}
		}
	}
}