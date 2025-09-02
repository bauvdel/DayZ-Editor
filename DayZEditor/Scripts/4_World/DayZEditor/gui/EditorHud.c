enum SelectionMode
{
	BOX,
	ELLIPSE,
	LASSO // ???? are you CRAZY?
};

class EditorCameraMarker: ScriptView
{
	Widget IconFrame;
	TextWidget Text;
	vector WorldPosition, WorldOrientation;
	
	void EditorCameraMarker(string text)
	{
		Text.SetText(text);
	}
	
	override void Update(float dt)
	{
		MapWidget map_widget = GetEditor().GetEditorHud().Map;
		if (!map_widget.IsVisible()) {
			m_LayoutRoot.Show(false);
			return;
		}
		
		m_LayoutRoot.Show(true);

		// Camera yaw matrix
		vector map_to_screen_cam = map_widget.MapToScreen(WorldPosition);
		float c_s_x, c_s_y;
		IconFrame.GetScreenSize(c_s_x, c_s_y);
		m_LayoutRoot.SetScreenPos(map_to_screen_cam[0] - c_s_x / 2, map_to_screen_cam[1] - c_s_y / 2);
		
		float camera_yaw = WorldOrientation[0];
		IconFrame.SetRotation(0, 0, camera_yaw - 90);		
	}
	
	override string GetLayoutFile()
	{
		return "DayZEditor\\GUI\\layouts\\EditorCameraMarker.layout";
	}
}

class EditorHud: ScriptView
{
	const float DEFAULT_BAR_WIDTH_PX = 380.0;

	const float BAR_WIDTH_MINIMUM_PX = 100.0;
	const float BAR_WIDTH_MAXIMUM_PX = 900.0;

	protected Editor m_Editor;
	protected bool m_IsBoxSelectActive;
	protected EditorHudController m_TemplateController;
	
	// Layout Elements
	Widget LoggerFrame;

	Widget LeftbarWrapper, RightbarWrapper;
	Widget LeftbarDrag, RightbarDrag;
	Widget LeftbarDrag0, RightbarDrag0;
	ScrollWidget RightbarScroll, LeftbarScroll;
	
	Widget RightbarCollapsePanel, LeftbarCollapsePanel;

	Widget NotificationPanel;
	TextWidget NotificationText;

	protected LinearColor m_MenuColor, m_ToolbarColor;
	protected Widget m_DragWidget;
	protected int m_DragBoxStartX = -1, m_DragBoxStartY = -1;
	protected float m_DragBoxDelayStart;
	protected SelectionMode m_SelectionMode;
	protected bool m_ObjectSelectToggle;
	protected vector m_DragOffset, m_MapPosition;
	protected float m_MapScale = 1.0, m_ScaleActual = 1.0;
	protected float m_ScaleVelocity[1];
	protected bool m_IsVisible = true;
	protected bool m_SearchBarDirty;
	
	// Folder collapse tracking
	protected int m_CollapseIteration;
	protected int m_CollapseMaxIterations;
	protected bool m_SuppressFolderCollapse;
	
	Widget Menubar, ToolsWrapper, InfobarFrame, ToolbarFrame;
	Widget LeftbarCategoryConfig, LeftbarCategoryStatic, SearchFavoriteTabPanel;
	Widget CameraPanel;
	Widget LeftbarPanelSearchBarPanel, RightPanelSearchBarPanel, TabPanel;
		
	CanvasWidget EditorCanvas;
	MapWidget Map;
	ButtonWidget CameraPanelButton, PlayerTabButton;
	ButtonWidget CameraTrackPreviousButton, CameraTrackRunButton, CameraTrackNextButton, CameraTrackStopButton, CameraTrackRecordButton; 
	ImageWidget CameraTrackPreviousButton_Icon, CameraTrackRunButton_Icon, CameraTrackNextButton_Icon, CameraTrackStopButton_Icon, CameraTrackRecordButton_Icon;

	EditBoxWidget LeftSearchBar, RightSearchBar;
	Widget LeftSearchBarIcon, RightSearchBarIcon;
	ImageWidget LeftSearchBarIconIcon, RightSearchBarIconIcon;
	TextWidget CameraSpeed, ObjectHoverSelectObjectReadout;	
	
	// Brush info new
	ButtonWidget BrushLeft, BrushRight;
	ImageWidget BrushLeft_Icon, BrushRight_Icon;
	Widget BrushToggle, BrushRadiusFrame, BrushDensityFrame, BrushWidthFrame, CinematicCameraButton;
	TextWidget BrushText, BrushRadiusText, BrushDensityText, BrushWidthText;
	
	Widget ChatBox;
	EditBoxWidget InputEditBoxWidget;
	Widget ChatFrameWidget;
	EditBoxWidget InfoBar_X_Value, InfoBar_Y_Value, InfoBar_Z_Value;
	protected ref EditorChat m_Chat;
	
	protected int m_CurrentBrushIndex = 0, m_BrushState = 0;
	protected ref array<ref EditorBrushData> m_BrushTypes = {};
	protected EditorSettings m_EditorSettings;

	protected ref array<vector> m_LassoHistory = {};
	
	protected ref EditorCameraMarker m_EditorCameraMarker;
	
	static const ref array<string> ThemedWidgetStrings = {
		"LeftbarPanelSearchBarIconButton",
		"FavoritesTabButton",
		"ShowPrivateButton",
		"LeftbarCategoryStatic",
		"LeftbarCategoryConfig",
		"DeletionsTabButton",
		"PlacementsTabButton",
		"PlacedSearchIconButton",
		"MenuBarFile",
		"MenuBarEdit",
		"MenuBarView",
		"MenuBarEditor",
		"BrushToggleButton",
		"CinematicCameraButton",
		"CameraTrackMinimizeButton",
		"AddNodeButton",
		"CameraTrackRunButton"
	};
	
	protected ref map<string, EditorListNode> m_FolderNodes = new map<string, EditorListNode>();		
	protected ref map<int, ref array<EditorListNode>> m_FolderNodesByDepth = new map<int, ref array<EditorListNode>>();		
	protected ref array<EditorListNode> m_SearchableListNodes = {};
	protected ref array<ref EditorVirtualFolderListNode> m_VirtualFolderNodes = {};
	protected ref EditorFolderListNode m_VirtualFoldersRoot;
	
	void EditorHud(notnull Editor editor)
	{	
		m_Editor = editor;
		m_EditorSettings = m_Editor.GetSettings();
		
		Map.Show(false);
		
		m_TemplateController = EditorHudController.Cast(m_Controller);
		
		m_MenuColor = Menubar.GetColor();
		m_ToolbarColor = ToolsWrapper.GetColor();
		
		// Load Placeable Items
#ifndef COMPONENT_SYSTEM		
		int item_size = m_EditorSettings.ListItemSize;
		array<ref EditorPlaceableItem> placeable_items = m_Editor.GetPlaceableObjects();
			
		foreach (EditorPlaceableItem placeable_item: placeable_items) {		
			
			//PrintFormat("%3] %1: %2", placeable_item.Type, model_name, placeable_item.ConsoleFriendly);

			if (m_EditorSettings.ConsoleMode && !placeable_item.ConsoleFriendly) {
				continue;
			}
			
			// Skip items that will be in virtual folders during initial tree building
			EditorVirtualFolderManager folderManager = EditorVirtualFolderManager.GetInstance();
			string virtualFolderName = folderManager.GetItemFolder(placeable_item);
			if (virtualFolderName != string.Empty) {
				continue;
			}
			
			string model_name = placeable_item.GetModelName();
			model_name.Replace(SystemPath.SEPERATOR_ALT, SystemPath.SEPERATOR);
			model_name.ToLower();
			model_name.TrimInPlace();
			if (model_name == "bmp" || model_name == "bmp.p3d" || model_name.Length() == 0) {
				continue;
			}
			
			if (model_name[0] == SystemPath.SEPERATOR) {
				model_name = model_name.Substring(1, model_name.Length() - 1);
			}
						
			array<string> model_path_split = {};
			model_name.Split(SystemPath.SEPERATOR, model_path_split);
			int depth = model_path_split.Count() - 1;
			for (int i = 0; i < model_path_split.Count(); i++) {
				string folder_name = model_path_split[i];
				string full_path = string.Empty;
				for (int j = 0; j <= i; j++) {
					full_path += model_path_split[j];
					if (j != i) {
						full_path += SystemPath.SEPERATOR;
					}
				}
												
				if (i < model_path_split.Count() - 1) {
					EditorFolderListNode folder_node;
					if (m_FolderNodes.Contains(full_path)) {
						folder_node = m_FolderNodes[full_path];
					} else {
						folder_node = new EditorFolderListNode(folder_name);
						m_FolderNodes[full_path] = folder_node;
						
						if (!m_FolderNodesByDepth[i]) {
							m_FolderNodesByDepth[i] = {};
						}
						
						//PrintFormat("%1: %2", full_path, i);
						m_FolderNodesByDepth[i].Insert(folder_node);
							
						if (i == 0) {
							m_TemplateController.LeftContent.Insert(folder_node);
						} else {
							string directory_parent = full_path.Substring(0, full_path.LastIndexOf(SystemPath.SEPERATOR));
							EditorFolderListNode parent_node = m_FolderNodes[directory_parent];
							if (parent_node) {
								parent_node.InsertChild(folder_node);
							}
						}
					}				
				}				
			}
			
			string model_directory = model_name.Substring(0, model_name.LastIndexOf(SystemPath.SEPERATOR));
			EditorPlaceableListNode placeable_node = new EditorPlaceableListNode(placeable_item);
			m_FolderNodes[model_name] = placeable_node;
			m_FolderNodes[model_directory].InsertChild(placeable_node);		
			
			if (!m_FolderNodesByDepth[depth]) {
				m_FolderNodesByDepth[depth] = {};
			}	
			
			m_FolderNodesByDepth[depth].Insert(placeable_node);
			m_SearchableListNodes.Insert(placeable_node);
		}
		
		EditorLog.Info("Loaded %1 Placeable Objects", placeable_items.Count().ToString());
		
		// Load Virtual Folders
		LoadVirtualFolders();
		
		SearchFavoriteTabPanel.SetColor(m_ToolbarColor);
		
		foreach (string themed_widget_name: ThemedWidgetStrings) {
			Widget themed_widget = m_LayoutRoot.FindAnyWidget(themed_widget_name);
			if (themed_widget) {
				themed_widget.SetColor(m_EditorSettings.SelectionColor);
			}
		}

		// Load Brushes
		ReloadBrushes(m_EditorSettings.BrushFile);
#endif		
		
		if (GetGame().IsMultiplayer()) {
			m_Chat = new EditorChat();
			m_Chat.Init(ChatFrameWidget);
			
			PlayerTabButton.Show(true);
			
			PlayerIdentity identity = GetGame().GetPlayer().GetIdentity();
			m_TemplateController.RightbarPlayerData.Insert(new EditorPlayerListItem(identity.GetPlayerId(), identity.GetName()));
		}
	
		m_TemplateController.ShowPrivate = m_EditorSettings.ShowScopeZeroObjects;
		m_TemplateController.NotifyPropertyChanged("ShowPrivate");

		m_TemplateController.FavoritesToggle = m_EditorSettings.ShowFavoriteObjects;
		m_TemplateController.NotifyPropertyChanged("FavoritesToggle");
		
		EditorCamera camera = m_Editor.GetCamera();
		m_TemplateController.CameraControls.Insert(new SliderPrefab("FOV", camera, "FOV", EditorCamera.FOV_MIN * Math.RAD2DEG, EditorCamera.FOV_MAX * Math.RAD2DEG));
		m_TemplateController.CameraControls.Insert(new SliderPrefab("Tilt", camera, "Tilt", -90, 90));
		m_TemplateController.CameraControls.Insert(new SliderPrefab("View Distance", GetEditor().GetCameraSettings(), "ViewDistance", EditorCamera.VIEW_DISTANCE_MIN, EditorCamera.VIEW_DISTANCE_MAX));
		m_TemplateController.CameraControls.Insert(new SliderPrefab("Gaussian Blur", camera, "Blur", 0, 1));
		m_TemplateController.CameraControls.Insert(new SliderPrefab("Near Plane", camera, "NearPlane",  0, 1));
		m_TemplateController.CameraControls.Insert(new SliderPrefab("DOF Distance", camera, "DOFDistance", 0, 500));
		m_TemplateController.CameraControls.Insert(new SliderPrefab("DOF Blur", camera, "DOFBlur", 0, 1));
		m_TemplateController.CameraControls.Insert(new SliderPrefab("Vignette", camera, "Vignette", 0, 1));
		m_TemplateController.CameraControls.Insert(new SliderPrefab("Sharpness", camera, "Sharpness", 0, 1));
		m_TemplateController.CameraControls.Insert(new SliderPrefab("Exposure", camera, "Exposure", 0, 3));
		m_TemplateController.CameraControls.Insert(new SliderPrefab("Smoothing", camera, "Smoothing", 0, 1));
								
		// Set up toolbars based on screen size
		int screen_w, screen_h;
		GetScreenSize(screen_w, screen_h);
		
		float tb_s_w, tb_s_h;
		ToolbarFrame.GetScreenSize(tb_s_w, tb_s_h);
		
		float ib_s_w, ib_s_h;
		InfobarFrame.GetScreenSize(ib_s_w, ib_s_h);
		
		float lbw_s_w, lbw_s_h;
		float rbw_s_w, rbw_s_h;
		LeftbarWrapper.GetScreenSize(lbw_s_w, lbw_s_h);
		RightbarWrapper.GetScreenSize(rbw_s_w, rbw_s_h);
		
		float bar_height = screen_h - ib_s_h - tb_s_h;
		LeftbarWrapper.SetScreenSize(m_EditorSettings.LeftBarPlacement, bar_height);
		RightbarWrapper.SetScreenSize(m_EditorSettings.RightBarPlacement, bar_height);
		
		// Leftbar scroll size
		float lbs_s_w, lbs_s_h;
		float lpsbp_s_w, lpsbp_s_h, sftp_s_w, sftp_s_h;
		LeftbarPanelSearchBarPanel.GetScreenSize(lpsbp_s_w, lpsbp_s_h);
		SearchFavoriteTabPanel.GetScreenSize(sftp_s_w, sftp_s_h);
		LeftbarScroll.GetScreenSize(lbs_s_w, lbs_s_h);
		LeftbarScroll.SetScreenSize(lbs_s_w, bar_height - sftp_s_h - lpsbp_s_h);
		
		// Rightbar scroll size
		float tp_s_w, tp_s_h, rpsbp_s_h, rpsbp_s_w, rbs_s_w, rbs_s_h;
		TabPanel.GetScreenSize(tp_s_w, tp_s_h);
		RightPanelSearchBarPanel.GetScreenSize(rpsbp_s_w, rpsbp_s_h);
		RightbarScroll.GetScreenSize(rbs_s_w, rbs_s_h);
		RightbarScroll.SetScreenSize(rbs_s_w, bar_height - tp_s_h - rpsbp_s_h);

		// Too many requests. It wont work fully but ill get the rest in later
		CinematicCameraButton.Show(true);
		
		m_EditorCameraMarker = new EditorCameraMarker(GetGame().GetUserManager().GetSelectedUser().GetName());
	}
	
