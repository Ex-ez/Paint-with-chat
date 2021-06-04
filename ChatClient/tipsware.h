#ifndef _TIPSWARE_H_
#define _TIPSWARE_H_


#include "resource.h"
#include "EasyWin32.h"

#pragma comment(lib, "gdiplus")
#pragma comment(lib, "Msimg32.lib")

#ifdef _DEBUG
	#pragma comment(lib, "DSH_EasyWin32.lib")
#else
	#pragma comment(lib, "RST_EasyWin32.lib")
#endif

/*
소켓에서 지켜야할 UserData 시작 형식!! - 1개의 클라이언트 정보를 저장할 구조체
struct UserData
{
	unsigned int h_socket;   // 소켓 핸들
	char ip_address[16];     // 접속한 클라이언트의 주소
};
*/

// 현재 수신한 데이터 정보를 저장할 구조체
struct CurrentServerNetworkData
{
	unsigned char m_net_msg_id;      // 메시지 ID
	unsigned short m_net_body_size;  // Body 데이터의 크기
	char *mp_net_body_data;          // Body 데이터 정보
	void *mp_net_user;               // 데이터를 전송한 클라이언트 정보
};

// 현재 수신한 데이터 정보를 저장할 구조체
struct CurrentClientNetworkData
{
	unsigned char m_net_msg_id;      // 메시지 ID
	unsigned short m_net_body_size;  // Body 데이터의 크기
	char *mp_net_body_data;          // Body 데이터 정보
};

// 아래의 두 변수 선언은 필수 사항입니다!! (응용 프로그램 이름과 창 제목 설정)
const char *gp_app_name = "EasyMyWindow";
const char *gp_window_title = "그림과 함께하는 채팅";

using namespace EasyAPI_Tipsware;

#define printf TextOut

#define TIMER void CALLBACK
#define NOT_USE_TIMER_DATA HWND ah_wnd, UINT a_msg_id, UINT_PTR a_timer_id, DWORD a_time

#define NOT_USE_MESSAGE SystemMessageMap g_system_map(NULL, NULL, NULL, NULL, NULL);
#define MOUSE_MESSAGE(left_down, left_up, move) SystemMessageMap g_system_map(left_down, left_up, move, NULL, NULL);
#define MOUSE_MESSAGE_EX(left_down, left_up, move, destory) SystemMessageMap g_system_map(left_down, left_up, move, NULL, destory);
#define MOUSE_CMD_MESSAGE(left_down, left_up, move, command) SystemMessageMap g_system_map(left_down, left_up, move, command, NULL);
#define MOUSE_CMD_MESSAGE_EX(left_down, left_up, move, command, destory) SystemMessageMap g_system_map(left_down, left_up, move, command, destory);
#define CMD_MESSAGE(command) SystemMessageMap g_system_map(NULL, NULL, NULL, command, NULL);
#define CMD_MESSAGE_EX(command, destory) SystemMessageMap g_system_map(NULL, NULL, NULL, command, destory);

#endif