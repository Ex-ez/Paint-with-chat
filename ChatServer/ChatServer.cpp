#include "pch.h"
#include <stdio.h>   
#include "tipsware.h"

#define ID_LB_CHAT         1000   // 채팅 정보가 추가될 리스트 박스 아이디
#define ID_LB_USER         1001   // 사용자 목록이 저장될 리스트 박스 아이디

#define ID_BTN_ADD         1011   // 추가 버튼의 아이디
#define ID_BTN_MODIFY      1012   // 변경 버튼의 아이디
#define ID_BTN_DEL         1013   // 삭제 버튼의 아이디

#define ID_EDIT_ID         1020   // 아이디 입력용 에디트
#define ID_EDIT_PASSWORD   1021   // 암호 입력용 에디트
#define ID_EDIT_NICKNAME   1022   // 별명 입력용 에디트

#define ID_CB_LEVEL        1030   // 등급 입력용 콤보 박스

struct UserData;

// 서버에 접속하는 사용자를 관리하기 위한 구조체!! (1명에 해당하는 정보만 구성)
typedef struct RegisteredUserData
{
	char id[32];         // 사용자 ID
	char pw[32];         // 사용자 Password
	char nickname[32];
	char level;          // 사용자 등급.
	UserData* p_socket;  // 접속중이라면 사용중인 소켓 정보의 주소
} RUD;

struct AppData   // 프로그램에서 사용할 내부 데이터
{
	void* p_user_list;  // 사용자 목록 리스트 박스의 주소
	void* p_chat_list;  // 채팅 목록 리스트 박스의 주소
	void* p_server;     // 서버 소켓 객체의 주소
};


struct UserData
{
	unsigned int h_socket;
	char ip_address[16];
};


const char* gp_user_level_str[5] = { "손님", "일반", "고급", "스텝", "관리자" };

// 새로운 클라이언트가 접속을 하면 이 함수가 호출됨!! 
// ap_user_data에는 접속한 클라이언트 정보가 이미 구성되어 있음!
// ap_server에는 서버 객체에 대한 주소가 들어있음!
void OnNewUser(UserData* ap_user_data, void* ap_server, int a_server_index)
{
	char temp_str[64];
	sprintf_s(temp_str, 64, "새로운 사용자가 %s에서 접속을 했습니다!", ap_user_data->ip_address);

	ListBox_InsertString(FindControl(ID_LB_CHAT), -1, temp_str);
}


int OnClientMessage(CurrentServerNetworkData* ap_data, void* ap_server, int a_server_index)
{

	UserData* p_user_data = (UserData*)ap_data->mp_net_user;
	char temp_str[128];
	if (ap_data->m_net_msg_id == 1) {
		sprintf_s(temp_str, 128, "%s : %s", p_user_data->ip_address, ap_data->mp_net_body_data);
		ListBox_InsertString(FindControl(ID_LB_CHAT), -1, temp_str);
		BroadcastFrameData(ap_server, 1, temp_str, strlen(temp_str) + 1);
	}
	else if (ap_data->m_net_msg_id == 2 || ap_data->m_net_msg_id == 3) {
		BroadcastFrameData(ap_server, ap_data->m_net_msg_id, ap_data->mp_net_body_data, ap_data->m_net_body_size);
	}
	return 1;
}

// 클라이언트가 접속을 해제하면 이 함수가 호출됨!!
void OnCloseUser(UserData* ap_user_data, void* ap_server, int a_error_flag, int a_server_index)
{
	char temp_str[64];
	if (a_error_flag == 1) {  // 오류로 인한 클라이언트 해제!!
		sprintf_s(temp_str, 64, "%s에서 접속한 사용자를 강제로 접속 해제했습니다.", ap_user_data->ip_address);
	}
	else {  // 정상적인 클라이언트 해제!!
		sprintf_s(temp_str, 64, "%s에서 사용자가 접속을 해제하였습니다!", ap_user_data->ip_address);
	}

	ListBox_InsertString(FindControl(ID_LB_CHAT), -1, temp_str);
}


RUD* FindUserID(AppData* ap_data, const char* ap_user_id)
{
	RUD* p_user_info;
	int count = ListBox_GetCount(ap_data->p_user_list); // 리스트 박스에 추가된 항목의 수를 얻는다.   
	for (int i = 0; i < count; i++) {
		// i 번째 항목에 저장된 사용자 정보의 주소를 가져온다.
		p_user_info = (RUD*)ListBox_GetItemDataPtr(ap_data->p_user_list, i);
		// ID가 일치하면 현재 사용자의 주소를 반환한다.
		if (!strcmp(p_user_info->id, ap_user_id)) return p_user_info;
	}
	return NULL;  // 지정한 ID를 찾기에 실패한 경우!
}



