modmanager={}

function modmanager:InitModuleManager()
	local t={}
	local value,c=C_LoadModuleList();
	self.count=c;
	local dptr=ffi.cast("Module*",value);
	for i=0,self.count-1 do
		t[i]={};
		t[i]._name=ffi.string(dptr[i]._name);
		t[i]._author=ffi.string(dptr[i]._author);
		t[i]._description=ffi.string(dptr[i]._description);
		t[i]._version=ffi.string(dptr[i]._version);
		t[i]._execute=ffi.string(dptr[i]._execute);
	end
	C_DeleteModuleList(value);
	self.mod=t;
end
