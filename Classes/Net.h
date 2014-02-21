#include "CCNode.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include "CCLuaEngine.h"
#include "ThreadSafeQueue.h"
#include "pomelo.h"

USING_NS_CC;

//PC_EVENT_KICK
//PC_EVENT_TIMEOUT
//PC_EVENT_DISCONNECT
#define PC_EVENT_CONNECTED "connected"
#define PC_EVENT_CONNECTEFAIL "connectFailed"
#define PC_EVENT_NOTIFYERR "notifyError"
#define PC_EVENT_NOTIFYFAIL "notifyFailed"
#define PC_EVENT_NOTIFYSUCCESS "notifySuccess"
#define PC_EVENT_REQUESTERR "requestError"
#define PC_EVENT_REQUESTFAIL "requestFailed"

class Net: public Node
{
public:
	Net();

	~Net();

	static inline Net* getInstance();

	void connect(const char *ip, int port);

	void addListener(const char* event);

	void removeListener(const char* event);

	void pomeloNotify(const char *route, const char *str);

	void pomeloRequest(const char *route, const char *str);
	
	bool httpRequest(std::string & url, int cbFunc);

	void registerOnMsgLuaCallBack(int luaCallback);	

	virtual void visit();

protected:
	void handleMsg();

	void pushMsg(std::string event, std::string msg);

	static void pomeloNotifyCallBack(pc_notify_t *req, int status);

	static void pomeloRequestCallBack(pc_request_t *req, int status, json_t *resp);

	static void pomeloMsgCallBack(pc_client_t *client, const char *event, void *data);

private:
	pc_client_t *client;
	static int onMsgLuaCallback;
	ThreadSafeQueue< std::map<std::string, std::string> > msgQueue;
};