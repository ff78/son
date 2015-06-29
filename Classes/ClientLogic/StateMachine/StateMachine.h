#pragma once

#include "cocos2d.h"

#define ACTION_UNDEFINED -1;

struct StateFlow
{
	int state = -1;
	int event = -1;
	int flowIndex = -1;
};

struct NextStateData
{
	int nextTactics = -1;
	int nextAction = -1;
	int flag = 0;
};

enum StateAIFlag
{
    rate = 0x1000,
    skillRate = 0x2000,
    getFlag = 0x7000,
    
    getData = 0xfff,
    invincible = 0x1,
    startFall = 0x3,
    endFall = 0x2
    
};

struct StateRate
{
    int rate1;
    int flowIndex;
};




class StateMachine
{
public:
	CC_SYNTHESIZE(int, currTactics, CurrTactics);
	CC_SYNTHESIZE(int, currEvent, CurrEvent);
	CC_SYNTHESIZE_READONLY(int, nextTactics, NextTactics);
	CC_SYNTHESIZE_READONLY(int, nextAction, NextAction);
	CC_SYNTHESIZE_READONLY(int, nextFlag, NextFlag);
    CC_SYNTHESIZE_READONLY(int, totalRate, TotalRate);
    
	//int currTactics;
	//int currEvent;
	//int nextTactics;
	//int nextAction = ACTION_UNDEFINED;
	//int nextFlag;

    /**
     *	@brief	ͨ����ǰ״̬���¼����ҳ�Ӧ�øı�Ϊ����һ��״̬�Ͷ���
     *
     */
    void nextState();
    
    /**
     *	@brief	�趨��ǰ״̬���¼�
     *
     *	@param 	state 	int ��ǰ״̬
     *	@param 	action 	int �����¼�
     */
    void changeState(int state, int action);
    
    /**
     *	@brief	�ɵ�ǰ״̬�ʹ����¼���Ѱ����һ״̬����
     *
     *	@param 	event 	int �����¼����������
     *	@param 	state 	int ��ǰ״̬
     */
    void getTacticsAction(int event, int state);
    
    /**
     *	@brief	������������ת��������ת�������������ѡ��
     *
     *	@param 	flowData 	int ��ת������Ŀ����
     */
    void parseData(int data);
    
    /**
     *	@brief	���������ʵ�������״̬��ת��
     *          ���ֵ�ķ����������ˮ�͡�
     *
     *	@param 	randIndex 	int �����������
     */
    void getRateAction(int randIndex);
    
    /**
     *	@brief	��������״̬������ļ�
     *
     *	@param 	filename std::string ״̬���ļ����·����ǰ׺
     */
	void loadFromFile(std::string fileName);
    
    /**
     *	@brief	�����¼�������code��Ӧ��
     *          �������붼���������棬����ʵ����������˳���Ӧ��
     *          �������ظ��¼���code��
     
     *	@param 	filename 	std::string ״̬���¼��б��ļ���·��
     */
    void loadEventList(std::string filename);
    
    /**
     *	@brief	����״̬������code��Ӧ���������ظ�״̬����code��
     *
     *	@param 	filename 	std::string ״̬��״̬�б��ļ���·��
     */
    void loadStateList(std::string filename);
    
    /**
     *	@brief	����״̬��ת�ļ���
     *          ״̬���¼���ֵ��������״̬����¼����ж�����ġ�
     *          ���������д���¼����ݣ�����ת�ļ�û�ж����������ִ���
     *
     *	@param 	filename 	std::string ״̬��״̬��ת�ļ���·��
     */
    void loadStateFlowList(std::string filename);
    
    /**
     *	@brief	������ת���ݱ�
     *          ����Ҫ��ת����״̬�Ͷ�����
     *          flag��������תǰ����һ���Ĵ���
     *
     *	@param 	filename"] 	std::string ���ݱ�·��
     */
    void loadFlowData(std::string filename);

    
    /**
     *	@brief	���������ת���ݱ�
     *          �����ݱ���ĳ������Rate��ǩʱ���ߴ˱�
     *          �ɴ˱������ת·������ת���ʡ�
     *
     *	@param 	filename 	std::string ���ݱ�·��
     */
    void loadRateData(std::string filename);
    
    /**
     *	@brief	ͨ���¼������ҵ��¼�code
     *
     *	@param 	eventName 	std::string �¼�����
     *
     *	@return	int �¼�code
     */
    int findEventVal(std::string eventName);
    
    std::vector<std::string> findActionNames(int action);
    
    std::map<std::string, int> getEventMap();
    std::map<std::string, int> getStateMap();

public:
    static const int action_undefined = -1;
    static const unsigned int max_Rate = 100;
    std::map<std::string, int> eventMap;
    std::map<std::string, int> stateMap;
    std::map<int, std::map<int, int>> stateFlowMap;
    std::vector<NextStateData> stateData;
//    std::map<int, std::string> actionNames;
    std::map<int, std::vector<std::string>> actionNames;
    std::map<int, std::string> stateName;
    std::map<int, std::string> eventName;
private:

    std::map<int, std::vector<StateRate>> rateData;
};