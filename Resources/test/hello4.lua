-- cclog
cclog = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
end

function domain( num )
	local tab = gettab(num)

	for k,v in pairs(tab) do
		print("key: " .. k)
		print("val: " .. v)
		print()
	end
end

function pass( tab )
	-- body
	for k,v in pairs(tab) do
		print("key: " .. k)
		print("val: " .. v)
		print()
	end
end

function parse_event( data_tab )
	
	if data_tab.hpRatio > 50 then
		print(">>>>>>>>>>>>dangerous>>>>>>>>>>")
	end
end

function switch_state( data_base, monster )
	-- print("state: " .. data_base.state)
	if data_base.state == "INIT" then
		if data_base.event ~= "action_undefined" then
			return "event"
		end
	elseif data_base.state == "IDLE" then
		if data_base.event ~= "action_undefined" then
			return "event"
		elseif monster:canFindOpponent() then
			return "EVENT_FIND_ENEMY"
		end
	elseif data_base.state == "PATROL" then
		if data_base.event ~= "action_undefined" then
			return "event"
		elseif monster:canFindOpponent() then
			return "EVENT_FIND_ENEMY"
		elseif monster:arriveTargetPos() then
			return "EVENT_ARRIVE_TARGET"
		end
	elseif data_base.state == "CHASE" then
		if data_base.event ~= "action_undefined" then
			return "event"
		elseif monster:arriveTargetPos() then
			return "EVENT_ARRIVE_TARGET"
		end
	elseif data_base.state == "BACK" then
		if data_base.event ~= "action_undefined" then
			return "event"
		elseif monster:arriveTargetPos() then
			return "EVENT_ARRIVE_TARGET"
		end
	elseif data_base.state == "RETURN" then
		if data_base.event ~= "action_undefined" then
			return "event"
		elseif monster:arriveTargetPos() then
			return "EVENT_ARRIVE_TARGET"
		elseif monster:canFindOpponent() then
			return "EVENT_FIND_ENEMY"
		end
	elseif data_base.state == "SNEAK" then
		if data_base.event ~= "action_undefined" then
			return "event"
		elseif monster:arriveTargetPos() then
			if data_base.sneak_empty == 1 then
				return "EVENT_ENDSNEAK"
			else
				return "EVENT_ARRIVE_TARGET"
			end
		end
	elseif data_base.state == "SNEAKRUSH" then
		if data_base.event ~= "action_undefined" then
			return "event"
		elseif monster:arriveTargetPos() then
			return "EVENT_ARRIVE_TARGET"
		end
	elseif data_base.state == "ATTACK" then
		if data_base.event ~= "action_undefined" then
			return "event"
		elseif monster:animOver() then
			return "EVENT_ACTIONOVER"
		end
	elseif data_base.state == "WAIT" then
		if data_base.event ~= "action_undefined" then
			return "event"
		elseif monster:getWaitTimeOut() then
			print("wait -----------------")
			if monster:lostTarget() then
				print("lost ---------------->>")
				return "EVENT_LOSTTARGET"
			else
				print("--------not lost-------------")
				if monster:canAttackTarget() then
					print("attack ------>>>>>>>>")
					return "EVENT_CANATTACK"
				elseif monster:canChase() then
					print("chase ------------>>>>")
					if monster:needSneak() then
						print("sneak =======>>>>>>>")
						return "EVENT_NEEDSNEAK"
					else
						print("sure chase =====>>>>>>>>>>>>")
						return "EVENT_CANCHASE"
					end
				end
                print("========== not change ===========")
			end
		end
	elseif data_base.state == "FAINT" then
		if data_base.isFaint ~= 1 then
			return "EVENT_CANATTACK"
		end
	elseif data_base.state == "HURT" then
		if data_base.event == "EVENT_HEADHURT" then
			return "event"
		elseif data_base.event == "EVENT_WAISTHURT" then
			return "event"
		elseif data_base.event == "EVENT_HIT2AIR" then
			return "event"
		elseif monster:animOver() then
			if data_base.delayEvent == "EVENT_HEADFELLGROUND" then
				return "delayEvent"
			elseif data_base.delayEvent == "EVENT_WAISTFELLGROUND" then
				return "delayEvent"
			elseif data_base.isFaint == 1 then
				return "EVENT_FAINT"
			elseif data_base.action == "HEADHIT" then
				return "action"
			elseif data_base.action == "WAISTHIT" then
				return "action"
			else
				return "event"
			end
		end
	elseif data_base.state == "FELLDOWN" then
		if monster:animOver() then
			if data_base.action == "HEADFELLDOWN" then
				if monster:getBlackActor():getHp() <= 0 then
					return "EVENT_DIE"
				else
					return "action"
				end
			elseif data_base.action == "WAISTFELLDOWN" then
				if monster:getBlackActor():getHp() <= 0 then
					return "EVENT_DIE"
				else
					return "action"
				end
			elseif data_base.action == "LIESHOCK" then
				if monster:getBlackActor():getHp() <= 0 then
					return "EVENT_DIE"
				else
					return "action"
				end
			elseif data_base.action == "GETUP" then
				if data_base.isFaint == 1 then
					return "EVENT_FAINT"
				else
					return "action"
				end
			elseif data_base.action == "LIE" then
				return "action"
			else
				return "event"
			end
		end
	elseif data_base.state == "INAIR" then
		if data_base.event == "EVENT_HIT2AIR" then
			return "EVENT_AIRHIT"
		elseif data_base.event == "EVENT_HEADHURT" then
			return "EVENT_AIRHIT"
		elseif data_base.event == "EVENT_WAISTHURT" then
			return "EVENT_AIRHIT"
		elseif data_base.event == "EVENT_HEADFELLGROUND" then
			return "EVENT_AIRHIT"
		elseif data_base.event == "EVENT_WAISTFELLGROUND" then
			return "EVENT_AIRHIT"
		elseif monster:isLandGround() then
			return "EVENT_LANDGROUND"
		elseif monster:animOver() then
			if data_base.action ~= "AIRHITDOWN" then
				return "action"
			end
		end
	elseif data_base.state == "BOUNDGROUND" then
		if monster:animOver() then
			return "EVENT_KGE"
		end
	elseif data_base.state == "BOUNDWALL" then
		if data_base.action == "BOUND2W" then
			if monster:isOutWindow() then
				return "EVENT_KWG"
			elseif monster:animOver() then
				return "EVENT_ACTIONOVER"
			end
		else
			if monster:animOver() then
				return "EVENT_KWE"
			end
		end
	end

	return "NONE"
end
