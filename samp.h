#include "main.h"

enum SampVersion
{
	SAMP_UNKNOWN,
	SAMP_037_R1,
	SAMP_037_R2,
	SAMP_037_R3,
	SAMP_037_R4,
	SAMP_037_R4_2,
	SAMP_037_R5,
	SAMP_03_DL,
};

enum DialogType
{
	DIALOG_MESSAGEBOX,
	DIALOG_INPUT,
	DIALOG_LIST,
	DIALOG_PASSWORD,
	DIALOG_TABLIST,
	DIALOG_HEADERSLIST
};

enum CursorMode
{
	CURSOR_NONE,
	CURSOR_LOCKKEYS_NOCURSOR,
	CURSOR_LOCKCAMANDCONTROL,
	CURSOR_LOCKCAM,
	CURSOR_LOCKCAM_NOCURSOR
};

#pragma pack(push, 1)

// DXUT
struct stDXUTEditBox
{
	uint8_t	pad_0[6];
	bool	m_bHasFocus;
};

struct stDXUTDialog
{
	uint8_t pad_0[278];
	int		m_pos[2];
	int		m_size[2];
	int		m_nCaptionHeight;
};

struct stDXUTListBox
{
	uint8_t	pad_0[323];
	int		m_nSelected;
	int		m_nSelStart;
};

// SAMP
class CInput
{
public:
	typedef void(__cdecl *CMDPROC)(PCHAR);

	IDirect3DDevice9*	m_pDevice;
	stDXUTDialog*		m_pGameUi;
	stDXUTEditBox*		m_pEditbox;
	CMDPROC				m_pCommandProc[144];
	char				m_szCommandName[144][32 + 1];
	int					m_nCommandCount;
	BOOL				m_bEnabled;
	char				m_szInput[128 + 1];
	char				m_szRecallBufffer[10][128 + 1];
	char				m_szCurrentBuffer[129];
	int					m_nCurrentRecall;
	int					m_nTotalRecall;
	CMDPROC				m_pDefaultCommand;
};

class CDialog
{
public:
	IDirect3DDevice9*	m_pDevice;
	POINT				m_position;
	POINT				m_size;
	unsigned long		m_buttonOffset[2];
	stDXUTDialog*		m_pDialog;
	stDXUTListBox*		m_pListbox;
	stDXUTEditBox*		m_pEditbox;
	BOOL				m_bIsActive;
	DialogType			m_nType;
	int					m_nId;
	char*				m_szText;
	int					m_textSize[2];
	char				m_szCaption[65];
	BOOL				m_bServerside;
};

#pragma pack(pop)

class CSAMP
{
private:
	DWORD		dwSAMPAddr = 0;
	DWORD		dwSAMPVersion = 0;

	CInput*		m_pInput = nullptr;
	CDialog*	m_pDialog = nullptr;
public:
	bool		init();
	bool		isAnyInputEnabled();

	CInput*		getInput() { return m_pInput; };
	CDialog*	getDialog() { return m_pDialog; };

	DWORD		getAddress() { return dwSAMPAddr; };
	DWORD		getVersion() { return dwSAMPVersion; };
};
