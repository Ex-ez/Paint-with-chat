#ifndef _EASY_WIN32_H_
#define _EASY_WIN32_H_

// 이 라이브러리는 C 언어로 Win32 프로그래밍을 쉽게 할수 있도록 도와주기 위해 만들었습니다.
// 이 방법을 사용해서 C 언어를 배우면서 Win32 프로그래밍으로 실습을 하면 됩니다.
//
// 제작자 : 김성엽 (tipsware@naver.com, https://blog.naver.com/tipsware, https://cafe.naver.com/easywin32)
// 참여자 : 이연진, 이경직
//
// 개발 시작 : 2019년 9월 3일 화요일
// 최근 업데이트 : 2019년 9월 25일 수요일
//
// 이 라이브러리의 저작권은 '(주)팁스웨어'에 있습니다.
// 이 라이브러리는 C 언어를 공부하는 사람들을 위해 만들어졌습니다.
// 따라서 비상업적인 용도로 사용하는 것은 무료로 사용이 가능하지만 상업적인 용도로 사용하는 것은 허락하지 않습니다.
// 만약, 이 라이브러리를 상업적인 용도로 사용하려면 [ manager@tipsware.com ]으로 라이브러리 사용 정책에 대해 문의하세요.

typedef void (*FP_MOUSE_MSG)(int a_mixed_key, POINT a_pos);
typedef void (*FP_COMMAND)(INT32 a_ctrl_id, INT32 a_notify_code, void *ap_ctrl);
typedef void (*FP_DESTROY)();

#define IMAGE_BMP   0
#define IMAGE_JPEG  1
#define IMAGE_GIF   2
#define IMAGE_TIFF  3
#define IMAGE_PNG   4

class SystemMessageMap
{
protected:
	void *mp_app_data;
	FP_MOUSE_MSG mp_left_down, mp_left_up, mp_mouse_move;
	FP_COMMAND mp_command;
	FP_DESTROY mp_destroy;
public:
	SystemMessageMap(FP_MOUSE_MSG ap_left_down, FP_MOUSE_MSG ap_left_up, FP_MOUSE_MSG ap_mouse_move, FP_COMMAND ap_command, FP_DESTROY ap_destroy);
	virtual ~SystemMessageMap();

	void SetAppData(void *ap_data, int a_data_size);
	void *GetAppData();

	FP_MOUSE_MSG GetLeftBtnDown();
	FP_MOUSE_MSG GetLeftBtnUp();
	FP_MOUSE_MSG GetMouseMove();
	FP_COMMAND GetCommand();
	FP_DESTROY GetDestroy();
};

namespace EasyAPI_Tipsware
{
	void Rectangle(int a_sx, int a_sy, int a_ex, int a_ey);
	void Rectangle(int a_sx, int a_sy, int a_ex, int a_ey, COLORREF a_color);
	void Rectangle(int a_sx, int a_sy, int a_ex, int a_ey, COLORREF a_line_color, COLORREF a_fill_color);

	void Ellipse(int a_sx, int a_sy, int a_ex, int a_ey);
	void Ellipse(int a_sx, int a_sy, int a_ex, int a_ey, COLORREF a_color);
	void Ellipse(int a_sx, int a_sy, int a_ex, int a_ey, COLORREF a_line_color, COLORREF a_fill_color);

	void TextOut(int a_x, int a_y, const char *ap_format, ...);
	void TextOut(int a_x, int a_y, COLORREF a_color, const char *ap_format, ...);


	void Line(int a_sx, int a_sy, int a_ex, int a_ey);
	void Line(int a_sx, int a_sy, int a_ex, int a_ey, COLORREF a_color, int a_tick = 1, int a_style = PS_SOLID);
	void MoveTo(int a_x, int a_y);
	void LineTo(int a_x, int a_y);

	HGDIOBJ SelectStockObject(int a_stock_index);
	HGDIOBJ SelectPenObject(COLORREF a_color, int a_tick = 1, int a_style = PS_SOLID);
	HGDIOBJ SelectBrushObject(COLORREF a_color);
	HGDIOBJ SelectFontObject(const char *ap_name, short a_size, unsigned char a_style = 0);

	void SetTextColor(COLORREF a_color);

	void UseDisplay(int a_index, int a_cx = 800, int a_cy = 600, HWND ah_wnd = NULL);
	void ShowDisplay(int a_index = 0);
	int ChooseColorDlg(COLORREF *ap_init_color);

