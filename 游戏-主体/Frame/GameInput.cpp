#include "GameInput.h"
#include <windows.h>

CGameInput::CGameInput()
{
	m_Key[_GI_M_L] = VK_LBUTTON; //������
	m_Key[_GI_M_M] = VK_MBUTTON; //����м�
	m_Key[_GI_M_R] = VK_RBUTTON; //����Ҽ�
	m_Key[_GI_K_A] = 'A'; //������ĸ��A
	m_Key[_GI_K_B] = 'B'; //������ĸ��B
	m_Key[_GI_K_C] = 'C'; //������ĸ��C
	m_Key[_GI_K_D] = 'D'; //������ĸ��D
	m_Key[_GI_K_E] = 'E'; //������ĸ��E
	m_Key[_GI_K_F] = 'F'; //������ĸ��F
	m_Key[_GI_K_G] = 'G'; //������ĸ��G
	m_Key[_GI_K_H] = 'H'; //������ĸ��H
	m_Key[_GI_K_I] = 'I'; //������ĸ��I
	m_Key[_GI_K_J] = 'J'; //������ĸ��J
	m_Key[_GI_K_K] = 'K'; //������ĸ��K
	m_Key[_GI_K_L] = 'L'; //������ĸ��L
	m_Key[_GI_K_M] = 'M'; //������ĸ��M
	m_Key[_GI_K_N] = 'N'; //������ĸ��N
	m_Key[_GI_K_O] = 'O'; //������ĸ��O
	m_Key[_GI_K_P] = 'P'; //������ĸ��P
	m_Key[_GI_K_Q] = 'Q'; //������ĸ��Q
	m_Key[_GI_K_R] = 'R'; //������ĸ��R
	m_Key[_GI_K_S] = 'S'; //������ĸ��S
	m_Key[_GI_K_T] = 'T'; //������ĸ��T
	m_Key[_GI_K_U] = 'U'; //������ĸ��U
	m_Key[_GI_K_V] = 'V'; //������ĸ��V
	m_Key[_GI_K_W] = 'W'; //������ĸ��W
	m_Key[_GI_K_X] = 'X'; //������ĸ��X
	m_Key[_GI_K_Y] = 'Y'; //������ĸ��Y
	m_Key[_GI_K_Z] = 'Z'; //������ĸ��Z
	m_Key[_GI_K_0] = 0x30; //�������ּ�0
	m_Key[_GI_K_1] = 0x31; //�������ּ�1
	m_Key[_GI_K_2] = 0x32; //�������ּ�2
	m_Key[_GI_K_3] = 0x33; //�������ּ�3
	m_Key[_GI_K_4] = 0x34; //�������ּ�4
	m_Key[_GI_K_5] = 0x35; //�������ּ�5
	m_Key[_GI_K_6] = 0x36; //�������ּ�6
	m_Key[_GI_K_7] = 0x37; //�������ּ�7
	m_Key[_GI_K_8] = 0x38; //�������ּ�8
	m_Key[_GI_K_9] = 0x39; //�������ּ�9
	m_Key[_GI_K_F01] = VK_F1; //���̼�F1
	m_Key[_GI_K_F02] = VK_F2; //���̼�F2
	m_Key[_GI_K_F03] = VK_F3; //���̼�F3
	m_Key[_GI_K_F04] = VK_F4; //���̼�F4
	m_Key[_GI_K_F05] = VK_F5; //���̼�F5
	m_Key[_GI_K_F06] = VK_F6; //���̼�F6
	m_Key[_GI_K_F07] = VK_F7; //���̼�F7
	m_Key[_GI_K_F08] = VK_F8; //���̼�F8
	m_Key[_GI_K_F09] = VK_F9; //���̼�F9
	m_Key[_GI_K_F10] = VK_F10; //���̼�F10
	m_Key[_GI_K_F11] = VK_F11; //���̼�F11
	m_Key[_GI_K_F12] = VK_F12; //���̼�F12
	m_Key[_GI_K_ESC] = VK_ESCAPE; //���̼�Esc
	m_Key[_GI_K_OEM_3] = VK_OEM_3; //���̼�~
	m_Key[_GI_K_OEM_MINUS] = VK_OEM_MINUS; //���̼�_
	m_Key[_GI_K_OEM_PLUS] = VK_OEM_PLUS; //���̼�+
	m_Key[_GI_K_OEM_5] = VK_OEM_5; //���̼�|
	m_Key[_GI_K_BACK] = VK_BACK; //���̼�Back Space
	m_Key[_GI_K_TAB] = VK_TAB; //���̼�Tab
	m_Key[_GI_K_OEM_4] = VK_OEM_4; //���̼�{
	m_Key[_GI_K_OEM_6] = VK_OEM_6; //���̼�}
	m_Key[_GI_K_RETURN] = VK_RETURN; //���̼�Enter
	m_Key[_GI_K_CAPITAL_LOCK] = VK_CAPITAL; //���̼�Caps Lock
	m_Key[_GI_K_OEM_1] = VK_OEM_1; //���̼�:
	m_Key[_GI_K_OEM_7] = VK_OEM_7; //���̼�"
	m_Key[_GI_K_L_SHIFT] = VK_LSHIFT; //���̼���Shift
	m_Key[_GI_K_OEM_COMMA] = VK_OEM_COMMA; //���̼�<
	m_Key[_GI_K_OEM_PERIOD] = VK_OEM_PERIOD; //���̼�>
	m_Key[_GI_K_OEM_2] = VK_OEM_2; //���̼�?
	m_Key[_GI_K_R_SHIFT] = VK_RSHIFT; //���̼���Shift
	m_Key[_GI_K_L_CTRL] = VK_LCONTROL; //���̼���Ctrl
	m_Key[_GI_K_L_ALT] = VK_LMENU; //���̼���Alt
	m_Key[_GI_K_SPACE] = VK_SPACE; //���̼�Spacebar
	m_Key[_GI_K_R_ALT] = VK_RMENU; //���̼���Alt
	m_Key[_GI_K_R_CTRL] = VK_RCONTROL; //���̼���Ctrl
	m_Key[_GI_K_PRINT_SCREEN] = VK_SNAPSHOT; //���̼�Print Screen
	m_Key[_GI_K_SCROLL_LOCK] = VK_SCROLL; //���̼�Scroll Lock
	m_Key[_GI_K_INSERT] = VK_INSERT; //���̼�Insert
	m_Key[_GI_K_HOME] = VK_HOME; //���̼�Home
	m_Key[_GI_K_PAGE_UP] = VK_PRIOR; //���̼�Page Up
	m_Key[_GI_K_DELETE] = VK_DELETE; //���̼�Delete
	m_Key[_GI_K_END] = VK_END; //���̼�End
	m_Key[_GI_K_PAGE_DOWN] = VK_NEXT; //���̼�Page Down
	m_Key[_GI_K_UP] = VK_UP; //���̼���
	m_Key[_GI_K_DOWN] = VK_DOWN; //���̼���
	m_Key[_GI_K_LEFT] = VK_LEFT; //���̼���
	m_Key[_GI_K_RIGHT] = VK_RIGHT; //���̼���
	m_Key[_GI_NK_NUM_LOCK] = VK_NUMLOCK; //С���̼�Num Lock
	m_Key[_GI_NK_DIVIDE] = VK_DIVIDE; //С���̼���
	m_Key[_GI_NK_MULTIPLY] = VK_MULTIPLY; //С���̼���
	m_Key[_GI_NK_ADD] = VK_ADD; //С���̼���
	m_Key[_GI_NK_SEPARATOR] = VK_SEPARATOR; //С���̼���
	m_Key[_GI_NK_DECIMAL] = VK_DECIMAL; //С���̼�С����
	m_Key[_GI_NK_0] = VK_NUMPAD0; //С���̼����ּ�0
	m_Key[_GI_NK_1] = VK_NUMPAD1; //С���̼����ּ�1
	m_Key[_GI_NK_2] = VK_NUMPAD2; //С���̼����ּ�2
	m_Key[_GI_NK_3] = VK_NUMPAD3; //С���̼����ּ�3
	m_Key[_GI_NK_4] = VK_NUMPAD4; //С���̼����ּ�4
	m_Key[_GI_NK_5] = VK_NUMPAD5; //С���̼����ּ�5
	m_Key[_GI_NK_6] = VK_NUMPAD6; //С���̼����ּ�6
	m_Key[_GI_NK_7] = VK_NUMPAD7; //С���̼����ּ�7
	m_Key[_GI_NK_8] = VK_NUMPAD8; //С���̼����ּ�8
	m_Key[_GI_NK_9] = VK_NUMPAD9; //С���̼����ּ�9

	for (unsigned int i = 0; i < _GI_KEY_NUM; ++i)
		m_KeyState[i] = _KS_UH;
}

CGameInput::~CGameInput()
{}

void CGameInput::Run()
{
	for (unsigned int i = 0; i < _GI_KEY_NUM; ++i)
		m_KeyState[i] = (GetAsyncKeyState(m_Key[i]) & 0x8000) ? ((m_KeyState[i] < _KS_DH) ? _KS_DC : _KS_DH) : ((m_KeyState[i] > _KS_UC) ? _KS_UC : _KS_UH);
}

int CGameInput::Get(unsigned char Key)
{
	return (Key >= _GI_KEY_NUM) ? _KS_IK : m_KeyState[Key];
}