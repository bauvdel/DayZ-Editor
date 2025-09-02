class CfgPatches
{
	class Editor
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data", "DZ_Worlds_Chernarusplus_World"};
	};
};


class CfgVehicles
{
	class Static;
	class HouseNoDestruct;
	class BigCamera : HouseNoDestruct
	{
		scope = 2;
		model = "\DayZEditor\Editor\BigCamera.p3d";
	};

	class DSLRCamera : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\CameraNormal.p3d";
	};

	class DSLRCameraChristmas : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\Camera_xmas_Normal.p3d";
	};

	class DSLRCameraAnniversary : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\Camera.p3d";
	};

	class XmasGiftRed1 : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\xmas_gift_red1.p3d";
	};
	class XmasGiftRed2 : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\xmas_gift_red2.p3d";
	};
	class XmasGiftGreen1 : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\xmas_gift_green1.p3d";
	};
	class XmasGiftGreen2 : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\xmas_gift_green2.p3d";
	};
	class XmasGiftBlue1 : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\xmas_gift_blue1.p3d";
	};
	class XmasGiftBlue2 : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\xmas_gift_blue2.p3d";
	};

	class GizmoBase : HouseNoDestruct
	{
		scope = 0;
	};

	class GizmoTranslation : GizmoBase
	{
		scope = 1;
		model = "\DayZEditor\Editor\MoveGizmo.p3d";
		hiddenSelections[] = {
			"origin_ball",
			"x_arrow", 
			"y_arrow", 
			"z_arrow",
			"x_square", 
			"y_square", 
			"z_square"
		};

		hiddenSelectionsTextures[] = {
			"#(argb,8,8,3)color(1.0,1.0,1.0,1.000,co)", 
			"#(argb,8,8,3)color(1.0,0.0,0.0,1.000,co)", 
			"#(argb,8,8,3)color(0.0,1.0,0.0,1.000,co)", 
			"#(argb,8,8,3)color(0.0,0.0,1.0,1.000,co)",
			"#(argb,8,8,3)color(1.0,0.0,0.0,1.000,co)", 
			"#(argb,8,8,3)color(0.0,1.0,0.0,1.000,co)", 
			"#(argb,8,8,3)color(0.0,0.0,1.0,1.000,co)"
		};

		hiddenSelectionsMaterials[] = {
			"DayZEditor\\Editor\\data\\no_sort.rvmat", 
			"DayZEditor\\Editor\\data\\no_sort.rvmat", 
			"DayZEditor\\Editor\\data\\no_sort.rvmat", 
			"DayZEditor\\Editor\\data\\no_sort.rvmat",
			"DayZEditor\\Editor\\data\\no_sort.rvmat", 
			"DayZEditor\\Editor\\data\\no_sort.rvmat", 
			"DayZEditor\\Editor\\data\\no_sort.rvmat"
		};
	};

	class GizmoRotation: GizmoBase
	{
		scope = 1;
		model = "\DayZEditor\Editor\RotateGizmo.p3d";
		hiddenSelections[] = {
			"x",
			"y",
			"z"
		};

		hiddenSelectionsTextures[] = {
			"#(argb,8,8,3)color(1.0,0.0,0.0,1.000,co)", 
			"#(argb,8,8,3)color(0.0,1.0,0.0,1.000,co)", 
			"#(argb,8,8,3)color(0.0,0.0,1.0,1.000,co)"
		};

		hiddenSelectionsMaterials[] = {
			"DayZEditor\\Editor\\data\\no_sort.rvmat", 
			"DayZEditor\\Editor\\data\\no_sort.rvmat", 
			"DayZEditor\\Editor\\data\\no_sort.rvmat"
		};
	};

	class GizmoScale: GizmoBase
	{
		scope = 1;
		model = "\DayZEditor\Editor\ScaleGizmo.p3d";
	};

	class BrushBase : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\BrushBase.p3d";
		hiddenSelections[] = {"BrushBase"};
		hiddenSelectionTextures[] = { "DayZEditor\Editor\data\BrushDelete.paa" };
		shadow = 0;
	};

	class BoundingBoxBase : HouseNoDestruct
	{
		scope = 1;
		model = "\DayZEditor\Editor\BoundingBoxBase.p3d";
		hiddenSelections[] = {"BoundingBoxSelection"};
		shadow = 0;
	};

	class EditorLootPoint : HouseNoDestruct
	{
		scope=2;
		model="DayZEditor\editor\DebugCylinder.p3d";
	};

	class Egg : HouseNoDestruct
	{
		scope=2;
		model="DZ\gear\food\eeg.p3d";
	};

	class DZE_Logo_Graffiti : HouseNoDestruct
	{
		scope=2;
		displayName="DZE_Logo_Graffiti";
		descriptionShort="Hype train is a hoax";
		model="\DayZEditor\Editor\Logo_Graffiti.p3d";
		shadow = 0;
	};
	/*
		class CinematicCamera: HouseNoDestruct
		{
			scope = 1;
			model = "\DayZEditor\Editor\CinematicCamera.p3d";
			hiddenSelections[] = {"CinematicCameraHighlight"};
		};*/
	class Inventory_Base;
	class EditorPreviewBase: Inventory_Base
	{
		scope = 0;
		displayName = "";
	};

	#define P3D_PREVIEW(_cls, _model) \
		class _cls: EditorPreviewBase { scope = 1; model = _model; }
        P3D_PREVIEW(preview_b_betulahumilis_1s, "DZ\plants\bush\b_betulaHumilis_1s.p3d");
        P3D_PREVIEW(preview_b_corylusavellana_1f, "DZ\plants\bush\b_corylusAvellana_1f.p3d");
        P3D_PREVIEW(preview_b_corylusavellana_2s, "DZ\plants\bush\b_corylusAvellana_2s.p3d");
        P3D_PREVIEW(preview_b_crataeguslaevigata_1s, "DZ\plants\bush\b_crataegusLaevigata_1s.p3d");
        P3D_PREVIEW(preview_b_crataeguslaevigata_2s, "DZ\plants\bush\b_crataegusLaevigata_2s.p3d");
        P3D_PREVIEW(preview_b_naked_2s, "DZ\plants\bush\b_naked_2s.p3d");
        P3D_PREVIEW(preview_b_prunusspinosa_1s, "DZ\plants\bush\b_prunusSpinosa_1s.p3d");
        P3D_PREVIEW(preview_b_prunusspinosa_2s, "DZ\plants\bush\b_prunusSpinosa_2s.p3d");
        P3D_PREVIEW(preview_b_rosacanina_1s, "DZ\plants\bush\b_rosaCanina_1s.p3d");
        P3D_PREVIEW(preview_b_rosacanina_2s, "DZ\plants\bush\b_rosaCanina_2s.p3d");
        P3D_PREVIEW(preview_b_sambucusnigra_1s, "DZ\plants\bush\b_sambucusNigra_1s.p3d");
        P3D_PREVIEW(preview_b_sambucusnigra_2s, "DZ\plants\bush\b_sambucusNigra_2s.p3d");
        P3D_PREVIEW(preview_c_anthoxanthum, "DZ\plants\clutter\c_Anthoxanthum.p3d");
        P3D_PREVIEW(preview_c_anthoxanthum_bended, "DZ\plants\clutter\c_Anthoxanthum_bended.p3d");
        P3D_PREVIEW(preview_c_broadleaf_sprouts, "DZ\plants\clutter\c_Broadleaf_sprouts.p3d");
        P3D_PREVIEW(preview_c_broadleaf_sprouts_tall, "DZ\plants\clutter\c_Broadleaf_sprouts_tall.p3d");
        P3D_PREVIEW(preview_c_calamagrostis, "DZ\plants\clutter\c_Calamagrostis.p3d");
        P3D_PREVIEW(preview_c_carduus, "DZ\plants\clutter\c_Carduus.p3d");
        P3D_PREVIEW(preview_c_carduus_f, "DZ\plants\clutter\c_Carduus_f.p3d");
        P3D_PREVIEW(preview_c_concretegrass_bunch, "DZ\plants\clutter\c_ConcreteGrass_bunch.p3d");
        P3D_PREVIEW(preview_c_cones, "DZ\plants\clutter\c_Cones.p3d");
        P3D_PREVIEW(preview_c_dirtgrass_bunch, "DZ\plants\clutter\c_DirtGrass_bunch.p3d");
        P3D_PREVIEW(preview_c_elytrigia, "DZ\plants\clutter\c_Elytrigia.p3d");
        P3D_PREVIEW(preview_c_elytrigiadirt, "DZ\plants\clutter\c_ElytrigiaDirt.p3d");
        P3D_PREVIEW(preview_c_elytrigiaforest, "DZ\plants\clutter\c_ElytrigiaForest.p3d");
        P3D_PREVIEW(preview_c_elytrigiatall, "DZ\plants\clutter\c_ElytrigiaTall.p3d");
        P3D_PREVIEW(preview_c_elytrigia_green, "DZ\plants\clutter\c_Elytrigia_green.p3d");
        P3D_PREVIEW(preview_c_hypericum, "DZ\plants\clutter\c_Hypericum.p3d");
        P3D_PREVIEW(preview_c_hypericum_f, "DZ\plants\clutter\c_Hypericum_f.p3d");
        P3D_PREVIEW(preview_c_leafs_spread, "DZ\plants\clutter\c_leafs_spread.p3d");
        P3D_PREVIEW(preview_c_lolium, "DZ\plants\clutter\c_Lolium.p3d");
        P3D_PREVIEW(preview_c_pines, "DZ\plants\clutter\c_Pines.p3d");
        P3D_PREVIEW(preview_c_polypodiophyta, "DZ\plants\clutter\c_Polypodiophyta.p3d");
        P3D_PREVIEW(preview_c_polypodiophyta_b, "DZ\plants\clutter\c_Polypodiophyta_b.p3d");
        P3D_PREVIEW(preview_c_polypodiophyta_c, "DZ\plants\clutter\c_Polypodiophyta_c.p3d");
        P3D_PREVIEW(preview_c_polypodiophyta_tall, "DZ\plants\clutter\c_Polypodiophyta_tall.p3d");
        P3D_PREVIEW(preview_c_taraxacum, "DZ\plants\clutter\c_Taraxacum.p3d");
        P3D_PREVIEW(preview_c_twigs, "DZ\plants\clutter\c_Twigs.p3d");
        P3D_PREVIEW(preview_c_twigs_b, "DZ\plants\clutter\c_Twigs_b.p3d");
        P3D_PREVIEW(preview_c_undergrowth, "DZ\plants\clutter\c_undergrowth.p3d");
        P3D_PREVIEW(preview_c_undergrowth_red, "DZ\plants\clutter\c_undergrowth_red.p3d");
        P3D_PREVIEW(preview_c_vaccinium, "DZ\plants\clutter\c_Vaccinium.p3d");
        P3D_PREVIEW(preview_c_vaccinium_green, "DZ\plants\clutter\c_Vaccinium_green.p3d");
        P3D_PREVIEW(preview_c_vaccinium_red, "DZ\plants\clutter\c_Vaccinium_red.p3d");
        P3D_PREVIEW(preview_c_vaccinium_tall, "DZ\plants\clutter\c_Vaccinium_tall.p3d");
        P3D_PREVIEW(preview_l_large_pile, "DZ\plants\clutter\l_large_pile.p3d");
        P3D_PREVIEW(preview_l_long_pile_a, "DZ\plants\clutter\l_long_pile_a.p3d");
        P3D_PREVIEW(preview_l_long_pile_b, "DZ\plants\clutter\l_long_pile_b.p3d");
        P3D_PREVIEW(preview_l_plane, "DZ\plants\clutter\l_plane.p3d");
        P3D_PREVIEW(preview_l_plane_long, "DZ\plants\clutter\l_plane_long.p3d");
        P3D_PREVIEW(preview_p_articum, "DZ\plants\clutter\p_articum.p3d");
        P3D_PREVIEW(preview_p_helianthus, "DZ\plants\clutter\p_Helianthus.p3d");
        P3D_PREVIEW(preview_p_heracleum, "DZ\plants\clutter\p_heracleum.p3d");
        P3D_PREVIEW(preview_p_phragmites, "DZ\plants\clutter\p_Phragmites.p3d");
        P3D_PREVIEW(preview_p_urtica, "DZ\plants\clutter\p_urtica.p3d");
        P3D_PREVIEW(preview_b_betulapendula_1f, "DZ\plants\tree\b_BetulaPendula_1f.p3d");
        P3D_PREVIEW(preview_b_fagussylvatica_1f, "DZ\plants\tree\b_FagusSylvatica_1f.p3d");
        P3D_PREVIEW(preview_b_piceaabies_1f, "DZ\plants\tree\b_PiceaAbies_1f.p3d");
        P3D_PREVIEW(preview_b_piceaabies_1fb, "DZ\plants\tree\b_PiceaAbies_1fb.p3d");
        P3D_PREVIEW(preview_b_quercusrobur_1f, "DZ\plants\tree\b_quercusRobur_1f.p3d");
        P3D_PREVIEW(preview_d_fagussylvatica_fallen, "DZ\plants\tree\d_FagusSylvatica_fallen.p3d");
        P3D_PREVIEW(preview_d_fagussylvatica_fallenb, "DZ\plants\tree\d_FagusSylvatica_fallenb.p3d");
        P3D_PREVIEW(preview_d_fagussylvatica_fallenc, "DZ\plants\tree\d_FagusSylvatica_fallenc.p3d");
        P3D_PREVIEW(preview_d_fagussylvatica_stump, "DZ\plants\tree\d_FagusSylvatica_stump.p3d");
        P3D_PREVIEW(preview_d_fagussylvatica_stumpb, "DZ\plants\tree\d_FagusSylvatica_stumpb.p3d");
        P3D_PREVIEW(preview_d_fagussylvatica_stumpc, "DZ\plants\tree\d_FagusSylvatica_stumpc.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallen, "DZ\plants\tree\d_piceaabies_fallen.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallenb, "DZ\plants\tree\d_piceaabies_fallenb.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallenc, "DZ\plants\tree\d_piceaabies_fallenc.p3d");
        P3D_PREVIEW(preview_d_piceaabies_stump, "DZ\plants\tree\d_piceaabies_stump.p3d");
        P3D_PREVIEW(preview_d_piceaabies_stumpb, "DZ\plants\tree\d_piceaabies_stumpb.p3d");
        P3D_PREVIEW(preview_d_pinussylvestris_fallen, "DZ\plants\tree\d_PinusSylvestris_fallen.p3d");
        P3D_PREVIEW(preview_d_pinussylvestris_fallenb, "DZ\plants\tree\d_PinusSylvestris_fallenb.p3d");
        P3D_PREVIEW(preview_d_pinussylvestris_fallenc, "DZ\plants\tree\d_PinusSylvestris_fallenc.p3d");
        P3D_PREVIEW(preview_d_pinussylvestris_stump, "DZ\plants\tree\d_PinusSylvestris_stump.p3d");
        P3D_PREVIEW(preview_d_pinussylvestris_stumpb, "DZ\plants\tree\d_PinusSylvestris_stumpb.p3d");
        P3D_PREVIEW(preview_d_quercusrobur_fallenb, "DZ\plants\tree\d_quercusRobur_fallenb.p3d");
        P3D_PREVIEW(preview_d_quercusrobur_fallenc, "DZ\plants\tree\d_quercusRobur_fallenc.p3d");
        P3D_PREVIEW(preview_d_quercusrobur_stump, "DZ\plants\tree\d_quercusRobur_stump.p3d");
        P3D_PREVIEW(preview_d_quercusrobur_stumpb, "DZ\plants\tree\d_quercusRobur_stumpb.p3d");
        P3D_PREVIEW(preview_t_betulapendula_1f, "DZ\plants\tree\t_BetulaPendula_1f.p3d");
        P3D_PREVIEW(preview_t_betulapendula_1fb, "DZ\plants\tree\t_BetulaPendula_1fb.p3d");
        P3D_PREVIEW(preview_t_betulapendula_1s, "DZ\plants\tree\t_BetulaPendula_1s.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2f, "DZ\plants\tree\t_BetulaPendula_2f.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2fb, "DZ\plants\tree\t_BetulaPendula_2fb.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2fc, "DZ\plants\tree\t_BetulaPendula_2fc.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2s, "DZ\plants\tree\t_BetulaPendula_2s.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2w, "DZ\plants\tree\t_BetulaPendula_2w.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3f, "DZ\plants\tree\t_BetulaPendula_3f.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3fb, "DZ\plants\tree\t_BetulaPendula_3fb.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3fc, "DZ\plants\tree\t_BetulaPendula_3fc.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3s, "DZ\plants\tree\t_BetulaPendula_3s.p3d");
        P3D_PREVIEW(preview_t_carpinus_2s, "DZ\plants\tree\t_carpinus_2s.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1f, "DZ\plants\tree\t_FagusSylvatica_1f.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1fb, "DZ\plants\tree\t_FagusSylvatica_1fb.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1fc, "DZ\plants\tree\t_FagusSylvatica_1fc.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1fd, "DZ\plants\tree\t_FagusSylvatica_1fd.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1fe, "DZ\plants\tree\t_FagusSylvatica_1fe.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1s, "DZ\plants\tree\t_FagusSylvatica_1s.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2d, "DZ\plants\tree\t_FagusSylvatica_2d.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2f, "DZ\plants\tree\t_FagusSylvatica_2f.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2fb, "DZ\plants\tree\t_FagusSylvatica_2fb.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2fc, "DZ\plants\tree\t_FagusSylvatica_2fc.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2s, "DZ\plants\tree\t_FagusSylvatica_2s.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2sb, "DZ\plants\tree\t_FagusSylvatica_2sb.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2sb_trail_b, "DZ\plants\tree\t_FagusSylvatica_2sb_Trail_B.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2sb_trail_g, "DZ\plants\tree\t_FagusSylvatica_2sb_Trail_G.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2sb_trail_r, "DZ\plants\tree\t_FagusSylvatica_2sb_Trail_R.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2sb_trail_y, "DZ\plants\tree\t_FagusSylvatica_2sb_Trail_Y.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_3d, "DZ\plants\tree\t_FagusSylvatica_3d.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_3f, "DZ\plants\tree\t_FagusSylvatica_3f.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_3fb, "DZ\plants\tree\t_FagusSylvatica_3fb.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_3fb_test, "DZ\plants\tree\t_FagusSylvatica_3fb_test.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_3s, "DZ\plants\tree\t_FagusSylvatica_3s.p3d");
        P3D_PREVIEW(preview_t_fraxinusexcelsior_2f, "DZ\plants\tree\t_FraxinusExcelsior_2f.p3d");
        P3D_PREVIEW(preview_t_fraxinusexcelsior_2s, "DZ\plants\tree\t_FraxinusExcelsior_2s.p3d");
        P3D_PREVIEW(preview_t_fraxinusexcelsior_2w, "DZ\plants\tree\t_FraxinusExcelsior_2w.p3d");
        P3D_PREVIEW(preview_t_fraxinusexcelsior_3s, "DZ\plants\tree\t_FraxinusExcelsior_3s.p3d");
        P3D_PREVIEW(preview_t_juglansregia_2s, "DZ\plants\tree\t_juglansRegia_2s.p3d");
        P3D_PREVIEW(preview_t_juglansregia_3s, "DZ\plants\tree\t_juglansRegia_3s.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_1f, "DZ\plants\tree\t_LarixDecidua_1f.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_1s, "DZ\plants\tree\t_LarixDecidua_1s.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_2f, "DZ\plants\tree\t_LarixDecidua_2f.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_2fb, "DZ\plants\tree\t_LarixDecidua_2fb.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_2s, "DZ\plants\tree\t_LarixDecidua_2s.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_3f, "DZ\plants\tree\t_LarixDecidua_3f.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_3fb, "DZ\plants\tree\t_LarixDecidua_3fb.p3d");
        P3D_PREVIEW(preview_t_malusdomestica_1s, "DZ\plants\tree\t_malusDomestica_1s.p3d");
        P3D_PREVIEW(preview_t_malusdomestica_2s, "DZ\plants\tree\t_malusDomestica_2s.p3d");
        P3D_PREVIEW(preview_t_malusdomestica_3s, "DZ\plants\tree\t_malusDomestica_3s.p3d");
        P3D_PREVIEW(preview_t_naked_1s, "DZ\plants\tree\t_naked_1s.p3d");
        P3D_PREVIEW(preview_t_naked_2s, "DZ\plants\tree\t_naked_2s.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1f, "DZ\plants\tree\t_PiceaAbies_1f.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1s, "DZ\plants\tree\t_PiceaAbies_1s.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1sb, "DZ\plants\tree\t_PiceaAbies_1sb.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2d, "DZ\plants\tree\t_piceaabies_2d.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2f, "DZ\plants\tree\t_PiceaAbies_2f.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2fb, "DZ\plants\tree\t_PiceaAbies_2fb.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2s, "DZ\plants\tree\t_PiceaAbies_2s.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2sb, "DZ\plants\tree\t_PiceaAbies_2sb.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2s_green_xmas, "DZ\plants\tree\t_PiceaAbies_2s_green_xmas.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2s_xmas, "DZ\plants\tree\t_PiceaAbies_2s_xmas.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3d, "DZ\plants\tree\t_piceaabies_3d.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3f, "DZ\plants\tree\t_PiceaAbies_3f.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3f_trail_b, "DZ\plants\tree\t_PiceaAbies_3f_Trail_B.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3f_trail_g, "DZ\plants\tree\t_PiceaAbies_3f_Trail_G.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3f_trail_r, "DZ\plants\tree\t_PiceaAbies_3f_Trail_R.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3f_trail_y, "DZ\plants\tree\t_PiceaAbies_3f_Trail_Y.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3s, "DZ\plants\tree\t_PiceaAbies_3s.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_1f, "DZ\plants\tree\t_PinusSylvestris_1f.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_1s, "DZ\plants\tree\t_PinusSylvestris_1s.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_2f, "DZ\plants\tree\t_PinusSylvestris_2f.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_2fb, "DZ\plants\tree\t_PinusSylvestris_2fb.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_2s, "DZ\plants\tree\t_PinusSylvestris_2s.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_2sb, "DZ\plants\tree\t_PinusSylvestris_2sb.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_3d, "DZ\plants\tree\t_PinusSylvestris_3d.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_3f, "DZ\plants\tree\t_PinusSylvestris_3f.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_3fb, "DZ\plants\tree\t_PinusSylvestris_3fb.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_3fc, "DZ\plants\tree\t_PinusSylvestris_3fc.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_3s, "DZ\plants\tree\t_PinusSylvestris_3s.p3d");
        P3D_PREVIEW(preview_t_populusalba_1f, "DZ\plants\tree\t_populusAlba_1f.p3d");
        P3D_PREVIEW(preview_t_populusalba_2s, "DZ\plants\tree\t_populusAlba_2s.p3d");
        P3D_PREVIEW(preview_t_populusalba_3s, "DZ\plants\tree\t_populusAlba_3s.p3d");
        P3D_PREVIEW(preview_t_populusnigra_3s, "DZ\plants\tree\t_populusNigra_3s.p3d");
        P3D_PREVIEW(preview_t_prunusdomestica_2s, "DZ\plants\tree\t_prunusDomestica_2s.p3d");
        P3D_PREVIEW(preview_t_pyruscommunis_2s, "DZ\plants\tree\t_pyrusCommunis_2s.p3d");
        P3D_PREVIEW(preview_t_pyruscommunis_3s, "DZ\plants\tree\t_pyrusCommunis_3s.p3d");
        P3D_PREVIEW(preview_t_pyruscommunis_3sb, "DZ\plants\tree\t_pyrusCommunis_3sb.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_1f, "DZ\plants\tree\t_quercusRobur_1f.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_1fb, "DZ\plants\tree\t_quercusRobur_1fb.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_1fc, "DZ\plants\tree\t_quercusRobur_1fc.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_1fd, "DZ\plants\tree\t_quercusRobur_1fd.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_1s, "DZ\plants\tree\t_quercusRobur_1s.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_2d, "DZ\plants\tree\t_quercusRobur_2d.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_2f, "DZ\plants\tree\t_quercusRobur_2f.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_2fb, "DZ\plants\tree\t_quercusRobur_2fb.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_2fc, "DZ\plants\tree\t_quercusRobur_2fc.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_2s, "DZ\plants\tree\t_quercusRobur_2s.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_2sb, "DZ\plants\tree\t_quercusRobur_2sb.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_2sc, "DZ\plants\tree\t_quercusRobur_2sc.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_3d, "DZ\plants\tree\t_quercusRobur_3d.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_3f, "DZ\plants\tree\t_quercusRobur_3f.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_3fb, "DZ\plants\tree\t_quercusRobur_3fb.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_3s, "DZ\plants\tree\t_quercusRobur_3s.p3d");
        P3D_PREVIEW(preview_t_quercusrobur_3sb, "DZ\plants\tree\t_quercusRobur_3sb.p3d");
        P3D_PREVIEW(preview_t_robiniapseudoacacia_1f, "DZ\plants\tree\t_robiniaPseudoacacia_1f.p3d");
        P3D_PREVIEW(preview_t_robiniapseudoacacia_2f, "DZ\plants\tree\t_robiniaPseudoacacia_2f.p3d");
        P3D_PREVIEW(preview_t_robiniapseudoacacia_2s, "DZ\plants\tree\t_robiniaPseudoacacia_2s.p3d");
        P3D_PREVIEW(preview_t_robiniapseudoacacia_3f, "DZ\plants\tree\t_robiniaPseudoacacia_3f.p3d");
        P3D_PREVIEW(preview_t_salixalba_2s, "DZ\plants\tree\t_salixAlba_2s.p3d");
        P3D_PREVIEW(preview_t_salixalba_2sb, "DZ\plants\tree\t_salixAlba_2sb.p3d");
        P3D_PREVIEW(preview_t_salixalba_2sb_swamp, "DZ\plants\tree\t_salixAlba_2sb_swamp.p3d");
        P3D_PREVIEW(preview_t_sorbus_2s, "DZ\plants\tree\t_sorbus_2s.p3d");
        P3D_PREVIEW(preview_t_town_1s, "DZ\plants\tree\t_town_1s.p3d");
        P3D_PREVIEW(preview_t_town_1sb, "DZ\plants\tree\t_town_1sb.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2f_cut, "DZ\plants\tree\cutted_cut\t_FagusSylvatica_2f_cut.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2f_stump, "DZ\plants\tree\cutted_stump\t_FagusSylvatica_2f_stump.p3d");
        P3D_PREVIEW(preview_ivy_a, "DZ\plants_bliss\building\ivy_A.p3d");
        P3D_PREVIEW(preview_ivy_b, "DZ\plants_bliss\building\ivy_B.p3d");
        P3D_PREVIEW(preview_ivy_c, "DZ\plants_bliss\building\ivy_C.p3d");
        P3D_PREVIEW(preview_ivy_c2, "DZ\plants_bliss\building\ivy_C2.p3d");
        P3D_PREVIEW(preview_ivy_d, "DZ\plants_bliss\building\ivy_D.p3d");
        P3D_PREVIEW(preview_ivy_dry_a, "DZ\plants_bliss\building\ivy_dry_A.p3d");
        P3D_PREVIEW(preview_ivy_dry_b, "DZ\plants_bliss\building\ivy_dry_B.p3d");
        P3D_PREVIEW(preview_ivy_dry_c, "DZ\plants_bliss\building\ivy_dry_C.p3d");
        P3D_PREVIEW(preview_ivy_dry_d, "DZ\plants_bliss\building\ivy_dry_D.p3d");
        P3D_PREVIEW(preview_ivy_dry_e, "DZ\plants_bliss\building\ivy_dry_E.p3d");
        P3D_PREVIEW(preview_ivy_dry_f, "DZ\plants_bliss\building\ivy_dry_F.p3d");
        P3D_PREVIEW(preview_ivy_dry_g, "DZ\plants_bliss\building\ivy_dry_G.p3d");
        P3D_PREVIEW(preview_ivy_dry_h, "DZ\plants_bliss\building\ivy_dry_H.p3d");
        P3D_PREVIEW(preview_ivy_dry_i, "DZ\plants_bliss\building\ivy_dry_I.p3d");
        P3D_PREVIEW(preview_ivy_dry_j, "DZ\plants_bliss\building\ivy_dry_J.p3d");
        P3D_PREVIEW(preview_ivy_f, "DZ\plants_bliss\building\ivy_F.p3d");
        P3D_PREVIEW(preview_ivy_g, "DZ\plants_bliss\building\ivy_G.p3d");
        P3D_PREVIEW(preview_ivy_h, "DZ\plants_bliss\building\ivy_H.p3d");
        P3D_PREVIEW(preview_ivy_i, "DZ\plants_bliss\building\ivy_I.p3d");
        P3D_PREVIEW(preview_ivy_j, "DZ\plants_bliss\building\ivy_J.p3d");
        P3D_PREVIEW(preview_ivy_k, "DZ\plants_bliss\building\ivy_K.p3d");
        P3D_PREVIEW(preview_ivy_l, "DZ\plants_bliss\building\ivy_L.p3d");
        P3D_PREVIEW(preview_ivy_m, "DZ\plants_bliss\building\ivy_M.p3d");
        P3D_PREVIEW(preview_ivy_n, "DZ\plants_bliss\building\ivy_N.p3d");
        P3D_PREVIEW(preview_ivy_o, "DZ\plants_bliss\building\ivy_O.p3d");
        P3D_PREVIEW(preview_ivy_p, "DZ\plants_bliss\building\ivy_P.p3d");
        P3D_PREVIEW(preview_ivy_r, "DZ\plants_bliss\building\ivy_R.p3d");
        P3D_PREVIEW(preview_ivy_roof_a, "DZ\plants_bliss\building\ivy_roof_A.p3d");
        P3D_PREVIEW(preview_ivy_roof_b, "DZ\plants_bliss\building\ivy_roof_B.p3d");
        P3D_PREVIEW(preview_ivy_s, "DZ\plants_bliss\building\ivy_S.p3d");
        P3D_PREVIEW(preview_ivy_special_a, "DZ\plants_bliss\building\ivy_special_A.p3d");
        P3D_PREVIEW(preview_ivy_special_b, "DZ\plants_bliss\building\ivy_special_B.p3d");
        P3D_PREVIEW(preview_ivy_special_c, "DZ\plants_bliss\building\Ivy_special_C.p3d");
        P3D_PREVIEW(preview_ivy_special_d, "DZ\plants_bliss\building\ivy_special_D.p3d");
        P3D_PREVIEW(preview_ivy_special_e, "DZ\plants_bliss\building\ivy_special_E.p3d");
        P3D_PREVIEW(preview_ivy_special_f, "DZ\plants_bliss\building\ivy_special_F.p3d");
        P3D_PREVIEW(preview_ivy_t, "DZ\plants_bliss\building\ivy_T.p3d");
        P3D_PREVIEW(preview_ivy_u, "DZ\plants_bliss\building\ivy_U.p3d");
        P3D_PREVIEW(preview_ivy_v, "DZ\plants_bliss\building\ivy_V.p3d");
        P3D_PREVIEW(preview_ivy_x, "DZ\plants_bliss\building\ivy_X.p3d");
        P3D_PREVIEW(preview_poison_ivy, "DZ\plants_bliss\building\poison_ivy.p3d");
        P3D_PREVIEW(preview_b_betulanana_1s_summer, "DZ\plants_bliss\Bush\b_betulaNana_1s_summer.p3d");
        P3D_PREVIEW(preview_b_caraganaarborescens_2s_summer, "DZ\plants_bliss\Bush\b_caraganaArborescens_2s_summer.p3d");
        P3D_PREVIEW(preview_b_corylusheterophylla_1s_summer, "DZ\plants_bliss\Bush\b_corylusHeterophylla_1s_summer.p3d");
        P3D_PREVIEW(preview_b_corylusheterophylla_2s_summer, "DZ\plants_bliss\Bush\b_corylusHeterophylla_2s_summer.p3d");
        P3D_PREVIEW(preview_b_fagussylvatica_1f_summer, "DZ\plants_bliss\Bush\b_FagusSylvatica_1f_summer.p3d");
        P3D_PREVIEW(preview_b_phragmitesaustralis_summer, "DZ\plants_bliss\Bush\b_phragmitesAustralis_summer.p3d");
        P3D_PREVIEW(preview_b_prunusspinosa_1s_summer, "DZ\plants_bliss\Bush\b_prunusSpinosa_1s_summer.p3d");
        P3D_PREVIEW(preview_b_prunusspinosa_2s_summer, "DZ\plants_bliss\Bush\b_prunusSpinosa_2s_summer.p3d");
        P3D_PREVIEW(preview_b_rosacanina_1s_summer, "DZ\plants_bliss\Bush\b_rosaCanina_1s_summer.p3d");
        P3D_PREVIEW(preview_b_rosacanina_2s_summer, "DZ\plants_bliss\Bush\b_rosaCanina_2s_summer.p3d");
        P3D_PREVIEW(preview_b_sambucusnigra_1s_summer, "DZ\plants_bliss\Bush\b_sambucusNigra_1s_summer.p3d");
        P3D_PREVIEW(preview_b_sambucusnigra_2s_summer, "DZ\plants_bliss\Bush\b_sambucusNigra_2s_summer.p3d");
        P3D_PREVIEW(preview_c_beech_big_summer, "DZ\plants_bliss\Clutter\c_beech_big_summer.p3d");
        P3D_PREVIEW(preview_c_beech_mid_summer, "DZ\plants_bliss\Clutter\c_beech_mid_summer.p3d");
        P3D_PREVIEW(preview_c_beech_small_summer, "DZ\plants_bliss\Clutter\c_beech_small_summer.p3d");
        P3D_PREVIEW(preview_c_branchesbig_picea_summer, "DZ\plants_bliss\Clutter\c_branchesBig_picea_summer.p3d");
        P3D_PREVIEW(preview_c_branches_deciduous_summer, "DZ\plants_bliss\Clutter\c_branches_deciduous_summer.p3d");
        P3D_PREVIEW(preview_c_branches_picea_summer, "DZ\plants_bliss\Clutter\c_branches_picea_summer.p3d");
        P3D_PREVIEW(preview_c_concretegrass_bunch_summer, "DZ\plants_bliss\Clutter\c_ConcreteGrass_bunch_summer.p3d");
        P3D_PREVIEW(preview_c_cones_summer, "DZ\plants_bliss\Clutter\c_Cones_summer.p3d");
        P3D_PREVIEW(preview_c_dirtgrass_bunch_summer, "DZ\plants_bliss\Clutter\c_DirtGrass_bunch_summer.p3d");
        P3D_PREVIEW(preview_c_elytrigiadirt_summer, "DZ\plants_bliss\Clutter\c_ElytrigiaDirt_summer.p3d");
        P3D_PREVIEW(preview_c_elytrigiatall2_summer, "DZ\plants_bliss\Clutter\c_ElytrigiaTall2_summer.p3d");
        P3D_PREVIEW(preview_c_elytrigiatall_summer, "DZ\plants_bliss\Clutter\c_ElytrigiaTall_summer.p3d");
        P3D_PREVIEW(preview_c_elytrigia_green_summer, "DZ\plants_bliss\Clutter\c_Elytrigia_green_summer.p3d");
        P3D_PREVIEW(preview_c_elytrigia_summer, "DZ\plants_bliss\Clutter\c_Elytrigia_summer.p3d");
        P3D_PREVIEW(preview_c_ferntall_summer, "DZ\plants_bliss\Clutter\c_fernTall_summer.p3d");
        P3D_PREVIEW(preview_c_fern_summer, "DZ\plants_bliss\Clutter\c_fern_summer.p3d");
        P3D_PREVIEW(preview_c_grassanthoxanthum_bended_summer, "DZ\plants_bliss\Clutter\c_GrassAnthoxanthum_bended_summer.p3d");
        P3D_PREVIEW(preview_c_grassanthoxanthum_summer, "DZ\plants_bliss\Clutter\c_GrassAnthoxanthum_summer.p3d");
        P3D_PREVIEW(preview_c_grassbasecarduus_f_summer, "DZ\plants_bliss\Clutter\c_GrassBaseCarduus_f_summer.p3d");
        P3D_PREVIEW(preview_c_grassbasehypericum_summer, "DZ\plants_bliss\Clutter\c_GrassBaseHypericum_summer.p3d");
        P3D_PREVIEW(preview_c_grasscropcarduus_f_summer, "DZ\plants_bliss\Clutter\c_GrassCropCarduus_f_summer.p3d");
        P3D_PREVIEW(preview_c_grasscrophypericum_summer, "DZ\plants_bliss\Clutter\c_GrassCropHypericum_summer.p3d");
        P3D_PREVIEW(preview_c_grassdry2_summer, "DZ\plants_bliss\Clutter\c_GrassDry2_summer.p3d");
        P3D_PREVIEW(preview_c_grassdry3_summer, "DZ\plants_bliss\Clutter\c_GrassDry3_summer.p3d");
        P3D_PREVIEW(preview_c_grassdrycarduus_f_summer, "DZ\plants_bliss\Clutter\c_GrassDryCarduus_f_summer.p3d");
        P3D_PREVIEW(preview_c_grassdryhypericum_summer, "DZ\plants_bliss\Clutter\c_GrassDryHypericum_summer.p3d");
        P3D_PREVIEW(preview_c_grassdryplant1_summer, "DZ\plants_bliss\Clutter\c_GrassDryPlant1_summer.p3d");
        P3D_PREVIEW(preview_c_grassdrytall2_summer, "DZ\plants_bliss\Clutter\c_GrassDryTall2_summer.p3d");
        P3D_PREVIEW(preview_c_grassdrytall3_summer, "DZ\plants_bliss\Clutter\c_GrassDryTall3_summer.p3d");
        P3D_PREVIEW(preview_c_grassdrytall_summer, "DZ\plants_bliss\Clutter\c_GrassDryTall_summer.p3d");
        P3D_PREVIEW(preview_c_grassdry_summer, "DZ\plants_bliss\Clutter\c_GrassDry_summer.p3d");
        P3D_PREVIEW(preview_c_grassflowerspurpleshort_summer, "DZ\plants_bliss\Clutter\c_GrassFlowersPurpleShort_summer.p3d");
        P3D_PREVIEW(preview_c_grassflowerspurpletall_summer, "DZ\plants_bliss\Clutter\c_GrassFlowersPurpleTall_summer.p3d");
        P3D_PREVIEW(preview_c_grassflowerspurple_summer, "DZ\plants_bliss\Clutter\c_GrassFlowersPurple_summer.p3d");
        P3D_PREVIEW(preview_c_grassflowerswhiteshort_summer, "DZ\plants_bliss\Clutter\c_GrassFlowersWhiteShort_summer.p3d");
        P3D_PREVIEW(preview_c_grassflowerswhitetall_summer, "DZ\plants_bliss\Clutter\c_GrassFlowersWhiteTall_summer.p3d");
        P3D_PREVIEW(preview_c_grassflowerswhite_summer, "DZ\plants_bliss\Clutter\c_GrassFlowersWhite_summer.p3d");
        P3D_PREVIEW(preview_c_grassflowersyellowshort_summer, "DZ\plants_bliss\Clutter\c_GrassFlowersYellowShort_summer.p3d");
        P3D_PREVIEW(preview_c_grassflowersyellowtall_summer, "DZ\plants_bliss\Clutter\c_GrassFlowersYellowTall_summer.p3d");
        P3D_PREVIEW(preview_c_grassflowersyellow_summer, "DZ\plants_bliss\Clutter\c_GrassFlowersYellow_summer.p3d");
        P3D_PREVIEW(preview_c_grasslow_summer, "DZ\plants_bliss\Clutter\c_GrassLow_summer.p3d");
        P3D_PREVIEW(preview_c_grassplant1_summer, "DZ\plants_bliss\Clutter\c_GrassPlant1_summer.p3d");
        P3D_PREVIEW(preview_c_grassplant2_summer, "DZ\plants_bliss\Clutter\c_GrassPlant2_summer.p3d");
        P3D_PREVIEW(preview_c_grasssmallconc_summer, "DZ\plants_bliss\Clutter\c_GrassSmallConc_summer.p3d");
        P3D_PREVIEW(preview_c_grasssmall_summer, "DZ\plants_bliss\Clutter\c_GrassSmall_summer.p3d");
        P3D_PREVIEW(preview_c_grasstall2_summer, "DZ\plants_bliss\Clutter\c_GrassTall2_summer.p3d");
        P3D_PREVIEW(preview_c_grasstall3_summer, "DZ\plants_bliss\Clutter\c_GrassTall3_summer.p3d");
        P3D_PREVIEW(preview_c_grasstinyconc_summer, "DZ\plants_bliss\Clutter\c_GrassTinyConc_summer.p3d");
        P3D_PREVIEW(preview_c_grasstiny_summer, "DZ\plants_bliss\Clutter\c_GrassTiny_summer.p3d");
        P3D_PREVIEW(preview_c_grass_flower1_summer, "DZ\plants_bliss\Clutter\c_Grass_flower1_summer.p3d");
        P3D_PREVIEW(preview_c_grass_summer, "DZ\plants_bliss\Clutter\c_Grass_summer.p3d");
        P3D_PREVIEW(preview_c_leaves_dead_half_summer, "DZ\plants_bliss\Clutter\c_leaves_dead_half_summer.p3d");
        P3D_PREVIEW(preview_c_leaves_dead_summer, "DZ\plants_bliss\Clutter\c_leaves_dead_summer.p3d");
        P3D_PREVIEW(preview_c_pines_summer, "DZ\plants_bliss\Clutter\c_Pines_summer.p3d");
        P3D_PREVIEW(preview_c_plantssmall1_summer, "DZ\plants_bliss\Clutter\c_plantsSmall1_summer.p3d");
        P3D_PREVIEW(preview_c_plantssmall2_summer, "DZ\plants_bliss\Clutter\c_plantsSmall2_summer.p3d");
        P3D_PREVIEW(preview_c_stubble_summer, "DZ\plants_bliss\Clutter\c_stubble_summer.p3d");
        P3D_PREVIEW(preview_c_vaccinium_summer, "DZ\plants_bliss\Clutter\c_Vaccinium_summer.p3d");
        P3D_PREVIEW(preview_c_wheat1_summer, "DZ\plants_bliss\Clutter\c_wheat1_summer.p3d");
        P3D_PREVIEW(preview_c_wheat2, "DZ\plants_bliss\Clutter\c_wheat2.p3d");
        P3D_PREVIEW(preview_c_wheattall_summer, "DZ\plants_bliss\Clutter\c_wheatTall_summer.p3d");
        P3D_PREVIEW(preview_c_wheat_summer, "DZ\plants_bliss\Clutter\c_wheat_summer.p3d");
        P3D_PREVIEW(preview_b_piceaabies_1fb_summer, "DZ\plants_bliss\Tree\b_PiceaAbies_1fb_summer.p3d");
        P3D_PREVIEW(preview_b_piceaabies_1f_summer, "DZ\plants_bliss\Tree\b_PiceaAbies_1f_summer.p3d");
        P3D_PREVIEW(preview_d_betulapendula_fallen, "DZ\plants_bliss\Tree\d_BetulaPendula_fallen.p3d");
        P3D_PREVIEW(preview_d_betulapendula_stump, "DZ\plants_bliss\Tree\d_BetulaPendula_stump.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallend, "DZ\plants_bliss\Tree\d_piceaabies_fallend.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallene, "DZ\plants_bliss\Tree\d_piceaabies_fallene.p3d");
        P3D_PREVIEW(preview_d_piceaabies_stumpc, "DZ\plants_bliss\Tree\d_piceaabies_stumpc.p3d");
        P3D_PREVIEW(preview_d_piceaabies_stumpd, "DZ\plants_bliss\Tree\d_piceaabies_stumpd.p3d");
        P3D_PREVIEW(preview_t_acer_2s_summer, "DZ\plants_bliss\Tree\t_acer_2s_summer.p3d");
        P3D_PREVIEW(preview_t_betulapendulae_1s_summer, "DZ\plants_bliss\Tree\t_BetulaPendulaE_1s_summer.p3d");
        P3D_PREVIEW(preview_t_betulapendulae_2f_summer, "DZ\plants_bliss\Tree\t_BetulaPendulaE_2f_summer.p3d");
        P3D_PREVIEW(preview_t_betulapendulae_2s_summer, "DZ\plants_bliss\Tree\t_BetulaPendulaE_2s_summer.p3d");
        P3D_PREVIEW(preview_t_betulapendulae_2w_summer, "DZ\plants_bliss\Tree\t_BetulaPendulaE_2w_summer.p3d");
        P3D_PREVIEW(preview_t_betulapendulae_3f_summer, "DZ\plants_bliss\Tree\t_BetulaPendulaE_3f_summer.p3d");
        P3D_PREVIEW(preview_t_betulapendulae_3s_summer, "DZ\plants_bliss\Tree\t_BetulaPendulaE_3s_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvaticae_2s_summer, "DZ\plants_bliss\Tree\t_FagusSylvaticaE_2s_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvaticae_3f_summer, "DZ\plants_bliss\Tree\t_FagusSylvaticaE_3f_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1fb_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_1fb_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1fc_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_1fc_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1fd_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_1fd_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1fe_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_1fe_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1f_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_1f_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_1s_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_1s_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2d_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_2d_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2fb_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_2fb_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2fc_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_2fc_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2f_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_2f_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2sb_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_2sb_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2sb_trail_b_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_2sb_Trail_B_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2sb_trail_g_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_2sb_Trail_G_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2sb_trail_r_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_2sb_Trail_R_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2sb_trail_y_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_2sb_Trail_Y_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_2s_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_2s_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_3d_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_3d_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_3fb_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_3fb_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_3f_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_3f_summer.p3d");
        P3D_PREVIEW(preview_t_fagussylvatica_3s_summer, "DZ\plants_bliss\Tree\t_FagusSylvatica_3s_summer.p3d");
        P3D_PREVIEW(preview_t_juglansregia_2s_summer, "DZ\plants_bliss\Tree\t_juglansRegia_2s_summer.p3d");
        P3D_PREVIEW(preview_t_juglansregia_3s_summer, "DZ\plants_bliss\Tree\t_juglansRegia_3s_summer.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_1f_summer, "DZ\plants_bliss\Tree\t_LarixDecidua_1f_summer.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_1s_summer, "DZ\plants_bliss\Tree\t_LarixDecidua_1s_summer.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_2fb_summer, "DZ\plants_bliss\Tree\t_LarixDecidua_2fb_summer.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_2f_summer, "DZ\plants_bliss\Tree\t_LarixDecidua_2f_summer.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_2s_summer, "DZ\plants_bliss\Tree\t_LarixDecidua_2s_summer.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_3fb_summer, "DZ\plants_bliss\Tree\t_LarixDecidua_3fb_summer.p3d");
        P3D_PREVIEW(preview_t_larixdecidua_3f_summer, "DZ\plants_bliss\Tree\t_LarixDecidua_3f_summer.p3d");
        P3D_PREVIEW(preview_t_malusdomestica_2s_summer, "DZ\plants_bliss\Tree\t_malusDomestica_2s_summer.p3d");
        P3D_PREVIEW(preview_t_malusdomestica_3s_summer, "DZ\plants_bliss\Tree\t_malusDomestica_3s_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1f_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_1f_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1sb_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_1sb_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1s_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_1s_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2fb_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_2fb_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2f_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_2f_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2sb_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_2sb_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2s_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_2s_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3f_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_3f_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3f_trail_b_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_3f_Trail_B_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3f_trail_g_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_3f_Trail_G_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3f_trail_r_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_3f_Trail_R_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3f_trail_y_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_3f_Trail_Y_summer.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3s_summer, "DZ\plants_bliss\Tree\t_PiceaAbies_3s_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_1f_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_1f_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_1s_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_1s_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_2fb_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_2fb_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_2f_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_2f_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_2sb_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_2sb_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_2s_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_2s_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_3d_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_3d_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_3fb_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_3fb_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_3fc_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_3fc_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_3f_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_3f_summer.p3d");
        P3D_PREVIEW(preview_t_pinussylvestris_3s_summer, "DZ\plants_bliss\Tree\t_PinusSylvestris_3s_summer.p3d");
        P3D_PREVIEW(preview_t_populusnigra_3sb_summer, "DZ\plants_bliss\Tree\t_populusNigra_3sb_summer.p3d");
        P3D_PREVIEW(preview_t_pyruscommunis_2s_summer, "DZ\plants_bliss\Tree\t_pyrusCommunis_2s_summer.p3d");
        P3D_PREVIEW(preview_t_pyruscommunis_3s_summer, "DZ\plants_bliss\Tree\t_pyrusCommunis_3s_summer.p3d");
        P3D_PREVIEW(preview_t_salixalba_2sb_summer, "DZ\plants_bliss\Tree\t_salixAlba_2sb_summer.p3d");
        P3D_PREVIEW(preview_t_sorbus_2s_summer, "DZ\plants_bliss\Tree\t_sorbus_2s_summer.p3d");
        P3D_PREVIEW(preview_c_birchleaves, "DZ\plants_sakhal\clutter\c_BirchLeaves.p3d");
        P3D_PREVIEW(preview_c_birchleaves_sparse, "DZ\plants_sakhal\clutter\c_BirchLeaves_Sparse.p3d");
        P3D_PREVIEW(preview_c_browngrass, "DZ\plants_sakhal\clutter\c_BrownGrass.p3d");
        P3D_PREVIEW(preview_c_browngrass_flat, "DZ\plants_sakhal\clutter\c_BrownGrass_Flat.p3d");
        P3D_PREVIEW(preview_c_browngrass_lump, "DZ\plants_sakhal\clutter\c_BrownGrass_Lump.p3d");
        P3D_PREVIEW(preview_c_browngrass_tall, "DZ\plants_sakhal\clutter\c_BrownGrass_Tall.p3d");
        P3D_PREVIEW(preview_c_browngrass_tall2, "DZ\plants_sakhal\clutter\c_BrownGrass_Tall2.p3d");
        P3D_PREVIEW(preview_c_drythistle, "DZ\plants_sakhal\clutter\c_DryThistle.p3d");
        P3D_PREVIEW(preview_c_greengrass_tall, "DZ\plants_sakhal\clutter\c_GreenGrass_Tall.p3d");
        P3D_PREVIEW(preview_c_greengrass_tall2, "DZ\plants_sakhal\clutter\c_GreenGrass_Tall2.p3d");
        P3D_PREVIEW(preview_c_piceacluster, "DZ\plants_sakhal\clutter\c_PiceaCluster.p3d");
        P3D_PREVIEW(preview_c_piceacones, "DZ\plants_sakhal\clutter\c_PiceaCones.p3d");
        P3D_PREVIEW(preview_c_stones, "DZ\plants_sakhal\clutter\c_Stones.p3d");
        P3D_PREVIEW(preview_c_stones_small, "DZ\plants_sakhal\clutter\c_Stones_small.p3d");
        P3D_PREVIEW(preview_c_twigs1, "DZ\plants_sakhal\clutter\c_Twigs1.p3d");
        P3D_PREVIEW(preview_c_twigs2, "DZ\plants_sakhal\clutter\c_Twigs2.p3d");
        P3D_PREVIEW(preview_c_volcanicstones_red, "DZ\plants_sakhal\clutter\c_VolcanicStones_Red.p3d");
        P3D_PREVIEW(preview_c_volcanicstones_yellow, "DZ\plants_sakhal\clutter\c_VolcanicStones_Yellow.p3d");
        P3D_PREVIEW(preview_b_piceaabies_1fb_dark, "DZ\plants_sakhal\dark\b_PiceaAbies_1fb_dark.p3d");
        P3D_PREVIEW(preview_b_piceaabies_1f_dark, "DZ\plants_sakhal\dark\b_PiceaAbies_1f_dark.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallenb_dark, "DZ\plants_sakhal\dark\d_piceaabies_fallenb_dark.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallenc_dark, "DZ\plants_sakhal\dark\d_piceaabies_fallenc_dark.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallend_dark, "DZ\plants_sakhal\dark\d_piceaabies_fallend_dark.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallene_dark, "DZ\plants_sakhal\dark\d_piceaabies_fallene_dark.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallen_dark, "DZ\plants_sakhal\dark\d_piceaabies_fallen_dark.p3d");
        P3D_PREVIEW(preview_d_piceaabies_stumpb_dark, "DZ\plants_sakhal\dark\d_piceaabies_stumpb_dark.p3d");
        P3D_PREVIEW(preview_d_piceaabies_stumpc_dark, "DZ\plants_sakhal\dark\d_piceaabies_stumpc_dark.p3d");
        P3D_PREVIEW(preview_d_piceaabies_stump_dark, "DZ\plants_sakhal\dark\d_piceaabies_stump_dark.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1f_dark, "DZ\plants_sakhal\dark\t_PiceaAbies_1f_dark.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1sb_dark, "DZ\plants_sakhal\dark\t_PiceaAbies_1sb_dark.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1s_dark, "DZ\plants_sakhal\dark\t_PiceaAbies_1s_dark.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2d_dark, "DZ\plants_sakhal\dark\t_piceaabies_2d_dark.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2fb_dark, "DZ\plants_sakhal\dark\t_PiceaAbies_2fb_dark.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2f_dark, "DZ\plants_sakhal\dark\t_PiceaAbies_2f_dark.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2sb_dark, "DZ\plants_sakhal\dark\t_PiceaAbies_2sb_dark.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2s_dark, "DZ\plants_sakhal\dark\t_PiceaAbies_2s_dark.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3d_dark, "DZ\plants_sakhal\dark\t_piceaabies_3d_dark.p3d");
        P3D_PREVIEW(preview_b_piceaabies_1fb_frozen, "DZ\plants_sakhal\frozen\b_PiceaAbies_1fb_frozen.p3d");
        P3D_PREVIEW(preview_b_piceaabies_1f_frozen, "DZ\plants_sakhal\frozen\b_PiceaAbies_1f_frozen.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1f_frozen, "DZ\plants_sakhal\frozen\t_PiceaAbies_1f_frozen.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1sb_frozen, "DZ\plants_sakhal\frozen\t_PiceaAbies_1sb_frozen.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1s_frozen, "DZ\plants_sakhal\frozen\t_PiceaAbies_1s_frozen.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2fb_frozen, "DZ\plants_sakhal\frozen\t_PiceaAbies_2fb_frozen.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2f_frozen, "DZ\plants_sakhal\frozen\t_PiceaAbies_2f_frozen.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2sb_frozen, "DZ\plants_sakhal\frozen\t_PiceaAbies_2sb_frozen.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2s_frozen, "DZ\plants_sakhal\frozen\t_PiceaAbies_2s_frozen.p3d");
        P3D_PREVIEW(preview_b_betulahumilis_1s_latefall, "DZ\plants_sakhal\latefall\b_betulaHumilis_1s_latefall.p3d");
        P3D_PREVIEW(preview_b_betulanana_1s_latefall, "DZ\plants_sakhal\latefall\b_betulaNana_1s_latefall.p3d");
        P3D_PREVIEW(preview_b_betulapendula_1f_latefall, "DZ\plants_sakhal\latefall\b_BetulaPendula_1f_latefall.p3d");
        P3D_PREVIEW(preview_b_caraganaarborescens_2s_leafless, "DZ\plants_sakhal\latefall\b_caraganaArborescens_2s_leafless.p3d");
        P3D_PREVIEW(preview_d_betulapendula_fallen_latefall, "DZ\plants_sakhal\latefall\d_BetulaPendula_fallen_latefall.p3d");
        P3D_PREVIEW(preview_d_betulapendula_stump_latefall, "DZ\plants_sakhal\latefall\d_BetulaPendula_stump_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendulae_2w_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendulaE_2w_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_1fb_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_1fb_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_1f_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_1f_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_1s_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_1s_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2fb_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_2fb_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2fc_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_2fc_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2f_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_2f_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2s_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_2s_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2w_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_2w_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3fb_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_3fb_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3fc_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_3fc_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3f_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_3f_latefall.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3s_latefall, "DZ\plants_sakhal\latefall\t_BetulaPendula_3s_latefall.p3d");
        P3D_PREVIEW(preview_t_populusalba_1f_latefall, "DZ\plants_sakhal\latefall\t_populusAlba_1f_latefall.p3d");
        P3D_PREVIEW(preview_t_populusalba_2s_latefall, "DZ\plants_sakhal\latefall\t_populusAlba_2s_latefall.p3d");
        P3D_PREVIEW(preview_t_populusalba_3s_latefall, "DZ\plants_sakhal\latefall\t_populusAlba_3s_latefall.p3d");
        P3D_PREVIEW(preview_t_populusnigra_3s_latefall, "DZ\plants_sakhal\latefall\t_populusNigra_3s_latefall.p3d");
        P3D_PREVIEW(preview_b_betulahumilis_1s_winter, "DZ\plants_sakhal\winter\b_betulaHumilis_1s_winter.p3d");
        P3D_PREVIEW(preview_b_betulanana_1s_winter, "DZ\plants_sakhal\winter\b_betulaNana_1s_winter.p3d");
        P3D_PREVIEW(preview_b_betulapendula_1f_winter, "DZ\plants_sakhal\winter\b_BetulaPendula_1f_winter.p3d");
        P3D_PREVIEW(preview_b_caraganaarborescens_2s_winter, "DZ\plants_sakhal\winter\b_caraganaArborescens_2s_winter.p3d");
        P3D_PREVIEW(preview_b_piceaabies_1fb_winter, "DZ\plants_sakhal\winter\b_PiceaAbies_1fb_winter.p3d");
        P3D_PREVIEW(preview_b_piceaabies_1f_winter, "DZ\plants_sakhal\winter\b_PiceaAbies_1f_winter.p3d");
        P3D_PREVIEW(preview_d_betulapendula_fallen_winter, "DZ\plants_sakhal\winter\d_BetulaPendula_fallen_winter.p3d");
        P3D_PREVIEW(preview_d_betulapendula_stump_winter, "DZ\plants_sakhal\winter\d_BetulaPendula_stump_winter.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallenb_winter, "DZ\plants_sakhal\winter\d_piceaabies_fallenb_winter.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallenc_winter, "DZ\plants_sakhal\winter\d_piceaabies_fallenc_winter.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallend_winter, "DZ\plants_sakhal\winter\d_piceaabies_fallend_winter.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallene_winter, "DZ\plants_sakhal\winter\d_piceaabies_fallene_winter.p3d");
        P3D_PREVIEW(preview_d_piceaabies_fallen_winter, "DZ\plants_sakhal\winter\d_piceaabies_fallen_winter.p3d");
        P3D_PREVIEW(preview_d_piceaabies_stumpb_winter, "DZ\plants_sakhal\winter\d_piceaabies_stumpb_winter.p3d");
        P3D_PREVIEW(preview_d_piceaabies_stumpc_winter, "DZ\plants_sakhal\winter\d_piceaabies_stumpc_winter.p3d");
        P3D_PREVIEW(preview_d_piceaabies_stump_winter, "DZ\plants_sakhal\winter\d_piceaabies_stump_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendulae_2w_winter, "DZ\plants_sakhal\winter\t_BetulaPendulaE_2w_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_1fb_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_1fb_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_1f_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_1f_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_1s_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_1s_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2fb_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_2fb_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2fc_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_2fc_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2f_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_2f_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2s_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_2s_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_2w_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_2w_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3fb_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_3fb_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3fc_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_3fc_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3f_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_3f_winter.p3d");
        P3D_PREVIEW(preview_t_betulapendula_3s_winter, "DZ\plants_sakhal\winter\t_BetulaPendula_3s_winter.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1f_winter, "DZ\plants_sakhal\winter\t_PiceaAbies_1f_winter.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1sb_winter, "DZ\plants_sakhal\winter\t_PiceaAbies_1sb_winter.p3d");
        P3D_PREVIEW(preview_t_piceaabies_1s_winter, "DZ\plants_sakhal\winter\t_PiceaAbies_1s_winter.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2d_winter, "DZ\plants_sakhal\winter\t_piceaabies_2d_winter.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2fb_winter, "DZ\plants_sakhal\winter\t_PiceaAbies_2fb_winter.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2f_winter, "DZ\plants_sakhal\winter\t_PiceaAbies_2f_winter.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2sb_winter, "DZ\plants_sakhal\winter\t_PiceaAbies_2sb_winter.p3d");
        P3D_PREVIEW(preview_t_piceaabies_2s_winter, "DZ\plants_sakhal\winter\t_PiceaAbies_2s_winter.p3d");
        P3D_PREVIEW(preview_t_piceaabies_3d_winter, "DZ\plants_sakhal\winter\t_piceaabies_3d_winter.p3d");
        P3D_PREVIEW(preview_rock_apart1, "DZ\rocks\rock_apart1.p3d");
        P3D_PREVIEW(preview_rock_apart2, "DZ\rocks\rock_apart2.p3d");
        P3D_PREVIEW(preview_rock_bright_apart1, "DZ\rocks\rock_bright_apart1.p3d");
        P3D_PREVIEW(preview_rock_bright_apart2, "DZ\rocks\rock_bright_apart2.p3d");
        P3D_PREVIEW(preview_rock_bright_monolith1, "DZ\rocks\rock_bright_monolith1.p3d");
        P3D_PREVIEW(preview_rock_bright_monolith2, "DZ\rocks\rock_bright_monolith2.p3d");
        P3D_PREVIEW(preview_rock_bright_monolith3, "DZ\rocks\rock_bright_monolith3.p3d");
        P3D_PREVIEW(preview_rock_bright_monolith4, "DZ\rocks\rock_bright_monolith4.p3d");
        P3D_PREVIEW(preview_rock_bright_spike1, "DZ\rocks\rock_bright_spike1.p3d");
        P3D_PREVIEW(preview_rock_bright_spike2, "DZ\rocks\rock_bright_spike2.p3d");
        P3D_PREVIEW(preview_rock_bright_spike3, "DZ\rocks\rock_bright_spike3.p3d");
        P3D_PREVIEW(preview_rock_bright_wallh1, "DZ\rocks\rock_bright_wallh1.p3d");
        P3D_PREVIEW(preview_rock_bright_wallh2, "DZ\rocks\rock_bright_wallh2.p3d");
        P3D_PREVIEW(preview_rock_bright_wallh3, "DZ\rocks\rock_bright_wallh3.p3d");
        P3D_PREVIEW(preview_rock_bright_wallv, "DZ\rocks\rock_bright_wallv.p3d");
        P3D_PREVIEW(preview_rock_monolith1, "DZ\rocks\rock_monolith1.p3d");
        P3D_PREVIEW(preview_rock_monolith2, "DZ\rocks\rock_monolith2.p3d");
        P3D_PREVIEW(preview_rock_monolith3, "DZ\rocks\rock_monolith3.p3d");
        P3D_PREVIEW(preview_rock_monolith4, "DZ\rocks\rock_monolith4.p3d");
        P3D_PREVIEW(preview_rock_spike1, "DZ\rocks\rock_spike1.p3d");
        P3D_PREVIEW(preview_rock_spike2, "DZ\rocks\rock_spike2.p3d");
        P3D_PREVIEW(preview_rock_spike3, "DZ\rocks\rock_spike3.p3d");
        P3D_PREVIEW(preview_rock_wallh1, "DZ\rocks\rock_wallh1.p3d");
        P3D_PREVIEW(preview_rock_wallh2, "DZ\rocks\rock_wallh2.p3d");
        P3D_PREVIEW(preview_rock_wallh3, "DZ\rocks\rock_wallh3.p3d");
        P3D_PREVIEW(preview_rock_wallv, "DZ\rocks\rock_wallv.p3d");
        P3D_PREVIEW(preview_stone1, "DZ\rocks\stone1.p3d");
        P3D_PREVIEW(preview_stone2, "DZ\rocks\stone2.p3d");
        P3D_PREVIEW(preview_stone3, "DZ\rocks\stone3.p3d");
        P3D_PREVIEW(preview_stone4, "DZ\rocks\stone4.p3d");
        P3D_PREVIEW(preview_stone5, "DZ\rocks\stone5.p3d");
        P3D_PREVIEW(preview_stone5_trail_b, "DZ\rocks\stone5_Trail_B.p3d");
        P3D_PREVIEW(preview_stone5_trail_g, "DZ\rocks\stone5_Trail_G.p3d");
        P3D_PREVIEW(preview_stone5_trail_r, "DZ\rocks\stone5_Trail_R.p3d");
        P3D_PREVIEW(preview_stone5_trail_y, "DZ\rocks\stone5_Trail_Y.p3d");
        P3D_PREVIEW(preview_stones_erosion, "DZ\rocks\stones_erosion.p3d");
        P3D_PREVIEW(preview_snow_rock_apart1, "DZ\rocks\snow_rocks\snow_rock_apart1.p3d");
        P3D_PREVIEW(preview_snow_rock_apart2, "DZ\rocks\snow_rocks\snow_rock_apart2.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_apart1, "DZ\rocks\snow_rocks\snow_rock_bright_apart1.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_apart2, "DZ\rocks\snow_rocks\snow_rock_bright_apart2.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_monolith1, "DZ\rocks\snow_rocks\snow_rock_bright_monolith1.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_monolith2, "DZ\rocks\snow_rocks\snow_rock_bright_monolith2.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_monolith3, "DZ\rocks\snow_rocks\snow_rock_bright_monolith3.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_monolith4, "DZ\rocks\snow_rocks\snow_rock_bright_monolith4.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_spike1, "DZ\rocks\snow_rocks\snow_rock_bright_spike1.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_spike2, "DZ\rocks\snow_rocks\snow_rock_bright_spike2.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_spike3, "DZ\rocks\snow_rocks\snow_rock_bright_spike3.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_wallh1, "DZ\rocks\snow_rocks\snow_rock_bright_wallh1.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_wallh2, "DZ\rocks\snow_rocks\snow_rock_bright_wallh2.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_wallh3, "DZ\rocks\snow_rocks\snow_rock_bright_wallh3.p3d");
        P3D_PREVIEW(preview_snow_rock_bright_wallv, "DZ\rocks\snow_rocks\snow_rock_bright_wallv.p3d");
        P3D_PREVIEW(preview_snow_rock_monolith1, "DZ\rocks\snow_rocks\snow_rock_monolith1.p3d");
        P3D_PREVIEW(preview_snow_rock_monolith2, "DZ\rocks\snow_rocks\snow_rock_monolith2.p3d");
        P3D_PREVIEW(preview_snow_rock_monolith3, "DZ\rocks\snow_rocks\snow_rock_monolith3.p3d");
        P3D_PREVIEW(preview_snow_rock_monolith4, "DZ\rocks\snow_rocks\snow_rock_monolith4.p3d");
        P3D_PREVIEW(preview_snow_rock_spike1, "DZ\rocks\snow_rocks\snow_rock_spike1.p3d");
        P3D_PREVIEW(preview_snow_rock_spike2, "DZ\rocks\snow_rocks\snow_rock_spike2.p3d");
        P3D_PREVIEW(preview_snow_rock_spike3, "DZ\rocks\snow_rocks\snow_rock_spike3.p3d");
        P3D_PREVIEW(preview_snow_rock_wallh1, "DZ\rocks\snow_rocks\snow_rock_wallh1.p3d");
        P3D_PREVIEW(preview_snow_rock_wallh2, "DZ\rocks\snow_rocks\snow_rock_wallh2.p3d");
        P3D_PREVIEW(preview_snow_rock_wallh3, "DZ\rocks\snow_rocks\snow_rock_wallh3.p3d");
        P3D_PREVIEW(preview_snow_rock_wallv, "DZ\rocks\snow_rocks\snow_rock_wallv.p3d");
        P3D_PREVIEW(preview_snow_stone1, "DZ\rocks\snow_rocks\snow_stone1.p3d");
        P3D_PREVIEW(preview_snow_stone2, "DZ\rocks\snow_rocks\snow_stone2.p3d");
        P3D_PREVIEW(preview_snow_stone3, "DZ\rocks\snow_rocks\snow_stone3.p3d");
        P3D_PREVIEW(preview_snow_stone4, "DZ\rocks\snow_rocks\snow_stone4.p3d");
        P3D_PREVIEW(preview_snow_stone5, "DZ\rocks\snow_rocks\snow_stone5.p3d");
        P3D_PREVIEW(preview_snow_stone5_trail_b, "DZ\rocks\snow_rocks\snow_stone5_Trail_B.p3d");
        P3D_PREVIEW(preview_snow_stone5_trail_g, "DZ\rocks\snow_rocks\snow_stone5_Trail_G.p3d");
        P3D_PREVIEW(preview_snow_stone5_trail_r, "DZ\rocks\snow_rocks\snow_stone5_Trail_R.p3d");
        P3D_PREVIEW(preview_snow_stone5_trail_y, "DZ\rocks\snow_rocks\snow_stone5_Trail_Y.p3d");
        P3D_PREVIEW(preview_snow_stones_erosion, "DZ\rocks\snow_rocks\snow_stones_erosion.p3d");
        P3D_PREVIEW(preview_rock_wallh4, "DZ\rocks_bliss\rock_wallh4.p3d");
        P3D_PREVIEW(preview_rock_wallh5, "DZ\rocks_bliss\rock_wallh5.p3d");
        P3D_PREVIEW(preview_rock_wallh6, "DZ\rocks_bliss\rock_wallh6.p3d");
        P3D_PREVIEW(preview_stone10, "DZ\rocks_bliss\stone10.p3d");
        P3D_PREVIEW(preview_stone10_moss, "DZ\rocks_bliss\stone10_moss.p3d");
        P3D_PREVIEW(preview_stone10_moss_lc, "DZ\rocks_bliss\stone10_moss_lc.p3d");
        P3D_PREVIEW(preview_stone6, "DZ\rocks_bliss\stone6.p3d");
        P3D_PREVIEW(preview_stone6_moss, "DZ\rocks_bliss\stone6_moss.p3d");
        P3D_PREVIEW(preview_stone6_moss_lc, "DZ\rocks_bliss\stone6_moss_lc.p3d");
        P3D_PREVIEW(preview_stone7, "DZ\rocks_bliss\stone7.p3d");
        P3D_PREVIEW(preview_stone7_moss, "DZ\rocks_bliss\stone7_moss.p3d");
        P3D_PREVIEW(preview_stone7_moss_lc, "DZ\rocks_bliss\stone7_moss_lc.p3d");
        P3D_PREVIEW(preview_stone7_trail_b, "DZ\rocks_bliss\stone7_Trail_B.p3d");
        P3D_PREVIEW(preview_stone7_trail_g, "DZ\rocks_bliss\stone7_Trail_G.p3d");
        P3D_PREVIEW(preview_stone7_trail_r, "DZ\rocks_bliss\stone7_Trail_R.p3d");
        P3D_PREVIEW(preview_stone7_trail_y, "DZ\rocks_bliss\stone7_Trail_Y.p3d");
        P3D_PREVIEW(preview_stone8, "DZ\rocks_bliss\stone8.p3d");
        P3D_PREVIEW(preview_stone8_carving, "DZ\rocks_bliss\stone8_carving.p3d");
        P3D_PREVIEW(preview_stone8_moss, "DZ\rocks_bliss\stone8_moss.p3d");
        P3D_PREVIEW(preview_stone8_moss_lc, "DZ\rocks_bliss\stone8_moss_lc.p3d");
        P3D_PREVIEW(preview_stone9, "DZ\rocks_bliss\stone9.p3d");
        P3D_PREVIEW(preview_stone9_moss, "DZ\rocks_bliss\stone9_moss.p3d");
        P3D_PREVIEW(preview_stone9_moss_lc, "DZ\rocks_bliss\stone9_moss_lc.p3d");
        P3D_PREVIEW(preview_rock_lava_boulder1, "DZ\rocks_sakhal\rock_lava_boulder1.p3d");
        P3D_PREVIEW(preview_rock_lava_boulder2, "DZ\rocks_sakhal\rock_lava_boulder2.p3d");
        P3D_PREVIEW(preview_rock_lava_boulder3, "DZ\rocks_sakhal\rock_lava_boulder3.p3d");
        P3D_PREVIEW(preview_rock_lava_boulder4, "DZ\rocks_sakhal\rock_lava_boulder4.p3d");
        P3D_PREVIEW(preview_rock_monolith5, "DZ\rocks_sakhal\rock_monolith5.p3d");
        P3D_PREVIEW(preview_rock_monolith5_int, "DZ\rocks_sakhal\rock_monolith5_int.p3d");
        P3D_PREVIEW(preview_rock_monolith5_snow, "DZ\rocks_sakhal\rock_monolith5_snow.p3d");
        P3D_PREVIEW(preview_rock_spike4, "DZ\rocks_sakhal\rock_spike4.p3d");
        P3D_PREVIEW(preview_rock_spike4_int, "DZ\rocks_sakhal\rock_spike4_int.p3d");
        P3D_PREVIEW(preview_rock_spike4_snow, "DZ\rocks_sakhal\rock_spike4_snow.p3d");
        P3D_PREVIEW(preview_rock_wallh7_long, "DZ\rocks_sakhal\rock_wallh7_long.p3d");
        P3D_PREVIEW(preview_rock_wallh7_long_int, "DZ\rocks_sakhal\rock_wallh7_long_int.p3d");
        P3D_PREVIEW(preview_rock_wallh7_long_snow, "DZ\rocks_sakhal\rock_wallh7_long_snow.p3d");
        P3D_PREVIEW(preview_rock_wallh7_round, "DZ\rocks_sakhal\rock_wallh7_round.p3d");
        P3D_PREVIEW(preview_rock_wallh7_round_int, "DZ\rocks_sakhal\rock_wallh7_round_int.p3d");
        P3D_PREVIEW(preview_rock_wallh7_round_snow, "DZ\rocks_sakhal\rock_wallh7_round_snow.p3d");
        P3D_PREVIEW(preview_rock_wallh7_tall, "DZ\rocks_sakhal\rock_wallh7_tall.p3d");
        P3D_PREVIEW(preview_rock_wallh7_tall_int, "DZ\rocks_sakhal\rock_wallh7_tall_int.p3d");
        P3D_PREVIEW(preview_rock_wallh7_tall_painting1, "DZ\rocks_sakhal\rock_wallh7_tall_painting1.p3d");
        P3D_PREVIEW(preview_rock_wallh7_tall_snow, "DZ\rocks_sakhal\rock_wallh7_tall_snow.p3d");
        P3D_PREVIEW(preview_stone10_snow, "DZ\rocks_sakhal\stone10_snow.p3d");
        P3D_PREVIEW(preview_stone10_snow_lc, "DZ\rocks_sakhal\stone10_snow_lc.p3d");
        P3D_PREVIEW(preview_stone11, "DZ\rocks_sakhal\stone11.p3d");
        P3D_PREVIEW(preview_stone11_int, "DZ\rocks_sakhal\stone11_int.p3d");
        P3D_PREVIEW(preview_stone11_lc, "DZ\rocks_sakhal\stone11_lc.p3d");
        P3D_PREVIEW(preview_stone11_snow_lc, "DZ\rocks_sakhal\stone11_snow_lc.p3d");
        P3D_PREVIEW(preview_stone12, "DZ\rocks_sakhal\stone12.p3d");
        P3D_PREVIEW(preview_stone12_lc, "DZ\rocks_sakhal\stone12_lc.p3d");
        P3D_PREVIEW(preview_stone12_snow_lc, "DZ\rocks_sakhal\stone12_snow_lc.p3d");
        P3D_PREVIEW(preview_stone13, "DZ\rocks_sakhal\stone13.p3d");
        P3D_PREVIEW(preview_stone13_lc, "DZ\rocks_sakhal\stone13_lc.p3d");
        P3D_PREVIEW(preview_stone13_snow_lc, "DZ\rocks_sakhal\stone13_snow_lc.p3d");
        P3D_PREVIEW(preview_stone14_lava, "DZ\rocks_sakhal\stone14_lava.p3d");
        P3D_PREVIEW(preview_stone14_lava_lc, "DZ\rocks_sakhal\stone14_lava_lc.p3d");
        P3D_PREVIEW(preview_stone15_lava, "DZ\rocks_sakhal\stone15_lava.p3d");
        P3D_PREVIEW(preview_stone15_lava_lc, "DZ\rocks_sakhal\stone15_lava_lc.p3d");
        P3D_PREVIEW(preview_stone6_snow, "DZ\rocks_sakhal\stone6_snow.p3d");
        P3D_PREVIEW(preview_stone6_snow_lc, "DZ\rocks_sakhal\stone6_snow_lc.p3d");
        P3D_PREVIEW(preview_stone7_snow, "DZ\rocks_sakhal\stone7_snow.p3d");
        P3D_PREVIEW(preview_stone7_snow_lc, "DZ\rocks_sakhal\stone7_snow_lc.p3d");
        P3D_PREVIEW(preview_stone8_snow, "DZ\rocks_sakhal\stone8_snow.p3d");
        P3D_PREVIEW(preview_stone8_snow_lc, "DZ\rocks_sakhal\stone8_snow_lc.p3d");
        P3D_PREVIEW(preview_stone9_snow, "DZ\rocks_sakhal\stone9_snow.p3d");
        P3D_PREVIEW(preview_stone9_snow_lc, "DZ\rocks_sakhal\stone9_snow_lc.p3d");
        P3D_PREVIEW(preview_stones_erosion2, "DZ\rocks_sakhal\stones_erosion2.p3d");
        P3D_PREVIEW(preview_stones_erosion2_snow, "DZ\rocks_sakhal\stones_erosion2_snow.p3d");
        P3D_PREVIEW(preview_stones_lava_cluster1, "DZ\rocks_sakhal\stones_lava_cluster1.p3d");
        P3D_PREVIEW(preview_stones_lava_cluster2, "DZ\rocks_sakhal\stones_lava_cluster2.p3d");
};