void CopyControlDataToMemory(int a_ctrl_id, char* ap_memory, int a_mem_size)
{
	void* p_edit = FindControl(a_ctrl_id); 
	GetCtrlName(p_edit, ap_memory, a_mem_size); 
	SetCtrlName(p_edit, "");
}

// 사용자 정보가 입력된 컨트롤에서 정보를 읽어 사용자 목록에 추가하는 함수
void RegisteringUserData()
{
	AppData* p_data = (AppData*)GetAppData();

	char str[32];
	void* p_edit = FindControl(ID_EDIT_ID);
	GetCtrlName(p_edit, str, 32); 
	int id_len = strlen(str) + 1;  // 입력된 아이디의 길이를 구한다.
	if (id_len > 5) { // 아이디는 최소 5자 이상이어야 한다.
		if (NULL == FindUserID(p_data, str)) {  // 동일한 아이디를 사용하는지 체크한다!
			SetCtrlName(p_edit, ""); // 에디트 컨트롤에 쓰여진 문자열을 지운다.

			// 사용자 정보를 저장할 메모리를 할당한다.
			RUD* p_temp_user = (RUD*)malloc(sizeof(RUD));
			if (p_temp_user != NULL) {
				memcpy(p_temp_user->id, str, id_len);  // 사용자 ID를 사용자 정보에 저장한다.
				CopyControlDataToMemory(ID_EDIT_PASSWORD, p_temp_user->pw, 32);
				CopyControlDataToMemory(ID_EDIT_NICKNAME, p_temp_user->nickname, 32);
				p_temp_user->level = ComboBox_GetCurSel(FindControl(ID_CB_LEVEL));
				p_temp_user->p_socket = NULL;   // 사용자 접속 정보를 초기화한다.

				int index = ListBox_AddString(p_data->p_user_list, p_temp_user->id, 0);
				ListBox_SetItemDataPtr(p_data->p_user_list, index, p_temp_user);
				ListBox_SetCurSel(p_data->p_user_list, index);
			}
		}
		else {  // ID 중복 오류 표시
			ListBox_InsertString(p_data->p_chat_list, -1,
				"[등록 오류]: 동일한 ID를 가진 사용자가 이미 있습니다!");
		}
	}
	else {  // ID 형식 오류 표시
		ListBox_InsertString(p_data->p_chat_list, -1,
			"[등록 오류]: ID는 최소 5자 이상 입력해야 합니다!!");
	}
}


void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl)
{
	COLORREF color[1] = { RGB(100,200,255) };
	if (a_ctrl_id == ID_BTN_ADD) RegisteringUserData();  // [추가] 버튼을 누른 경우!
	else if (a_ctrl_id == 1234) {
		void* p_image = LoadImageGP("tips.png");

		DrawImageGP(p_image, 15, 15, 0.25, 0.25);


		ShowDisplay(); 
	}
}

// 사용자 목록에 등록된 정보를 파일에 저장하는 함수!
void SaveUserData(const char* ap_file_name)
{
	FILE* p_file = NULL;  
	
	if (0 == fopen_s(&p_file, ap_file_name, "wb") && p_file != NULL) {
		void* p_ctrl = FindControl(ID_LB_USER); 
		int count = ListBox_GetCount(p_ctrl);
		fwrite(&count, sizeof(int), 1, p_file);  
		for (int i = 0; i < count; i++) {
			
			fwrite(ListBox_GetItemDataPtr(p_ctrl, i), sizeof(RUD), 1, p_file);
		}
		fclose(p_file);  // 파일을 닫는다.
	}
}


void DestoryUserData()
{
	SaveUserData("user_list.dat");

	void* p_data, * p_ctrl = FindControl(ID_LB_USER); .
	int count = ListBox_GetCount(p_ctrl); .   
	for (int i = 0; i < count; i++) {  
		p_data = ListBox_GetItemDataPtr(p_ctrl, i);
		free(p_data); // p_data가 가리키는 메모리를 해제한다.
	}
	ListBox_ResetContent(p_ctrl);  // 리스트 박스의 모든 항목을 제거한다.
}

CMD_USER_MESSAGE(OnCommand, DestoryUserData, NULL)