	void *FindControl(int a_id);
	void *CreateButton(const char *ap_name, int a_x, int a_y, int a_width, int a_height, int a_id, int a_style = 0, int a_ex_syle = 0);
	void *CreateEdit(int a_x, int a_y, int a_width, int a_height, int a_id, int a_style, int a_ex_syle = 0);
	void *CreateListBox(int a_x, int a_y, int a_width, int a_height, int a_id, void *afp_draw = NULL, int a_style = 0, int a_ex_syle = 0);
	void DestroyControl(void *ap_ctrl);
	void ChangeCtrlColor(void *ap_ctrl, COLORREF a_fill_color, COLORREF a_out_border_color, COLORREF a_in_border_color, COLORREF a_text_color);
	void ChangeEditColor(void *ap_ctrl, COLORREF a_fill_color, COLORREF a_text_color);
	void SetCtrlName(void *ap_ctrl, const char *ap_name);
	void GetCtrlName(void *ap_ctrl, char *ap_name, int a_limit_size);
	void Invalidate(void *ap_ctrl, int a_bk_flag = 1);
	void SetCtrlFont(void *ap_ctrl, char *ap_font_name, int a_font_size, int a_attr = 0);
	void CallDrawItem(int a_id, LPARAM lParam);
	void CallMeasureItem(int a_id, LPARAM lParam);
	INT32 CallCtrlColor(WPARAM wParam, LPARAM lParam);

	void ListBox_ChangeDrawFunc(void *ap_ctrl, void *afp_draw);

	int ListBox_AddString(void *ap_ctrl, const char *ap_string, UINT8 a_auto_select = 1);
	int ListBox_InsertString(void *ap_ctrl, INT32 a_index, const char *ap_string, UINT8 a_auto_select = 1);
	int ListBox_GetTextLength(void *ap_ctrl, INT32 a_index);
	int ListBox_GetText(void *ap_ctrl, INT32 a_index, char *ap_string, int a_max_len);
	void ListBox_SetCurSel(void *ap_ctrl, INT32 a_index);
	INT32 ListBox_GetCurSel(void *ap_ctrl);
	INT32 ListBox_GetCount(void *ap_ctrl);
	void ListBox_DeleteString(void *ap_ctrl, INT32 a_index);
	void ListBox_ResetContent(void *ap_ctrl);
	void ListBox_SetItemDataPtr(void *ap_ctrl, INT32 a_index, void *ap_data);
	void ListBox_SetItemDataPtrEx(void *ap_ctrl, INT32 a_index, const char *ap_string, void *ap_data, UINT8 a_auto_select = 1);
	void *ListBox_GetItemDataPtr(void *ap_ctrl, INT32 a_index);
	void ListBox_SetItemData(void *ap_ctrl, INT32 a_index, INT32 a_data);
	void ListBox_SetItemDataEx(void *ap_ctrl, INT32 a_index, const char *ap_string, INT32 a_data, UINT8 a_auto_select = 1);
	INT32 ListBox_GetItemData(void *ap_ctrl, INT32 a_index);
	INT32 ListBox_FindString(void *ap_ctrl, INT32 a_index, const char *ap_string);
	INT32 ListBox_FindStringExact(void *ap_ctrl, INT32 a_index, const char *ap_string);
	void ListBox_SetItemWidth(void *ap_ctrl, INT32 a_width);
	void ListBox_SetItemHeight(void *ap_ctrl, INT32 a_height);

	UINT32 Edit_GetLength(void* ap_ctrl);
	INT32 Edit_ReadTextFromFile(void* ap_ctrl, const char* ap_file_path);
	INT32 Edit_SaveTextToFile(void* ap_ctrl, const char* ap_file_path);

	void EnableEnterKey(void *ap_ctrl);
	void Clear(int a_index = 0, COLORREF a_color = RGB(255, 255, 255));

	void SetAppData(void *ap_data, int a_data_size);
	void *GetAppData();

	HDC GetCurrentDC();
	HBITMAP GetCurrentBitmap();
	void *GetMemDC(int a_index);
	void *GetCurrentMemDC();

	void SetTimer(UINT a_timer_id, UINT a_elapse, void *ap_timer_proc);
	void SetTimer(UINT ah_wnd, UINT a_timer_id, UINT a_elapse, void *ap_timer_proc);

	void KillTimer(UINT a_timer_id);
	void KillTimer(UINT ah_wnd, UINT a_timer_id);

	// ...GP 는 GDI+ 관련 함수들입니다!
	// ap_image_path 경로에 있는 이미지 파일을 읽는 함수!
	void *LoadImageGP(const char *ap_image_path);
	// ap_image에 저장된 이미지 정보를 ap_image_path경로에 a_image_type 형식의 이미지 파일로 저장합니다.
	void SaveImageGP(void *ap_image, const char *ap_image_path, int a_image_type = IMAGE_PNG);
	void *CreateBitmapGP(int a_width, int a_height, DWORD a_flag = 0, int a_bpp = 32);
	void DeleteImageGP(void *ap_image);