	override void Update(float dt)
	{
		super.Update(dt);
		
		if (!GetGame().IsAppActive()) {
			m_DragWidget = null;
			m_DragBoxDelayStart = 10;
			m_DragBoxStartX = -1;
			m_DragBoxStartY = -1;
			Map.ClearFlags(WidgetFlags.IGNOREPOINTER);
			return;
		}
		
		if (GetGame().GetUIManager().GetMenu()) {
			m_LayoutRoot.Show(false);
			return;
		}
		
		if (GetGame().GetMission().IsPaused()) {
			ShowCursor(true);
			return;
		}		
		
		int mouse_x, mouse_y;
		GetMousePos(mouse_x, mouse_y);

		int screen_x, screen_y;
		GetScreenSize(screen_x, screen_y);

		UAInputAPI input_api = GetUApi();
		UAInput left_mouse_input = input_api.GetInputByID(UAMenuSelect);
		UAInput right_mouse_input = input_api.GetInputByID(UAMenuBack);
		UAInput toggle_hud_input = input_api.GetInputByName("EditorToggleUI");
		UAInput toggle_cursor = input_api.GetInputByName("EditorToggleCursor");
		UAInput toggle_editor = input_api.GetInputByName("EditorToggleActive");
		UAInput teleport_to_cursor = input_api.GetInputByName("EditorTeleportPlayerToCursor");
		UAInput toggle_map = input_api.GetInputByName("EditorToggleMap");
		UAInput zoom_up = input_api.GetInputByID(UAZoomInOptics);
		UAInput zoom_down = input_api.GetInputByID(UAZoomOutOptics);
		UAInput shift_input = input_api.GetInputByID(UATurbo);
		UAInput chat_input = input_api.GetInputByID(UAChat);
		
		Widget widget_under_cursor = GetWidgetUnderCursor();
		bool useful_widget_under_cursor = widget_under_cursor && widget_under_cursor.GetName() != "HudPanel" && widget_under_cursor.GetName() != "CursorIcons";
		Widget focus_widget = GetFocus();
		bool cursor_visible = GetGame().GetUIManager().IsCursorVisible();
		bool input_unlocked = (!focus_widget || !focus_widget.IsInherited(EditBoxWidget)) && !m_Dialog;
		bool any_mouse_press = (left_mouse_input.LocalPress() || right_mouse_input.LocalPress());

		if (m_Editor.IsInventoryEditorActive()) {
			m_LayoutRoot.Show(false);
			return;
		}
		
		if (toggle_map.LocalPress() && input_unlocked && m_LayoutRoot.IsVisible()) {
			Map.Show(!Map.IsVisible());
			Map.SetMapPos(GetGame().GetCurrentCameraPosition());
			ShowCursor(true);
		
			EditorEvents.MapToggled(this, Map, Map.IsVisible());
			return;
		}
		
		if (!m_LayoutRoot.IsVisible() && Map.IsVisible()) {
			Map.Show(false);
			EditorEvents.MapToggled(this, Map, Map.IsVisible());
			return;
		}
		
		if (Map.IsVisible()) {
			GetGame().GetUIManager().ShowCursor(true);
		}
		
		if (any_mouse_press && !useful_widget_under_cursor) {
			SetFocus(null);
		}
		
		if (Map.IsVisible()) {
			UpdateMap(Map, dt);
		}
				
#ifdef GIZMOS_ENABLED
		
		// todo: a cursor hide mask
		//if (m_Editor.GetGizmo() && m_Editor.GetGizmo().IsInteracting()) {
		//	ShowCursor(false);
		//	return;
		//}
#endif
		
		// lctrl for commands
		if (toggle_editor.LocalPress() && !GetDayZGame().IsLeftCtrlDown() && input_unlocked) {
			// Control current player
			if (m_Editor.IsActive()) {
				m_Editor.ControlPlayer(m_Editor.GetPlayer());
			} else {
				m_Editor.Activate();
			}
		}
		
		if (toggle_hud_input.LocalPress() && input_unlocked && !GetDayZGame().IsLeftCtrlDown()) {		
			m_IsVisible = !m_IsVisible;
			m_Editor.ClearSelection();
		}
		
		m_LayoutRoot.Show(m_IsVisible);
		
		// Dont want to toggle cursor on map 
		if (toggle_cursor.LocalPress() && input_unlocked) {
			if (!Map.IsVisible() && !m_Editor.IsPlayerControlled() && m_Editor.IsActive() && !(m_Dialog && EditorHud.CurrentDialog && m_EditorSettings.LockCameraDuringDialogs)) {	
				ToggleCursor();
			}
		}
		
		// Teleport the player
		if (teleport_to_cursor.LocalPress() && GetGame().GetUIManager().IsCursorVisible() && !GetDayZGame().IsLeftCtrlDown() && input_unlocked) {
			PlayerBase teleport_player = m_Editor.GetControllingPlayer();
			if (!teleport_player) {
				teleport_player = m_Editor.GetPlayer();
			}
			
			if (teleport_player) {
				Raycast teleport_player_raycast = m_Editor.GetCursorRaycastModeSafe(teleport_player);
				if (teleport_player_raycast) {
					teleport_player.SetPosition(teleport_player_raycast.Bounce.Position);
					
					if (GetGame().IsMultiplayer()) {
						ScriptRPC rpc_teleport = new ScriptRPC();
						rpc_teleport.Write(teleport_player);
						rpc_teleport.Write(teleport_player_raycast.Bounce.Position);
						rpc_teleport.Send(null, 39258, false);
					}
				}
			}
		}

		if (left_mouse_input.LocalPress() && m_DragBoxStartX == -1 && m_DragBoxStartY == -1) {
			if ((!widget_under_cursor || widget_under_cursor == Map) && GetGame().GetInput().HasGameFocus() && cursor_visible && !m_Editor.IsPlacing() && !m_Editor.IsDragging()) {
				m_DragBoxDelayStart = 0.12;
				GetMousePos(m_DragBoxStartX, m_DragBoxStartY);
				m_LassoHistory.Clear();
			}

			Map.SetFlags(WidgetFlags.IGNOREPOINTER);
		}
		
		if (left_mouse_input.LocalRelease() || !GetDayZGame().IsAppActive()) {
			m_DragWidget = null;
			m_DragBoxDelayStart = 10;
			m_DragBoxStartX = -1;
			m_DragBoxStartY = -1;
			Map.ClearFlags(WidgetFlags.IGNOREPOINTER);
		}

		float rs_s_w, rs_s_h;
		RightbarScroll.GetScreenSize(rs_s_w, rs_s_h);
		if (RightbarScroll.GetVScrollPos() + rs_s_h > RightbarScroll.GetContentHeight()) {
			RightbarScroll.VScrollToPos(RightbarScroll.GetContentHeight());
		}

		float ls_s_w, ls_s_h;
		LeftbarScroll.GetScreenSize(ls_s_w, ls_s_h);
		if (LeftbarScroll.GetVScrollPos() + ls_s_h > LeftbarScroll.GetContentHeight()) {
			LeftbarScroll.VScrollToPos(LeftbarScroll.GetContentHeight());
		}
				
		EditorCanvas.Clear();
		m_DragBoxDelayStart -= dt;
		if (left_mouse_input.LocalValue() && m_DragBoxDelayStart < 0 && GetGame().GetInput().HasGameFocus() && cursor_visible && !m_Editor.IsPlacing() && !m_Editor.IsDragging() && !m_Editor.Brush && !m_DragWidget && m_DragBoxStartX != -1 && m_DragBoxStartY != -1 && EditorMarker.s_AllMarkers) {	
			switch (m_SelectionMode) {
				case SelectionMode.LASSO: {
					vector current = Vector(mouse_x, mouse_y, 0);
					if (m_LassoHistory.Count() > 0) {
						vector last = m_LassoHistory[m_LassoHistory.Count() - 1];
						
						if (vector.Distance(last, current) > 4) {
							m_LassoHistory.Insert(current);
						}				
					} else {
						m_LassoHistory.Insert(current);
					}
					
					for (int j = 0; j < m_LassoHistory.Count() - 1; j++) {
						EditorCanvas.DrawLine(m_LassoHistory[j][0], m_LassoHistory[j][1], m_LassoHistory[j + 1][0], m_LassoHistory[j + 1][1], 4, 0xFF4B77BE);
					}
					
					if (m_LassoHistory.Count() > 2) {
						EditorCanvas.DrawLine(m_LassoHistory[0][0], m_LassoHistory[0][1], m_LassoHistory[m_LassoHistory.Count() - 1][0], m_LassoHistory[m_LassoHistory.Count() - 1][1], 2, 0xFF4B77BE);
					}
					
					foreach (EditorMarker marker0: EditorMarker.s_AllMarkers) {
						if (!marker0 || !marker0.GetLayoutRoot().IsVisible()) {
							continue;
						}

						EditorObjectMarker object_marker0 = EditorObjectMarker.Cast(marker0);
						float x_n0, y_n0;
						marker0.GetLayoutRoot().GetScreenPos(x_n0, y_n0);
						if (IsPointInPolygon(x_n0, y_n0, m_LassoHistory)) {
							if (object_marker0 && !object_marker0.GetEditorObject().IsSelected()) {
								m_Editor.SelectObject(object_marker0.GetEditorObject());
							}
						} else {
							if (object_marker0 && object_marker0.GetEditorObject().IsSelected() && !shift_input.LocalValue()) {
								m_Editor.DeselectObject(object_marker0.GetEditorObject());
							}
						}
					}
					
					break;
				}
				
				case SelectionMode.BOX: {
			
					// Rectangle
					int x_avg = (m_DragBoxStartX + mouse_x) / 2;
					int y_avg = (m_DragBoxStartY + mouse_y) / 2;
					EditorCanvas.DrawLine(x_avg, m_DragBoxStartY, x_avg, mouse_y, mouse_x - m_DragBoxStartX, 0x644B77BE);		
					
					foreach (EditorMarker marker: EditorMarker.s_AllMarkers) {
						if (!marker || !marker.GetLayoutRoot() || !marker.GetLayoutRoot().IsVisible()) {
							continue;
						}
						
						EditorObjectMarker object_marker = EditorObjectMarker.Cast(marker);
						
						float x_n, y_n;
						marker.GetLayoutRoot().GetScreenPos(x_n, y_n);
						//if (top_left[0] <= m_screen_x && m_screen_x <= bottom_right[0] && top_left[1] <= m_screen_y && m_screen_y <= bottom_right[1]) {
						if ((x_n < Math.Max(m_DragBoxStartX, mouse_x) && x_n > Math.Min(m_DragBoxStartX, mouse_x)) && (y_n < Math.Max(m_DragBoxStartY, mouse_y) && y_n > Math.Min(m_DragBoxStartY, mouse_y))) {
							if (object_marker && !object_marker.GetEditorObject().IsSelected()) {
								m_Editor.SelectObject(object_marker.GetEditorObject());
							}
						} else {
							if (object_marker && object_marker.GetEditorObject().IsSelected() && !shift_input.LocalValue()) {
								m_Editor.DeselectObject(object_marker.GetEditorObject());
							}
						}
					}
					
					break;
				}
				
				case SelectionMode.ELLIPSE: {
					int x1 = Math.Min(mouse_x, m_DragBoxStartX);
					int x2 = Math.Max(mouse_x, m_DragBoxStartX);
					int y1 = Math.Min(mouse_y, m_DragBoxStartY);
					int y2 = Math.Max(mouse_y, m_DragBoxStartY);

					// Calculate dimensions
					float width = x2 - x1;
					float height = y2 - y1;

					// Get center point
					float center_x = (x1 + x2) / 2.0;
					float center_y = (y1 + y2) / 2.0;

					float abs_height = Math.AbsFloat(height);
					float abs_width = Math.AbsFloat(width);
					if (abs_width == 0 || abs_height == 0) {
						break;
					}

					float lineThickness = 0.5;

					// Scan from top to bottom of the ellipse
					for (float y = -abs_height/2; y <= (abs_height/2); y += lineThickness) {
						// For each y, calculate the x coordinates where we intersect the ellipse
						// Using the equation: x = ±(width/2)*sqrt(1 - (y/(height/2))²)
						float term = 1.0 - Math.Pow(y / (abs_height / 2), 2);
						if (term >= 0) {
							float x = (abs_width/2) * Math.Sqrt(term);
							
							// Draw a horizontal line from -x to +x at this y coordinate
							EditorCanvas.DrawLine(center_x - x, center_y + y, center_x + x, center_y + y, lineThickness, 0x644B77BE);
						}
					}

					foreach (EditorMarker marker2: EditorMarker.s_AllMarkers) {
						if (!marker2 || !marker2.GetLayoutRoot().IsVisible()) {
							continue;
						}
						
						EditorObjectMarker object_marker2 = EditorObjectMarker.Cast(marker2);
						
						float x_n2, y_n2;
						marker2.GetLayoutRoot().GetScreenPos(x_n2, y_n2);
						float relative_x = x_n2 - center_x;
						float relative_y = y_n2 - center_y;
						float test = (relative_x * relative_x)/((abs_width/2) * (abs_width/2)) + (relative_y * relative_y)/((abs_height/2) * (abs_height/2));
						if (test <= 1.0) {
							if (object_marker2 && !object_marker2.GetEditorObject().IsSelected()) {
								m_Editor.SelectObject(object_marker2.GetEditorObject());
							}
						} else {
							if (object_marker2 && object_marker2.GetEditorObject().IsSelected() && !shift_input.LocalValue()) {
								m_Editor.DeselectObject(object_marker2.GetEditorObject());
							}
						}
					}
					
					break;
				}
			}
		}
		
		float lb_d_s_x, lb_d_s_y;
		LeftbarDrag.GetScreenPos(lb_d_s_x, lb_d_s_y);
		if (ChatBox) {
			ChatBox.SetScreenPos(lb_d_s_x + 12, screen_y / 4);
			ChatBox.Show(true);
		}
		
		if (chat_input.LocalPress() && GetFocus() != InputEditBoxWidget && GetGame().IsMultiplayer()) {
			InputEditBoxWidget.Show(true);
			SetFocus(InputEditBoxWidget);
		}

		bool is_curtain_open = m_TemplateController.LeftbarFrame.IsVisible() || m_TemplateController.RightbarFrame.IsVisible();
		if (input_api.GetInputByID(UAGear).LocalPress()) {
			m_TemplateController.LeftbarFrame.Show(!is_curtain_open);
			m_TemplateController.RightbarFrame.Show(!is_curtain_open);
		}

		float wr_s_w, wr_s_h, wr_col_s_w, wr_col_s_h;
		switch (widget_under_cursor) {
			case LeftbarDrag: {
				if (left_mouse_input.LocalPress()) {
					m_DragWidget = LeftbarWrapper;
				}
				
				if (left_mouse_input.LocalDoubleClick()) {
					LeftbarWrapper.GetSize(wr_s_w, wr_s_h);
					LeftbarWrapper.SetSize(DEFAULT_BAR_WIDTH_PX, wr_s_h);
				}
				
				break;
			}

			case RightbarDrag: {
				if (left_mouse_input.LocalPress()) {
					m_DragWidget = RightbarWrapper;
				}

				if (left_mouse_input.LocalDoubleClick()) {
					RightbarWrapper.GetSize(wr_s_w, wr_s_h);
					RightbarWrapper.SetSize(DEFAULT_BAR_WIDTH_PX, wr_s_h);
				}

				break;
			}
		}
		
		m_LayoutRoot.FindAnyWidget("LeftbarFiller").SetColor(LinearColor.Create(180, 0, 0, 0));
		LeftbarScroll.SetColor(LinearColor.Create(255, 255, 255, 255));
		
		if (m_DragWidget) {
			switch (m_DragWidget) {
				case LeftbarWrapper: {
					LeftbarDrag0.SetColor(LinearColor.SLATE_BLUE);
					LeftbarCollapsePanel.GetScreenSize(wr_col_s_w, wr_col_s_h);
					LeftbarWrapper.GetScreenSize(wr_s_w, wr_s_h);
					float LeftWidth = Math.Clamp(mouse_x + wr_col_s_w + 25, BAR_WIDTH_MINIMUM_PX, BAR_WIDTH_MAXIMUM_PX);
					LeftbarWrapper.SetScreenSize(LeftWidth, wr_s_h);
					m_EditorSettings.LeftBarPlacement = LeftWidth;
					break;
				}

				case RightbarWrapper: {
					RightbarDrag0.SetColor(LinearColor.SLATE_BLUE);
					RightbarCollapsePanel.GetScreenSize(wr_col_s_w, wr_col_s_h);
					RightbarWrapper.GetScreenSize(wr_s_w, wr_s_h);
					float RightWidth = Math.Clamp(screen_x - mouse_x + wr_col_s_w + 25, BAR_WIDTH_MINIMUM_PX, BAR_WIDTH_MAXIMUM_PX);
					RightbarWrapper.SetScreenSize(RightWidth, wr_s_h);
					m_EditorSettings.RightBarPlacement = RightWidth;
					break;
				}
			}			
									
		} else {
			if (widget_under_cursor == LeftbarDrag || widget_under_cursor == RightbarDrag) {
				widget_under_cursor.GetChildren().SetColor(LinearColor.LIGHT_GRAY);
			} else {
				LeftbarDrag0.SetColor(LinearColor.Create(40, 40, 40));
				RightbarDrag0.SetColor(LinearColor.Create(40, 40, 40));
			}
		}

		if (m_Editor.IsRunningCameraTrack()) {
			Symbols.PAUSE.Load(CameraTrackRunButton_Icon);
		} else {
			Symbols.PLAY.Load(CameraTrackRunButton_Icon);
		}
		
		int color = Ternary<int>.If(m_BrushState, m_EditorSettings.SelectionColor, 0xff262729);
		if (widget_under_cursor != BrushToggle) {
			BrushToggle.SetColor(color);
		}
		
		string speed_s = Math.Round(GetEditor().GetCamera().GetSettings().Speed).ToString();
		CameraSpeed.SetText(speed_s);
		
		LoggerFrame.Show(m_EditorSettings.ShowScreenLogs);

		if (m_EditorSettings.RuleOfThirds) {			
			EditorCanvas.DrawLine(screen_x / 3, 0, screen_x / 3, screen_y, 1, COLOR_BLACK);
			EditorCanvas.DrawLine((screen_x / 3) * 2, 0, (screen_x / 3) * 2, screen_y, 1, COLOR_BLACK);
			
			EditorCanvas.DrawLine(0, screen_y / 3, screen_x, screen_y / 3, 1, COLOR_BLACK);
			EditorCanvas.DrawLine(0, (screen_y / 3) * 2, screen_x, (screen_y / 3) * 2, 1, COLOR_BLACK);
		}	
		
		EditorObjectMap selected_objects = m_Editor.GetSelectedObjects();
		if (selected_objects.Count() > 0 && selected_objects[0]) {
			// Spams errors
			GetTemplateController().SetInfoObjectPosition(selected_objects[0].GetPosition());
		}
		
		// Update loop runs from inside out to deterministically resize nodes correctly
		for (int i = m_FolderNodesByDepth.Count() - 1; i >= 0; --i) {
			// See there should be folders at every depth. this will never happen unless some gap occurs. 
			if (!m_FolderNodesByDepth[i]) {
				Error(string.Format("GAP OCCURED AT INDEX %1", i));
				continue;
			}
			
			array<EditorListNode> list_nodes = m_FolderNodesByDepth[i];
			foreach (EditorListNode list_node: list_nodes) {
				if (list_node) {
					list_node.Update(dt);
				}
			}
		}
					
		m_EditorCameraMarker.WorldPosition = GetEditor().GetCamera().GetPosition();
		m_EditorCameraMarker.WorldOrientation = GetEditor().GetCamera().GetOrientation();
		
		EditorCamera camera = GetEditor().GetCamera();
		vector position = camera.GetPosition();
		if (focus_widget != InfoBar_X_Value) {
			InfoBar_X_Value.SetText(position[0].ToString(false));
		}
		
		if (focus_widget != InfoBar_Y_Value) {
			InfoBar_Y_Value.SetText(position[1].ToString(false));
		}
		
		if (focus_widget != InfoBar_Z_Value) {
			InfoBar_Z_Value.SetText(position[2].ToString(false));
		}
		
		BrushRadiusText.SetText(m_TemplateController.BrushRadius.ToString());
		BrushDensityText.SetText(m_TemplateController.BrushDensity.ToString());
		BrushWidthText.SetText(m_TemplateController.BrushWidth.ToString());
				
#ifdef DIAG_DEVELOPER
		/*
		float tbf_s_w, tbf_s_h;
		ToolbarFrame.GetScreenSize(tbf_s_w, tbf_s_h);
		DbgUI.Begin("Editor", m_EditorSettings.LeftBarPlacement + 24, tbf_s_h + 24);
		string widget_under_cursor_name = "None";
		string focus_widget_name = "None";
		if (widget_under_cursor) {
			widget_under_cursor_name = widget_under_cursor.GetName();
		}
		if (focus_widget) {
			focus_widget_name = focus_widget.GetName();
		}

		DbgUI.Text(string.Format("Widget Under Cursor: %1", widget_under_cursor_name));
		DbgUI.Text(string.Format("Focus Widget: %1", focus_widget_name));
		
		array<ref EditorAction> action_stack = EnScriptVar<array<ref EditorAction>>.Get(GetEditor(), "m_ActionStack", 0);
		for (int a = action_stack.Count() - 1; a >= 0; a--) {
			string format_action_string = string.Format("[%3] Undo: %1, Redo: %2", action_stack[a].GetUndoAction(), action_stack[a].GetRedoAction(), a);
			DbgUI.Text(format_action_string);
		}
				
		DbgUI.End();*/
#endif
	}
		
