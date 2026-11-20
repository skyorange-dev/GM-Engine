local SDL_SCANCODE = {
    UNKNOWN = 0,

    A = 4,  B = 5,  C = 6,  D = 7,  E = 8,
    F = 9,  G = 10, H = 11, I = 12, J = 13,
    K = 14, L = 15, M = 16, N = 17, O = 18,
    P = 19, Q = 20, R = 21, S = 22, T = 23,
    U = 24, V = 25, W = 26, X = 27, Y = 28, Z = 29,

    NUM_1 = 30, NUM_2 = 31, NUM_3 = 32, NUM_4 = 33, NUM_5 = 34,
    NUM_6 = 35, NUM_7 = 36, NUM_8 = 37, NUM_9 = 38, NUM_0 = 39,

    RETURN = 40, ESCAPE = 41, BACKSPACE = 42, TAB = 43, SPACE = 44,

    MINUS = 45, EQUALS = 46,
    LEFTBRACKET = 47, RIGHTBRACKET = 48, BACKSLASH = 49,
    NONUSHASH = 50, SEMICOLON = 51, APOSTROPHE = 52,
    GRAVE = 53, COMMA = 54, PERIOD = 55, SLASH = 56,

    CAPSLOCK = 57,

    F1 = 58,  F2 = 59,  F3 = 60,  F4 = 61,
    F5 = 62,  F6 = 63,  F7 = 64,  F8 = 65,
    F9 = 66,  F10 = 67, F11 = 68, F12 = 69,

    PRINTSCREEN = 70, SCROLLLOCK = 71, PAUSE = 72,
    INSERT = 73, HOME = 74, PAGEUP = 75, DELETE = 76,
    END = 77, PAGEDOWN = 78,
    RIGHT = 79, LEFT = 80, DOWN = 81, UP = 82,

    NUMLOCKCLEAR = 83,
    KP_DIVIDE = 84, KP_MULTIPLY = 85, KP_MINUS = 86, KP_PLUS = 87,
    KP_ENTER = 88,
    KP_1 = 89, KP_2 = 90, KP_3 = 91,
    KP_4 = 92, KP_5 = 93, KP_6 = 94,
    KP_7 = 95, KP_8 = 96, KP_9 = 97,
    KP_0 = 98, KP_PERIOD = 99,

    NONUSBACKSLASH = 100, APPLICATION = 101, POWER = 102,
    KP_EQUALS = 103,
    F13 = 104, F14 = 105, F15 = 106, F16 = 107,
    F17 = 108, F18 = 109, F19 = 110, F20 = 111,
    F21 = 112, F22 = 113, F23 = 114, F24 = 115,
    EXECUTE = 116, HELP = 117, MENU = 118, SELECT = 119,
    STOP = 120, AGAIN = 121, UNDO = 122, CUT = 123,
    COPY = 124, PASTE = 125, FIND = 126,
    MUTE = 127, VOLUMEUP = 128, VOLUMEDOWN = 129,
    KP_COMMA = 133, KP_EQUALSAS400 = 134,

    INTERNATIONAL1 = 135, INTERNATIONAL2 = 136, INTERNATIONAL3 = 137,
    INTERNATIONAL4 = 138, INTERNATIONAL5 = 139, INTERNATIONAL6 = 140,
    INTERNATIONAL7 = 141, INTERNATIONAL8 = 142, INTERNATIONAL9 = 143,
    LANG1 = 144, LANG2 = 145, LANG3 = 146, LANG4 = 147,
    LANG5 = 148, LANG6 = 149, LANG7 = 150, LANG8 = 151, LANG9 = 152,

    ALTERASE = 153, SYSREQ = 154, CANCEL = 155, CLEAR = 156,
    PRIOR = 157, RETURN2 = 158, SEPARATOR = 159, OUT = 160,
    OPER = 161, CLEARAGAIN = 162, CRSEL = 163, EXSEL = 164,

    KP_00 = 176, KP_000 = 177,
    THOUSANDSSEPARATOR = 178, DECIMALSEPARATOR = 179,
    CURRENCYUNIT = 180, CURRENCYSUBUNIT = 181,
    KP_LEFTPAREN = 182, KP_RIGHTPAREN = 183,
    KP_LEFTBRACE = 184, KP_RIGHTBRACE = 185,
    KP_TAB = 186, KP_BACKSPACE = 187,
    KP_A = 188, KP_B = 189, KP_C = 190, KP_D = 191,
    KP_E = 192, KP_F = 193,
    KP_XOR = 194, KP_POWER = 195, KP_PERCENT = 196,
    KP_LESS = 197, KP_GREATER = 198,
    KP_AMPERSAND = 199, KP_DBLAMPERSAND = 200,
    KP_VERTICALBAR = 201, KP_DBLVERTICALBAR = 202,
    KP_COLON = 203, KP_HASH = 204, KP_SPACE = 205,
    KP_AT = 206, KP_EXCLAM = 207,
    KP_MEMSTORE = 208, KP_MEMRECALL = 209, KP_MEMCLEAR = 210,
    KP_MEMADD = 211, KP_MEMSUBTRACT = 212, KP_MEMMULTIPLY = 213,
    KP_MEMDIVIDE = 214, KP_PLUSMINUS = 215,
    KP_CLEAR = 216, KP_CLEARENTRY = 217,
    KP_BINARY = 218, KP_OCTAL = 219, KP_DECIMAL = 220, KP_HEXADECIMAL = 221,

    LCTRL = 224, LSHIFT = 225, LALT = 226, LGUI = 227,
    RCTRL = 228, RSHIFT = 229, RALT = 230, RGUI = 231,

    MODE = 257,
    AUDIONEXT = 258, AUDIOPREV = 259, AUDIOSTOP = 260, AUDIOPLAY = 261,
    AUDIOMUTE = 262, MEDIASELECT = 263, WWW = 264, MAIL = 265,
    CALCULATOR = 266, COMPUTER = 267,
    AC_SEARCH = 268, AC_HOME = 269, AC_BACK = 270, AC_FORWARD = 271,
    AC_STOP = 272, AC_REFRESH = 273, AC_BOOKMARKS = 274,

    BRIGHTNESSDOWN = 275, BRIGHTNESSUP = 276,
    DISPLAYSWITCH = 277, KBDILLUMTOGGLE = 278,
    KBDILLUMDOWN = 279, KBDILLUMUP = 280,
    EJECT = 281, SLEEP = 282,

    APP1 = 283, APP2 = 284,
    AUDIOREWIND = 285, AUDIOFASTFORWARD = 286,
    SOFTLEFT = 287, SOFTRIGHT = 288,
    CALL = 289, ENDCALL = 290,

    NUM_SCANCODES = 512,
}


