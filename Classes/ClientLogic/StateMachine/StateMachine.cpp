#include "StateMachine.h"
#include "cocostudio/CocoStudio.h"
#include "json/document.h"
#include "../Utils/GameReader.h"
#include "../Utils/BaseUtils.h"

using namespace cocostudio;




void StateMachine::loadFromFile(std::string filename)
{
    std::string eventListFile(filename);
    eventListFile += "_Event.json";
    loadEventList(eventListFile);
    
    std::string stateListFile(filename);
    stateListFile += "_State.json";
    loadStateList(stateListFile);

    std::string stateFlowFile(filename);
    stateFlowFile += "_Flow.json";
    loadStateFlowList(stateFlowFile);

    std::string stateDataFile(filename);
    stateDataFile += "_Data.json";
    loadFlowData(stateDataFile);
    
    std::string stateRateFile(filename);
    stateRateFile += "_Rate.json";
    loadRateData(stateRateFile);

}

void StateMachine::loadEventList(std::string filename)
{
    auto doc = GameReader::getDocInstance(filename);
    if (doc->IsArray()){
        int size = doc->Size();
        int objId;
        int val;
        std::string name;
        std::string action;
        
        for (int i = 0; i<size; i++) {
            const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
            objId =DICTOOL->getIntValue_json(dic, "ID");
            name = DICTOOL->getStringValue_json(dic, "eventLib");
            val = DICTOOL->getIntValue_json(dic, "value");
            action = DICTOOL->getStringValue_json(dic, "animName");
            eventMap[name] = val;
            eventName[val] = name;
            auto actNames = YNBaseUtil::splitString(action, ",");
            actionNames[val] = actNames;
        }
    }
}
    
void StateMachine::loadStateList(std::string filename)

{
    auto doc = GameReader::getDocInstance(filename);
    if (doc->IsArray()){
        int size = doc->Size();
        int objId;
        int val;
        std::string name;
        
        for (int i = 0; i<size; i++) {
            const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
            objId =DICTOOL->getIntValue_json(dic, "ID");
            name = DICTOOL->getStringValue_json(dic, "stateLib");
            val = DICTOOL->getIntValue_json(dic, "value");

            stateMap[name] = val;
            stateName[val] = name;
        }
    }
    
}

void StateMachine::loadStateFlowList(std::string filename)

{
    auto doc = GameReader::getDocInstance(filename);
    if (doc->IsArray()){
        int size = doc->Size();
        int objId;
        std::string stateName;
        std::string eventName;
        int flowIndex;
        
        for (int i = 0; i<size; i++) {
            const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
            objId =DICTOOL->getIntValue_json(dic, "ID");
            stateName = DICTOOL->getStringValue_json(dic, "state");
            eventName = DICTOOL->getStringValue_json(dic, "event");
            flowIndex = DICTOOL->getIntValue_json(dic, "index");
            
            int state = stateMap[stateName];
            int event = eventMap[eventName];
            
            auto flow = stateFlowMap.find(state);
            if (flow == stateFlowMap.end()) {
                std::map<int, int> eventFlowMap;
                eventFlowMap[event] = flowIndex;
                stateFlowMap[state] = eventFlowMap;
            } else {
                stateFlowMap[state][event] = flowIndex;
            }
        }
    }
    
}

void StateMachine::loadFlowData(std::string filename)

{
    auto doc = GameReader::getDocInstance(filename);
    if (doc->IsArray()){
        int size = doc->Size();
        int objId;
        std::string nextStateName;
        std::string nextActionName;
        int flag;
        
        for (int i = 0; i<size; i++) {
            const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
            objId =DICTOOL->getIntValue_json(dic, "ID");
            nextStateName = DICTOOL->getStringValue_json(dic, "nextstate");
            nextActionName = DICTOOL->getStringValue_json(dic, "nextaction");
            flag = DICTOOL->getIntValue_json(dic, "flag");
            
            int state = stateMap[nextStateName];
            int action = eventMap[nextActionName];
            
            NextStateData nextData;
            nextData.nextTactics = state;
            nextData.nextAction = action;
            nextData.flag = flag;
            
            stateData.push_back(nextData);
        }
    }
}

