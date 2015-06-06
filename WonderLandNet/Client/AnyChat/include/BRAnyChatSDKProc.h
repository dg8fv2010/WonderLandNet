// BRAnyChatSDKProc.h : header file
//
#ifndef _BR_ANY_CHAT_SDK_PROC_H__
#define _BR_ANY_CHAT_SDK_PROC_H__

#ifdef __AFX_H__
	#define	BR_AFX_MANAGE_STATE	AFX_MANAGE_STATE(AfxGetStaticModuleState())
#else
	#define	BR_AFX_MANAGE_STATE
#endif //__AFX_H__

#include "BRAnyChatCoreSDK.h"


class CBRAnyChatSDKProc
{
public:
	CBRAnyChatSDKProc()
	{
		RegAnyChatSDKCallback();
	}
	virtual ~CBRAnyChatSDKProc()
	{
		UnRegAnyChatSDKCallback();
	}

private:
	// ע��SDK�ص�����
	void RegAnyChatSDKCallback(void)
	{
		BRAC_SetVideoDataCallBack(BRAC_PIX_FMT_RGB24,VideoData_CallBack,this);
		BRAC_SetAudioDataCallBack(AudioData_CallBack,this);
		BRAC_SetVolumeChangeCallBack(VolumeChange_CallBack,this);
		BRAC_SetTextMessageCallBack(TextMessage_CallBack,this);
		BRAC_SetTransBufferExCallBack(TransBufferEx_CallBack,this);
		BRAC_SetTransBufferCallBack(TransBuffer_CallBack,this);
		BRAC_SetTransFileCallBack(TransFile_CallBack,this);
		BRAC_SetRecordSnapShotCallBack(RecordSnapShot_CallBack,this);
		BRAC_SetSDKFilterDataCallBack(SDKFilterData_CallBack,this);
		BRAC_SetNotifyMessageCallBack(NotifyMessage_CallBack,this);
	}
	// ע��SDK�ص�����
	void UnRegAnyChatSDKCallback(void)
	{
		BRAC_SetVideoDataCallBack(BRAC_PIX_FMT_RGB24,NULL,NULL);
		BRAC_SetAudioDataCallBack(NULL,NULL);
		BRAC_SetVolumeChangeCallBack(NULL,NULL);
		BRAC_SetTextMessageCallBack(NULL,NULL);
		BRAC_SetTransBufferExCallBack(NULL,NULL);
		BRAC_SetTransBufferCallBack(NULL,NULL);
		BRAC_SetTransFileCallBack(NULL,NULL);
		BRAC_SetRecordSnapShotCallBack(NULL,NULL);
		BRAC_SetSDKFilterDataCallBack(NULL,NULL);
		BRAC_SetNotifyMessageCallBack(NULL,NULL);
	}

protected:
	// ���ӷ�������Ϣ
	virtual void OnAnyChatConnectMessage(BOOL bSuccess) {}
	// �û���½��Ϣ
	virtual void OnAnyChatLoginMessage(DWORD dwUserId, DWORD dwErrorCode) {}
	// �û����뷿����Ϣ
	virtual void OnAnyChatEnterRoomMessage(DWORD dwRoomId, DWORD dwErrorCode) {}
	// ���������û���Ϣ
	virtual void OnAnyChatOnlineUserMessage(DWORD dwUserNum, DWORD dwRoomId) {}
	// �û��õ�/�ͷ�mic��Ϣ
	virtual void OnAnyChatMicStateChgMessage(DWORD dwUserId, BOOL bGetMic) {}
	// �û�����/�˳�������Ϣ
	virtual void OnAnyChatUserAtRoomMessage(DWORD dwUserId, BOOL bEnter) {}
	//����Ͽ���Ϣ
	virtual void OnAnyChatLinkCloseMessage(DWORD dwErrorCode) {}

	// �û�����ͷ״̬�ı���Ϣ
	virtual void OnAnyChatCameraStateChgMessage(DWORD dwUserId, DWORD dwState) {}
	// �û�����ģʽ�ı���Ϣ
	virtual void OnAnyChatChatModeChgMessage(DWORD dwUserId, BOOL bPublicChat) {}
	// �û��״̬�����仯��Ϣ
	virtual void OnAnyChatActiveStateChgMessage(DWORD dwUserId, DWORD dwState) {}
	// P2P����״̬�仯��Ϣ
	virtual void OnAnyChatP2PConnectStateMessage(DWORD dwUserId, DWORD dwState){}
	// �û���Ƶ�ֱ��ʸı���Ϣ
	virtual void OnAnyChatVideoSizeChgMessage(DWORD dwUserId, DWORD dwWidth, DWORD dwHeight) {}

