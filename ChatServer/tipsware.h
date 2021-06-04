#ifndef _TIPSWARE_H_
#define _TIPSWARE_H_


#include "resource.h"

// ExpParserEx���� ����ϴ� ����ü
struct ExpDataType {
	unsigned char d_type;
	union {
		__int8 i8;
		__int16 i16;
		__int32 i32;
		__int64 i64;
		float f;
		double d;
	};
};

#include "EasyWin32.h"

#pragma comment(lib, "gdiplus")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "WS2_32.lib")

#ifdef _DEBUG
	#pragma comment(lib, "DSH_EasyWin32.lib")
#else
	#pragma comment(lib, "RST_EasyWin32.lib")
#endif

/*
���Ͽ��� ���Ѿ��� UserData ���� ����!! - 1���� Ŭ���̾�Ʈ ������ ������ ����ü
struct UserData
{
	unsigned int h_socket;   // ���� �ڵ�
	char ip_address[16];     // ������ Ŭ���̾�Ʈ�� �ּ�
};
*/

// ���� ������ ������ ������ ������ ����ü
struct CurrentServerNetworkData
{
	unsigned char m_net_msg_id;      // �޽��� ID
	unsigned short m_net_body_size;  // Body �������� ũ��
	char *mp_net_body_data;          // Body ������ ����
	void *mp_net_user;               // �����͸� ������ Ŭ���̾�Ʈ ����
};

// ���� ������ ������ ������ ������ ����ü
struct CurrentClientNetworkData
{
	unsigned char m_net_msg_id;      // �޽��� ID
	unsigned short m_net_body_size;  // Body �������� ũ��
	char *mp_net_body_data;          // Body ������ ����
};

// ���� ���α׷��� ����ϴ� ���� ������ Ŭ���� �̸��Դϴ�. (���� ����)
const char *gp_app_name = "EasyServerWindow";
// ���� ���α׷��� ����ϴ� �����Դϴ�. (���� ����)
const char *gp_window_title = "�׸��� �Բ��ϴ� ä�� ����";
// ���� ���α׷��� ����� �޴��� ID�Դϴ�. (0�̸� �޴��� ������� �ʴ´ٴ� ���Դϴ�.)
int g_menu_id = IDI_EXAMEASYSERVER;

using namespace EasyAPI_Tipsware;

#define printf TextOut

#define TIMER void CALLBACK
#define NOT_USE_TIMER_DATA HWND ah_wnd, UINT a_msg_id, UINT_PTR a_timer_id, DWORD a_time

#define NOT_USE_MESSAGE SystemMessageMap g_system_map(NULL, NULL, NULL, NULL, NULL, NULL);
#define MOUSE_MESSAGE(left_down, left_up, move) SystemMessageMap g_system_map(left_down, left_up, move, NULL, NULL, NULL);
#define MOUSE_MESSAGE_EX(left_down, left_up, move, destory) SystemMessageMap g_system_map(left_down, left_up, move, NULL, destory, NULL);
#define MOUSE_CMD_MESSAGE(left_down, left_up, move, command) SystemMessageMap g_system_map(left_down, left_up, move, command, NULL, NULL);
#define MOUSE_CMD_MESSAGE_EX(left_down, left_up, move, command, destory) SystemMessageMap g_system_map(left_down, left_up, move, command, destory, NULL);
#define CMD_MESSAGE(command) SystemMessageMap g_system_map(NULL, NULL, NULL, command, NULL, NULL);
#define CMD_USER_MESSAGE(command, destory, user_msg) SystemMessageMap g_system_map(NULL, NULL, NULL, command, destory, user_msg);
#define ON_MESSAGE(left_down, left_up, move, command, destory, user_msg) SystemMessageMap g_system_map(left_down, left_up, move, command, destory, user_msg);

#endif