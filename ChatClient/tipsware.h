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

// �Ʒ��� �� ���� ������ �ʼ� �����Դϴ�!! (���� ���α׷� �̸��� â ���� ����)
const char *gp_app_name = "EasyMyWindow";
const char *gp_window_title = "�׸��� �Բ��ϴ� ä��";

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