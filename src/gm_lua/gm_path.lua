Path={}

local function SetAudioPath(path)
       C_SetAudioPath(path);
end

local function SetImagePath(image_path)
       C_SetImagePath(image_path);
end

local function SetFontPath(font_path)
       C_SetFontPath(font_path);
end

Path.SetAudioPath=SetAudioPath;
Path.SetImagePath=SetImagePath;
Path.SetFontPath=SetFontPath;