
OPC2OPCPluginps.dll: dlldata.obj OPC2OPCPlugin_p.obj OPC2OPCPlugin_i.obj
	link /dll /out:OPC2OPCPluginps.dll /def:OPC2OPCPluginps.def /entry:DllMain dlldata.obj OPC2OPCPlugin_p.obj OPC2OPCPlugin_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del OPC2OPCPluginps.dll
	@del OPC2OPCPluginps.lib
	@del OPC2OPCPluginps.exp
	@del dlldata.obj
	@del OPC2OPCPlugin_p.obj
	@del OPC2OPCPlugin_i.obj