	void DrawImageGP(void *ap_image, int a_x, int a_y);
	void DrawImageGP(void *ap_image, int a_x, int a_y, int a_width, int a_height);
	void DrawImageGP(void *ap_image, int a_x, int a_y, double a_cx_rate, double a_cy_rate);
	void TransparentDrawGP(void *ap_image, int a_x, int a_y, COLORREF a_remove_color);
	void TransparentDrawGP(void *ap_image, int a_x, int a_y, int a_width, int a_height, COLORREF a_remove_color);
	void TransparentDrawGP(void *ap_image, int a_x, int a_y, double a_cx_rate, double a_cy_rate, COLORREF a_remove_color);

	HDC GetDCGP(void *ap_image);
	HBITMAP GetBitmapGP(void *ap_image);
	int GetWidthGP(void *ap_image);
	int GetHeightGP(void *ap_image);
	int GetBppGP(void *ap_image);
	int GetPitchGP(void *ap_image);
	void *GetBitsGP(void *ap_image);

	void *CaptureScreenGP(int a_sx, int a_sy, int a_ex, int a_ey);
	void *CaptureScreenGP();

	void StartSocketSystem();
	void StopSocketSystem();

	// [[[ 서버 소켓 관련 ]]]
	void *CreateServerSocket(unsigned int a_user_data_size, void *ap_accept_user, void *ap_proc_net_msg, void *ap_close_user,
								int a_index = 0, int a_max_user_count = 100, unsigned char a_key = 0x51);
	void DeleteServerSocket(void *ap_object);
	void DeleteServerSockets();
	int GetServerSocketIndex(void *ap_object);

	void *GetUsersData(void *ap_object);
	void *GetUserDataByHandle(void *ap_object, unsigned int ah_socket);
	void *GetUserDataByIndex(void *ap_object, int a_index);

	void StartListenService(void *ap_object, const char *ap_ip_address, int a_port);
	void SendFrameDataToClient(void *ap_object, unsigned int ah_socket, char a_msg_id, const void *ap_data, int a_size);
	void BroadcastFrameData(void *ap_object, char a_msg_id, const void *ap_data, int a_size);
	void *GetProcessServerData(void *ap_object);
	void CloseSocketInServer(void *ap_object, unsigned int ah_socket, char *ap_close_user);
	void DestroySocketsInServer(void *ap_object);

	// [[[ 클라이언트 소켓 관련 ]]]
	void *CreateClientSocket(void *ap_connect, void *ap_net_msg, void *ap_close, int a_index = 0, unsigned char a_key = 0x51);
	int GetClientSocketIndex(void *ap_object);
	void DeleteClientSocket(void *ap_object);
	void DeleteClientSockets();
	void *GetProcessClientData(void *ap_object);
	int IsConnect(void *ap_object);
	void ConnectToServer(void *ap_object, const char *ap_ip_address, int a_port);
	void CloseSocket(void *ap_object);
	void SendFrameDataToServer(void *ap_object, char a_msg_id, const void *ap_data, int a_size);
	
	// [[ 문자열 처리 관련 일반 유틸리티 ]]
	char* GetNextString(char* ap_src_str, char a_delimiter, char* ap_buffer);
	char* GetNextStringEx(char* ap_src_str, char a_delimiter, char* ap_buffer, char a_remove_prefix = ' ');
	char* ConvertTabToSpace(const char* ap_src_string);

	// [[ 연산 수식 분석기 관련 ]]
	void* CreateExpParsor();
	const char* GetExpString(void* ap_parsor);
	void InitExpParser(void* ap_parsor);
	void SetExpString(void* ap_parsor, const char* ap_string);
	void RunExpParsing(void* ap_parsor);   // 사용자가 지정한 수식을 분석한다

	int GetExpVariableCount(void* ap_parsor);
	const char* GetExpVariableName(void* ap_parsor, int a_index);
	// 지정된 변수에 값을 대입한다.
	void SetExpVarValue(void* ap_parsor, int a_index, double a_value);
	// 지정된 변수가 참조할 값이 있는 위치를 주소로 알려준다
	void SetExpVariablePointer(void* ap_parsor, int a_index, double* ap_data);
	// 변수값을 주소로 참조하도록 되어 있는 변수가 있다면 해당 주소에서 값을 읽어 변수값을 업데이트 한다.
	void UpdateExpVariableValue(void* ap_parsor);
	// 이미 수식이 parsing되었다면 다시 parsing할 필요가 없고 이함수를 호출한후, ExecExp 함수를 호출하면 된다
	char RestoreExpParserInfo(void* ap_parsor);
	char GetExpReadyFlag(void* ap_parsor);   // Parsing 이 되어있는지를 알려준다 ( 0 -> 파싱안됨, 1 -> 파싱됨 )
	double ExecExp(void* ap_parsor, unsigned int a_prev_depth = 0);  // Parsing된 수식을 실행하여 수식의 결과값을 얻는다
	void DestroyExpParsor(void* ap_parsor);