void StateMachine::loadRateData(std::string filename)
{
    auto doc = GameReader::getDocInstance(filename);
    if (doc->IsArray()){
        int size = doc->Size();
        int objId;
        int rateIdx = -1;
        int rate = -1;
        int flowData = -1;
        
        for (int i = 0; i<size; i++) {
            const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
            objId =DICTOOL->getIntValue_json(dic, "ID");
            rateIdx = DICTOOL->getIntValue_json(dic, "index");
            rate = DICTOOL->getIntValue_json(dic, "rate");
            flowData = DICTOOL->getIntValue_json(dic, "flow");
            
            StateRate rateObj;
            rateObj.rate1 = rate;
            rateObj.flowIndex = flowData;
            auto rateVec = rateData.find(rateIdx);
            if (rateVec == rateData.end()) {
                std::vector<StateRate> stateRateVec;
                stateRateVec.push_back(rateObj);
                rateData[rateIdx] = stateRateVec;
            }else{
                rateData[rateIdx].push_back(rateObj);
            }
        }
    }
}

int StateMachine::findEventVal(std::string eventName)
{
    auto eventMap = getEventMap();
    auto eventVal = eventMap.find(eventName);
    if (eventVal == eventMap.end()) {
        return action_undefined;
    }
    return eventMap[eventName];
}

std::vector<std::string> StateMachine::findActionNames(int action)
{
    auto name = actionNames.find(action);
    if (name == actionNames.end()) {
        return *new std::vector<std::string>;
    }
    if (actionNames[action][0] == "null") {
        return *new std::vector<std::string>;
    }
    return actionNames[action];
}

void StateMachine::nextState()

{
    nextAction = action_undefined;
    
    getTacticsAction(currEvent, currTactics);
    
}


void StateMachine::getTacticsAction(int event, int state)

{
    //�Ҳ���״̬��������
    auto eventFlowMap = stateFlowMap.find(state);
    if(eventFlowMap == stateFlowMap.end())
    {
        return;
    }
    
    //�Ҳ����¼���������
    auto flowMap = eventFlowMap->second;
    auto flowVal = flowMap.find(event);
    if (flowVal == flowMap.end()) {
        return;
    }
    
    //�������ԣ�������
    auto flowIndex = flowVal->second;
    int flag = flowIndex & StateAIFlag::getFlag;
    if (flag == 0) {
        if (flowIndex < action_undefined || flowIndex >= stateData.size()) {
            return;
        }
    }
    
    parseData(flowIndex);
    
}


void StateMachine::parseData(int flowData)

{
    int flag, data;
    
    if (flowData == action_undefined) {
        //��Ҫ���¸�������Ϊδ����ʱ
        nextAction = action_undefined;
    }else{
        //��������
        flag = flowData & StateAIFlag::getFlag;
        data = flowData & StateAIFlag::getData;
        
        if (flag == StateAIFlag::rate) {
            //���ֵ�ж�
            getRateAction(data);
        }else{
            //��ֵ����
            auto nextData = stateData.at(data);
            nextTactics = nextData.nextTactics;
            nextAction = nextData.nextAction;
            nextFlag = nextData.flag;
        }
    }
}


void StateMachine::getRateAction(int randIndex)

{
    //�ҵ��������
    auto rateVal = rateData.find(randIndex);
    if(rateVal == rateData.end())
    {
        return;
    }
    
    auto rateVec = rateVal->second;
    
    //��ʼ��
    int total, gameRand;
    int vecIndex = 0;
    total = 0;

    gameRand = rand()%max_Rate;
    
    //�ڼ�����ƥ���Ӧ�����ֵ
    while (total < max_Rate) {    
        if (vecIndex>=rateVec.size()) {
            //û���ҵ�ƥ������ֵ
            break;
        }
        
        auto data = rateVec.at(vecIndex);
        total += data.rate1;
        //��������ʱ���ֵ��ƥ�䷶Χ��
        if (gameRand < total) {
            parseData(data.flowIndex);
            break;
        }
        vecIndex++;
    }
}


void StateMachine::changeState(int state, int action)

{
    currTactics = state;
    currEvent = action;
}

std::map<std::string, int> StateMachine::getEventMap()
{
    return eventMap;
}

std::map<std::string, int> StateMachine::getStateMap()
{
    return stateMap;
}