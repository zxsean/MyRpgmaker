#include "GameInput.h"
#include <windows.h>

CGameInput::CGameInput()
{
	m_Key[_GI_M_L] = VK_LBUTTON; //йС╠ЙвС╪Э
	m_Key[_GI_M_M] = VK_MBUTTON; //йС╠Йжп╪Э
	m_Key[_GI_M_R] = VK_RBUTTON; //йС╠Йср╪Э
	m_Key[_GI_K_A] = 'A'; //╪Эелвжд╦╪ЭA
	m_Key[_GI_K_B] = 'B'; //╪Эелвжд╦╪ЭB
	m_Key[_GI_K_C] = 'C'; //╪Эелвжд╦╪ЭC
	m_Key[_GI_K_D] = 'D'; //╪Эелвжд╦╪ЭD
	m_Key[_GI_K_E] = 'E'; //╪Эелвжд╦╪ЭE
	m_Key[_GI_K_F] = 'F'; //╪Эелвжд╦╪ЭF
	m_Key[_GI_K_G] = 'G'; //╪Эелвжд╦╪ЭG
	m_Key[_GI_K_H] = 'H'; //╪Эелвжд╦╪ЭH
	m_Key[_GI_K_I] = 'I'; //╪Эелвжд╦╪ЭI
	m_Key[_GI_K_J] = 'J'; //╪Эелвжд╦╪ЭJ
	m_Key[_GI_K_K] = 'K'; //╪Эелвжд╦╪ЭK
	m_Key[_GI_K_L] = 'L'; //╪Эелвжд╦╪ЭL
	m_Key[_GI_K_M] = 'M'; //╪Эелвжд╦╪ЭM
	m_Key[_GI_K_N] = 'N'; //╪Эелвжд╦╪ЭN
	m_Key[_GI_K_O] = 'O'; //╪Эелвжд╦╪ЭO
	m_Key[_GI_K_P] = 'P'; //╪Эелвжд╦╪ЭP
	m_Key[_GI_K_Q] = 'Q'; //╪Эелвжд╦╪ЭQ
	m_Key[_GI_K_R] = 'R'; //╪Эелвжд╦╪ЭR
	m_Key[_GI_K_S] = 'S'; //╪Эелвжд╦╪ЭS
	m_Key[_GI_K_T] = 'T'; //╪Эелвжд╦╪ЭT
	m_Key[_GI_K_U] = 'U'; //╪Эелвжд╦╪ЭU
	m_Key[_GI_K_V] = 'V'; //╪Эелвжд╦╪ЭV
	m_Key[_GI_K_W] = 'W'; //╪Эелвжд╦╪ЭW
	m_Key[_GI_K_X] = 'X'; //╪Эелвжд╦╪ЭX
	m_Key[_GI_K_Y] = 'Y'; //╪Эелвжд╦╪ЭY
	m_Key[_GI_K_Z] = 'Z'; //╪Эелвжд╦╪ЭZ
	m_Key[_GI_K_0] = 0x30; //╪ЭелйЩвж╪Э0
	m_Key[_GI_K_1] = 0x31; //╪ЭелйЩвж╪Э1
	m_Key[_GI_K_2] = 0x32; //╪ЭелйЩвж╪Э2
	m_Key[_GI_K_3] = 0x33; //╪ЭелйЩвж╪Э3
	m_Key[_GI_K_4] = 0x34; //╪ЭелйЩвж╪Э4
	m_Key[_GI_K_5] = 0x35; //╪ЭелйЩвж╪Э5
	m_Key[_GI_K_6] = 0x36; //╪ЭелйЩвж╪Э6
	m_Key[_GI_K_7] = 0x37; //╪ЭелйЩвж╪Э7
	m_Key[_GI_K_8] = 0x38; //╪ЭелйЩвж╪Э8
	m_Key[_GI_K_9] = 0x39; //╪ЭелйЩвж╪Э9
	m_Key[_GI_K_F01] = VK_F1; //╪Эел╪ЭF1
	m_Key[_GI_K_F02] = VK_F2; //╪Эел╪ЭF2
	m_Key[_GI_K_F03] = VK_F3; //╪Эел╪ЭF3
	m_Key[_GI_K_F04] = VK_F4; //╪Эел╪ЭF4
	m_Key[_GI_K_F05] = VK_F5; //╪Эел╪ЭF5
	m_Key[_GI_K_F06] = VK_F6; //╪Эел╪ЭF6
	m_Key[_GI_K_F07] = VK_F7; //╪Эел╪ЭF7
	m_Key[_GI_K_F08] = VK_F8; //╪Эел╪ЭF8
	m_Key[_GI_K_F09] = VK_F9; //╪Эел╪ЭF9
	m_Key[_GI_K_F10] = VK_F10; //╪Эел╪ЭF10
	m_Key[_GI_K_F11] = VK_F11; //╪Эел╪ЭF11
	m_Key[_GI_K_F12] = VK_F12; //╪Эел╪ЭF12
	m_Key[_GI_K_ESC] = VK_ESCAPE; //╪Эел╪ЭEsc
	m_Key[_GI_K_OEM_3] = VK_OEM_3; //╪Эел╪Э~
	m_Key[_GI_K_OEM_MINUS] = VK_OEM_MINUS; //╪Эел╪Э_
	m_Key[_GI_K_OEM_PLUS] = VK_OEM_PLUS; //╪Эел╪Э+
	m_Key[_GI_K_OEM_5] = VK_OEM_5; //╪Эел╪Э|
	m_Key[_GI_K_BACK] = VK_BACK; //╪Эел╪ЭBack Space
	m_Key[_GI_K_TAB] = VK_TAB; //╪Эел╪ЭTab
	m_Key[_GI_K_OEM_4] = VK_OEM_4; //╪Эел╪Э{
	m_Key[_GI_K_OEM_6] = VK_OEM_6; //╪Эел╪Э}
	m_Key[_GI_K_RETURN] = VK_RETURN; //╪Эел╪ЭEnter
	m_Key[_GI_K_CAPITAL_LOCK] = VK_CAPITAL; //╪Эел╪ЭCaps Lock
	m_Key[_GI_K_OEM_1] = VK_OEM_1; //╪Эел╪Э:
	m_Key[_GI_K_OEM_7] = VK_OEM_7; //╪Эел╪Э"
	m_Key[_GI_K_L_SHIFT] = VK_LSHIFT; //╪Эел╪ЭвСShift
	m_Key[_GI_K_OEM_COMMA] = VK_OEM_COMMA; //╪Эел╪Э<
	m_Key[_GI_K_OEM_PERIOD] = VK_OEM_PERIOD; //╪Эел╪Э>
	m_Key[_GI_K_OEM_2] = VK_OEM_2; //╪Эел╪Э?
	m_Key[_GI_K_R_SHIFT] = VK_RSHIFT; //╪Эел╪ЭсрShift
	m_Key[_GI_K_L_CTRL] = VK_LCONTROL; //╪Эел╪ЭвСCtrl
	m_Key[_GI_K_L_ALT] = VK_LMENU; //╪Эел╪ЭвСAlt
	m_Key[_GI_K_SPACE] = VK_SPACE; //╪Эел╪ЭSpacebar
	m_Key[_GI_K_R_ALT] = VK_RMENU; //╪Эел╪ЭсрAlt
	m_Key[_GI_K_R_CTRL] = VK_RCONTROL; //╪Эел╪ЭсрCtrl
	m_Key[_GI_K_PRINT_SCREEN] = VK_SNAPSHOT; //╪Эел╪ЭPrint Screen
	m_Key[_GI_K_SCROLL_LOCK] = VK_SCROLL; //╪Эел╪ЭScroll Lock
	m_Key[_GI_K_INSERT] = VK_INSERT; //╪Эел╪ЭInsert
	m_Key[_GI_K_HOME] = VK_HOME; //╪Эел╪ЭHome
	m_Key[_GI_K_PAGE_UP] = VK_PRIOR; //╪Эел╪ЭPage Up
	m_Key[_GI_K_DELETE] = VK_DELETE; //╪Эел╪ЭDelete
	m_Key[_GI_K_END] = VK_END; //╪Эел╪ЭEnd
	m_Key[_GI_K_PAGE_DOWN] = VK_NEXT; //╪Эел╪ЭPage Down
	m_Key[_GI_K_UP] = VK_UP; //╪Эел╪Э║Э
	m_Key[_GI_K_DOWN] = VK_DOWN; //╪Эел╪Э║Щ
	m_Key[_GI_K_LEFT] = VK_LEFT; //╪Эел╪Э║Ш
	m_Key[_GI_K_RIGHT] = VK_RIGHT; //╪Эел╪Э║З
	m_Key[_GI_NK_NUM_LOCK] = VK_NUMLOCK; //п║╪Эел╪ЭNum Lock
	m_Key[_GI_NK_DIVIDE] = VK_DIVIDE; //п║╪Эел╪ЭЁЩ
	m_Key[_GI_NK_MULTIPLY] = VK_MULTIPLY; //п║╪Эел╪ЭЁк
	m_Key[_GI_NK_ADD] = VK_ADD; //п║╪Эел╪Э╪с
	m_Key[_GI_NK_SEPARATOR] = VK_SEPARATOR; //п║╪Эел╪Э╪У
	m_Key[_GI_NK_DECIMAL] = VK_DECIMAL; //п║╪Эел╪Эп║йЩ╣Ц
	m_Key[_GI_NK_0] = VK_NUMPAD0; //п║╪Эел╪ЭйЩвж╪Э0
	m_Key[_GI_NK_1] = VK_NUMPAD1; //п║╪Эел╪ЭйЩвж╪Э1
	m_Key[_GI_NK_2] = VK_NUMPAD2; //п║╪Эел╪ЭйЩвж╪Э2
	m_Key[_GI_NK_3] = VK_NUMPAD3; //п║╪Эел╪ЭйЩвж╪Э3
	m_Key[_GI_NK_4] = VK_NUMPAD4; //п║╪Эел╪ЭйЩвж╪Э4
	m_Key[_GI_NK_5] = VK_NUMPAD5; //п║╪Эел╪ЭйЩвж╪Э5
	m_Key[_GI_NK_6] = VK_NUMPAD6; //п║╪Эел╪ЭйЩвж╪Э6
	m_Key[_GI_NK_7] = VK_NUMPAD7; //п║╪Эел╪ЭйЩвж╪Э7
	m_Key[_GI_NK_8] = VK_NUMPAD8; //п║╪Эел╪ЭйЩвж╪Э8
	m_Key[_GI_NK_9] = VK_NUMPAD9; //п║╪Эел╪ЭйЩвж╪Э9

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