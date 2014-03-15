require "json"

net = { 
	listenerMap = nil,
	requestMap = nil,
	notifyMap = nil,
	
	connected = "connected",
	beKicked = "onKick",
	timeout = "timeout",	
	disconnect = "disconnect",
	connectFail = "connectFailed",
	
	notifyError = "notifyError",
	notifyFail = "notifyFailed",
	
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
	net.notifyMap = {}
	
	Net:getInstance():registerOnMsgLuaCallBack(net.onMessage)
end

function net.connect(ip, port, connectedCB, connectFailCB)
	Net:getInstance():connect(tostring(ip), tonumber(port))
	
	net.addListener(net.connected, connectedCB)
	net.addListener(net.disconnect, connectFailCB)
	--net.addListener(net.connectFail, net.onConnectFailed)
end

function net.request(route, msg, callback)
	net.requestMap[route] = callback
	Net:getInstance():pomeloRequest(tostring(route), tostring(json.encode(msg)))
end

function net.notify(route, msg, callback)
	net.notifyMap[route] = callback
	Net:getInstance():pomeloNotify(tostring(route), tostring(json.encode(msg)))
end

function net.httpRequest(url, callback)
	Net:getInstance():httpRequestSync(url, callback);
end

function net.addListener(event, callback)
	net.listenerMap[event] = callback
	Net:getInstance():addListener(tostring(event))
end
function net.removeListener(event)
	net.listenerMap[event] = nil
	Net:getInstance():removeListener(tostring(event))
end

function net.onMessage(event, msg)
	print("event: " .. event)
	if((type(msg) == "string") and (string.len(msg) > 0))then
		msg = json.decode(msg)
	else
		msg = nil --{}
	end
	if(net.listenerMap[event])then
		net.listenerMap[event](msg)
	end
	if(net.requestMap[event])then
		net.requestMap[event](msg)
		net.requestMap[event] = nil
	end
	if(net.notifyMap[event])then
		net.notifyMap[event](msg)
		net.notifyMap[event] = nil
	end
end

-- net state callbacks
function net.onKick()
	cclog("--- be kicked ---")
end

function net.onTimeout()
	cclog("--- timeout ---")
end

function net.onConnectFailed()
	cclog("--- connect failed ---")
end

function net.onDisconnect()
	cclog("--- disconnect ---")
end

function net.onNotifyError()
	cclog("--- notify error ---")
end

function net.onNotifyFail()
	cclog("--- notify fail ---")
end
	
function net.onInvalidRequest()
	cclog("--- invalid request ---")
end

function net.onRequestFail()
	cclog("--- request fail ---")
end

function net.addDefaultListeners()	
	cclog("-----------addDefaultListeners()")
	net.addListener(net.beKicked, net.onKick)
	net.addListener(net.timeout, net.onTimeout)
	net.addListener(net.disconnect, net.onDisconnect)
	
	--net.addListener(net.notifyError, net.onNotifyError)
	--net.addListener(net.notifyFail, net.onNotifyFail)
	net.requestMap[net.notifyError] = net.onNotifyError
	net.requestMap[net.notifyFail] = net.onNotifyFail
	
	--net.addListener(net.invalidRequest, net.onInvalidRequest)
	--net.addListener(net.requestFail, net.onRequestFail)
	net.notifyMap[net.invalidRequest] = net.onInvalidRequest
	net.notifyMap[net.requestFail] = net.onRequestFail
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