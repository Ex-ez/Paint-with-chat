#ifndef _EASY_WIN32_H_
#define _EASY_WIN32_H_

// �� ���̺귯���� C ���� Win32 ���α׷����� ���� �Ҽ� �ֵ��� �����ֱ� ���� ��������ϴ�.
// �� ����� ����ؼ� C �� ���鼭 Win32 ���α׷������� �ǽ��� �ϸ� �˴ϴ�.
//
// ������ : �輺�� (tipsware@naver.com, https://blog.naver.com/tipsware, https://cafe.naver.com/easywin32)
// ������ : �̿���, �̰���
//
// ���� ���� : 2019�� 9�� 3�� ȭ����
// �ֱ� ������Ʈ : 2019�� 9�� 25�� ������
//
// �� ���̺귯���� ���۱��� '(��)��������'�� �ֽ��ϴ�.
// �� ���̺귯���� C �� �����ϴ� ������� ���� ����������ϴ�.
// ���� �������� �뵵�� ����ϴ� ���� ����� ����� ���������� ������� �뵵�� ����ϴ� ���� ������� �ʽ��ϴ�.
// ����, �� ���̺귯���� ������� �뵵�� ����Ϸ��� [ manager@tipsware.com ]���� ���̺귯�� ��� ��å�� ���� �����ϼ���.

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

	// ...GP �� GDI+ ���� �Լ����Դϴ�!
	// ap_image_path ��ο� �ִ� �̹��� ������ �д� �Լ�!
	void *LoadImageGP(const char *ap_image_path);
	// ap_image�� ����� �̹��� ������ ap_image_path��ο� a_image_type ������ �̹��� ���Ϸ� �����մϴ�.
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

	// [[[ ���� ���� ���� ]]]
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

	// [[[ Ŭ���̾�Ʈ ���� ���� ]]]
	void *CreateClientSocket(void *ap_connect, void *ap_net_msg, void *ap_close, int a_index = 0, unsigned char a_key = 0x51);
	int GetClientSocketIndex(void *ap_object);
	void DeleteClientSocket(void *ap_object);
	void DeleteClientSockets();
	void *GetProcessClientData(void *ap_object);
	int IsConnect(void *ap_object);
	void ConnectToServer(void *ap_object, const char *ap_ip_address, int a_port);
	void CloseSocket(void *ap_object);
	void SendFrameDataToServer(void *ap_object, char a_msg_id, const void *ap_data, int a_size);
	
	// [[ ���ڿ� ó�� ���� �Ϲ� ��ƿ��Ƽ ]]
	char* GetNextString(char* ap_src_str, char a_delimiter, char* ap_buffer);
	char* GetNextStringEx(char* ap_src_str, char a_delimiter, char* ap_buffer, char a_remove_prefix = ' ');
	char* ConvertTabToSpace(const char* ap_src_string);

	// [[ ���� ���� �м��� ���� ]]
	void* CreateExpParsor();
	const char* GetExpString(void* ap_parsor);
	void InitExpParser(void* ap_parsor);
	void SetExpString(void* ap_parsor, const char* ap_string);
	void RunExpParsing(void* ap_parsor);   // ����ڰ� ������ ������ �м��Ѵ�

	int GetExpVariableCount(void* ap_parsor);
	const char* GetExpVariableName(void* ap_parsor, int a_index);
	// ������ ������ ���� �����Ѵ�.
	void SetExpVarValue(void* ap_parsor, int a_index, double a_value);
	// ������ ������ ������ ���� �ִ� ��ġ�� �ּҷ� �˷��ش�
	void SetExpVariablePointer(void* ap_parsor, int a_index, double* ap_data);
	// �������� �ּҷ� �����ϵ��� �Ǿ� �ִ� ������ �ִٸ� �ش� �ּҿ��� ���� �о� �������� ������Ʈ �Ѵ�.
	void UpdateExpVariableValue(void* ap_parsor);
	// �̹� ������ parsing�Ǿ��ٸ� �ٽ� parsing�� �ʿ䰡 ���� ���Լ��� ȣ������, ExecExp �Լ��� ȣ���ϸ� �ȴ�
	char RestoreExpParserInfo(void* ap_parsor);
	char GetExpReadyFlag(void* ap_parsor);   // Parsing �� �Ǿ��ִ����� �˷��ش� ( 0 -> �Ľ̾ȵ�, 1 -> �Ľ̵� )
	double ExecExp(void* ap_parsor, unsigned int a_prev_depth = 0);  // Parsing�� ������ �����Ͽ� ������ ������� ��´�
	void DestroyExpParsor(void* ap_parsor);

	void* CreateExpParsorEx();
	const char* GetExpStringEx(void* ap_parsor);
	void InitExpParserEx(void* ap_parsor);
	void SetExpStringEx(void* ap_parsor, const char* ap_string);
	void RunExpParsingEx(void* ap_parsor);   // ����ڰ� ������ ������ �м��Ѵ�

	int GetExpVariableCountEx(void* ap_parsor);
	const char* GetExpVariableNameEx(void* ap_parsor, int a_index);
	// ������ ������ ������ ���� �ִ� ��ġ�� �ּҷ� �˷��ش�
	void SetExpVariablePointerEx(void* ap_parsor, int a_index, unsigned char a_data_type, double* ap_data);
	// �������� �ּҷ� �����ϵ��� �Ǿ� �ִ� ������ �ִٸ� �ش� �ּҿ��� ���� �о� �������� ������Ʈ �Ѵ�.
	void UpdateExpVariableValueEx(void* ap_parsor);
	// �̹� ������ parsing�Ǿ��ٸ� �ٽ� parsing�� �ʿ䰡 ���� ���Լ��� ȣ������, ExecExp �Լ��� ȣ���ϸ� �ȴ�
	char RestoreExpParserInfoEx(void* ap_parsor);
	char GetExpReadyFlagEx(void* ap_parsor);   // Parsing �� �Ǿ��ִ����� �˷��ش� ( 0 -> �Ľ̾ȵ�, 1 -> �Ľ̵� )
	void DestroyExpParsorEx(void* ap_parsor);

	// [ ��ũ�� ���� �Լ��� ]
	// �ý��� Ű�� �Է��ϴ� �Լ�. 
	void SystemKeyWrite(char a_key, int a_delay = 250);  // (Key Down & Up�� �� ���� ó��)
	void SystemKeyDown(char a_key);
	void SystemKeyUp(char a_key);
	// �Ϲ� Ű�� �Է��ϴ� �Լ�. Shift Ű�� ����ϴ� ��쿡�� a_is_shift�� 1�� �Է��ؾ� �Ѵ�. 
	void InputNormalChar(char a_is_shift, char a_key);  // (Key Down & Up�� �� ���� ó��)
	void InputNormalCharDown(char a_is_shift, char a_key);
	void InputNormalCharUp(char a_is_shift, char a_key);
	// ap_string�� ���޵� Ű����� �Է��Ѵ�.
	char InputNormalString(const char* ap_string, char a_is_han_mode, int a_delay = 100);
	void WaitInputSystem(int a_delay);

	void MouseMoveWrite(int a_x, int a_y);  // ���콺 �̵�!
	void MouseClickWrite(int a_x, int a_y, int a_is_left = 1, int a_delay = 0);
	void MouseClickDown(int a_x, int a_y, int a_is_left = 1);
	void MouseClickUp(int a_x, int a_y, int a_is_left = 1);

	void CheckOBjectPos(RECT* p_target_rect, int a_x, int a_y, unsigned int a_org_color, unsigned int a_change_color, unsigned int* ap_image_data, int a_image_width, int a_image_height);

	// Ŭ������ ���� �Լ�
	int CopyTextToClipboard(const char* ap_string);
	int CopyTextFromClipboard(char** ap_string, char a_is_clear);
	HBITMAP MakeDupBitmap(HBITMAP ah_bitmap);
	HBITMAP MakeDupBitmap(HBITMAP ah_bitmap, unsigned int* ap_image_data);
	HBITMAP CopyBitmapFromClipBoard();
	void CopyBitmapToClipBoard(HBITMAP ah_bitmap);

	// Common Dialog ���� �Լ�
	int ChooseOpenFileName(char* ap_open_path, int a_path_size, const char* ap_filter = "All\0*.*\0Text\0*.txt\0", int a_filter_index = 1, const char* ap_init_path = NULL, int a_add_attr = 0);
	int ChooseSaveFileName(char* ap_open_path, int a_path_size, const char* ap_filter = "All\0*.*\0Text\0*.txt\0", int a_filter_index = 1, const char* ap_init_path = NULL, int a_add_attr = 0);
	int ChooseColorDlg(COLORREF a_init_color, COLORREF* ap_selected_color);
	int ChooseFontDlg(char* ap_font_name, int* ap_font_size, int* ap_font_style, COLORREF a_init_color = RGB(0, 0, 0), COLORREF* ap_selected_color = NULL);
}

extern const char *gp_app_name;
extern const char *gp_window_title;
extern HWND gh_main_wnd;
#endif