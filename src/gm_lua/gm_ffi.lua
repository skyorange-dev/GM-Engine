ffi = require("ffi");

ffi_ctype={}

ffi_dll={}
function DeclarationCType(str)
    local tem=C_DeleteStrBlank(str);
    if ffi_ctype[tem]==nil then
        ffi_ctype[tem]=true;
        ffi.cdef(str);
        return;
    end
    --print(str);
    
end

function LoadDynamicLibraryFile(str)
    local tem=C_GetFileNameSuffix(str);
    if ffi_dll[tem]==nil then
         ffi_dll[tem]=true;
        return ffi.load(str);
    end
     --print(str);
end

-- 声明标准库中的内容
DeclarationCType("typedef intptr_t luaintptr;");
DeclarationCType("void* malloc(size_t size);");
DeclarationCType("void free(void* ptr);");

--声明SDL中的内容
DeclarationCType([[typedef struct {
        int x, y;
        int w, h;
    } SDL_Rect;]]);
DeclarationCType([[typedef short  int16_t;]]);
DeclarationCType([[typedef int16_t Sint16;]]);
DeclarationCType([[typedef unsigned int       uint32_t;]]);
DeclarationCType([[typedef uint32_t Uint32;]]);
DeclarationCType([[typedef unsigned char      uint8_t;]]);
DeclarationCType([[typedef uint8_t Uint8;]]);
DeclarationCType([[typedef int                int32_t;]])
DeclarationCType([[typedef int32_t Sint32;]])
DeclarationCType([[
typedef struct
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} SDL_Color;]])
DeclarationCType([[struct SDL_Renderer;]]);
DeclarationCType([[typedef struct SDL_Renderer SDL_Renderer;]]);
DeclarationCType([[typedef struct SDL_Texture SDL_Texture;]]);
DeclarationCType([[
typedef struct
{
    float x;
    float y;
} SDL_FPoint;]]);
DeclarationCType([[
typedef struct
{
    SDL_FPoint position;        /**< Vertex position, in SDL_Renderer coordinates  */
    SDL_Color  color;           /**< Vertex color */
    SDL_FPoint tex_coord;       /**< Normalized texture coordinates, if needed */
} SDL_Vertex;
]]);
DeclarationCType([[
typedef struct
{
    int x;
    int y;
} SDL_Point;]]);
DeclarationCType([[
typedef struct{
    int allocated;
    Uint8 *abuf;
    Uint32 alen;
    Uint8 volume;       /* Per-sample volume, 0-128 */
} Mix_Chunk;]]);
DeclarationCType([[
typedef enum
{
    SDL_SCANCODE_UNKNOWN = 0,

    SDL_SCANCODE_A = 4,
    SDL_SCANCODE_B = 5,
    SDL_SCANCODE_C = 6,
    SDL_SCANCODE_D = 7,
    SDL_SCANCODE_E = 8,
    SDL_SCANCODE_F = 9,
    SDL_SCANCODE_G = 10,
    SDL_SCANCODE_H = 11,
    SDL_SCANCODE_I = 12,
    SDL_SCANCODE_J = 13,
    SDL_SCANCODE_K = 14,
    SDL_SCANCODE_L = 15,
    SDL_SCANCODE_M = 16,
    SDL_SCANCODE_N = 17,
    SDL_SCANCODE_O = 18,
    SDL_SCANCODE_P = 19,
    SDL_SCANCODE_Q = 20,
    SDL_SCANCODE_R = 21,
    SDL_SCANCODE_S = 22,
    SDL_SCANCODE_T = 23,
    SDL_SCANCODE_U = 24,
    SDL_SCANCODE_V = 25,
    SDL_SCANCODE_W = 26,
    SDL_SCANCODE_X = 27,
    SDL_SCANCODE_Y = 28,
    SDL_SCANCODE_Z = 29,

    SDL_SCANCODE_1 = 30,
    SDL_SCANCODE_2 = 31,
    SDL_SCANCODE_3 = 32,
    SDL_SCANCODE_4 = 33,
    SDL_SCANCODE_5 = 34,
    SDL_SCANCODE_6 = 35,
    SDL_SCANCODE_7 = 36,
    SDL_SCANCODE_8 = 37,
    SDL_SCANCODE_9 = 38,
    SDL_SCANCODE_0 = 39,

    SDL_SCANCODE_RETURN = 40,
    SDL_SCANCODE_ESCAPE = 41,
    SDL_SCANCODE_BACKSPACE = 42,
    SDL_SCANCODE_TAB = 43,
    SDL_SCANCODE_SPACE = 44,

    SDL_SCANCODE_MINUS = 45,
    SDL_SCANCODE_EQUALS = 46,
    SDL_SCANCODE_LEFTBRACKET = 47,
    SDL_SCANCODE_RIGHTBRACKET = 48,
    SDL_SCANCODE_BACKSLASH = 49, 
    SDL_SCANCODE_NONUSHASH = 50, 
    SDL_SCANCODE_SEMICOLON = 51,
    SDL_SCANCODE_APOSTROPHE = 52,
    SDL_SCANCODE_GRAVE = 53, 
    SDL_SCANCODE_COMMA = 54,
    SDL_SCANCODE_PERIOD = 55,
    SDL_SCANCODE_SLASH = 56,

    SDL_SCANCODE_CAPSLOCK = 57,

    SDL_SCANCODE_F1 = 58,
    SDL_SCANCODE_F2 = 59,
    SDL_SCANCODE_F3 = 60,
    SDL_SCANCODE_F4 = 61,
    SDL_SCANCODE_F5 = 62,
    SDL_SCANCODE_F6 = 63,
    SDL_SCANCODE_F7 = 64,
    SDL_SCANCODE_F8 = 65,
    SDL_SCANCODE_F9 = 66,
    SDL_SCANCODE_F10 = 67,
    SDL_SCANCODE_F11 = 68,
    SDL_SCANCODE_F12 = 69,

    SDL_SCANCODE_PRINTSCREEN = 70,
    SDL_SCANCODE_SCROLLLOCK = 71,
    SDL_SCANCODE_PAUSE = 72,
    SDL_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    SDL_SCANCODE_HOME = 74,
    SDL_SCANCODE_PAGEUP = 75,
    SDL_SCANCODE_DELETE = 76,
    SDL_SCANCODE_END = 77,
    SDL_SCANCODE_PAGEDOWN = 78,
    SDL_SCANCODE_RIGHT = 79,
    SDL_SCANCODE_LEFT = 80,
    SDL_SCANCODE_DOWN = 81,
    SDL_SCANCODE_UP = 82,

    SDL_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    SDL_SCANCODE_KP_DIVIDE = 84,
    SDL_SCANCODE_KP_MULTIPLY = 85,
    SDL_SCANCODE_KP_MINUS = 86,
    SDL_SCANCODE_KP_PLUS = 87,
    SDL_SCANCODE_KP_ENTER = 88,
    SDL_SCANCODE_KP_1 = 89,
    SDL_SCANCODE_KP_2 = 90,
    SDL_SCANCODE_KP_3 = 91,
    SDL_SCANCODE_KP_4 = 92,
    SDL_SCANCODE_KP_5 = 93,
    SDL_SCANCODE_KP_6 = 94,
    SDL_SCANCODE_KP_7 = 95,
    SDL_SCANCODE_KP_8 = 96,
    SDL_SCANCODE_KP_9 = 97,
    SDL_SCANCODE_KP_0 = 98,
    SDL_SCANCODE_KP_PERIOD = 99,

    SDL_SCANCODE_NONUSBACKSLASH = 100, 
    SDL_SCANCODE_APPLICATION = 101,
    SDL_SCANCODE_POWER = 102, 
    SDL_SCANCODE_KP_EQUALS = 103,
    SDL_SCANCODE_F13 = 104,
    SDL_SCANCODE_F14 = 105,
    SDL_SCANCODE_F15 = 106,
    SDL_SCANCODE_F16 = 107,
    SDL_SCANCODE_F17 = 108,
    SDL_SCANCODE_F18 = 109,
    SDL_SCANCODE_F19 = 110,
    SDL_SCANCODE_F20 = 111,
    SDL_SCANCODE_F21 = 112,
    SDL_SCANCODE_F22 = 113,
    SDL_SCANCODE_F23 = 114,
    SDL_SCANCODE_F24 = 115,
    SDL_SCANCODE_EXECUTE = 116,
    SDL_SCANCODE_HELP = 117,    /**< AL Integrated Help Center */
    SDL_SCANCODE_MENU = 118,    /**< Menu (show menu) */
    SDL_SCANCODE_SELECT = 119,
    SDL_SCANCODE_STOP = 120,    /**< AC Stop */
    SDL_SCANCODE_AGAIN = 121,   /**< AC Redo/Repeat */
    SDL_SCANCODE_UNDO = 122,    /**< AC Undo */
    SDL_SCANCODE_CUT = 123,     /**< AC Cut */
    SDL_SCANCODE_COPY = 124,    /**< AC Copy */
    SDL_SCANCODE_PASTE = 125,   /**< AC Paste */
    SDL_SCANCODE_FIND = 126,    /**< AC Find */
    SDL_SCANCODE_MUTE = 127,
    SDL_SCANCODE_VOLUMEUP = 128,
    SDL_SCANCODE_VOLUMEDOWN = 129,
    SDL_SCANCODE_KP_COMMA = 133,
    SDL_SCANCODE_KP_EQUALSAS400 = 134,

    SDL_SCANCODE_INTERNATIONAL1 = 135, 
    SDL_SCANCODE_INTERNATIONAL2 = 136,
    SDL_SCANCODE_INTERNATIONAL3 = 137,
    SDL_SCANCODE_INTERNATIONAL4 = 138,
    SDL_SCANCODE_INTERNATIONAL5 = 139,
    SDL_SCANCODE_INTERNATIONAL6 = 140,
    SDL_SCANCODE_INTERNATIONAL7 = 141,
    SDL_SCANCODE_INTERNATIONAL8 = 142,
    SDL_SCANCODE_INTERNATIONAL9 = 143,
    SDL_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
    SDL_SCANCODE_LANG2 = 145, /**< Hanja conversion */
    SDL_SCANCODE_LANG3 = 146, /**< Katakana */
    SDL_SCANCODE_LANG4 = 147, /**< Hiragana */
    SDL_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
    SDL_SCANCODE_LANG6 = 149, /**< reserved */
    SDL_SCANCODE_LANG7 = 150, /**< reserved */
    SDL_SCANCODE_LANG8 = 151, /**< reserved */
    SDL_SCANCODE_LANG9 = 152, /**< reserved */

    SDL_SCANCODE_ALTERASE = 153,    /**< Erase-Eaze */
    SDL_SCANCODE_SYSREQ = 154,
    SDL_SCANCODE_CANCEL = 155,      /**< AC Cancel */
    SDL_SCANCODE_CLEAR = 156,
    SDL_SCANCODE_PRIOR = 157,
    SDL_SCANCODE_RETURN2 = 158,
    SDL_SCANCODE_SEPARATOR = 159,
    SDL_SCANCODE_OUT = 160,
    SDL_SCANCODE_OPER = 161,
    SDL_SCANCODE_CLEARAGAIN = 162,
    SDL_SCANCODE_CRSEL = 163,
    SDL_SCANCODE_EXSEL = 164,

    SDL_SCANCODE_KP_00 = 176,
    SDL_SCANCODE_KP_000 = 177,
    SDL_SCANCODE_THOUSANDSSEPARATOR = 178,
    SDL_SCANCODE_DECIMALSEPARATOR = 179,
    SDL_SCANCODE_CURRENCYUNIT = 180,
    SDL_SCANCODE_CURRENCYSUBUNIT = 181,
    SDL_SCANCODE_KP_LEFTPAREN = 182,
    SDL_SCANCODE_KP_RIGHTPAREN = 183,
    SDL_SCANCODE_KP_LEFTBRACE = 184,
    SDL_SCANCODE_KP_RIGHTBRACE = 185,
    SDL_SCANCODE_KP_TAB = 186,
    SDL_SCANCODE_KP_BACKSPACE = 187,
    SDL_SCANCODE_KP_A = 188,
    SDL_SCANCODE_KP_B = 189,
    SDL_SCANCODE_KP_C = 190,
    SDL_SCANCODE_KP_D = 191,
    SDL_SCANCODE_KP_E = 192,
    SDL_SCANCODE_KP_F = 193,
    SDL_SCANCODE_KP_XOR = 194,
    SDL_SCANCODE_KP_POWER = 195,
    SDL_SCANCODE_KP_PERCENT = 196,
    SDL_SCANCODE_KP_LESS = 197,
    SDL_SCANCODE_KP_GREATER = 198,
    SDL_SCANCODE_KP_AMPERSAND = 199,
    SDL_SCANCODE_KP_DBLAMPERSAND = 200,
    SDL_SCANCODE_KP_VERTICALBAR = 201,
    SDL_SCANCODE_KP_DBLVERTICALBAR = 202,
    SDL_SCANCODE_KP_COLON = 203,
    SDL_SCANCODE_KP_HASH = 204,
    SDL_SCANCODE_KP_SPACE = 205,
    SDL_SCANCODE_KP_AT = 206,
    SDL_SCANCODE_KP_EXCLAM = 207,
    SDL_SCANCODE_KP_MEMSTORE = 208,
    SDL_SCANCODE_KP_MEMRECALL = 209,
    SDL_SCANCODE_KP_MEMCLEAR = 210,
    SDL_SCANCODE_KP_MEMADD = 211,
    SDL_SCANCODE_KP_MEMSUBTRACT = 212,
    SDL_SCANCODE_KP_MEMMULTIPLY = 213,
    SDL_SCANCODE_KP_MEMDIVIDE = 214,
    SDL_SCANCODE_KP_PLUSMINUS = 215,
    SDL_SCANCODE_KP_CLEAR = 216,
    SDL_SCANCODE_KP_CLEARENTRY = 217,
    SDL_SCANCODE_KP_BINARY = 218,
    SDL_SCANCODE_KP_OCTAL = 219,
    SDL_SCANCODE_KP_DECIMAL = 220,
    SDL_SCANCODE_KP_HEXADECIMAL = 221,

    SDL_SCANCODE_LCTRL = 224,
    SDL_SCANCODE_LSHIFT = 225,
    SDL_SCANCODE_LALT = 226, 
    SDL_SCANCODE_LGUI = 227,
    SDL_SCANCODE_RCTRL = 228,
    SDL_SCANCODE_RSHIFT = 229,
    SDL_SCANCODE_RALT = 230, 
    SDL_SCANCODE_RGUI = 231, 

    SDL_SCANCODE_MODE = 257, 
    SDL_SCANCODE_AUDIONEXT = 258,
    SDL_SCANCODE_AUDIOPREV = 259,
    SDL_SCANCODE_AUDIOSTOP = 260,
    SDL_SCANCODE_AUDIOPLAY = 261,
    SDL_SCANCODE_AUDIOMUTE = 262,
    SDL_SCANCODE_MEDIASELECT = 263,
    SDL_SCANCODE_WWW = 264,             
    SDL_SCANCODE_MAIL = 265,
    SDL_SCANCODE_CALCULATOR = 266,      
    SDL_SCANCODE_COMPUTER = 267,
    SDL_SCANCODE_AC_SEARCH = 268,       
    SDL_SCANCODE_AC_HOME = 269,        
    SDL_SCANCODE_AC_BACK = 270,        
    SDL_SCANCODE_AC_FORWARD = 271,      
    SDL_SCANCODE_AC_STOP = 272,        
    SDL_SCANCODE_AC_REFRESH = 273,      
    SDL_SCANCODE_AC_BOOKMARKS = 274,    


    SDL_SCANCODE_BRIGHTNESSDOWN = 275,
    SDL_SCANCODE_BRIGHTNESSUP = 276,
    SDL_SCANCODE_DISPLAYSWITCH = 277, 
    SDL_SCANCODE_KBDILLUMTOGGLE = 278,
    SDL_SCANCODE_KBDILLUMDOWN = 279,
    SDL_SCANCODE_KBDILLUMUP = 280,
    SDL_SCANCODE_EJECT = 281,
    SDL_SCANCODE_SLEEP = 282,           

    SDL_SCANCODE_APP1 = 283,
    SDL_SCANCODE_APP2 = 284,
    SDL_SCANCODE_AUDIOREWIND = 285,
    SDL_SCANCODE_AUDIOFASTFORWARD = 286,
    SDL_SCANCODE_SOFTLEFT = 287,
    SDL_SCANCODE_SOFTRIGHT = 288, 
    SDL_SCANCODE_CALL = 289, 
    SDL_SCANCODE_ENDCALL = 290, 

    SDL_NUM_SCANCODES = 512 
} SDL_Scancode;]]);

