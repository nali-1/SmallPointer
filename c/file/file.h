#ifndef SMPThF
	#define SMPThF

	#ifdef SMPT_CM_GEN
		//.c source folder
		#define SMPTFcFACTORY "../source/"
		#define SMPTFcFACTORY_MODEL SMPTFcFACTORY "model"
		#define SMPTFcFACTORY_KEYFRAME SMPTFcFACTORY "keyframe"
	#endif

	#ifdef SMPT_CM_ST_ANDROID
		#define SMPTFcHOME
		//.c package folder
		#define SMPTFcPACKAGE "/storage/emulated/0/Android/data/com.nali.smallpointer/"
		#define SMPTFcSAVE SMPTFcPACKAGE "save/"
		#define SMPTFcREAD_CACHE SMPTFcPACKAGE "c"
	#endif
	#ifdef SMPT_CM_ST_LINUX
		#define SMPTFcHOME "../asset/"
		#define SMPTFcSAVE "save/"
	#endif
	#ifdef SMPT_CM_ST_UI
		#define SMPTFcHOME ""
		#define SMPTFcSAVE "smpt/"
	#endif

	//! will clean this
	#define SMPTFcHOME_SOUND SMPTFcHOME "sound/"
	#define SMPTFcHOME_SOUND_BGM SMPTFcHOME_SOUND "bgm.ogg"

	//#define SMPTFcHOME_IMAGE SMPTFcHOME "image"

	#define SMPTFcHOME_ASSET SMPTFcHOME "asset.bin"
	#define SMPTFcHOME_VERT SMPTFcHOME "vert.spv"
	#define SMPTFcHOME_FRAG SMPTFcHOME "frag.spv"
	#define SMPTFcHOME_COMP SMPTFcHOME "comp.spv"

	#define SMPTFcSAVE_LOG SMPTFcSAVE "log.dat"
	#define SMPTFcSAVE_SPACE SMPTFcSAVE "map.bin"

	//#define SMPTFcSAVE_USER SMPTFcSAVE "user/"
	//#define SMPTFcSAVE_USER_ITEM SMPTFcSAVE "user/item/"
	//#define SMPTFcSAVE_USER_TEAM SMPTFcSAVE "user/team/"

	//#define SMPTFcSAVE_MAP SMPTFcSAVE "map/"

	void *smptfMread(const char *Pc, uint64_t *Pl);
	void *smptfMread1(FILE *Pfile, uint64_t *Pl);
#endif
