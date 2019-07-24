#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_

#define _GI_M_L 0x00 //������
#define _GI_M_M 0x01 //����м�
#define _GI_M_R 0x02 //����Ҽ�
#define _GI_K_A 0x03 //������ĸ��A
#define _GI_K_B 0x04 //������ĸ��B
#define _GI_K_C 0x05 //������ĸ��C
#define _GI_K_D 0x06 //������ĸ��D
#define _GI_K_E 0x07 //������ĸ��E
#define _GI_K_F 0x08 //������ĸ��F
#define _GI_K_G 0x09 //������ĸ��G
#define _GI_K_H 0x0A //������ĸ��H
#define _GI_K_I 0x0B //������ĸ��I
#define _GI_K_J 0x0C //������ĸ��J
#define _GI_K_K 0x0D //������ĸ��K
#define _GI_K_L 0x0E //������ĸ��L
#define _GI_K_M 0x0F //������ĸ��M
#define _GI_K_N 0x10 //������ĸ��N
#define _GI_K_O 0x11 //������ĸ��O
#define _GI_K_P 0x12 //������ĸ��P
#define _GI_K_Q 0x13 //������ĸ��Q
#define _GI_K_R 0x14 //������ĸ��R
#define _GI_K_S 0x15 //������ĸ��S
#define _GI_K_T 0x16 //������ĸ��T
#define _GI_K_U 0x17 //������ĸ��U
#define _GI_K_V 0x18 //������ĸ��V
#define _GI_K_W 0x19 //������ĸ��W
#define _GI_K_X 0x1A //������ĸ��X
#define _GI_K_Y 0x1B //������ĸ��Y
#define _GI_K_Z 0x1C //������ĸ��Z
#define _GI_K_0 0x1D //�������ּ�0
#define _GI_K_1 0x1E //�������ּ�1
#define _GI_K_2 0x1F //�������ּ�2
#define _GI_K_3 0x20 //�������ּ�3
#define _GI_K_4 0x21 //�������ּ�4
#define _GI_K_5 0x22 //�������ּ�5
#define _GI_K_6 0x23 //�������ּ�6
#define _GI_K_7 0x24 //�������ּ�7
#define _GI_K_8 0x25 //�������ּ�8
#define _GI_K_9 0x26 //�������ּ�9
#define _GI_K_F01 0x27 //���̼�F1
#define _GI_K_F02 0x28 //���̼�F2
#define _GI_K_F03 0x29 //���̼�F3
#define _GI_K_F04 0x2A //���̼�F4
#define _GI_K_F05 0x2B //���̼�F5
#define _GI_K_F06 0x2C //���̼�F6
#define _GI_K_F07 0x2D //���̼�F7
#define _GI_K_F08 0x2E //���̼�F8
#define _GI_K_F09 0x2F //���̼�F9
#define _GI_K_F10 0x30 //���̼�F10
#define _GI_K_F11 0x31 //���̼�F11
#define _GI_K_F12 0x32 //���̼�F12
#define _GI_K_ESC 0x33 //���̼�Esc
#define _GI_K_OEM_3 0x34 //���̼�~
#define _GI_K_OEM_MINUS 0x35 //���̼�_
#define _GI_K_OEM_PLUS 0x36 //���̼�+
#define _GI_K_OEM_5 0x37 //���̼�|
#define _GI_K_BACK 0x38 //���̼�Back Space
#define _GI_K_TAB 0x39 //���̼�Tab
#define _GI_K_OEM_4 0x3A //���̼�{
#define _GI_K_OEM_6 0x3B //���̼�}
#define _GI_K_RETURN 0x3C //���̼�Enter
#define _GI_K_CAPITAL_LOCK 0x3D //���̼�Caps Lock
#define _GI_K_OEM_1 0x3E //���̼�:
#define _GI_K_OEM_7 0x3F //���̼�"
#define _GI_K_L_SHIFT 0x40 //���̼���Shift
#define _GI_K_OEM_COMMA 0x41 //���̼�<
#define _GI_K_OEM_PERIOD 0x42 //���̼�>
#define _GI_K_OEM_2 0x43 //���̼�?
#define _GI_K_R_SHIFT 0x44 //���̼���Shift
#define _GI_K_L_CTRL 0x45 //���̼���Ctrl
#define _GI_K_L_ALT 0x46 //���̼���Alt
#define _GI_K_SPACE 0x47 //���̼�Spacebar
#define _GI_K_R_ALT 0x48 //���̼���Alt
#define _GI_K_R_CTRL 0x49 //���̼���Ctrl
#define _GI_K_PRINT_SCREEN 0x4A //���̼�Print Screen
#define _GI_K_SCROLL_LOCK 0x4B //���̼�Scroll Lock
#define _GI_K_INSERT 0x4C //���̼�Insert
#define _GI_K_HOME 0x4D //���̼�Home
#define _GI_K_PAGE_UP 0x4E //���̼�Page Up
#define _GI_K_DELETE 0x4F //���̼�Delete
#define _GI_K_END 0x50 //���̼�End
#define _GI_K_PAGE_DOWN 0x51 //���̼�Page Down
#define _GI_K_UP 0x52 //���̼���
#define _GI_K_DOWN 0x53 //���̼���
#define _GI_K_LEFT 0x54 //���̼���
#define _GI_K_RIGHT 0x55 //���̼���
#define _GI_NK_NUM_LOCK 0x56 //С���̼�Num Lock
#define _GI_NK_DIVIDE 0x57 //С���̼���
#define _GI_NK_MULTIPLY 0x58 //С���̼���
#define _GI_NK_ADD 0x59 //С���̼���
#define _GI_NK_SEPARATOR 0x5A //С���̼���
#define _GI_NK_RETURN _GI_K_RETURN //С���̼�Enter
#define _GI_NK_DECIMAL 0x5B //С���̼�С����
#define _GI_NK_0 0x5C //С���̼����ּ�0
#define _GI_NK_1 0x5D //С���̼����ּ�1
#define _GI_NK_2 0x5E //С���̼����ּ�2
#define _GI_NK_3 0x5F //С���̼����ּ�3
#define _GI_NK_4 0x60 //С���̼����ּ�4
#define _GI_NK_5 0x61 //С���̼����ּ�5
#define _GI_NK_6 0x62 //С���̼����ּ�6
#define _GI_NK_7 0x63 //С���̼����ּ�7
#define _GI_NK_8 0x64 //С���̼����ּ�8
#define _GI_NK_9 0x65 //С���̼����ּ�9

#define _GI_KEY_NUM (_GI_NK_9 + 1) //���̼�������

#define _KS_IK 0 //��״̬:��Ч
#define _KS_UH 1 //��״̬:�����ſ�
#define _KS_UC 2 //��״̬:��ǰ�ſ�
#define _KS_DH 3 //��״̬:��������
#define _KS_DC 4 //��״̬:��ǰ����

class CGameInput
{
private:
	unsigned char m_Key[_GI_KEY_NUM];
	int m_KeyState[_GI_KEY_NUM];

public:
	CGameInput();
	virtual ~CGameInput();

	virtual void Run();
	virtual int Get(unsigned char Key);
};

#endif