--声明自定义结体
DeclarationCType([[
typedef struct
	{
		SDL_Texture* _data;
		int _width;
		int _height;
	} GM_Texture;]]);
DeclarationCType([[
//事件
	typedef struct
	{
		//鼠标信息
		SDL_Point _mouse_position;//鼠标位置
		Uint32 _mouse_message ;//鼠标事件
		Uint8 _mouse_buttondown ;//鼠标被按下的键
		Sint32 _mouse_wheel;//鼠标滚轮滚动
		//键盘信息
		Uint32 _keyboard_message ;//键盘事件
		Uint8 _IsRepeated;//是否重复按下
		SDL_Scancode _keyboard_down;//键盘按下的键

		//窗口信息
		Uint32 _window_message;//窗口事件

		//时间
		size_t _frequency;
		size_t _time;
        size_t _ntime;

	} Event;]])
DeclarationCType([[
//实体
	typedef  int Render;]])
DeclarationCType([[typedef  int Update;]])
DeclarationCType([[typedef int Track;]])
DeclarationCType([[
    typedef struct
	{
	   	SDL_Rect _last_value;//实体的上一次更新所记录的值
		SDL_Rect _last_cvalue;//摄像机的上一次更新所记录的值
		SDL_Rect _cvalue;//摄像机的坐标以及大小
		SDL_Point _coffset;//摄像机偏移量位置
		void* _pr;//绑定的实体
		void* _ipr;//绑定的迭代器
		Track _track;//跟踪方法
		int _priority;//放映画面的优先级
		unsigned char _IsUpdate;//是否需要更新
		unsigned char _IsRender;//是否需要把该摄像机的画面进行渲染
	}Camera;
]])
DeclarationCType([[
    //直接检查消息缓冲区是否有消息进行相关操作
	typedef struct
	{
        size_t _mask[4];//碰撞类型屏蔽
		size_t _maskid[4];//碰撞子类型屏蔽
		void* _ptr;//刚性碰撞箱的缓冲区
		int _width;
		int _height;
		unsigned char _typeid;//实体子类型id
		unsigned char _cap;//刚性碰撞箱缓冲区大小
		unsigned char _type;//实体的碰撞类型
		unsigned char _IsCheck;//是否需要碰撞检测
		unsigned char _IsRigidity;//是否为刚性碰撞箱
	} Collision_Box;]])