	protected void UpdateMap(notnull MapWidget map_widget, float dt)
	{
		int mouse_x, mouse_y;
		GetMousePos(mouse_x, mouse_y);
		UAInputAPI input = GetUApi();
		UAInput left_mouse_input = input.GetInputByID(UAMenuSelect);
		UAInput right_mouse_input =  input.GetInputByID(UAMenuBack);
		UAInput speed_modifier_input =  input.GetInputByID(UATurbo);
		Widget widget_under_cursor = GetWidgetUnderCursor();
		int world_size = GetGame().GetWorld().GetWorldSize();
		
		if (widget_under_cursor) {
			map_widget.SetFlags(WidgetFlags.IGNOREPOINTER);
		} else {
			map_widget.ClearFlags(WidgetFlags.IGNOREPOINTER);
		}
		
		vector mouse_world = map_widget.ScreenToMap(Vector(mouse_x, mouse_y, 0));
		
		float scale_min = GetGame().ConfigGetFloat("RscMapControl scaleMin");
		float scale_max = GetGame().ConfigGetFloat("RscMapControl scaleMax");
		float scale_01 = Math.InverseLerp(scale_min, scale_max, m_MapScale);
		
		float scale_change_value = Math.Exp(scale_01) / (50 - 30 * speed_modifier_input.LocalValue());
		if (input.GetInputByID(UANextAction).LocalValue()) {
			m_MapScale += scale_change_value;
		}
		
		if (input.GetInputByID(UAPrevAction).LocalValue()) {
			m_MapScale -= scale_change_value;
		}
		
		m_MapScale = Math.Clamp(m_MapScale, scale_min, scale_max);
		
		float vertical_view_size = m_MapScale * world_size;		
		if (input.GetInputByID(UAUIRotateInventory).LocalPress()) {
			m_MapPosition = GetGame().GetCurrentCameraPosition();
			m_MapScale = 0.333;
		}
		
		if (right_mouse_input.LocalPress()) {
			SetFocus(null);
			m_DragOffset = map_widget.ScreenToMap(Vector(mouse_x, mouse_y, 0));
		}			
		
		float p[1];
		copyarray(p, m_ScaleVelocity);		
		//Print(widget_under_cursor);
		if (!right_mouse_input.LocalValue()) {
			//Scale = Math.Clamp(Scale, 0.05, 0.95);
			
			//m_ScaleActual += (Scale - m_SclaeActual) * dt;
			
			m_ScaleActual = Math.SmoothCD(m_ScaleActual, m_MapScale, p, 0.007, 100, dt);
			//Scale = Math.Clamp(m_ScaleActual, 0.05, 0.95);
		} else {
			m_ScaleActual = m_MapScale;
		}

		map_widget.SetScale(m_ScaleActual);
		
		if (right_mouse_input.LocalValue()) {
			m_MapPosition = m_DragOffset - map_widget.ScreenToMap(Vector(mouse_x, mouse_y, 0)) + map_widget.GetMapPos();
		}
		
		map_widget.SetMapPos(m_MapPosition);
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{		
		switch (w) {
			case CameraPanelButton: {
				CameraPanel.Show(!CameraPanel.IsVisible());
				break;
			}

			case CameraTrackPreviousButton: {
				m_Editor.CameraTrackPrevious();
				break;
			}

			case CameraTrackRunButton: {
				if (m_Editor.IsRunningCameraTrack()) {
					m_Editor.PauseCameraTrack();
				} else {
					m_Editor.StartCameraTrack();
				}

				break;
			}

			case CameraTrackNextButton: {
				m_Editor.CameraTrackNext();
				break;
			}

			case CameraTrackStopButton: {
				m_Editor.StopCameraTrack();
				break;
			}

			case CameraTrackRecordButton: {

				break;
			}
			
			case BrushRight: {
				SetBrushIndex(Math.Rollover(m_CurrentBrushIndex + 1, 0, m_BrushTypes.Count()));
				break;
			}
			
			case BrushLeft: {
				SetBrushIndex(Math.Rollover(m_CurrentBrushIndex - 1, 0, m_BrushTypes.Count()));
				break;
			}
		}
		

		return super.OnClick(w, x, y, button);
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		if (button != 0) {
			return super.OnMouseButtonUp(w, x, y, button);
		}

		switch (w) {
			case BrushToggle: {
				SetBrushState(!GetBrushState());
				break;
			}
		}

		return super.OnMouseButtonUp(w, x, y, button);
	}

	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		switch (w) {
			case LeftSearchBar: {
				if (button == 1) {
					LeftSearchBar.SetText(string.Empty);
					OnChange(LeftSearchBar, x, y, true);
					return true;
				}
				
				break;
			}
			
			case RightSearchBar: {
				if (button == 1) {
					RightSearchBar.SetText(string.Empty);
					OnChange(RightSearchBar, x, y, true);
					return true;
				}
				break;
			}
			
			case LeftSearchBarIcon: {
				LeftSearchBar.SetText(string.Empty);
				OnChange(LeftSearchBar, x, y, true);
				break;
			}
			
			case RightSearchBarIcon: {
				RightSearchBar.SetText(string.Empty);
				OnChange(RightSearchBar, x, y, true);
				break;
			}
		}
		
		return super.OnMouseButtonDown(w, x, y, button);
	}

	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		switch (w) {
			case BrushRight: {
				BrushRight_Icon.SetImage(2);
				break;
			}
			
			case BrushLeft: {
				BrushLeft_Icon.SetImage(2);
				break;
			}
		}
		
