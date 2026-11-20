
local u=ffi.new("GM_Ptr");
ffi.gc(u,function (val)
        u=nil;
end)

function ValueToPtr(ctype,value)
    u._c_ptr=value;
    return ffi.cast(ctype,u._lua_ptr);
end

function PtrToValue(ptr)
    u._lua_ptr=ptr;
    return  u._c_ptr;
end

function ValueToEntityPtr(value)
    u._c_ptr=value;
    return u._lua_ptr;
end

auto_ptr={}

function auto_ptr.new(type,delete)
    local ptr=ffi.new();
    ffi.gc(ptr,function(val)
        delete(ptr)
    end);
end




