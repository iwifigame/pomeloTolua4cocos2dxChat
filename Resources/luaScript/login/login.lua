require "net"

login = {}

function login.login()
	local scene = cc.Scene:create()
	local layer = cc.Layer:create()
	local bg = cc.Sprite:create("images/bg.png")
	bg:setAnchorPoint(cc.p(0,0))
	layer:addChild(bg)
	scene:addChild(layer)
	cc.Director:getInstance():runWithScene(scene)
	
	net.connect("192.168.12.133", 3014)
	net.addListener(net.connected, login.onConnectGateServer)
end

function login.onConnectGateServer()
	local route = "gate.gateHandler.queryEntry"
	local msg = { uid = "luaClient" }
	net.request(route, msg, login.onRequestGateBack)
end

function login.onRequestGateBack(msg)
	cclog("--- host: " .. msg["host"])
	cclog("--- port: " .. msg["port"])
	net.connect(msg["host"], msg["port"])
	net.removeListener(net.connected)
	net.addListener(net.connected, login.onConnectGameServer)
end

function login.onConnectGameServer()
	local route = "connector.entryHandler.enter"
	local msg = { username = "luaClient", rid = "111" }
	
	net.request(route, msg, login.onRequestGameServerBack)
end

function login.onRequestGameServerBack(msg)
	require "chatScene/chatScene"
	chatScene.runScene(msg)
end