-- ============================================================
-- SDL_Scancode → 字符/名称 映射表
-- ============================================================
local sdl_scancode_map = {
    -- 字母
    [SDL_SCANCODE.A] = "a", [SDL_SCANCODE.B] = "b", [SDL_SCANCODE.C] = "c",
    [SDL_SCANCODE.D] = "d", [SDL_SCANCODE.E] = "e", [SDL_SCANCODE.F] = "f",
    [SDL_SCANCODE.G] = "g", [SDL_SCANCODE.H] = "h", [SDL_SCANCODE.I] = "i",
    [SDL_SCANCODE.J] = "j", [SDL_SCANCODE.K] = "k", [SDL_SCANCODE.L] = "l",
    [SDL_SCANCODE.M] = "m", [SDL_SCANCODE.N] = "n", [SDL_SCANCODE.O] = "o",
    [SDL_SCANCODE.P] = "p", [SDL_SCANCODE.Q] = "q", [SDL_SCANCODE.R] = "r",
    [SDL_SCANCODE.S] = "s", [SDL_SCANCODE.T] = "t", [SDL_SCANCODE.U] = "u",
    [SDL_SCANCODE.V] = "v", [SDL_SCANCODE.W] = "w", [SDL_SCANCODE.X] = "x",
    [SDL_SCANCODE.Y] = "y", [SDL_SCANCODE.Z] = "z",

    -- 数字
    [SDL_SCANCODE.NUM_1] = "1", [SDL_SCANCODE.NUM_2] = "2",
    [SDL_SCANCODE.NUM_3] = "3", [SDL_SCANCODE.NUM_4] = "4",
    [SDL_SCANCODE.NUM_5] = "5", [SDL_SCANCODE.NUM_6] = "6",
    [SDL_SCANCODE.NUM_7] = "7", [SDL_SCANCODE.NUM_8] = "8",
    [SDL_SCANCODE.NUM_9] = "9", [SDL_SCANCODE.NUM_0] = "0",

    -- 控制字符
    [SDL_SCANCODE.RETURN]    = "Enter",
    [SDL_SCANCODE.ESCAPE]    = "Esc",
    [SDL_SCANCODE.BACKSPACE] = "Backspace",
    [SDL_SCANCODE.TAB]       = "Tab",
    [SDL_SCANCODE.SPACE]     = " ",

    -- 符号
    [SDL_SCANCODE.MINUS]        = "-",
    [SDL_SCANCODE.EQUALS]       = "=",
    [SDL_SCANCODE.LEFTBRACKET]  = "[",
    [SDL_SCANCODE.RIGHTBRACKET] = "]",
    [SDL_SCANCODE.BACKSLASH]    = "\\",
    [SDL_SCANCODE.NONUSHASH]    = "#",
    [SDL_SCANCODE.SEMICOLON]    = ";",
    [SDL_SCANCODE.APOSTROPHE]   = "'",
    [SDL_SCANCODE.GRAVE]        = "`",
    [SDL_SCANCODE.COMMA]        = ",",
    [SDL_SCANCODE.PERIOD]       = ".",
    [SDL_SCANCODE.SLASH]        = "/",

    -- 功能键
    [SDL_SCANCODE.CAPSLOCK] = "CapsLock",
    [SDL_SCANCODE.F1]  = "F1",  [SDL_SCANCODE.F2]  = "F2",
    [SDL_SCANCODE.F3]  = "F3",  [SDL_SCANCODE.F4]  = "F4",
    [SDL_SCANCODE.F5]  = "F5",  [SDL_SCANCODE.F6]  = "F6",
    [SDL_SCANCODE.F7]  = "F7",  [SDL_SCANCODE.F8]  = "F8",
    [SDL_SCANCODE.F9]  = "F9",  [SDL_SCANCODE.F10] = "F10",
    [SDL_SCANCODE.F11] = "F11", [SDL_SCANCODE.F12] = "F12",

    -- 编辑/导航键
    [SDL_SCANCODE.PRINTSCREEN] = "PrintScreen",
    [SDL_SCANCODE.SCROLLLOCK]  = "ScrollLock",
    [SDL_SCANCODE.PAUSE]       = "Pause",
    [SDL_SCANCODE.INSERT]      = "Insert",
    [SDL_SCANCODE.HOME]        = "Home",
    [SDL_SCANCODE.PAGEUP]      = "PageUp",
    [SDL_SCANCODE.DELETE]      = "Delete",
    [SDL_SCANCODE.END]         = "End",
    [SDL_SCANCODE.PAGEDOWN]    = "PageDown",
    [SDL_SCANCODE.RIGHT]       = "Right",
    [SDL_SCANCODE.LEFT]        = "Left",
    [SDL_SCANCODE.DOWN]        = "Down",
    [SDL_SCANCODE.UP]          = "Up",

    -- 小键盘
    [SDL_SCANCODE.NUMLOCKCLEAR] = "NumLock",
    [SDL_SCANCODE.KP_DIVIDE]    = "KP_Divide",
    [SDL_SCANCODE.KP_MULTIPLY]  = "KP_Multiply",
    [SDL_SCANCODE.KP_MINUS]     = "KP_Minus",
    [SDL_SCANCODE.KP_PLUS]      = "KP_Plus",
    [SDL_SCANCODE.KP_ENTER]     = "KP_Enter",
    [SDL_SCANCODE.KP_1] = "KP_1", [SDL_SCANCODE.KP_2] = "KP_2",
    [SDL_SCANCODE.KP_3] = "KP_3", [SDL_SCANCODE.KP_4] = "KP_4",
    [SDL_SCANCODE.KP_5] = "KP_5", [SDL_SCANCODE.KP_6] = "KP_6",
    [SDL_SCANCODE.KP_7] = "KP_7", [SDL_SCANCODE.KP_8] = "KP_8",
    [SDL_SCANCODE.KP_9] = "KP_9", [SDL_SCANCODE.KP_0] = "KP_0",
    [SDL_SCANCODE.KP_PERIOD] = "KP_Period",

    -- 修饰键
    [SDL_SCANCODE.LCTRL]  = "LCtrl",
    [SDL_SCANCODE.LSHIFT] = "LShift",
    [SDL_SCANCODE.LALT]   = "LAlt",
    [SDL_SCANCODE.LGUI]   = "LGUI",
    [SDL_SCANCODE.RCTRL]  = "RCtrl",
    [SDL_SCANCODE.RSHIFT] = "RShift",
    [SDL_SCANCODE.RALT]   = "RAlt",
    [SDL_SCANCODE.RGUI]   = "RGUI",
}