		return super.OnMouseLeave(w, enterW, x, y);
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		switch (w) {
			case LeftbarCategoryStatic: {
				CreateDelayedTooltip(w, "Static Objects", TooltipPosition.TOP_LEFT, "Static Non-Interactive Objects");
				break;
			}

			case LeftbarCategoryConfig: {
				CreateDelayedTooltip(w, "Config Objects", TooltipPosition.TOP_LEFT, "Interactive Objects & Items");
				break;
			}
			
			case BrushToggle: {
				if (!m_BrushState) {
					LinearColor c = m_EditorSettings.SelectionColor;
					
					WidgetAnimator.AnimateColor(w, c.With(3, 100), 100);
				}
				
				break;
			}
			
			case BrushRight: {
				BrushRight_Icon.SetImage(3);
				break;
			}
			
			case BrushLeft: {
				BrushLeft_Icon.SetImage(3);
				break;
			}
			
			case RightSearchBar:
			case LeftSearchBar: {
				return true;
			}
		}

		return super.OnMouseEnter(w, x, y);
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		switch (w) {
			case LeftSearchBar:
			case RightSearchBar: {
				m_Editor.CancelPlacing();
				break;
			}
		}

		return super.OnFocus(w, x, y);
	}	
	
	protected string m_LastSearchString;
	protected bool m_LastFavoritesState;
	
	void RefreshSearchBar()
	{
		bool favorite_toggle = GetEditor().GetSettings().ShowFavoriteObjects;
		string search_string = LeftSearchBar.GetText();
		search_string.ToLower();
		
				
		if (search_string.Length() < 3 || favorite_toggle) {
			// Smoother UX - only skip if we're staying in the same short search state
			if (search_string.Length() < 3 && m_LastSearchString.Length() < 3 && m_LastFavoritesState == favorite_toggle && search_string == m_LastSearchString) {
				return;
			}
						
			for (int i = 0; i < m_SearchableListNodes.Count(); i++) {
				bool filter_state = m_SearchableListNodes[i].FilterType("", favorite_toggle);
				
				// Don't call Show() on virtual folders - they handle their own visibility internally
				if (!m_SearchableListNodes[i].IsInherited(EditorVirtualFolderListNode)) {
					m_SearchableListNodes[i].Show(filter_state);
					if (filter_state) {
						GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_SearchableListNodes[i].GetListParent().SetCollapsed, 0, 0, false);
					}
				}
			}
			
			// Also expand virtual folders when their items match
			bool hasShortSearchVirtualFolderMatches = false;
			foreach (EditorVirtualFolderListNode virtualFolderNode: m_VirtualFolderNodes) {
				bool hasMatchingChildren = false;
				foreach (EditorListNode childNode: virtualFolderNode.ChildrenItems) {
					if (childNode.FilterType("", favorite_toggle)) {
						hasMatchingChildren = true;
						break;
					}
				}
				if (hasMatchingChildren) {
					GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(virtualFolderNode.SetCollapsed, 0, 0, false);
					hasShortSearchVirtualFolderMatches = true;
				}
			}
			
			// Expand Virtual Folders root if any virtual folders have matches
			if (hasShortSearchVirtualFolderMatches && m_VirtualFoldersRoot) {
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_VirtualFoldersRoot.SetCollapsed, 0, 0, false);
			} else if (hasShortSearchVirtualFolderMatches && !m_VirtualFoldersRoot) {
				EditorLog.Warning("Virtual Folders root is null during short search expansion");
			}
			
			// Collapse folders when transitioning from long search to short search or when search is cleared
			// But only if not suppressed (e.g., during virtual folder operations)
			if (!m_SuppressFolderCollapse && (search_string.Length() == 0 || (m_LastSearchString.Length() >= 3 && search_string.Length() < 3))) {
				
				// Use the same recursive approach as the working CollapseAll command
				CollapseAllFolders();
			}
						
			m_LastSearchString = search_string;
			m_LastFavoritesState = favorite_toggle;
			return;
		}
	
		bool hasVirtualFolderMatches = false;
		
		foreach (EditorListNode list_node: m_SearchableListNodes) {
			bool matches = list_node.FilterType(search_string, favorite_toggle);
			
			// Don't call Show() on virtual folders - they handle their own visibility internally
			if (!list_node.IsInherited(EditorVirtualFolderListNode)) {
				list_node.Show(matches);
				
				// Expand virtual folders if they have matching children
				if (matches) {
					EditorListNode matchParent = list_node.GetListParent();
					if (matchParent && matchParent.IsInherited(EditorVirtualFolderListNode)) {
						EditorVirtualFolderListNode virtualParent = EditorVirtualFolderListNode.Cast(matchParent);
						if (virtualParent) {
							virtualParent.SetCollapsed(false);
							hasVirtualFolderMatches = true;
						}
					}
				}
			} else if (matches) {
				// This is a virtual folder that has matches - track it for root expansion
				hasVirtualFolderMatches = true;
			}
		}
		
		// Expand Virtual Folders root if any virtual folders have matches
		if (hasVirtualFolderMatches && m_VirtualFoldersRoot) {
			m_VirtualFoldersRoot.SetCollapsed(false);
		} else if (hasVirtualFolderMatches && !m_VirtualFoldersRoot) {
			EditorLog.Warning("Virtual Folders root is null during search expansion");
		}
						
		LeftbarScroll.VScrollToPos(0);
		
		/*
		EnProfiler.SortData();
		Print("\n\n");
		PrintFormat("RecalculateSize Count: %1", EnProfiler.GetCountOfFunc("RecalculateSize", EditorListNode, true));
		Print(EnProfiler.GetTimeOfFunc("RecalculateSize", EditorListNode, true));
		PrintFormat("Show Count: %1", EnProfiler.GetCountOfFunc("Show", EditorListNode, true));
		Print(EnProfiler.GetTimeOfFunc("Show", EditorPlaceableListNode, true));
		PrintFormat("SetCollapsed Count: %1", EnProfiler.GetCountOfFunc("SetCollapsed", EditorListNode, true));
		Print(EnProfiler.GetTimeOfFunc("SetCollapsed", EditorListNode, true));
		array<ref EnProfilerTimeFuncPair> times = {};
		EnProfiler.GetTimePerFunc(times, 20);
		foreach (auto time: times) {
			PrintFormat("%1: %2", time.param1, time.param2);
		}*/
		
		Symbols left_search_bar_icon = Ternary<Symbols>.If(!search_string.Length(), Symbols.MAGNIFYING_GLASS, Symbols.X);
		left_search_bar_icon.Load(LeftSearchBarIconIcon);
		m_LastSearchString = search_string;
		m_LastFavoritesState = favorite_toggle;
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		int i;
		vector camera_position = GetEditor().GetCamera().GetPosition();
		bool set_camera_position = false;
		switch (w) {
			case LeftSearchBar: {				
				RefreshSearchBar();
				break;
			}
			
			case RightSearchBar: {
				string right_search_bar_text = RightSearchBar.GetText();
				auto right_spacer_config = Ternary<ObservableCollection<EditorListItem>>.If(m_TemplateController.CategoryPlacements, m_TemplateController.RightbarPlacedData, m_TemplateController.RightbarDeletionData);
				for (i = 0; i < right_spacer_config.Count(); i++) {					
					right_spacer_config[i].GetLayoutRoot().Show(right_spacer_config[i].FilterType(right_search_bar_text));
				}
				
				RightbarScroll.VScrollToPos(0);
				Symbols right_search_bar_icon = Ternary<Symbols>.If(!right_search_bar_text.Length(), Symbols.MAGNIFYING_GLASS, Symbols.X);
				right_search_bar_icon.Load(RightSearchBarIconIcon);
				break;
			}
			
			case InputEditBoxWidget: {
				if (!finished) {
					return false;
				}
		
				string text = InputEditBoxWidget.GetText();
				if (text != "") {
					ScriptRPC chat_rpc = new ScriptRPC();
					chat_rpc.Write(text);
					chat_rpc.Send(null, 39260, true, null);
					
					if (!GetGame().IsMultiplayer()) {
						string name;
						GetGame().GetPlayerName(name);
						ChatMessageEventParams chat_params = new ChatMessageEventParams(CCDirect, name, text, "");
						m_Chat.Add(chat_params);
					}
				}
				
				GetUApi().GetInputByID(UAChat).Supress();	
				InputEditBoxWidget.SetText(string.Empty);	
				InputEditBoxWidget.Show(false);
				SetFocus(null);				
				break;
			}
			
			case InfoBar_X_Value: {
				string x_text = InfoBar_X_Value.GetText();
				for (i = x_text.Length() - 1; i >= 0; --i) {
					if (!CF_Encoding.IsNumeric(x_text[i]) && x_text[i] != ".") {
						x_text = x_text.Substring(0, i);
					}
				}
				
				InfoBar_X_Value.SetText(x_text);	
				camera_position[0] = x_text.ToFloat();		
				set_camera_position = true;	
				break;
			}
			
			case InfoBar_Y_Value: {
				string y_text = InfoBar_Y_Value.GetText();
				for (i = y_text.Length() - 1; i >= 0; --i) {
					if (!CF_Encoding.IsNumeric(y_text[i]) && y_text[i] != ".") {
						y_text = y_text.Substring(0, i);
					}
				}
				
				InfoBar_Y_Value.SetText(y_text);
				camera_position[1] = y_text.ToFloat();
				set_camera_position = true;
				break;
			}
			
			case InfoBar_Z_Value: {
				string z_text = InfoBar_Z_Value.GetText();
				for (i = z_text.Length() - 1; i >= 0; --i) {
					if (!CF_Encoding.IsNumeric(z_text[i]) && z_text[i] != ".") {
						z_text = z_text.Substring(0, i);
					}
				}
				
				InfoBar_Z_Value.SetText(z_text);
				
				camera_position[2] = z_text.ToFloat();
				set_camera_position = true;
				break;
			}
		}
		
		if (set_camera_position) {
			GetEditor().GetCamera().SetPosition(camera_position);
		}
		
		return super.OnChange(w, x, y, finished);
	}
		
	void SetObjectSelectState(bool state)
	{
		m_ObjectSelectToggle = state;
	}

	void ToggleObjectSelect()
	{
		m_ObjectSelectToggle = !m_ObjectSelectToggle;
	}

	bool GetObjectSelect()
	{
		return m_ObjectSelectToggle;
	}
	
	void SetSelectionMode(SelectionMode selection_mode)
	{
		m_SelectionMode = selection_mode;
	}
	
	SelectionMode GetSelectionMode()
	{
		return m_SelectionMode;
	}

	/*
	override void Show(bool show) 
	{
		if (m_LayoutRoot.IsVisible() == show) {
			return;
		}
		
		super.Show(show);
		
		if (CurrentDialog) {
			CurrentDialog.GetLayoutRoot().Show(show);
		}
		
		if (m_Dialog) {
			m_Dialog.GetLayoutRoot().Show(show);
		}
		
		GetGame().GetUIManager().ShowCursor(show);
	}*/
		
	void SetEditorMode(eEditorMode editor_mode)
	{
		//@ stub
	}
		
	void ToggleCursor() 
	{	
		// An excellent place to do this!	
		m_EditorSettings.Save();
		m_Editor.GetCameraSettings().Save();
		
		ShowCursor(!GetGame().GetUIManager().IsCursorVisible());
	}
	
	void ShowCursor(bool state) 
	{
		GetGame().GetUIManager().ShowCursor(state);
		
		if (!state) {
			delete CurrentMenu;
			SetFocus(null);
			ClearCurrentTooltip();
		}
	}
			
	void CreateNotification(string text, float duration = 4.0)
	{		
		WidgetAnimator.CancelAnimate(NotificationPanel, WidgetAnimatorProperty.POSITION_Y);
		WidgetAnimator.Animate(NotificationPanel, WidgetAnimatorProperty.POSITION_Y, -24, 100);
		NotificationPanel.SetColor(m_EditorSettings.SelectionColor);
		NotificationText.SetText(text);

		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(CleanupNotification);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(CleanupNotification, duration * 1000);
	}

	protected void CleanupNotification()
	{
		WidgetAnimator.Animate(NotificationPanel, WidgetAnimatorProperty.POSITION_Y, 0, 100);
	}
	
	bool IsMapVisible()
	{
		return Map.IsVisible();
	}
	
	bool IsSelectionBoxActive()
	{
		return m_IsBoxSelectActive;
	}
	
	void ScrollToListItem(EditorListItem list_item)
	{
		
		//VScrollToWidget(list_item.GetLayoutRoot());
	}
		
	bool IsObjectSelectionEnabled()
	{
		return m_ObjectSelectToggle;
	}
	
	override string GetLayoutFile() 
	{
		return "DayZEditor/gui/layouts/hud/EditorHud.layout";
	}
	
	override typename GetControllerType()
	{
		return EditorHudController;
	}
	
	// Modal Menu Control
	static ref EditorMenu CurrentMenu;
	
	// ToolTip Control
	void SetCurrentTooltip(ScriptView current_tooltip) 
	{
		if (!current_tooltip) {
			ClearCurrentTooltip();
		} else {
			if (CanCreateTooltip()) {
				GetDayZGame().SetCurrentTooltip(current_tooltip);
			}
		}
	}
	
	TooltipView CreateDelayedTooltip(Widget w, string text, TooltipPosition position, string desc = string.Empty, Symbols icon = string.Empty, int delay = 300)
	{
		return GetDayZGame().CreateDelayedTooltip(w, text, position, desc, icon, delay);
	}

	protected bool CanCreateTooltip()
	{		
		return !IsSelectionBoxActive();
	}
	
	void ClearCurrentTooltip()
	{
		GetDayZGame().ClearTooltip();
	}
	
	bool ReloadBrushes(string file)
	{
		string brushes_filename = SystemPath.Format(file);
		if (File.Exists(brushes_filename)) {
			XMLEditorBrushes xml_brushes = new XMLEditorBrushes(m_BrushTypes);
			GetXMLApi().Read(brushes_filename, xml_brushes);			
			SetBrushIndex(0);
			
			float largest_size;
			for (int i = 0; i < m_BrushTypes.Count(); i++) {
				float size = m_BrushTypes[i].Name.Length() * 12;
				if (size > largest_size) {
					largest_size = size;
				}
			}
			
			float bt_s_w, bt_s_h;
			BrushToggle.GetScreenSize(bt_s_w, bt_s_h);
			BrushToggle.SetScreenSize(largest_size, bt_s_h);
			return true;
		}

		return false;
	}

	void SetBrushState(int state)
	{
		m_BrushState = state;
		
		EditorBrushData brush_data = m_BrushTypes[m_CurrentBrushIndex];
		if (brush_data && m_BrushState) {
			m_Editor.Brush = EditorBrush.Create(brush_data);
		} else {
			m_Editor.Brush = null;
		}

		BrushRadiusFrame.Show(m_BrushState);
		BrushDensityFrame.Show(m_BrushState);
		BrushWidthFrame.Show(m_BrushState);
		
		m_Editor.CommandManager[EditorBrushRadiusCommand].SetCanExecute(m_BrushState);
		m_Editor.CommandManager[EditorBrushDensityCommand].SetCanExecute(m_BrushState);
		m_Editor.CommandManager[EditorBrushWidthCommand].SetCanExecute(m_BrushState);
	}

	int GetBrushState()
	{
		return m_BrushState;
	}
	
	void SetBrushIndex(int index)
	{
		if (!m_BrushTypes.IsValidIndex(index)) {
			return;
		}
		
		m_CurrentBrushIndex = index;
		EditorBrushData brush_data = m_BrushTypes[m_CurrentBrushIndex];
		string name = m_BrushTypes[m_CurrentBrushIndex].Name;
		BrushText.SetText(name);
		
		if (m_BrushState) {
			m_Editor.Brush = EditorBrush.Create(brush_data);
		} else {
			delete m_Editor.Brush;
		}
		
		m_Editor.CommandManager[EditorBrushRadiusCommand].SetCanExecute(m_BrushState);
		m_Editor.CommandManager[EditorBrushDensityCommand].SetCanExecute(m_BrushState);
		m_Editor.CommandManager[EditorBrushWidthCommand].SetCanExecute(m_BrushState);
	}

	int GetBrushIndex()
	{
		return m_CurrentBrushIndex;
	}
	
	void SetBrushByTypename(typename type)
	{
		for (int i = 0; i < m_BrushTypes.Count(); i++) {
			if (m_BrushTypes[i].BrushClassName == type) {
				SetBrushIndex(i);
				return;
			}
		}		
	}
	
	void SetBrushByName(string name)
	{
		for (int i = 0; i < m_BrushTypes.Count(); i++) {
			if (m_BrushTypes[i].Name == name || m_BrushTypes[i].BrushClassName.ToString() == name) {
				SetBrushIndex(i);
				return;
			}
		}	
	}
		
	ScriptView ShowFileDialog(string title, typename file_type, ScriptCaller on_file_chosen, eDialogMode dialog_mode, eDialogFlags dialog_flags = 0, string default_file = string.Empty)
	{
		EditorFileDialog dialog = new EditorFileDialog(file_type, on_file_chosen, dialog_mode, dialog_flags, default_file);
		m_Dialog = dialog;
		
		GetGame().GetUIManager().ShowCursor(true);
		return m_Dialog;
	}
	
	ScriptView ShowMessageBox(string caption, MessageBoxButtons buttons, ScriptCaller on_close)
	{
		EditorMessageBox message_box = new EditorMessageBox(caption, buttons, on_close);
		m_Dialog = message_box;
		GetGame().GetUIManager().ShowCursor(true);
		return m_Dialog;
	}
	
	ScriptView GetDialog()
	{
		return m_Dialog;
	}
	
	protected ref ScriptView m_Dialog;
	protected ref ScriptView m_MessageBox;
		
	// Dialog Control
	static ref DialogBase CurrentDialog;
	
	static bool IsDialogCommand(Widget w) 
	{
		return (CurrentDialog && CurrentDialog.GetLayoutRoot() && CurrentDialog.GetLayoutRoot().FindAnyWidget(w.GetName()));
	}
	
	protected ref map<typename, vector> m_LastDialogPosition = new map<typename, vector>();
	
	void RegisterLastDialogPosition(ScriptView dialog)
	{
		float x, y;
		dialog.GetLayoutRoot().GetPos(x, y);
		m_LastDialogPosition[dialog.Type()] = Vector(x, y, 0);
	}
	
	vector GetLastDialogPosition(ScriptView dialog)
	{
		return m_LastDialogPosition[dialog.Type()];
	}
	
	EditorChat GetChat()
	{
		return m_Chat;
	}
	
	EditorHudController GetTemplateController()
	{
		return m_TemplateController;
	}
		
	static bool IsPointInPolygon(float x, float y, array<vector> points)
	{
		bool inside = false;
        for (int i = 0, j = points.Count() - 1; i < points.Count(); j = i++) {
            if ((points[i][1] > y) != (points[j][1] > y) && x < (points[j][0] - points[i][0]) * (y - points[i][1]) / (points[j][1] - points[i][1]) + points[i][0]) {
                inside = !inside;
            }
        }

        return inside;
	}
	
	void LoadVirtualFolders()
	{
		// Suppress folder collapse during virtual folder operations to prevent slowdown
		m_SuppressFolderCollapse = true;
		
		// No need to rebuild - the initial tree was already built with virtual folder filtering
		
		// Clear existing virtual folder nodes
		foreach (EditorVirtualFolderListNode existingNode: m_VirtualFolderNodes)
		{
			if (existingNode)
				existingNode.GetLayoutRoot().Unlink();
		}
		m_VirtualFolderNodes.Clear();
		
		// Remove existing virtual folders root
		if (m_VirtualFoldersRoot)
		{
			m_VirtualFoldersRoot.GetLayoutRoot().Unlink();
			m_FolderNodes.Remove("virtual_folders_root");
			if (m_FolderNodesByDepth[0])
			{
				m_FolderNodesByDepth[0].RemoveItem(m_VirtualFoldersRoot);
			}
			m_VirtualFoldersRoot = null;
		}
		
		EditorVirtualFolderManager folderManager = EditorVirtualFolderManager.GetInstance();
		array<string> folderNames = folderManager.GetFolderNames();
		
		if (folderNames.Count() == 0)
		{
			// Re-enable folder collapse and return if no virtual folders
			m_SuppressFolderCollapse = false;
			return;
		}
		
		// Create Virtual Folders root node
		m_VirtualFoldersRoot = new EditorFolderListNode("Virtual Folders");
		m_TemplateController.LeftContent.Insert(m_VirtualFoldersRoot);
		
		// Add to folder depth system
		if (!m_FolderNodesByDepth[0])
			m_FolderNodesByDepth[0] = {};
		m_FolderNodesByDepth[0].Insert(m_VirtualFoldersRoot);
		m_FolderNodes["virtual_folders_root"] = m_VirtualFoldersRoot;
		
		// Hide original items that are now in virtual folders BEFORE creating virtual folder contents
		HideVirtualizedItems();
		
		// Create individual virtual folder nodes
		foreach (string folderName: folderNames)
		{
			EditorVirtualFolderData folderData = folderManager.GetFolder(folderName);
			if (folderData)
			{
				EditorVirtualFolderListNode newVirtualFolderNode = new EditorVirtualFolderListNode(folderData.Name, folderData);
				
				m_VirtualFoldersRoot.InsertChild(newVirtualFolderNode);
				m_VirtualFolderNodes.Insert(newVirtualFolderNode);
				
				// Add virtual folder itself to searchable nodes so it gets filtered during search
				m_SearchableListNodes.Insert(newVirtualFolderNode);
				
				if (!m_FolderNodesByDepth[1])
					m_FolderNodesByDepth[1] = {};
				m_FolderNodesByDepth[1].Insert(newVirtualFolderNode);
				
				m_FolderNodes["virtual_folder_" + folderName] = newVirtualFolderNode;
				
			}
			else
			{
				EditorLog.Error("Could not get folder data for: " + folderName);
			}
		}
		
		// Re-enable folder collapse after virtual folder operations are complete
		m_SuppressFolderCollapse = false;
	}
	
	void RebuildBaseFolderTree()
	{
		
		// Clear all existing folder nodes and rebuild from scratch
		// This ensures any previously unlinked items are restored
		m_FolderNodes.Clear();
		m_FolderNodesByDepth.Clear();
		m_SearchableListNodes.Clear();
		
		// Clear existing content from the left panel (except virtual folders which are handled separately)
		m_TemplateController.LeftContent.Clear();
		
		// Rebuild the folder tree using the same logic as initial load
		array<ref EditorPlaceableItem> placeable_items = m_Editor.GetPlaceableObjects();
			
		foreach (EditorPlaceableItem placeable_item: placeable_items) {		
			
			if (m_EditorSettings.ConsoleMode && !placeable_item.ConsoleFriendly) {
				continue;
			}
			
			// Skip items that should be hidden due to virtual folder rules
			EditorVirtualFolderManager folderManager = EditorVirtualFolderManager.GetInstance();
			string virtualFolderName = folderManager.GetItemFolder(placeable_item);
			if (virtualFolderName != string.Empty) {
				continue;
			}
			
			string model_name = placeable_item.GetModelName();
			model_name.Replace(SystemPath.SEPERATOR_ALT, SystemPath.SEPERATOR);
			model_name.ToLower();
			model_name.TrimInPlace();
			if (model_name == "bmp" || model_name == "bmp.p3d" || model_name.Length() == 0) {
				continue;
			}
			
			if (model_name[0] == SystemPath.SEPERATOR) {
				model_name = model_name.Substring(1, model_name.Length() - 1);
			}
						
			array<string> model_path_split = {};
			model_name.Split(SystemPath.SEPERATOR, model_path_split);
			int depth = model_path_split.Count() - 1;
			for (int i = 0; i < model_path_split.Count(); i++) {
				string folder_name = model_path_split[i];
				string full_path = string.Empty;
				for (int j = 0; j <= i; j++) {
					full_path += model_path_split[j];
					if (j != i) {
						full_path += SystemPath.SEPERATOR;
					}
				}
												
				if (i < model_path_split.Count() - 1) {
					EditorFolderListNode folder_node;
					if (m_FolderNodes.Contains(full_path)) {
						folder_node = m_FolderNodes[full_path];
					} else {
						folder_node = new EditorFolderListNode(folder_name);
						m_FolderNodes[full_path] = folder_node;
						
						if (!m_FolderNodesByDepth[i]) {
							m_FolderNodesByDepth[i] = {};
						}
						
						m_FolderNodesByDepth[i].Insert(folder_node);
							
						if (i == 0) {
							m_TemplateController.LeftContent.Insert(folder_node);
						} else {
							string directory_parent = full_path.Substring(0, full_path.LastIndexOf(SystemPath.SEPERATOR));
							EditorFolderListNode parent_node = m_FolderNodes[directory_parent];
							if (parent_node) {
								parent_node.InsertChild(folder_node);
							}
						}
					}				
				}				
			}
			
			string model_directory = model_name.Substring(0, model_name.LastIndexOf(SystemPath.SEPERATOR));
			EditorPlaceableListNode placeable_node = new EditorPlaceableListNode(placeable_item);
			m_FolderNodes[model_name] = placeable_node;
			m_FolderNodes[model_directory].InsertChild(placeable_node);		
			
			if (!m_FolderNodesByDepth[depth]) {
				m_FolderNodesByDepth[depth] = {};
			}	
			
			m_FolderNodesByDepth[depth].Insert(placeable_node);
			m_SearchableListNodes.Insert(placeable_node);
		}
		
		EditorLog.Info("Rebuilt base folder tree with %1 placeable objects", placeable_items.Count().ToString());
	}
	
	
	void CollapseAllFolders()
	{
		
		// Try a different approach - use longer delays and direct calls
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(CollapseAllFoldersDelayed, 100, 0);
	}
	
	void CollapseAllFoldersDelayed()
	{
		
		// Start the aggressive approach manually with proper iteration tracking
		m_CollapseIteration = 0;
		m_CollapseMaxIterations = 6; // Back to 6 attempts for completeness
		CollapseAllFoldersAggressively(m_CollapseIteration, m_CollapseMaxIterations);
	}
	
	void CollapseAllFoldersOnce()
	{
		// Check if search is active - if so, don't collapse
		string currentSearchText = LeftSearchBar.GetText();
		if (currentSearchText.Length() > 0) {
			return;
		}
		
		int foldersCollapsed = 0;
		int depthFolders = 0;
		int namedFolders = 0;
		int virtualFolders = 0;
		int searchableFolders = 0;
		
		
		// Check all folder nodes by depth with recursive collapse
		for (int depth = 0; depth < m_FolderNodesByDepth.Count(); depth++) {
			if (m_FolderNodesByDepth[depth]) {
				foreach (EditorListNode folderAtDepth: m_FolderNodesByDepth[depth]) {
					if (folderAtDepth && folderAtDepth.IsInherited(EditorFolderListNode)) {
						if (!folderAtDepth.IsCollapsed()) {
							folderAtDepth.SetCollapsed(true);
							depthFolders++;
							foldersCollapsed++;
						}
						// Also recursively collapse all children
						CollapseAllChildren(folderAtDepth);
					}
				}
			}
		}
		
		// Check all named folder nodes with recursive collapse and detailed logging
		int namedTotal = 0;
		int namedFolderType = 0;
		int namedAlreadyCollapsed = 0;
		
		foreach (string folderKey, EditorListNode folderNode: m_FolderNodes) {
			namedTotal++;
			if (folderNode) {
				if (folderNode.IsInherited(EditorFolderListNode)) {
					namedFolderType++;
					if (!folderNode.IsCollapsed()) {
						folderNode.SetCollapsed(true);
						namedFolders++;
						foldersCollapsed++;
					} else {
						namedAlreadyCollapsed++;
					}
					// Also recursively collapse all children
					CollapseAllChildren(folderNode);
				}
			}
		}
		
		
		// Check all virtual folders
		foreach (EditorVirtualFolderListNode vfNode: m_VirtualFolderNodes) {
			if (vfNode && !vfNode.IsCollapsed()) {
				vfNode.SetCollapsed(true);
				virtualFolders++;
				foldersCollapsed++;
			}
		}
		
		// Check Virtual Folders root
		if (m_VirtualFoldersRoot && !m_VirtualFoldersRoot.IsCollapsed()) {
			m_VirtualFoldersRoot.SetCollapsed(true);
			foldersCollapsed++;
		}
		
		// Check all searchable nodes for any folders we might have missed
		foreach (EditorListNode searchableNode: m_SearchableListNodes) {
			if (searchableNode && searchableNode.IsInherited(EditorFolderListNode)) {
				if (!searchableNode.IsCollapsed()) {
					searchableNode.SetCollapsed(true);
					searchableFolders++;
					foldersCollapsed++;
				}
			}
		}
		
	}
	
	void CollapseAllChildren(EditorListNode parentNode)
	{
		if (!parentNode) return;
		
		foreach (EditorListNode child: parentNode.ChildrenItems) {
			if (child && child.IsInherited(EditorFolderListNode)) {
				if (!child.IsCollapsed()) {
					child.SetCollapsed(true);
				}
				// Recurse into children
				CollapseAllChildren(child);
			}
		}
	}
	
	void CollapseUsingCommandSystem()
	{
		// Check if search is active - if so, don't collapse
		string currentSearchText = LeftSearchBar.GetText();
		if (currentSearchText.Length() > 0) {
			return;
		}
		
		
		int foldersProcessed = 0;
		
		// Try to use the EditorCollapseAllCommand approach on every folder we can find
		for (int depth = 0; depth < m_FolderNodesByDepth.Count(); depth++) {
			if (m_FolderNodesByDepth[depth]) {
				foreach (EditorListNode folderAtDepth: m_FolderNodesByDepth[depth]) {
					if (folderAtDepth && folderAtDepth.IsInherited(EditorFolderListNode)) {
						// Use the same approach as EditorCollapseAllCommand.CollapseAll
						ApplyCommandCollapseToFolder(folderAtDepth);
						foldersProcessed++;
					}
				}
			}
		}
		
		// Also try on all named folders
		foreach (string folderKey, EditorListNode folderNode: m_FolderNodes) {
			if (folderNode && folderNode.IsInherited(EditorFolderListNode)) {
				ApplyCommandCollapseToFolder(folderNode);
				foldersProcessed++;
			}
		}
		
	}
	
	void ApplyCommandCollapseToFolder(EditorListNode folderNode)
	{
		if (!folderNode) return;
		
		// Use the exact same logic as EditorCollapseAllCommand.CollapseAll
		folderNode.SetCollapsed(true);
		
		// The working command does NOT recursively collapse children (line 60 is commented out)
		// So we also don't recurse here
	}
	
	void CollapseAllFoldersAggressively(int iteration, int maxIterations)
	{
		// Check if search is active - if so, stop collapsing
		string currentSearchText = LeftSearchBar.GetText();
		if (currentSearchText.Length() > 0) {
			return;
		}
		
		if (iteration >= maxIterations) {
			return;
		}
		
		iteration++;
		int foldersCollapsedThisIteration = 0;
		
		
		// Check all folder nodes by depth
		for (int depth = 0; depth < m_FolderNodesByDepth.Count(); depth++) {
			if (m_FolderNodesByDepth[depth]) {
				foreach (EditorListNode folderAtDepth: m_FolderNodesByDepth[depth]) {
					if (folderAtDepth && folderAtDepth.IsInherited(EditorFolderListNode)) {
						if (!folderAtDepth.IsCollapsed()) {
							folderAtDepth.SetCollapsed(true);
							foldersCollapsedThisIteration++;
						}
					}
				}
			}
		}
		
		// Check all named folder nodes
		foreach (string folderKey, EditorListNode folderNode: m_FolderNodes) {
			if (folderNode && folderNode.IsInherited(EditorFolderListNode)) {
				if (!folderNode.IsCollapsed()) {
					folderNode.SetCollapsed(true);
					foldersCollapsedThisIteration++;
				}
			}
		}
		
		// Check all virtual folders
		foreach (EditorVirtualFolderListNode vfNode: m_VirtualFolderNodes) {
			if (vfNode && !vfNode.IsCollapsed()) {
				vfNode.SetCollapsed(true);
				foldersCollapsedThisIteration++;
			}
		}
		
		// Check Virtual Folders root
		if (m_VirtualFoldersRoot && !m_VirtualFoldersRoot.IsCollapsed()) {
			m_VirtualFoldersRoot.SetCollapsed(true);
			foldersCollapsedThisIteration++;
		}
		
		// Check all searchable nodes for any folders we might have missed
		foreach (EditorListNode searchableNode: m_SearchableListNodes) {
			if (searchableNode && searchableNode.IsInherited(EditorFolderListNode)) {
				if (!searchableNode.IsCollapsed()) {
					searchableNode.SetCollapsed(true);
					foldersCollapsedThisIteration++;
				}
			}
		}
		
		
		// If no folders were collapsed for 2 consecutive attempts, stop early
		if (foldersCollapsedThisIteration == 0 && iteration > 1) {
			return;
		}
		
		// Schedule next iteration if we haven't reached the limit
		if (iteration < maxIterations) {
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.CollapseAllFoldersAggressively, 50, 0, iteration, maxIterations); // Small 50ms delay for UI processing
		} else {
		}
	}
	

	void RefreshVirtualFolders()
	{
		// Refresh contents and hide newly virtualized items efficiently
		
		// Clear any stale selection to prevent crashes
		ClearSelection();
		
		// Suppress folder collapse during refresh
		m_SuppressFolderCollapse = true;
		
		// Refresh virtual folder contents to show new/removed items
		foreach (EditorVirtualFolderListNode folderNode: m_VirtualFolderNodes)
		{
			if (folderNode)
			{
				folderNode.RefreshContents();
			}
		}
		
		// Hide newly virtualized items (but only scan items that are in virtual folders now)
		HideNewlyVirtualizedItems();
		
		// Re-enable folder collapse
		m_SuppressFolderCollapse = false;
	}
	
	void HideNewlyVirtualizedItems()
	{
		// Use existing hiding logic but don't process ALL items - just the ones in virtual folders
		EditorVirtualFolderManager folderManager = EditorVirtualFolderManager.GetInstance();
		array<ref EditorPlaceableItem> allPlaceableObjects = m_Editor.GetPlaceableObjects();
		
		// Create a smaller list of just items that are in virtual folders
		array<ref EditorPlaceableItem> virtualizedItems = new array<ref EditorPlaceableItem>();
		foreach (EditorPlaceableItem placeableItem: allPlaceableObjects)
		{
			string virtualFolderName = folderManager.GetItemFolder(placeableItem);
			if (virtualFolderName != string.Empty)
			{
				virtualizedItems.Insert(placeableItem);
			}
		}
		
		
		// Now hide only the virtualized items - this should be much faster
		foreach (EditorPlaceableItem virtualizedItem: virtualizedItems)
		{
			HideOriginalItemNode(virtualizedItem);
		}
		
	}
	
	void RefreshVirtualFoldersWithHiding()
	{
		// Use this only when we actually need to hide/restore items
		EditorLog.Info("RefreshVirtualFoldersWithHiding called - using full refresh");
		
		// Clear any stale selection to prevent crashes
		ClearSelection();
		
		// Suppress folder collapse during refresh
		m_SuppressFolderCollapse = true;
		
		// Do full refresh with hiding
		HideVirtualizedItems();
		
		// Refresh virtual folder contents
		foreach (EditorVirtualFolderListNode folderNode: m_VirtualFolderNodes)
		{
			if (folderNode)
				folderNode.RefreshContents();
		}
		
		// Re-enable folder collapse
		m_SuppressFolderCollapse = false;
	}
	
	void RestoreSpecificRemovedItems()
	{
		EditorVirtualFolderManager folderManager = EditorVirtualFolderManager.GetInstance();
		array<ref EditorPlaceableItem> allPlaceableObjects = m_Editor.GetPlaceableObjects();
		
		bool needsFullRebuild = false;
		array<ref EditorPlaceableItem> modelItemsToRestore = new array<ref EditorPlaceableItem>();
		
		// First pass: check what needs restoration and if we need full rebuild
		foreach (EditorPlaceableItem placeableItem: allPlaceableObjects)
		{
			string virtualFolderName = folderManager.GetItemFolder(placeableItem);
			// If item is NOT in any virtual folder, ensure it exists in the original tree
			if (virtualFolderName == string.Empty)
			{
				bool itemExists = CheckIfItemExistsInTree(placeableItem);
				if (!itemExists)
				{
					// Check if this is a class-based item that would need full rebuild
					string model_name = placeableItem.GetModelName();
					if (!model_name || model_name == "bmp" || model_name == "bmp.p3d" || model_name.Length() == 0)
					{
						// This is a class-based item, we need full rebuild
						needsFullRebuild = true;
						break;
					}
					else
					{
						// This is a model-based item, we can restore it individually
						modelItemsToRestore.Insert(placeableItem);
					}
				}
			}
		}
		
		if (needsFullRebuild)
		{
			EditorLog.Info("Class-based items detected, triggering full rebuild");
			RefreshVirtualFoldersWithReload();
			return;
		}
		
		// Second pass: restore model-based items individually
		foreach (EditorPlaceableItem modelItem: modelItemsToRestore)
		{
			RestoreSpecificModelItem(modelItem);
		}
	}
	
	bool CheckIfItemExistsInTree(EditorPlaceableItem item)
	{
		// For model-based items, check m_FolderNodes
		string model_name = item.GetModelName();
		if (model_name && model_name != "bmp" && model_name != "bmp.p3d" && model_name.Length() > 0)
		{
			model_name.Replace(SystemPath.SEPERATOR_ALT, SystemPath.SEPERATOR);
			model_name.ToLower();
			model_name.TrimInPlace();
			
			if (model_name[0] == SystemPath.SEPERATOR) {
				model_name = model_name.Substring(1, model_name.Length() - 1);
			}
			
			return m_FolderNodes.Contains(model_name);
		}
		
		// For class-based items, check if they exist in searchable nodes
		string itemTypeLower = item.Type;
		itemTypeLower.ToLower();
		
		foreach (EditorListNode searchableNode: m_SearchableListNodes)
		{
			EditorPlaceableListNode searchablePlaceableNode = EditorPlaceableListNode.Cast(searchableNode);
			if (searchablePlaceableNode)
			{
				EditorListNode itemNodeParent = searchablePlaceableNode.GetListParent();
				bool isInVirtualFolder = (itemNodeParent && itemNodeParent.IsInherited(EditorVirtualFolderListNode));
				
				if (!isInVirtualFolder && searchablePlaceableNode.FilterType(itemTypeLower, false))
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	void RestoreSpecificModelItem(EditorPlaceableItem item)
	{
		// Item doesn't exist in tree, need to restore it (model-based items only)
		EditorLog.Info("Restoring missing model item: " + item.Type);
		
		string model_name = item.GetModelName();
		model_name.Replace(SystemPath.SEPERATOR_ALT, SystemPath.SEPERATOR);
		model_name.ToLower();
		model_name.TrimInPlace();
		
		if (model_name[0] == SystemPath.SEPERATOR) {
			model_name = model_name.Substring(1, model_name.Length() - 1);
		}
		
		// Create the item node
		EditorPlaceableListNode placeable_node = new EditorPlaceableListNode(item);
		m_FolderNodes[model_name] = placeable_node;
		
		// Find or create the parent folder
		string model_directory = model_name.Substring(0, model_name.LastIndexOf(SystemPath.SEPERATOR));
		
		// Ensure parent folder exists
		if (!m_FolderNodes.Contains(model_directory))
		{
			CreateMissingFolderPath(model_directory);
		}
		
		// Add item to parent folder
		EditorListNode parentNode = m_FolderNodes[model_directory];
		if (parentNode)
		{
			parentNode.InsertChild(placeable_node);
		}
		
		// Add to searchable list
		m_SearchableListNodes.Insert(placeable_node);
		
		// Add to depth tracking
		array<string> model_path_split = {};
		model_name.Split(SystemPath.SEPERATOR, model_path_split);
		int depth = model_path_split.Count() - 1;
		
		if (!m_FolderNodesByDepth[depth]) {
			m_FolderNodesByDepth[depth] = {};
		}	
		
		m_FolderNodesByDepth[depth].Insert(placeable_node);
	}
	
	void CreateMissingFolderPath(string folderPath)
	{
		// Split the path and ensure all parent folders exist
		array<string> path_parts = {};
		folderPath.Split(SystemPath.SEPERATOR, path_parts);
		
		for (int i = 0; i < path_parts.Count(); i++)
		{
			string current_path = string.Empty;
			for (int j = 0; j <= i; j++) {
				current_path += path_parts[j];
				if (j != i) {
					current_path += SystemPath.SEPERATOR;
				}
			}
			
			// If this folder doesn't exist, create it
			if (!m_FolderNodes.Contains(current_path))
			{
				EditorLog.Info("Creating missing folder: " + current_path);
				
				EditorFolderListNode folder_node = new EditorFolderListNode(path_parts[i]);
				m_FolderNodes[current_path] = folder_node;
				
				if (!m_FolderNodesByDepth[i]) {
					m_FolderNodesByDepth[i] = {};
				}
				
				m_FolderNodesByDepth[i].Insert(folder_node);
				
				// Add to parent or root
				if (i == 0) {
					m_TemplateController.LeftContent.Insert(folder_node);
				} else {
					string parent_path = current_path.Substring(0, current_path.LastIndexOf(SystemPath.SEPERATOR));
					EditorFolderListNode parent_node = m_FolderNodes[parent_path];
					if (parent_node) {
						parent_node.InsertChild(folder_node);
					}
				}
			}
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
			string virtualFolderName = folderManager.GetItemFolder(placeableItem);
			// If item is NOT in any virtual folder, check if it exists in the tree
			if (virtualFolderName == string.Empty)
			{
				bool itemExists = false;
				
				// Check model-based items
				string model_name = placeableItem.GetModelName();
				if (model_name && model_name != "bmp" && model_name != "bmp.p3d")
				{
					itemExists = m_FolderNodes.Contains(model_name);
				}
				else
				{
					// Check class-based items in searchable nodes
					string itemTypeLower = placeableItem.Type;
					itemTypeLower.ToLower();
					
					foreach (EditorListNode searchableNode: m_SearchableListNodes)
					{
						EditorPlaceableListNode searchablePlaceableNode = EditorPlaceableListNode.Cast(searchableNode);
						if (searchablePlaceableNode)
						{
							EditorListNode itemNodeParent = searchablePlaceableNode.GetListParent();
							bool isInVirtualFolder = (itemNodeParent && itemNodeParent.IsInherited(EditorVirtualFolderListNode));
							
							if (!isInVirtualFolder && searchablePlaceableNode.FilterType(itemTypeLower, false))
							{
								itemExists = true;
								break;
							}
						}
					}
				}
				
				// If item doesn't exist in the tree but should, we need a reload
				if (!itemExists)
				{
					needsReload = true;
					break;
				}
			}
		}
		
		if (needsReload)
		{
			EditorLog.Info("Items removed from virtual folders detected, triggering full reload to restore them");
			// Clear selection first to prevent issues
			ClearSelection();
			// Do a full reload which will rebuild the entire tree structure
			LoadVirtualFolders();
			// Stop here since LoadVirtualFolders already handles everything
			m_SuppressFolderCollapse = false;
			return;
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
		
		// Now hide only the virtualized items
		foreach (EditorPlaceableItem virtualizedItem: virtualizedItems)
		{
			HideOriginalItemNode(virtualizedItem);
		}
		
	}
	
	void HideOriginalItemNode(EditorPlaceableItem item)
	{
		// Determine HOW this item is classified in virtual folders
		EditorVirtualFolderManager folderManager = EditorVirtualFolderManager.GetInstance();
		string virtualFolderName = folderManager.GetItemFolder(item);
		if (virtualFolderName == string.Empty)
		{
			EditorLog.Warning("Item not in any virtual folder, shouldn't be hiding: " + item.Type);
			return;
		}
		
		EditorVirtualFolderData folderData = folderManager.GetFolder(virtualFolderName);
		if (!folderData)
		{
			EditorLog.Warning("Could not find virtual folder data: " + virtualFolderName);
			return;
		}
		
		int hiddenCount = 0;
		
		// Determine the classification type and hide only the matching type
		bool isClassNameMatch = folderData.ContainsClassName(item.Type);
		bool isModelPathMatch = folderData.ContainsModelPath(item.GetModelName());
		bool isRootFolderMatch = folderData.ContainsItemByData(item.Type, item.GetModelName(), item.Path) && !isClassNameMatch && !isModelPathMatch;
		
		// Only hide model-based items if it was added as a ModelPath
		if (isModelPathMatch && !isClassNameMatch)
		{
			string model_name = item.GetModelName();
			if (model_name)
			{
				model_name.Replace(SystemPath.SEPERATOR_ALT, SystemPath.SEPERATOR);
				model_name.ToLower();
				model_name.TrimInPlace();
				
				if (model_name.Length() > 0 && model_name[0] == SystemPath.SEPERATOR) {
					model_name = model_name.Substring(1, model_name.Length() - 1);
				}
				
				if (model_name != "" && model_name != "bmp" && model_name != "bmp.p3d")
				{
					if (m_FolderNodes.Contains(model_name))
					{
						EditorListNode node = m_FolderNodes.Get(model_name);
						EditorPlaceableListNode placeableNode = EditorPlaceableListNode.Cast(node);
						if (placeableNode)
						{
							EditorListNode parentNode = placeableNode.GetListParent();
							if (parentNode)
							{
								parentNode.ChildrenItems.RemoveItem(placeableNode);
							}
							placeableNode.GetLayoutRoot().Unlink();
							m_SearchableListNodes.RemoveItem(placeableNode);
							m_FolderNodes.Remove(model_name);
							
							hiddenCount++;
						}
					}
				}
			}
		}
		
		// Only hide class-based items if it was added as a ClassName
		if (isClassNameMatch && !isModelPathMatch)
		{
			EditorListNode classNodeToRemove = null;
			
			foreach (EditorListNode searchableNode: m_SearchableListNodes)
			{
				EditorPlaceableListNode searchablePlaceableNode = EditorPlaceableListNode.Cast(searchableNode);
				if (searchablePlaceableNode)
				{
					EditorListNode itemNodeParent = searchablePlaceableNode.GetListParent();
					bool isInVirtualFolder = (itemNodeParent && itemNodeParent.IsInherited(EditorVirtualFolderListNode));
					
					string itemTypeLower = item.Type;
					itemTypeLower.ToLower();
					if (!isInVirtualFolder && searchablePlaceableNode.FilterType(itemTypeLower, false))
					{
						classNodeToRemove = searchableNode;
						break;
					}
				}
			}
			
			if (classNodeToRemove)
			{
				EditorPlaceableListNode removeablePlaceableNode = EditorPlaceableListNode.Cast(classNodeToRemove);
				if (removeablePlaceableNode)
				{
					EditorListNode removeableParentNode = removeablePlaceableNode.GetListParent();
					if (removeableParentNode)
					{
						removeableParentNode.ChildrenItems.RemoveItem(removeablePlaceableNode);
					}
					removeablePlaceableNode.GetLayoutRoot().Unlink();
					m_SearchableListNodes.RemoveItem(removeablePlaceableNode);
					
					hiddenCount++;
				}
			}
		}
		
		// Hide root folder items
		if (isRootFolderMatch)
		{
			EditorListNode rootFolderNodeToRemove = null;
			
			foreach (EditorListNode rootFolderSearchableNode: m_SearchableListNodes)
			{
				EditorPlaceableListNode rootFolderPlaceableNode = EditorPlaceableListNode.Cast(rootFolderSearchableNode);
				if (rootFolderPlaceableNode)
				{
					EditorListNode rootFolderItemParent = rootFolderPlaceableNode.GetListParent();
					bool rootFolderIsInVirtualFolder = (rootFolderItemParent && rootFolderItemParent.IsInherited(EditorVirtualFolderListNode));
					
					// For root folder items, we match by checking if this item would be matched by the same root folder logic
					if (!rootFolderIsInVirtualFolder)
					{
						string rootFolderItemType = item.Type;
						rootFolderItemType.ToLower();
						if (rootFolderPlaceableNode.FilterType(rootFolderItemType, false))
						{
							rootFolderNodeToRemove = rootFolderSearchableNode;
							break;
						}
					}
				}
			}
			
			if (rootFolderNodeToRemove)
			{
				EditorPlaceableListNode rootFolderRemovableNode = EditorPlaceableListNode.Cast(rootFolderNodeToRemove);
				if (rootFolderRemovableNode)
				{
					EditorListNode rootFolderRemovableParent = rootFolderRemovableNode.GetListParent();
					if (rootFolderRemovableParent)
					{
						rootFolderRemovableParent.ChildrenItems.RemoveItem(rootFolderRemovableNode);
					}
					rootFolderRemovableNode.GetLayoutRoot().Unlink();
					m_SearchableListNodes.RemoveItem(rootFolderRemovableNode);
					
					hiddenCount++;
				}
			}
		}
	}
	
	void ClearSelection()
	{
		// Clear any selected node to prevent stale references after widget unlinking
		if (EditorListNode.s_SelectedNode)
		{
			EditorListNode.s_SelectedNode.Panel.SetColor(0);
			EditorListNode.s_SelectedNode = null;
		}
	}
	
	void RefreshVirtualFoldersWithReload()
	{
		// Clear any stale selection to prevent crashes
		ClearSelection();
		
		// Use this for major changes that require full reload (like new folder creation)
		LoadVirtualFolders();
	}
	
	
	
	bool IsFolderCollapseSupressed()
	{
		return m_SuppressFolderCollapse;
	}

	void AddToSearchableNodes(EditorListNode node)
	{
		if (node && m_SearchableListNodes)
		{
			m_SearchableListNodes.Insert(node);
		}
	}
	
	void RemoveFromSearchableNodes(EditorListNode node)
	{
		if (node && m_SearchableListNodes)
		{
			m_SearchableListNodes.RemoveItem(node);
		}
	}
	
	void RestoreOriginalItemNode(EditorPlaceableItem item)
	{
		// Re-add the item to its original location in the folder tree
		string model_name = item.GetModelName();
		if (!model_name || model_name == "bmp" || model_name == "bmp.p3d")
			return;
			
		// Check if it's already been restored
		if (m_FolderNodes.Contains(model_name))
			return;
		
		// Create new placeable node
		EditorPlaceableListNode placeable_node = new EditorPlaceableListNode(item);
		m_FolderNodes[model_name] = placeable_node;
		
		// Find parent folder and add as child
		string model_directory = model_name.Substring(0, model_name.LastIndexOf(SystemPath.SEPERATOR));
		if (m_FolderNodes.Contains(model_directory))
		{
			EditorListNode parentNode = m_FolderNodes[model_directory];
			parentNode.InsertChild(placeable_node);
		}
		
		// Add back to searchable list
		m_SearchableListNodes.Insert(placeable_node);
	}
	
}