void DrawUserDataItem(int index, char* ap_str, int a_str_len, void* ap_data, int a_is_selected, RECT* ap_rect)
{
	if (a_is_selected) SelectPenObject(RGB(200, 255, 255));  // 선택 됨
	else SelectPenObject(RGB(62, 77, 104));  // 선택 안됨

	SelectBrushObject(RGB(62, 77, 104));

	Rectangle(ap_rect->left, ap_rect->top, ap_rect->right, ap_rect->bottom);

	RUD* p_data = (RUD*)ap_data;
	SelectFontObject("굴림", 12);
	// 사용자 아이디와 이름을 함께 출력한다.
	TextOut(ap_rect->left + 5, ap_rect->top + 3, RGB(255, 255, 255), "%s(%s)", p_data->id, p_data->nickname);
	// 사용자 등급을 출력한다.
	TextOut(ap_rect->left + 200, ap_rect->top + 3, RGB(255, 255, 0), gp_user_level_str[p_data->level]);

	if (p_data->p_socket != NULL) {  // 사용자가 접속 상태라면 IP를 함께 표시해준다!
		TextOut(ap_rect->left + 300, ap_rect->top + 3, RGB(200, 212, 225), p_data->p_socket->ip_address);
	}
}

void LoadUserData(AppData* ap_data, const char* ap_file_name)
{
	FILE* p_file = NULL;  // 파일을 열어서 사용할 파일 포인터!
	if (0 == fopen_s(&p_file, ap_file_name, "rb") && p_file != NULL) {
		int count = 0, index;
		fread(&count, sizeof(int), 1, p_file);  // 파일에 저장된 사용자 수를 읽는다.
		RUD* p_user_info;
		for (int i = 0; i < count; i++) {
			p_user_info = (RUD*)malloc(sizeof(RUD));
			if (p_user_info != NULL) {
				fread(p_user_info, sizeof(RUD), 1, p_file);
				p_user_info->p_socket = NULL;
				index = ListBox_AddString(ap_data->p_user_list, p_user_info->id, 0);
				// 새로 추가된 항목에 사용자 정보의 주소를 함께 저장한다.
				ListBox_SetItemDataPtr(ap_data->p_user_list, index, p_user_info);
			}
		}
		fclose(p_file);
	}
}

void CreateUI(AppData* ap_data)
{
	SelectFontObject("굴림", 12);
	TextOut(15, 10, RGB(200, 255, 200), "사용자 채팅글 목록");
	ap_data->p_chat_list = CreateListBox(10, 30, 600, 200, ID_LB_CHAT);

	TextOut(15, 243, RGB(200, 255, 200), "등록된 사용자 목록");
	ap_data->p_user_list = CreateListBox(10, 263, 600, 160,
		ID_LB_USER, DrawUserDataItem);

	CreateButton("추가", 207, 430, 70, 28, 1011);
	CreateButton("변경", 280, 430, 70, 28, ID_BTN_MODIFY);
	CreateButton("삭제", 353, 430, 70, 28, ID_BTN_DEL);

	TextOut(15, 476, RGB(255, 255, 255), "아이디 : ");
	CreateEdit(65, 470, 100, 24, ID_EDIT_ID, 0);

	TextOut(180, 476, RGB(255, 255, 255), "암호 : ");
	CreateEdit(218, 470, 100, 24, ID_EDIT_PASSWORD, 0);

	TextOut(333, 476, RGB(255, 255, 255), "별명 : ");
	CreateEdit(371, 470, 100, 24, ID_EDIT_NICKNAME, 0);

	TextOut(486, 476, RGB(255, 255, 255), "등급 : ");
	void* p = CreateComboBox(524, 470, 76, 186, ID_CB_LEVEL);
	for (int i = 0; i < 5; i++) ComboBox_InsertString(p, i, gp_user_level_str[i], 0);
	ComboBox_SetCurSel(p, 0);
}

int main()
{
	ChangeWorkSize(620, 500);
	Clear(0, RGB(72, 87, 114));// 배경색
	StartSocketSystem();


	AppData data;

	data.p_server = CreateServerSocket(sizeof(UserData), OnNewUser, OnClientMessage, OnCloseUser);

	CreateUI(&data);
	SetAppData(&data, sizeof(AppData));

	LoadUserData(&data, "user_list.dat");

	StartListenService(data.p_server, "192.168.0.3", 25001);

	
	ShowDisplay();
	return 0;
}
