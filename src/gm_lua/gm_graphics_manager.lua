GM_Texture={}

function GM_Texture.new(ptr)
    local value=ptr;
    local auto_ptr=ffi.cast("GM_Texture*",value);
	ffi.gc(auto_ptr, function(val)
        C_DeleteGM_Texture(value);
    end);
    return {
        value=value,
        dptr=auto_ptr
    }
end


Graphics_Manager={}

function Graphics_Manager.new()
    local image={};
    local text={};
    local tt={};
    local function GetImage(image_name,render)
        if image[image_name]== nil then
            image[image_name]=GM_Texture.new(C_GetImage(image_name,render))
        end
        return  image[image_name];
    end

    local function GetText(font_name,text_size,text_str,render)--字体font_str,字体大小text_size,字符串data
        if text[font_name]~=nil then
            if text[font_name][text_size]~= nuil then
                if  text[font_name][text_size][text_str]~= nuil then
                     return text[font_name][text_size][text_str];
                end
            end
            text[font_name][text_size]={};
        else
            text[font_name]={};
            text[font_name][text_size]={};
        end
        text[font_name][text_size][text_str]=GM_Texture.new(C_GetText(font_name,text_size,text_str,render));
        return text[font_name][text_size][text_str];
    end

    local function GetTTexture(tex_name)
       if  tt[tex_name]== nil then
            tt[tex_name]= C_FindTexture(tex_name)
       end
      
       return tt[tex_name];
    end

    local function Delete()
        for k,v in pairs(image) do
            C_DeleteImage(k);
        end

        for k,v in pairs(text) do
            for i,j in pairs(text[k]) do
                for x,y in pairs(text[k][i]) do
                    C_DeleteText(k,i,x);
                end
            end
        end

        for k,v in pairs(tt) do
            C_DeleteTexture(k);
        end
    end

    return{
        GetImage=GetImage,
        GetText=GetText,
        Delete=Delete,
        GetTTexture=GetTTexture,
        DeleteTTexture=DeleteTTexture
    }

end


