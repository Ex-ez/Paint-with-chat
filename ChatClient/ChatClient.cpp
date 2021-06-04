#include "pch.h"
#include <stdio.h>   
#include "tipsware.h"

#pragma comment(lib, "WS2_32.lib")   // Windows Socket API 이용
#define IDC_SAVE_FILE_BTN 1014
#define BLOCK_LENGTH		50



struct AppData
{
	void *p_socket;  
	char is_clicked;   // 마우스 클릭 여부(1: 클릭, 0: 클릭 해제)
	char thick;   // 선 굵기 정보
	COLORREF color;    // 선 색상 정보
	POINT prev_pos;    // 마우스를 클릭해서 이동할 때, 이전 마우스 좌표 저장


};

struct DrawLineData   // 메시지 아이디 2번에서 사용할 구조체 (사용자의 선 그리기 정보)
{
	char thick;       // 선 굵기 정보
	COLORREF color;   // 선 색상 정보
	POINT start_pos;  // 선의 시작 좌표
	POINT end_pos;    // 선의 끝 좌표
};

void OnServerConnection(void* ap_this, int a_client_index)
{
	char temp_str[64];
	if (IsConnect(ap_this)) sprintf_s(temp_str, 64, "서버에 접속했습니다!!");
	else sprintf_s(temp_str, 64, "서버에 접속할 수 없습니다.!!");
	ListBox_InsertString(FindControl(1000), -1, temp_str);
}

int OnServerMessage(CurrentClientNetworkData* ap_data, void* ap_this, int a_client_index)
{
	if (ap_data->m_net_msg_id == 1) { // 채팅 데이터가 전달됨
		ListBox_InsertString(FindControl(1000), -1, ap_data->mp_net_body_data);
	}
	else if (ap_data->m_net_msg_id == 2) {  // 선 그리기 정보가 전달됨
		DrawLineData* p_line_data = (DrawLineData*)ap_data->mp_net_body_data;
		Line(p_line_data->start_pos.x, p_line_data->start_pos.y, p_line_data->end_pos.x,
			p_line_data->end_pos.y, p_line_data->color, p_line_data->thick);
		ShowDisplay();
	}
	else if (ap_data->m_net_msg_id == 3) { // 사용자가 지우기 버튼을 누른 경우!
		Clear(0, RGB(155, 187, 212)); 
		ShowDisplay(); 
	}
	return 1;
}

void OnCloseUser(void* ap_this, int a_error_flag, int a_client_index)
{
	char temp_str[64];
	if (a_error_flag == 1) sprintf_s(temp_str, 64, "서버에서 접속을 해제했습니다."); 
	else sprintf_s(temp_str, 64, "서버와 접속을 해제했습니다.");
	ListBox_InsertString(FindControl(1000), -1, temp_str);
}

void SendChatData(AppData* ap_data)
{
	void* p_edit = FindControl(1020); 
	char str[128]; 

	GetCtrlName(p_edit, str, 128);
	SetCtrlName(p_edit, "");

	// 클라이언트 소켓 객체가 만들어져 있고 서버와 접속상태인지 확인한다.
	if (ap_data->p_socket && IsConnect(ap_data->p_socket)) {
		SendFrameDataToServer(ap_data->p_socket, 1, str, strlen(str) + 1);
	}
}

// 서버에 접속을 시도합니다.
void OnConnectBtn(AppData* ap_data)
{
	if (ap_data->p_socket == NULL) {  // 클라이언트 소켓 객체가 만들어져 있는지 확인!
		ap_data->p_socket = CreateClientSocket(OnServerConnection, OnServerMessage, OnCloseUser);
	}
	if (!IsConnect(ap_data->p_socket)) {  // 서버와의 접속 상태를 체크한다.
		ConnectToServer(ap_data->p_socket, "192.168.0.3", 25001);
	}
}

