#include "Net.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#include <winsock2.h>
#else
#include <unistd.h>
#endif

int Net::onMsgLuaCallback = 0;

Net* Net::getInstance() 
{
		static Net *pInstance = NULL;
		if(pInstance == NULL)
		{
			pInstance = new Net();
			pInstance->autorelease();
		}
		return pInstance;
	}

Net::Net(): client(0)
{
	msgQueue.clear();
}

Net::~Net()
{
	if(client)
	{
		pc_client_destroy(client); 
	}
	msgQueue.clear();
}

void Net::nonSyncConnect()
{
	struct sockaddr_in address;
	memset(&address, 0, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(ip.c_str());

	if(pc_client_connect(client, &address))
	{
		//pushMsg(PC_EVENT_CONNECTEFAIL, "");
	}
	else
	{
		pushMsg(PC_EVENT_CONNECTED, "");
	}	
}
void Net::connect(const char *ip_, int port_)
{
	pc_client_t *pre_client = client;
	client = pc_client_new();
	if(pre_client)
	{
		pc_client_destroy(pre_client);
	}

	ip = ip_;
	port = port_;
	
	auto t = std::thread(&Net::nonSyncConnect, this);
    t.detach();
}

void Net::addListener(const char* event)
{
	pc_add_listener(client, event, &Net::pomeloMsgCallBack);
}

void Net::removeListener(const char* event)
{
	pc_remove_listener(client, event, &Net::pomeloMsgCallBack);
}

void Net::pomeloNotify(const char *route, const char *str)
{
	pc_notify_t *notify = pc_notify_new();
	json_error_t error;
	json_t *msg = json_loads(str, JSON_DECODE_ANY, &error);
	if(!msg)
	{
		pushMsg(std::string(PC_EVENT_REQUESTERR), std::string(""));
	}
	else
	{
		pc_notify(client, notify, route, msg, &Net::pomeloNotifyCallBack);
		//json_decref(msg);
	}
}

void Net::pomeloRequest(const char *route, const char *str)
{
	pc_request_t *request = pc_request_new();
	json_error_t error;
	json_t *msg = json_loads(str, JSON_DECODE_ANY, &error);
	if(!msg)
	{
		pushMsg(std::string(PC_EVENT_REQUESTERR), std::string(""));
	}
	else
	{
		pc_request(client, request, route, msg, &Net::pomeloRequestCallBack);
		//json_decref(msg);
	}
}

static size_t getUrlStringValue(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	std::string *version = (std::string*)userdata;
	version->append((char*)ptr, size * nmemb);
   
	return (size * nmemb);
}
bool Net::httpRequest(std::string & url, int cbFunc)
{
	void *curl;  
	CURLcode res;  
	char buf[16] = {0};
	bool ret = false; 
	std::string value;
	value.clear();

	curl = curl_easy_init();  
	if (curl)  
	{  
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); 
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getUrlStringValue);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &value);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 5L);
		res = curl_easy_perform(curl);  
		curl_easy_cleanup(curl);  
		if (res == 0)  
		{  
			ret = true;
			std::cout << "value: " << value << std::endl;
		}  
		else
		{
			snprintf(buf, sizeof(buf)-1, "%d", res);
			value.append(buf);
		}

	}  
	  
	auto L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
	lua_pushboolean(L, ret);
	lua_pushstring(L, value.c_str());
	LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(cbFunc, 2);

	return ret;
}

void Net::registerOnMsgLuaCallBack(int luaCallback)
{
	onMsgLuaCallback = luaCallback;
}

void Net::visit()
{
	if(!msgQueue.empty())
	{
		handleMsg();
	}
}

void Net::handleMsg()
{
	if(onMsgLuaCallback)
	{
		auto L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
		auto msg = msgQueue.front();
		lua_pushstring(L, msg["event"].c_str());
		lua_pushstring(L, msg["msg"].c_str());
		LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(onMsgLuaCallback, 2);
		msgQueue.pop_front();
	}
}

void Net::pushMsg(std::string event, std::string msg)
{
	std::map<std::string, std::string> m;
	m["event"] = event;
	m["msg"] = msg;
	msgQueue.push_back(m);
}
	
void Net::pomeloNotifyCallBack(pc_notify_t *req, int status)
{
	if(status == -1)
	{
		Net::getInstance()->pushMsg(std::string(PC_EVENT_NOTIFYFAIL), std::string(""));
	}
	else
	{
		auto event = req->route;
		Net::getInstance()->pushMsg(std::string(event), std::string(""));
	}
	json_t *msg = req->msg;
	json_decref(msg);
	pc_notify_destroy(req);
}

void Net::pomeloRequestCallBack(pc_request_t *req, int status, json_t *resp)
{
	if(status == -1)
	{
		Net::getInstance()->pushMsg(std::string(PC_EVENT_REQUESTFAIL), std::string(""));
	} 
	else if(status == 0) 
	{
		auto event = req->route;
		auto msg = json_dumps(resp, 0);
		Net::getInstance()->pushMsg(std::string(event), std::string(msg));
		free(msg);
	}
	json_t *msg = req->msg;
	json_decref(msg);
	pc_request_destroy(req);
}

void Net::pomeloMsgCallBack(pc_client_t *client, const char *event, void *data)
{
	char nullStr[] = "";
	void *msg = data ? data : (void*)nullStr;
	if(data)
	{
		msg = json_dumps((const json_t*)data, 0);
	}
	
	Net::getInstance()->pushMsg(std::string(event), std::string((const char*)msg));
	if(data)
	{
		free(msg);
	}
}

