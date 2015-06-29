
--------------------------------
-- @module FightActor
-- @extend Actor
-- @parent_module 

--------------------------------
-- @function [parent=#FightActor] getBHero 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] buffChangeFireResist 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeCurrApBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeMaxAp 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeMp 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeCurrMpBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getMaxCombo 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#FightActor] addCombo 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] skillBulletHurt 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] needSneak 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] getAtking 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] removeLightResistBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] addBuff 
-- @param self
-- @param #bool bool
-- @param #SkillTag skilltag
        
--------------------------------
-- @function [parent=#FightActor] getFrameCommand 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#FightActor] removeThunderResistBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeCurrHpBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] setIsFrozen 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#FightActor] buffImmuFrozen 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeMaxHpBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] gethurtStiff 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] parseHurtEvent 
-- @param self
-- @param #cc.EventCustom eventcustom
        
--------------------------------
-- @function [parent=#FightActor] getAttackHead 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] removeDarkResistBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeTenacity 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeImmuAllDeBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeThunderResist 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] setHurtEffectLayer 
-- @param self
-- @param #cc.Layer layer
        
--------------------------------
-- @function [parent=#FightActor] animationEvent 
-- @param self
-- @param #ccs.Armature armature
-- @param #int movementeventtype
-- @param #string str
        
--------------------------------
-- @function [parent=#FightActor] removeFaintBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getDeHitDownVal 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#FightActor] lostTarget 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] removeFrozenBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeHpRecoverBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getHurtMoveSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#FightActor] dispatchResetPunchTag 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] getComboNum 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#FightActor] canUseSomeSkill 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#FightActor] getIsFix 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] getDying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] removeMoveSpeedBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getAtkRect 
-- @param self
-- @param #bool bool
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#FightActor] getHit2Ground 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] getBlackActor 
-- @param self
-- @return BlackActor#BlackActor ret (return value: BlackActor)
        
--------------------------------
-- @function [parent=#FightActor] setWaitTimeOut 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#FightActor] buffFrozenState 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getIsFaint 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] getLieShockSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#FightActor] DeStiff 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] removeImmuFaintBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] preloadSkillRes 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] removeDodgeRatioBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeMpRecover 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffImmuFaint 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeMaxHp 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeMaxApBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeDarkResist 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeLightResist 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeApRecover 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getBombHitVal 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#FightActor] getHit2Air 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] setMp 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#FightActor] getBackInAir 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] changeActionWithName 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#FightActor] getAsBomb 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] setTargetActor 
-- @param self
-- @param #FightActor fightactor
        
--------------------------------
-- @function [parent=#FightActor] removeImmuFrozenBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffFaintState 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeCritRatio 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] setIsFaint 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#FightActor] DealAttackRectByFlip 
-- @param self
-- @param #bool bool
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#FightActor] initFightData 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#FightActor] buffChangeHpRecover 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] backSkill2Base 
-- @param self
-- @param #int int
-- @param #int int
        
--------------------------------
-- @function [parent=#FightActor] getTargetActor 
-- @param self
-- @return FightActor#FightActor ret (return value: FightActor)
        
--------------------------------
-- @function [parent=#FightActor] removeWindResistBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getDieLie 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] buffChangeMaxMp 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeMoveSpeed 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeAttackBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] setTargetToActor 
-- @param self
-- @param #FightActor fightactor
        
--------------------------------
-- @function [parent=#FightActor] getBombAtkRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#FightActor] removeApRecoverBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getShowCombo 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] getCurrSkillTag 
-- @param self
-- @return SkillTag#SkillTag ret (return value: SkillTag)
        
--------------------------------
-- @function [parent=#FightActor] isLandGround 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] setCurrHitDownVal 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#FightActor] removeHitRatioBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getHurtEffectLayer 
-- @param self
-- @return Layer#Layer ret (return value: cc.Layer)
        
--------------------------------
-- @function [parent=#FightActor] buffChangeDodgeRatio 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] setHp 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#FightActor] resetPunchTag 
-- @param self
-- @param #cc.EventCustom eventcustom
        
--------------------------------
-- @function [parent=#FightActor] getSkillAction 
-- @param self
-- @param #int int
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#FightActor] canFindOpponent 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] canChase 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] buffChangeIceResist 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeDeHitDown 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeAp 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffFixState 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getAtkStiff 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] adjustHurtEffectPos 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] changeSkill 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#FightActor] removeCritRatioBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] onFrameEvent 
-- @param self
-- @param #ccs.Bone bone
-- @param #string str
-- @param #int int
-- @param #int int
        
--------------------------------
-- @function [parent=#FightActor] hurt 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] removeIceResistBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeDehitDownBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeHitRatio 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] updateBackEffect 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] getIsValidAtk 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] clearCombo 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] buffImmuAll 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] setDeHitDownVal 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#FightActor] getCurrHitDownVal 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#FightActor] getAttackFoot 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] getCurrAction 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#FightActor] getBombHitDownVal 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#FightActor] buffChangeAttack 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] initFightState 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] setIsFix 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#FightActor] removeFireResistBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffImmuFix 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] startAtkStiff 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#FightActor] removeMaxMpBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] setIsValidAtk 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#FightActor] removeMpRecoverBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeDefloatBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] setDieLie 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#FightActor] initViewRes 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] updateFrontEffect 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] bodyHurt 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] canAttackTarget 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] getCurrSkill 
-- @param self
-- @return Skill#Skill ret (return value: Skill)
        
--------------------------------
-- @function [parent=#FightActor] buffChangeDefence 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] addHurtListener 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] getWaitTimeOut 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] bulletHurt 
-- @param self
-- @param #Bullet bullet
        
--------------------------------
-- @function [parent=#FightActor] removeTenacityBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] effAnimEvent 
-- @param self
-- @param #ccs.Armature armature
-- @param #int movementeventtype
-- @param #string str
        
--------------------------------
-- @function [parent=#FightActor] getHit2Wall 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] getIsFrozen 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] waitTimeEnough 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] removeImmuFixBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getAttackTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#FightActor] removeDefenceBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] startHurtStiff 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#FightActor] buffChangeHp 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeFixBuff 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] buffChangeWindResist 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] getAttackWaist 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FightActor] buffChangeDeFloat 
-- @param self
-- @param #Buff buff
        
--------------------------------
-- @function [parent=#FightActor] removeHurtListener 
-- @param self
        
--------------------------------
-- @function [parent=#FightActor] FightActor 
-- @param self
        
return nil
