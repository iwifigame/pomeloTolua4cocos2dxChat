require "net"

local ip = "192.168.2.111"
local port = 3014

login = {}

function login.login()
	local scene = cc.Scene:create()
	local layer = cc.Layer:create()
	local bg = cc.Sprite:create("images/bg.png")
	bg:setAnchorPoint(cc.p(0,0))
	layer:addChild(bg)
	
	scene:addChild(layer)
	
	net.connect(ip, port, login.onConnectGateServer)
	cc.Director:getInstance():runWithScene(scene)
end

function login.onConnectGateServer()
	local route = "gate.gateHandler.queryEntry"
	local msg = { uid = "luaClientWindows" }
	net.request(route, msg, login.onRequestGateBack)
end

function login.onRequestGateBack(msg)
	cclog("--- host: " .. msg["host"])
	cclog("--- port: " .. msg["port"])
	net.connect(msg["host"], msg["port"], login.onConnectGameServer)
end

function login.onConnectGameServer()
	local route = "connector.entryHandler.enter"
	local msg = { username = "luaClient" .. os.time(), rid = "111" }
	
	net.request(route, msg, login.onRequestGameServerBack)
end

function login.onRequestGameServerBack(msg)
	require "chatScene/chatScene"
	chatScene.runScene(msg)
end

return login