DeclarationCType([[

 //用C的方式实现继承与多态，每个具体的实体都要有以下字段
	typedef struct
	{
	   	SDL_Rect _source;//图像截取的矩形
		SDL_Rect _dest;//输出到逻辑窗口的位置和大小
		SDL_Texture** _data;
		unsigned short _rindex;//下次渲染的索引
		unsigned char _IsVisible;//是否可见
		unsigned char _IsUpdate;//是否需要更新数据
		unsigned char _IsWRender;//是否是窗口渲染模式
		unsigned char _IsSDraw;//当实体为Draw类型时为是否静态渲染
		////////////////////////////////////////////////
		void* _ipr;//绑定的迭代器
		Collision_Box* _b_ptr;//与哪个碰撞箱绑定
		Render _render; //执行该实体的渲染逻辑
		Update _update;//执行该实体的数据更新逻辑
		unsigned char _type;//实体类型
	} Entity;]])

DeclarationCType([[

    typedef struct 
	{
		const char* _name;
		const char* _author;
		const char* _description;
		const char* _version;
		const char* _execute;
	}Module;]])
DeclarationCType([[

    typedef union
	{
	    Entity* _lua_ptr;
		intptr_t _c_ptr;
	} GM_Ptr;]])
DeclarationCType([[
	typedef struct 
	{
		void* _entity;
		void* _check;
		size_t _index;
	}UpdateNode;]])
DeclarationCType([[
	//GM提供给外部dll所能使用的接口
	typedef struct 
	{
		void* (*UserMalloc)(size_t num);
		void (*UserFree)(void* ptr);
	}GM_API;
]])
DeclarationCType([[struct lua_State;]])
DeclarationCType([[typedef struct lua_State lua_State;]])
DeclarationCType([[
	typedef struct 
	{
		SDL_Renderer* _render;//对应的render指针
		lua_State* _L;//对应的lua栈
		SDL_Texture* _data;//纹理指针
		int _width;//所创建的纹理宽度
		int _height;//所创建的纹理高度
		int _func;//创建纹理的方法
	}TTexture_Node;
]])

   
    	