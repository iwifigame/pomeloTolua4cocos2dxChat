require "json"

net = { 
	requestMap = nil,
	messageMap = nil,
	connected = "connected",
	beKicked = "onKick",
	timeout = "timeout",	
	disconnect = "disconnect",
	connectFail = "connectFailed",
	notifyError = "notifyError",
	notifyFail = "notifyFailed",
	notifySuccess = "notifySuccess",
	invalidRequest = "requestError",
	requestFail = "requestFailed",
	
	none = 0,
	onGate = 1,
	onConnector = 2,
	state = 0,
}

function net.init()
	net.state = net.none
	net.listenerMap = {}
	net.requestMap = {}
	
	Net:getInstance():registerOnMsgLuaCallBack(net.onMessage)
end

function net.connect(ip, port)
	Net:getInstance():connect(tostring(ip), tonumber(port))
	net.addListener(net.beKicked, net.onKick)
	net.addListener(net.timeout, net.onTimeout)
	net.addListener(net.disconnect, net.onDisconnect)
	net.addListener(net.connectFail, net.onConnectFail)
	net.addListener(net.notifyError, net.onNotifyError)
	net.addListener(net.notifyFail, net.onNotifyFail)
	net.addListener(net.notifySuccess, net.onNotifySuccess)
	net.addListener(net.invalidRequest, net.onInvalidRequest)
	net.addListener(net.requestFail, net.onRequestFail)
end

function net.request(route, msg, callback)
	if(not net.requestMap[route])then
		net.requestMap[route] = callback
	end
	Net:getInstance():pomeloRequest(tostring(route), tostring(json.encode(msg)))
end

function net.httpRequest(url, callback)
	Net:getInstance():httpRequest(url, callback);
end

function net.addListener(event, callback)
	if(not net.listenerMap[event])then
		net.listenerMap[event] = callback
		Net:getInstance():addListener(tostring(event))
	end
end
function net.removeListener(event)
	net.listenerMap[event] = nil
	Net:getInstance():removeListener(tostring(event))
end

function net.onMessage(event, msg)
	if((type(msg) == "string") and (string.len(msg) > 0))then
		msg = json.decode(msg)
	else
		msg = {}
	end
	if(net.listenerMap[event])then
		net.listenerMap[event](msg)
	end
	if(net.requestMap[event])then
		net.requestMap[event](msg)
	end
end

-- net state callbacks
function net.onKick()
	cclog("--- be kicked ---")
end

function net.onTimeout()
	cclog("--- timeout ---")
end

function net.onDisconnect()
	cclog("--- disconnect ---")
end

function net.onConnectFail()
	cclog("--- connect fail ---")
end

function net.onNotifyError()
	cclog("--- notify error ---")
end

function net.onNotifyFail()
	cclog("--- notify fail ---")
end

function net.onNotifySuccess()
	cclog("--- notify success ---")
end
	
function net.onInvalidRequest()
	cclog("--- invalid request ---")
end

function net.onRequestFail()
	cclog("--- request fail ---")
end

--[[ example:
function net.testHttpRequest()
	local function httpRequestCallback(isSuccess, value)
		print("---", isSuccess, value)
		cclog("");
	end
	net.httpRequest("http://192.168.2.210/serverlist.txt", httpRequestCallback)
end
--]]