	void* CreateExpParsorEx();
	const char* GetExpStringEx(void* ap_parsor);
	void InitExpParserEx(void* ap_parsor);
	void SetExpStringEx(void* ap_parsor, const char* ap_string);
	void RunExpParsingEx(void* ap_parsor);   // 사용자가 지정한 수식을 분석한다

	int GetExpVariableCountEx(void* ap_parsor);
	const char* GetExpVariableNameEx(void* ap_parsor, int a_index);
	// 지정된 변수가 참조할 값이 있는 위치를 주소로 알려준다
	void SetExpVariablePointerEx(void* ap_parsor, int a_index, unsigned char a_data_type, double* ap_data);
	// 변수값을 주소로 참조하도록 되어 있는 변수가 있다면 해당 주소에서 값을 읽어 변수값을 업데이트 한다.
	void UpdateExpVariableValueEx(void* ap_parsor);
	// 이미 수식이 parsing되었다면 다시 parsing할 필요가 없고 이함수를 호출한후, ExecExp 함수를 호출하면 된다
	char RestoreExpParserInfoEx(void* ap_parsor);
	char GetExpReadyFlagEx(void* ap_parsor);   // Parsing 이 되어있는지를 알려준다 ( 0 -> 파싱안됨, 1 -> 파싱됨 )
	void DestroyExpParsorEx(void* ap_parsor);

	// [ 매크로 관련 함수들 ]
	// 시스템 키를 입력하는 함수. 
	void SystemKeyWrite(char a_key, int a_delay = 250);  // (Key Down & Up을 한 번에 처리)
	void SystemKeyDown(char a_key);
	void SystemKeyUp(char a_key);
	// 일반 키를 입력하는 함수. Shift 키를 사용하는 경우에는 a_is_shift에 1을 입력해야 한다. 
	void InputNormalChar(char a_is_shift, char a_key);  // (Key Down & Up을 한 번에 처리)
	void InputNormalCharDown(char a_is_shift, char a_key);
	void InputNormalCharUp(char a_is_shift, char a_key);
	// ap_string에 전달된 키보드로 입력한다.
	char InputNormalString(const char* ap_string, char a_is_han_mode, int a_delay = 100);
	void WaitInputSystem(int a_delay);

	void MouseMoveWrite(int a_x, int a_y);  // 마우스 이동!
	void MouseClickWrite(int a_x, int a_y, int a_is_left = 1, int a_delay = 0);
	void MouseClickDown(int a_x, int a_y, int a_is_left = 1);
	void MouseClickUp(int a_x, int a_y, int a_is_left = 1);

	void CheckOBjectPos(RECT* p_target_rect, int a_x, int a_y, unsigned int a_org_color, unsigned int a_change_color, unsigned int* ap_image_data, int a_image_width, int a_image_height);

	// 클립보드 관련 함수
	int CopyTextToClipboard(const char* ap_string);
	int CopyTextFromClipboard(char** ap_string, char a_is_clear);
	HBITMAP MakeDupBitmap(HBITMAP ah_bitmap);
	HBITMAP MakeDupBitmap(HBITMAP ah_bitmap, unsigned int* ap_image_data);
	HBITMAP CopyBitmapFromClipBoard();
	void CopyBitmapToClipBoard(HBITMAP ah_bitmap);

	// Common Dialog 관련 함수
	int ChooseOpenFileName(char* ap_open_path, int a_path_size, const char* ap_filter = "All\0*.*\0Text\0*.txt\0", int a_filter_index = 1, const char* ap_init_path = NULL, int a_add_attr = 0);
	int ChooseSaveFileName(char* ap_open_path, int a_path_size, const char* ap_filter = "All\0*.*\0Text\0*.txt\0", int a_filter_index = 1, const char* ap_init_path = NULL, int a_add_attr = 0);
	int ChooseColorDlg(COLORREF a_init_color, COLORREF* ap_selected_color);
	int ChooseFontDlg(char* ap_font_name, int* ap_font_size, int* ap_font_style, COLORREF a_init_color = RGB(0, 0, 0), COLORREF* ap_selected_color = NULL);
}

extern const char *gp_app_name;
extern const char *gp_window_title;
extern HWND gh_main_wnd;
#endif