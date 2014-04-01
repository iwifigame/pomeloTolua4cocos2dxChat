require "net"

chatScene = {
	count = 1,
}

function chatScene.onAdd(msg)
	cclog("--- onAdd: ")
end

function chatScene.onChat(msg)
	cclog("--- onChat: " .. msg["from"] .. " say to " .. msg["target"] .. ": " .. msg["msg"])
end

function chatScene.onLeave(msg)
	cclog("--- onLeave: ")
end

function chatScene.runScene(data)
	cclog("chat scene run chat scene")
	net.addListener("onAdd", chatScene.onAdd)		
	net.addListener("onChat", chatScene.onChat)		
	net.addListener("onLeave", chatScene.onLeave)		
	
	local users = data["users"]
	for i=1, #users do
		cclog("user " .. i .. ": " .. users[i])
	end
	
	local function sendMsg(sender,eventType)
		if(eventType == ccui.TouchEventType.ended)then
			local tab = {}
			tab["content"] = "luaClient" .. " says to all: " .. "client message " .. chatScene.count
			tab["rid"] = "111"
			tab["from"] = "luaClient"
			tab["target"] = "*"		
			chatScene.count = chatScene.count + 1
			local route = "chat.chatHandler.send"
			net.request(route, tab)
		end
	end
	local scene = cc.Scene:create()
	local layer = cc.Layer:create()
	local bg = cc.Sprite:create("images/bg.png")
	bg:setPosition(cc.p(640/2, 480/2))
	local widget = ccui.Widget:create()
	widget:setAnchorPoint(cc.p(0, 0))
	local sendBtn = ccui.Button:create()
	sendBtn:loadTextures("images/btnNormal.png", "images/btnPressed.png", "")
	sendBtn:setTouchEnabled(true)
	sendBtn:addTouchEventListener(sendMsg)
	sendBtn:setPosition(cc.p(640/2, 480/2))
	widget:addChild(sendBtn)
	layer:addChild(bg)
	layer:addChild(widget)
	scene:addChild(layer)
	
	--cc.Director:getInstance():runWithScene(scene)
	cc.Director:getInstance():replaceScene(scene)
end