--鼠标按键
local SDL_MOUSE = {
    LEFT=1,
    MIDDLE=2,
    RIGHT=3,
    X1=4,
    X2=5
}

local sdl_mouse_map = {
    [SDL_MOUSE.LEFT] = "Left",
    [SDL_MOUSE.RIGHT]    = "Right",
    [SDL_MOUSE.MIDDLE]  = "Middle",
    [SDL_MOUSE.X1]     = "X1",
    [SDL_MOUSE.X2]      = "X2"
}

local function GetMouseWheelMessage()
       if event.dptr._mouse_message==1027 then
            return tonumber(ffi.cast("int",event.dptr._mouse_wheel));
       else
            return nil;--无滚轮滚动消息
       end
end

local function GetMouseKeyMessage()
       if event.dptr._mouse_message==1025 then
            return sdl_mouse_map[tonumber(ffi.cast("unsigned char",event.dptr._mouse_buttondown))],1;
       elseif event.dptr._mouse_message==1026 then
            return sdl_mouse_map[tonumber(ffi.cast("unsigned char",event.dptr._mouse_buttondown))],0;
       else
            return nil,nil;--无鼠标按键消息
       end
end

local function GetKeyBoardMessage()
   if event.dptr._keyboard_message==768 then
        return sdl_scancode_map[tonumber(ffi.cast("int",event.dptr._keyboard_down))],1;
   elseif event.dptr._keyboard_message==769 then
         return sdl_scancode_map[tonumber(ffi.cast("int",event.dptr._keyboard_down))],0;
   else
        return nil,nil;--无键盘消息
   end
	