	// �û�˽��������Ϣ
	virtual void OnAnyChatPrivateRequestMessage(DWORD dwUserId, DWORD dwRequestId) {}
	// �û�˽������ظ���Ϣ
	virtual void OnAnyChatPrivateEchoMessage(DWORD dwUserId, DWORD dwErrorCode) {}
	// �û��˳�˽����Ϣ
	virtual void OnAnyChatPrivateExitMessage(DWORD dwUserId, DWORD dwErrorCode) {}

	// SDK������Ϣ
	virtual void OnAnyChatSDKWarningMessage(DWORD dwErrorCode, DWORD dwReserved) {}

	// ��Ƶ���ݻص�
	virtual void OnAnyChatVideoDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPBITMAPINFOHEADER lpbmiHeader) {}
	// ��Ƶ���ݻص�
	virtual void OnAnyChatAudioDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPWAVEFORMATEX lpWaveFormatEx) {}
	// �������ֵĻص�����
	virtual void OnAnyChatTextMsgCallBack(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen) {}
	// ͸��ͨ���ص�����
	virtual void OnAnyChatTransBufferCallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen) {}
	// ͸��ͨ��������չ�ص�����
	virtual void OnAnyChatTransBufferExCallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId) {}
	// �ļ�����ص�����
	virtual void OnAnyChatTransFileCallBack(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId) {}
	// �����仯�ص�����
	virtual void OnAnyChatVolumeChangeCallBack(BRAC_AudioDevice device, DWORD dwCurrentVolume) {}
	// SDK Filter ͨ�����ݻص�����
	virtual void OnAnyChatSDKFilterDataCallBack(LPBYTE lpBuf, DWORD dwLen) {}
	// ¼�񡢿���������ɻص�����
	virtual void OnAnyChatRecordSnapShotCallBack(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType) {}
	// �첽��Ϣ֪ͨ�ص�����
	virtual void OnAnyChatNotifyMessageCallBack(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam) {}


	// ��Ƶ���ݻص���������
	static void CALLBACK VideoData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue)
	{
		BR_AFX_MANAGE_STATE;
		CBRAnyChatSDKProc*	pAnyChatSDKProc = (CBRAnyChatSDKProc*)lpUserValue;
		if(pAnyChatSDKProc)
			pAnyChatSDKProc->OnAnyChatVideoDataCallBack(dwUserid,lpBuf,dwLen,&bmiHeader);
	}
	// ��Ƶ���ݻص���������
	static void CALLBACK AudioData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue)
	{
		BR_AFX_MANAGE_STATE;
		CBRAnyChatSDKProc*	pAnyChatSDKProc = (CBRAnyChatSDKProc*)lpUserValue;
		if(pAnyChatSDKProc)
			pAnyChatSDKProc->OnAnyChatAudioDataCallBack(dwUserid,lpBuf,dwLen,&waveFormatEx);
	}
	// ������Ϣ�ص���������
	static void CALLBACK TextMessage_CallBack(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue)
	{
		BR_AFX_MANAGE_STATE;
		CBRAnyChatSDKProc*	pAnyChatSDKProc = (CBRAnyChatSDKProc*)lpUserValue;
		if(pAnyChatSDKProc)
			pAnyChatSDKProc->OnAnyChatTextMsgCallBack(dwFromUserid,dwToUserid,bSecret,lpMsgBuf,dwLen);
	}
	// ͸��ͨ�����ݻص���������
	static void CALLBACK TransBuffer_CallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue)
	{
		BR_AFX_MANAGE_STATE;
		CBRAnyChatSDKProc*	pAnyChatSDKProc = (CBRAnyChatSDKProc*)lpUserValue;
		if(pAnyChatSDKProc)
			pAnyChatSDKProc->OnAnyChatTransBufferCallBack(dwUserid,lpBuf,dwLen);
	}
	// ͸��ͨ��������չ�ص���������
	static void CALLBACK TransBufferEx_CallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
	{
		BR_AFX_MANAGE_STATE;
		CBRAnyChatSDKProc*	pAnyChatSDKProc = (CBRAnyChatSDKProc*)lpUserValue;
		if(pAnyChatSDKProc)
			pAnyChatSDKProc->OnAnyChatTransBufferExCallBack(dwUserid,lpBuf,dwLen,wParam,lParam,dwTaskId);
	}
	// �ļ�����ص���������
	static void CALLBACK TransFile_CallBack(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
	{
		BR_AFX_MANAGE_STATE;
		CBRAnyChatSDKProc*	pAnyChatSDKProc = (CBRAnyChatSDKProc*)lpUserValue;
		if(pAnyChatSDKProc)
			pAnyChatSDKProc->OnAnyChatTransFileCallBack(dwUserid,lpFileName,lpTempFilePath,dwFileLength,wParam,lParam,dwTaskId);
	}
	// �����仯�ص���������
	static void CALLBACK VolumeChange_CallBack(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue)
	{
		BR_AFX_MANAGE_STATE;
		CBRAnyChatSDKProc*	pAnyChatSDKProc = (CBRAnyChatSDKProc*)lpUserValue;
		if(pAnyChatSDKProc)
			pAnyChatSDKProc->OnAnyChatVolumeChangeCallBack(device,dwCurrentVolume);
	}
	// SDK Filter ͨ�����ݻص���������
	static void CALLBACK SDKFilterData_CallBack(LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue)
	{
		BR_AFX_MANAGE_STATE;
		CBRAnyChatSDKProc*	pAnyChatSDKProc = (CBRAnyChatSDKProc*)lpUserValue;
		if(pAnyChatSDKProc)
			pAnyChatSDKProc->OnAnyChatSDKFilterDataCallBack(lpBuf,dwLen);
	}
	// ¼�񡢿���������ɻص���������
	static void CALLBACK RecordSnapShot_CallBack(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType, LPVOID lpUserValue)
	{
		BR_AFX_MANAGE_STATE;
		CBRAnyChatSDKProc*	pAnyChatSDKProc = (CBRAnyChatSDKProc*)lpUserValue;
		if(pAnyChatSDKProc)
			pAnyChatSDKProc->OnAnyChatRecordSnapShotCallBack(dwUserid,lpFileName,dwParam,bRecordType);
	}
	// �첽��Ϣ֪ͨ�ص���������
	static void CALLBACK NotifyMessage_CallBack(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue)
	{
		BR_AFX_MANAGE_STATE;
		CBRAnyChatSDKProc*	pAnyChatSDKProc = (CBRAnyChatSDKProc*)lpUserValue;
		if(!pAnyChatSDKProc)
			return;
		switch(dwNotifyMsg)
		{
		case WM_GV_CONNECT:			pAnyChatSDKProc->OnAnyChatConnectMessage(wParam);				break;
		case WM_GV_LOGINSYSTEM:		pAnyChatSDKProc->OnAnyChatLoginMessage(wParam,lParam);			break;
		case WM_GV_ENTERROOM:		pAnyChatSDKProc->OnAnyChatEnterRoomMessage(wParam,lParam);		break;
		case WM_GV_MICSTATECHANGE:	pAnyChatSDKProc->OnAnyChatMicStateChgMessage(wParam,lParam);	break;
		case WM_GV_USERATROOM:		pAnyChatSDKProc->OnAnyChatUserAtRoomMessage(wParam,lParam);		break;
		case WM_GV_LINKCLOSE:		pAnyChatSDKProc->OnAnyChatLinkCloseMessage(wParam);				break;
		case WM_GV_ONLINEUSER:		pAnyChatSDKProc->OnAnyChatOnlineUserMessage(wParam,lParam);		break;
			
		case WM_GV_CAMERASTATE:		pAnyChatSDKProc->OnAnyChatCameraStateChgMessage(wParam,lParam);	break;
		case WM_GV_CHATMODECHG:		pAnyChatSDKProc->OnAnyChatChatModeChgMessage(wParam,lParam);	break;
		case WM_GV_ACTIVESTATE:		pAnyChatSDKProc->OnAnyChatActiveStateChgMessage(wParam,lParam);	break;
		case WM_GV_P2PCONNECTSTATE:	pAnyChatSDKProc->OnAnyChatP2PConnectStateMessage(wParam,lParam);break;
		case WM_GV_VIDEOSIZECHG:	pAnyChatSDKProc->OnAnyChatVideoSizeChgMessage(wParam, LOWORD(lParam), HIWORD(lParam));	break;
			
		case WM_GV_PRIVATEREQUEST:	pAnyChatSDKProc->OnAnyChatPrivateRequestMessage(wParam,lParam);	break;
		case WM_GV_PRIVATEECHO:		pAnyChatSDKProc->OnAnyChatPrivateEchoMessage(wParam,lParam);	break;
		case WM_GV_PRIVATEEXIT:		pAnyChatSDKProc->OnAnyChatPrivateExitMessage(wParam,lParam);	break;

		case WM_GV_SDKWARNING:		pAnyChatSDKProc->OnAnyChatSDKWarningMessage(wParam,lParam);		break;
		default:
			break;
		}
		pAnyChatSDKProc->OnAnyChatNotifyMessageCallBack(dwNotifyMsg,wParam,lParam);
	}
};

#endif // #ifndef _BR_ANY_CHAT_SDK_PROC_H__