// 서버와 연결을 해제합니다.
void OnDisconnectBtn(AppData* ap_data)
{
	if (ap_data->p_socket != NULL) { 	
		DeleteClientSocket(ap_data->p_socket); 
		ap_data->p_socket = NULL;
	}
}

//  화면에 그려진 이미지를 지우기 위해 서버로 3번 메시지를 전송한다.
void OnClearImageBtn(AppData* ap_data)
{
	if (ap_data->p_socket && IsConnect(ap_data->p_socket)) {.
		SendFrameDataToServer(ap_data->p_socket, 3, "", 1);
	}
}

// 선 색상 목록에서 색상을 변경한 경우에 호출됩니다.
void OnChangeColorBtn(AppData* ap_data, INT32 a_notify_code, void* ap_ctrl)
{
	if (a_notify_code == LBN_SELCHANGE) {
		ap_data->color = ListBox_GetItemData(ap_ctrl, ListBox_GetCurSel(ap_ctrl));
	}
}


// 선 굵기 목록에서 굵기를 변경한 경우에 호출됩니다.
void OnChangeThickBtn(AppData* ap_data, INT32 a_notify_code, void* ap_ctrl)
{
	if (a_notify_code == LBN_SELCHANGE) {
		ap_data->thick = ListBox_GetItemData(ap_ctrl, ListBox_GetCurSel(ap_ctrl));
	}
}
/*void OpenTextFile()   // 사용자가 선택한 파일을 열어서 에디트 컨트롤에 보여주는 함수
{
	char path[MAX_PATH];  
	if (ChooseOpenFileName(path, MAX_PATH)) {  
		Edit_ReadTextFromFile(FindControl(1000), path);
	}
}

void SaveTextFile()  // 에디트 컨트롤에 적힌 문자열을 사용자가 선택한 파일에 저장한다.
{
	//char path[MAX_PATH]; 
	if (ChooseSaveFileName(path, MAX_PATH)) { 
		Edit_SaveTextToFile(FindControl(1014), path);
	}
}*/
void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl)
{
	AppData* p_data = (AppData*)GetAppData();  // 프로그램 내부 데이터의 주소를 가져온다.
	COLORREF color[1] = { RGB(100,200,255) };
	// '입력' 버튼을 누르거나 에디트 박스에서 '엔터' 키를 누른 경우!
	if (a_ctrl_id == 1013 || (a_ctrl_id == 1020 && a_notify_code == 1000)) SendChatData(p_data);
	else if (a_ctrl_id == 1011) OnConnectBtn(p_data);  // [접속] 버튼을 누른 경우!
	else if (a_ctrl_id == 1012) OnDisconnectBtn(p_data); // [해제] 버튼을 누른 경우!
	else if (a_ctrl_id == 1001) OnChangeColorBtn(p_data, a_notify_code, ap_ctrl); // 선 색상 변경!
	else if (a_ctrl_id == 1002) OnChangeThickBtn(p_data, a_notify_code, ap_ctrl); // 선 굵기 변경!
	else if (a_ctrl_id == 1010) OnClearImageBtn(p_data); // [지우기] 버튼을 누른 경우!
	else if (a_ctrl_id == 1100) {
		void* p_image = LoadImageGP("tips.png");

		DrawImageGP(p_image, 100, 100, 0.25, 0.25);


		ShowDisplay(); // 정보를 윈도우에 출력한다.
	}
	else if (a_ctrl_id == 1101) {
		void* p_image = LoadImageGP("air.png");

		DrawImageGP(p_image, 0, 0, 1.00, 0.85);


		ShowDisplay(); // 정보를 윈도우에 출력한다.
	}
	else if (a_ctrl_id == 1102) {
		void* p_image = LoadImageGP("coro.png");

		DrawImageGP(p_image, 0, 0, 0.70, 0.75);


		ShowDisplay(); // 정보를 윈도우에 출력한다.
	}
	else if (a_ctrl_id == 1103) {
		void* p_image = LoadImageGP("jaju.png");

		DrawImageGP(p_image, 0, 0, 1.00, 0.85);


		ShowDisplay(); // 정보를 윈도우에 출력한다.
	}
	else if (a_ctrl_id == 1104) {
		void* p_image = LoadImageGP("pro.png");

		DrawImageGP(p_image, 0, 0, 0.85, 0.85);


		ShowDisplay(); // 정보를 윈도우에 출력한다.
	}
}