end

local function GetMousePosition(camera_t)
	  return camera_t.dptr._cvalue.x+event.dptr._mouse_position.x,camera_t.dptr._cvalue.y+event.dptr._mouse_position.y
end
event={ 
    value=C_GetEventDptr();
    UpdateEvent=C_UpdateEvent;
    GetKeyBoardMessage=GetKeyBoardMessage;
    GetMousePosition=GetMousePosition;
    GetMouseKeyMessage=GetMouseKeyMessage;
    GetMouseWheelMessage=GetMouseWheelMessage;
}

event.dptr=ffi.cast("Event*",event.value);

package.path = package.path .. (";"..stl_path.."?.lua");

local NULL=ffi.NULL;

local delete_array={};

local delete_count=1;

local function DDeleteGRTable(value)
      delete_array[delete_count]=value;
      delete_count=delete_count+1;
end

function GM_Update()
	local t=GM_Update_Func;
	local func=t[1];
	local value=t[2][1];
	local ptr=ffi.cast("UpdateNode*",value);
	local count=t[5];
	local start=1;
	local code=0;
    local node;
    local index;
	for i=start,count do
        node=ptr[i-1];
        index=tonumber(node._index);
		if node._check~= NULL then
			code=func[index](node._entity,node._check,DDeleteGRTable);
		else
			code=func[index](node._entity,0,DDeleteGRTable);
		end
		if code~=0 then
			t.value_count=0;
			return code;
		end
	end

	t.value_count=0;
    
    local dcount=delete_count;
    if dcount~=1 then
        local Delete=grmanager.scene.DeleteGRTable;
        local darray=delete_array;
        for i=1,dcount-1 do
            Delete(darray[i]);
        end

        delete_count=1;
    end
  
	return code;
end

function LoadLocalDll()
    if is_dec==true then
        dofile(work_path.."C/declaration.lua");
    end
	if ExistLocalDll ~=nil then
		if jit.os=="Windows" then
           
			return ffi.load(work_path.."C/local.dll");
		end
	end
end

ldll=LoadLocalDll();

local global_color={0,0,0,0}

local FFI=ffi;
local SDL=LoadDynamicLibraryFile("SDL2.dll");
DeclarationCType([[
int SDL_SetRenderDrawColor(SDL_Renderer* renderer,uint8_t r, uint8_t g, uint8_t b, uint8_t a);
]])
DeclarationCType([[
int SDL_RenderDrawPoint(SDL_Renderer * renderer,int x, int y);
]])
DeclarationCType([[
int SDL_RenderDrawLine(SDL_Renderer * renderer,int x1, int y1, int x2, int y2);
]])
DeclarationCType([[
int SDL_RenderDrawRect(SDL_Renderer * renderer,const SDL_Rect * rect);
]])
DeclarationCType([[
int SDL_RenderFillRect(SDL_Renderer * renderer, const SDL_Rect * rect);
]])
DeclarationCType([[
int SDL_RenderGeometry(SDL_Renderer *renderer,SDL_Texture *texture,const SDL_Vertex *vertices, int num_vertices,const int *indices, int num_indices);
]])

local tem_point=FFI.new("SDL_Point");

