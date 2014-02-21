/*
** Lua binding: net
** Generated automatically by tolua++-1.0.92 on 02/19/14 11:06:24.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "tolua_fix.h"
#include "Net.h"


/* Exported function */
TOLUA_API int  tolua_net_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"pc_client_t");
 tolua_usertype(tolua_S,"pc_request_t");
 tolua_usertype(tolua_S,"Net");
 tolua_usertype(tolua_S,"Node");
 tolua_usertype(tolua_S,"json_t");
}

/* method: getInstance of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_getInstance00
static int tolua_net_Net_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Net* tolua_ret = (Net*)  Net::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Net");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_connect00
static int tolua_net_Net_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  int port = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->connect(ip,port);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connectStateHandler of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_connectStateHandler00
static int tolua_net_Net_connectStateHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pc_client_t",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pc_client_t* client = ((pc_client_t*)  tolua_tousertype(tolua_S,2,0));
  const char* event = ((const char*)  tolua_tostring(tolua_S,3,0));
  void* data = ((void*)  tolua_touserdata(tolua_S,4,0));
  {
   Net::connectStateHandler(client,event,data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connectStateHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onConnectFailed of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_onConnectFailed00
static int tolua_net_Net_onConnectFailed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onConnectFailed'", NULL);
#endif
  {
   self->onConnectFailed();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onConnectFailed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addListener of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_addListener00
static int tolua_net_Net_addListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  const char* event = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addListener'", NULL);
#endif
  {
   self->addListener(event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeListener of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_removeListener00
static int tolua_net_Net_removeListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  const char* event = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeListener'", NULL);
#endif
  {
   self->removeListener(event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pomeloMsgCallBack of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_pomeloMsgCallBack00
static int tolua_net_Net_pomeloMsgCallBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pc_client_t",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pc_client_t* client = ((pc_client_t*)  tolua_tousertype(tolua_S,2,0));
  const char* event = ((const char*)  tolua_tostring(tolua_S,3,0));
  void* data = ((void*)  tolua_touserdata(tolua_S,4,0));
  {
   Net::pomeloMsgCallBack(client,event,data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pomeloMsgCallBack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pomeloRequest of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_pomeloRequest00
static int tolua_net_Net_pomeloRequest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  const char* route = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* str = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pomeloRequest'", NULL);
#endif
  {
   self->pomeloRequest(route,str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pomeloRequest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pomeloRequestCallBack of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_pomeloRequestCallBack00
static int tolua_net_Net_pomeloRequestCallBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Net",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pc_request_t",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"json_t",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pc_request_t* req = ((pc_request_t*)  tolua_tousertype(tolua_S,2,0));
  int status = ((int)  tolua_tonumber(tolua_S,3,0));
  json_t* resp = ((json_t*)  tolua_tousertype(tolua_S,4,0));
  {
   Net::pomeloRequestCallBack(req,status,resp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pomeloRequestCallBack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaCallBack of class  Net */
#ifndef TOLUA_DISABLE_tolua_net_Net_registerLuaCallBack00
static int tolua_net_Net_registerLuaCallBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Net",0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,4,"LUA_FUNCTION",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Net* self = (Net*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION func1 = (  toluafix_ref_function(tolua_S,2,0));
  LUA_FUNCTION func2 = (  toluafix_ref_function(tolua_S,3,0));
  LUA_FUNCTION func3 = (  toluafix_ref_function(tolua_S,4,0));
 /* int func1 = ((int)  tolua_tonumber(tolua_S,2,0));
  int func2 = ((int)  tolua_tonumber(tolua_S,3,0));
  int func3 = ((int)  tolua_tonumber(tolua_S,4,0));*/
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaCallBack'", NULL);
#endif
  {
   self->registerLuaCallBack(func1,func2,func3);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerLuaCallBack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_net_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Net","Net","Node",NULL);
  tolua_beginmodule(tolua_S,"Net");
   tolua_function(tolua_S,"getInstance",tolua_net_Net_getInstance00);
   tolua_function(tolua_S,"connect",tolua_net_Net_connect00);
   tolua_function(tolua_S,"connectStateHandler",tolua_net_Net_connectStateHandler00);
   tolua_function(tolua_S,"onConnectFailed",tolua_net_Net_onConnectFailed00);
   tolua_function(tolua_S,"addListener",tolua_net_Net_addListener00);
   tolua_function(tolua_S,"removeListener",tolua_net_Net_removeListener00);
   tolua_function(tolua_S,"pomeloMsgCallBack",tolua_net_Net_pomeloMsgCallBack00);
   tolua_function(tolua_S,"pomeloRequest",tolua_net_Net_pomeloRequest00);
   tolua_function(tolua_S,"pomeloRequestCallBack",tolua_net_Net_pomeloRequestCallBack00);
   tolua_function(tolua_S,"registerLuaCallBack",tolua_net_Net_registerLuaCallBack00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_net (lua_State* tolua_S) {
 return tolua_net_open(tolua_S);
};
#endif