void SendLineData(AppData* ap_data, POINT a_pos)
{
	// 클라이언트 소켓 객체가 만들어져 있고 서버와 접속상태인지 확인한다.
	if (ap_data->p_socket && IsConnect(ap_data->p_socket)) {
		DrawLineData send_data;  // 선 그리기 정보를 저장할 구조체로 변수 선언!
		send_data.color = ap_data->color;  // 선의 색상
		send_data.thick = ap_data->thick;  // 선의 굵기
		send_data.start_pos = ap_data->prev_pos;  // 선의 시작 좌표
		send_data.end_pos = a_pos;   // 선의 끝 좌표
		// 선 그리기 정보를 서버로 전송한다. 메시지 아이디는 2로 지정한다.
		SendFrameDataToServer(ap_data->p_socket, 2, &send_data, sizeof(DrawLineData));
	}
}

// 마우스 왼쪽 버튼을 눌렀을 때 호출될 함수
void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
	AppData* p_data = (AppData*)GetAppData();  // 프로그램의 내부 데이터 주소를 가져온다.
	p_data->prev_pos = a_pos;  // 선 그리기의 시작 점으로 사용할 좌표를 저장한다.
	p_data->is_clicked = 1; // 마우스가 클릭되었음을 설정한다.
}

// 마우스를 움직일 때 호출될 함수
void OnMouseMove(int a_mixed_key, POINT a_pos)
{
	AppData* p_data = (AppData*)GetAppData();  // 프로그램의 내부 데이터 주소를 가져온다.
	if (p_data->is_clicked == 1) { // 마우스가 클릭되었는지 확인한다.
		SendLineData(p_data, a_pos);  // 선 그리기 정보를 서버로 전송한다.
		p_data->prev_pos = a_pos; // 다음 그리기의 시작 점으로 사용할 좌표를 저장한다.
	}
}

// 마우스 왼족 버튼을 눌렀다가 해제했을 때 호출될 함수
void OnMouseLeftUp(int a_mixed_key, POINT a_pos)
{
	AppData* p_data = (AppData*)GetAppData(); // 프로그램의 내부 데이터 주소를 가져온다.
	if (p_data->is_clicked == 1) {  // 마우스가 클릭되었는지 확인한다.
		SendLineData(p_data, a_pos); // 선 그리기 정보를 서버로 전송한다.
		p_data->is_clicked = 0; // 마우스가 클릭이 해제되었음을 설정한다.
	}
}

// 마우스 왼쪽 버튼을 클릭, 해제 그리고 움직일 때 각 함수가 호출되도록 등록!
MOUSE_CMD_MESSAGE(OnMouseLeftDown, OnMouseLeftUp, OnMouseMove, OnCommand)

// 선 굵기 선택 리스트 박스에서 각 항목을 그리는 함수를 직접 구현함!
void DrawThickItem(int index, char* ap_str, int a_str_len, void* ap_data, int a_is_selected, RECT* ap_rect)
{

	if (a_is_selected) SelectPenObject(RGB(100, 220, 255), 2);
	else SelectPenObject(RGB(62, 77, 104), 2);


	SelectBrushObject(RGB(62, 77, 104));
	Rectangle(ap_rect->left + 1, ap_rect->top + 1, ap_rect->right, ap_rect->bottom);


	SelectPenObject(RGB(255, 255, 255), (int)ap_data);
	Line(ap_rect->left + 6, ap_rect->top + 8, ap_rect->right - 7, ap_rect->top + 8);
}