function SetRenderDrawColor(render,r,g,b,a)
    global_color[1]=r;
    global_color[2]=g;
    global_color[3]=b;
    global_color[4]=a;
    local renderer=FFI.cast("SDL_Renderer*",render)
    SDL.SDL_SetRenderDrawColor(renderer,r,g,b,a);
end

function RenderDrawPoint(render,x,y,r,g,b,a)
    local renderer=FFI.cast("SDL_Renderer*",render);
    if r~=nil then
        if g~=nil then
            if b~=nil then
                if a~=nil then
                    SDL.SDL_SetRenderDrawColor(renderer,r,g,b,a);
                    SDL.SDL_RenderDrawPoint(renderer,x,y);
                    SDL.SDL_SetRenderDrawColor(renderer,global_color[1],global_color[2],global_color[3],global_color[4]);
                     return;
                end
            end
        end
    end
	SDL.SDL_RenderDrawPoint(renderer,x,y);
end

function RenderDrawPoints(render,t)
    local renderer=FFI.cast("SDL_Renderer*",render);
    for k,v in ipairs(t) do
        SDL.SDL_RenderDrawPoint(renderer,v.x,v.y);
    end
end

function RenderDrawLine(render,x1,y1,x2,y2,r,g,b,a)
    local renderer=FFI.cast("SDL_Renderer*",render);
    if r~=nil then
        if g~=nil then
            if b~=nil then
                if a~=nil then
                    SDL.SDL_SetRenderDrawColor(renderer,r,g,b,a);
                    SDL.SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
                    SDL.SDL_SetRenderDrawColor(renderer,global_color[1],global_color[2],global_color[3],global_color[4]);
                    return;
                end
            end
        end
    end
	SDL.SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
end

function RenderDrawLines(render,t)
    local renderer=FFI.cast("SDL_Renderer*",render);
    for k,v in ipairs(t) do
        SDL.SDL_RenderDrawLine(renderer,v.x1,v.y1,v,x2,v.y2);
    end
end

local tem_rect=FFI.new("SDL_Rect");

function RenderDrawRect(render,x,y,w,h,r,g,b,a)
    local renderer=FFI.cast("SDL_Renderer*",render)
    if r~=nil then
        if g~=nil then
            if b~=nil then
                if a~=nil then
                    SDL.SDL_SetRenderDrawColor(renderer,r,g,b,a);
                    tem_rect.x=x;
                    tem_rect.y=y;
                    tem_rect.w=w;
                    tem_rect.h=h;
                    SDL.SDL_RenderDrawRect(renderer,tem_rect,count);
                    SDL.SDL_SetRenderDrawColor(renderer,global_color[1],global_color[2],global_color[3],global_color[4]);
                     return;
                end
            end
        end
    end
    tem_rect.x=x;
    tem_rect.y=y;
    tem_rect.w=w;
    tem_rect.h=h;
	SDL.SDL_RenderDrawRect(renderer,tem_rect,count);
end

function RenderDrawRects(render,t)
    local renderer=FFI.cast("SDL_Renderer*",render);
    for k,v in ipairs(t) do
        tem_rect.x=v.x;
        tem_rect.y=v.y;
        tem_rect.w=v.w;
        tem_rect.h=v.h;
        SDL.SDL_RenderDrawRect(renderer,tem_rect);
    end
end

function RenderFillRect(render,x,y,w,h,r,g,b,a)
    local renderer=FFI.cast("SDL_Renderer*",render);
    if r~=nil then
        if g~=nil then
            if b~=nil then
                if a~=nil then
                    SDL.SDL_SetRenderDrawColor(renderer,r,g,b,a);
                    tem_rect.x=x;
                    tem_rect.y=y;
                    tem_rect.w=w;
                    tem_rect.h=h;
                    SDL.SDL_RenderFillRect(renderer,tem_rect,count);
                    SDL.SDL_SetRenderDrawColor(renderer,global_color[1],global_color[2],global_color[3],global_color[4]);
                     return;
                end
            end
        end
    end
    tem_rect.x=x;
    tem_rect.y=y;
    tem_rect.w=w;
    tem_rect.h=h;
	SDL.SDL_RenderFillRect(renderer,tem_rect,count);
end

function RenderFillRects(render,t)
    local renderer=FFI.cast("SDL_Renderer*",render);
    for k,v in ipairs(t) do
        tem_rect.x=v.x;
        tem_rect.y=v.y;
        tem_rect.w=v.w;
        tem_rect.h=v.h;
        SDL.SDL_RenderFillRect(renderer,tem_rect);
    end
end