// 색상 선택 리스트 박스에서 각 항목을 그리는 함수를 직접 구현함!
void DrawColorItem(int index, char* ap_str, int a_str_len, void* ap_data, int a_is_selected, RECT* ap_rect)
{
	if (a_is_selected) SelectPenObject(RGB(100, 220, 255), 2);
	else SelectPenObject(RGB(62, 77, 104), 2);

	SelectBrushObject((COLORREF)ap_data);
	Rectangle(ap_rect->left + 1, ap_rect->top + 1, ap_rect->right, ap_rect->bottom);
}

// 만들어진 리스트 박스에 20개의 색상을 추가한다.
void AddColorToList(void* ap_list_box)
{
	COLORREF color_table[21] = {  
		 RGB(0,0,0), RGB(0,0,255), RGB(0,255,0), RGB(0,255,255), RGB(255,0,0), RGB(255,0,255),
		 RGB(255,255,0), RGB(255,255,255), RGB(0,0,128), RGB(0,128,0), RGB(0,128,128),
		 RGB(128,0,0), RGB(128,0,128), RGB(128,128,0), RGB(128,128,128), RGB(192,192,192),
		 RGB(192,220,192), RGB(166,202,240), RGB(255,251,240), RGB(160,160,164),
	};
	ListBox_SetItemWidth(ap_list_box, 18);
	// 20개의 색상을 리스트 박스에 추가한다.
	for (int i = 0; i < 21; i++) ListBox_SetItemDataEx(ap_list_box, i, "", color_table[i], 0);
	// a_init_index 위치에 있는 항목을 선택한다.
	ListBox_SetCurSel(ap_list_box, 0);
}

int main()
{

	AppData data = { NULL, 0, 2, RGB(0, 0, 0), { 0, 0 } };
	SetAppData(&data, sizeof(AppData));  

	Clear(0, RGB(155, 187, 212)); 
	StartSocketSystem(); 
	CreateListBox(10, 400, 500, 100, 1000); 
	void* p = CreateListBox(520, 400, 56, 114, 1001, DrawColorItem, LBS_MULTICOLUMN); // 선 색상 목록!
	AddColorToList(p); 
	// 선 굵기를 선택하는 리스트 박스를 만들고 1 ~ 7까지 굵기를 추가한다.
	p = CreateListBox(586, 400, 56, 114, 1002, DrawThickItem); 
	for (int i = 0; i < 7; i++) ListBox_SetItemDataEx(p, i, "", i + 1, 0); 
	ListBox_SetCurSel(p, 1);  

	CreateButton("지우기", 354, 370, 50, 28, 1010);   // [지우기] 버튼 생성
	CreateButton("접속", 407, 370, 50, 28, 1011);     // [접속] 버튼 생성
	CreateButton("해제", 460, 370, 50, 28, 1012);     // [해제] 버튼 생성
	CreateButton("입력", 460, 510, 50, 28, 1013);   // [입력] 버튼 생성 140
	//CreateButton("파일 저장", 460, 550, 50, 28, 1014);
	p = CreateEdit(10, 510, 446, 24, 1020, 0);  // 문자열을 입력할 에디트 컨트롤을 생성!
	EnableEnterKey(p);

	SelectFontObject("굴림", 13); // 글꼴을 '굴림', 12 크기로 변경한다.	
	TextOut(15, 380, RGB(82, 97, 124), "사용자 채팅글 목록"); 
	TextOut(525, 380, RGB(82, 97, 124), "선 색상");
	TextOut(591, 380, RGB(82, 97, 124), "선 굵기");  

	SelectPenObject(RGB(0, 0, 0), 1, PS_SOLID);
	CreateButton("1", 150, 370, 50, 28, 1100);
	CreateButton("2", 200, 370, 50, 28, 1101);
	CreateButton("3", 250, 370, 50, 28, 1102);
	CreateButton("4", 300, 370, 50, 28, 1103);
	CreateButton("대문", 588, 520, 50, 28, 1104);
	
	ShowDisplay(); // 정보를 윈도우에 출력한다.
	return 0;
}
