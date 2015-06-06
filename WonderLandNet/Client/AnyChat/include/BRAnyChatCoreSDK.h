#if !defined(BR_ANYCHAT_CORE_SDK_H__INCLUDED_)
#define BR_ANYCHAT_CORE_SDK_H__INCLUDED_

#include <mmsystem.h>
#include <wingdi.h>


/**
 *	AnyChat Core SDK Include File
 */


#pragma once

#include "GVSDK.h"

#define BRAC_API extern "C" __declspec(dllexport)

// ��Ƶͼ���ʽ����
enum BRAC_PixelFormat{
	BRAC_PIX_FMT_RGB24 = 0,						///< Packed RGB 8:8:8, 24bpp, RGBRGB...��MEDIASUBTYPE_RGB24��
	BRAC_PIX_FMT_RGB32,							///< ��Ӧ�ڣ�MEDIASUBTYPE_RGB32��Packed RGB 8:8:8, 32bpp, (msb)8A 8R 8G 8B(lsb), in cpu endianness
	BRAC_PIX_FMT_YV12,							///< ��Ӧ�ڣ�MEDIASUBTYPE_YV12��Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	BRAC_PIX_FMT_YUY2,							///< ��Ӧ�ڣ�MEDIASUBTYPE_YUY2��Packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
	BRAC_PIX_FMT_YUV420P,						///< Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	BRAC_PIX_FMT_RGB565,						///< ��Ӧ�ڣ�MEDIASUBTYPE_RGB565
	BRAC_PIX_FMT_RGB555,						///< ��Ӧ�ڣ�MEDIASUBTYPE_RGB555
};

// ��Ƶ�豸����
enum BRAC_AudioDevice{
	BRAC_AD_WAVEIN = 0,							///< �����豸��Mic
	BRAC_AD_WAVEOUT,							///< ����豸��Wave
};

// ��Ƶ��ʾ��������
enum BRAC_VideoShowDriver{
	BRAC_VSD_DEFAULT = 0,						///< Ĭ����ʾ����
	BRAC_VSD_DIRECTSHOW,						///< DirectShow��ʾ����
	BRAC_VSD_WINDOWSGDI,						///< Windows GDI����
};

// ����ģʽ����
#define BRAC_FUNC_VIDEO_CBDATA		0x00000001L	///< ͨ���ص����������Ƶ����
#define BRAC_FUNC_VIDEO_AUTODISP	0x00000002L	///< ��SDK��������Ƶ������Ƶ��ʾ��ָ���Ĵ�����
#define BRAC_FUNC_AUDIO_CBDATA		0x00000004L	///< ͨ���ص����������Ƶ����
#define BRAC_FUNC_AUDIO_AUTOPLAY	0x00000008L	///< ��SDK��������Ƶ��ֱ�Ӳ���
#define BRAC_FUNC_CONFIG_LOCALINI	0x00000010L	///< ���ɱ��������ļ���AnyChatSDK.ini��
#define BRAC_FUNC_FIREWALL_OPEN		0x00000020L	///< ����SDK����Windows����ǽ������ǰӦ�ó���������ǽ�����б�����Windows��ʾ�û��Ƿ���ֹ��ǰӦ�ó���
#define BRAC_FUNC_CHKDEPENDMODULE	0x00000040L	///< �Զ����SDK����������������Զ�ע��
#define BRAC_FUNC_AUDIO_VOLUMECALC	0x00000080L	///< ��SDK�Զ���������������
#define BRAC_FUNC_AUDIO_AUTOVOLUME	0x00000100L	///< ����SDK�Զ�����Mic¼������
#define BRAC_FUNC_NET_SUPPORTUPNP	0x00000200L	///< ����SDK���û������е�UPNP�豸������û���·�������Ƿ���ǽ֧��UPNPЭ�飬������P2P�򶴵ĳɹ���
#define BRAC_FUNC_DISABLEDECODE		0x00000400L	///< ��ֹ���յ������ݽ��н���Ͳ��ţ�Ϊ����ߴ���ͻ��˵�����ת�����ܣ������øñ�־�����������øñ�־


// �ں˲�������
#define BRAC_SO_AUDIO_VADCTRL				1	///< ��Ƶ���������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_NSCTRL				2	///< ��Ƶ�������ƿ��ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_ECHOCTRL				3	///< ��Ƶ�����������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_AGCCTRL				4	///< ��Ƶ�Զ�������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_CPATUREMODE			5	///< ��Ƶ�ɼ�ģʽ���ã�����Ϊ��int�ͣ�0 ����ģʽ��1 �Ÿ�ģʽ��2 ����OKģʽ��3 ��·����ģʽ��
#define BRAC_SO_AUDIO_MICBOOST				6	///< ��Ƶ�ɼ�Mic��ǿ���ƣ�����Ϊ��int�ͣ�0 ȡ����1 ѡ�У�2 �豸������[��ѯʱ����ֵ]��
#define BRAC_SO_AUDIO_AUTOPARAM				7	///< ������Ƶ�ɼ�ģʽ���Զ�ѡ����ʵ���ز������������������������������ʲ����ȣ�����Ϊint�ͣ�1 ���ã�0 �ر�[Ĭ��]��
#define BRAC_SO_AUDIO_MONOBITRATE			8	///< ���õ�����ģʽ����Ƶ����Ŀ�����ʣ�����Ϊ��int�ͣ���λ��bps��
#define BRAC_SO_AUDIO_STEREOBITRATE			9	///< ����˫����ģʽ����Ƶ����Ŀ�����ʣ�����Ϊ��int�ͣ���λ��bps��
#define BRAC_SO_AUDIO_PLAYDRVCTRL			70	///< ��Ƶ��������ѡ�񣨲���Ϊ��int�ͣ�0Ĭ�������� 1 DSound������ 2 WaveOut������
#define BRAC_SO_AUDIO_CNGCTRL				71	///< �����������ɿ��ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_SOFTVOLMODE			73	///< �����������ģʽ���ƣ�����Ϊint�ͣ�1�򿪣�0�ر�[Ĭ��]����ʹ���������ģʽ��������ı�ϵͳ����������

#define BRAC_SO_RECORD_VIDEOBR				10	///< ¼����Ƶ�������ã�����Ϊ��int�ͣ���λ��bps��
#define BRAC_SO_RECORD_AUDIOBR				11	///< ¼����Ƶ�������ã�����Ϊ��int�ͣ���λ��bps��
#define BRAC_SO_RECORD_TMPDIR				12	///< ¼���ļ���ʱĿ¼���ã�����Ϊ�ַ���TCHAR���ͣ������������ľ���·����
#define BRAC_SO_SNAPSHOT_TMPDIR				13	///< �����ļ���ʱĿ¼���ã�����Ϊ�ַ���TCHAR���ͣ������������ľ���·����
#define BRAC_SO_CORESDK_TMPDIR				14	///< ����AnyChat Core SDK��ʱĿ¼������Ϊ�ַ���TCHAR���ͣ������������ľ���·����
#define BRAC_SO_CORESDK_MAGICADJUST			15	///< �ں˵��Բ���
#define BRAC_SO_CORESDK_LOADCODEC			16	///< �����ⲿ�������������Ϊ�ַ���TCHAR���ͣ������������ľ���·���������ļ�����������ļ����ľ���·����
#define BRAC_SO_CORESDK_USEARMV6LIB			17	///< ǿ��ʹ��ARMv6ָ��Ŀ⣬androidƽ̨ʹ�ã�����Ϊ��int�ͣ�1ʹ��ARMv6ָ��� 0�ں��Զ��ж�[Ĭ��]��
#define BRAC_SO_CORESDK_USEHWCODEC			18	///< ʹ��ƽ̨����Ӳ���������������Ϊint�ͣ�0 ��ʹ��Ӳ���������[Ĭ��]  1 ʹ������Ӳ�����������

#define BRAC_SO_CORESDK_PATH				20	///< ����AnyChat Core SDK������·��������Ϊ�ַ���TCHAR���ͣ������������ľ���·����
#define BRAC_SO_CORESDK_DUMPCOREINFO		21	///< ����ں���Ϣ����־�ļ��У����ڷ�������ԭ�򣨲���Ϊ��int�ͣ�1 �����
#define BRAC_SO_CORESDK_MAINVERSION			22	///< ��ѯSDK���汾�źţ�����Ϊint�ͣ�
#define BRAC_SO_CORESDK_SUBVERSION			23	///< ��ѯSDK�Ӱ汾�ţ�����Ϊint�ͣ�
#define BRAC_SO_CORESDK_BUILDTIME			24	///< ��ѯSDK����ʱ�䣨����Ϊ�ַ���TCHAR���ͣ�
#define BRAC_SO_CORESDK_ACTIVESTATE			25	///< Ӧ�ó���״̬���ƣ�����Ϊint�ͣ� 1 Ӧ�ó����ڻ״̬�� 0 Ӧ�ó����ڷǻ״̬����������iPhone���豸����ɺ�̨���еĳ���
#define BRAC_SO_CORESDK_EXTVIDEOINPUT		26	///< �ⲿ��չ��Ƶ������ƣ�����Ϊint�ͣ� 0 �ر��ⲿ��Ƶ����[Ĭ��]�� 1 �����ⲿ��Ƶ���룩
#define BRAC_SO_CORESDK_EXTAUDIOINPUT		27	///< �ⲿ��չ��Ƶ������ƣ�����Ϊint�ͣ� 0 �ر��ⲿ��Ƶ����[Ĭ��]�� 1 �����ⲿ��Ƶ���룩

#define BRAC_SO_LOCALVIDEO_BITRATECTRL		30	///< ������Ƶ�����������ã�����Ϊint�ͣ���λbps��ͬ���������ã�VideoBitrate��
#define BRAC_SO_LOCALVIDEO_QUALITYCTRL		31	///< ������Ƶ�����������ӿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoQuality��
#define BRAC_SO_LOCALVIDEO_GOPCTRL			32	///< ������Ƶ����ؼ�֡������ƣ�����Ϊint�ͣ�ͬ���������ã�VideoGOPSize��
#define BRAC_SO_LOCALVIDEO_FPSCTRL			33	///< ������Ƶ����֡�ʿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoFps��
#define BRAC_SO_LOCALVIDEO_PRESETCTRL		34	///< ������Ƶ����Ԥ��������ƣ�����Ϊint�ͣ�1-5��
#define BRAC_SO_LOCALVIDEO_APPLYPARAM		35	///< Ӧ�ñ�����Ƶ���������ʹ��ǰ���޸ļ�ʱ��Ч������Ϊint�ͣ�1 ʹ���²�����0 ʹ��Ĭ�ϲ�����
#define BRAC_SO_LOCALVIDEO_VIDEOSIZEPOLITIC	36	///< ������Ƶ�ɼ��ֱ��ʿ��Ʋ��ԣ�����Ϊint�ͣ�0 �Զ�������ƥ��[Ĭ��]��1 ʹ�òɼ��豸Ĭ�Ϸֱ��ʣ��������õķֱ��ʲ����ɼ��豸֧��ʱ��Ч
#define BRAC_SO_LOCALVIDEO_DEINTERLACE		37	///< ������Ƶ����֯�������ƣ�����Ϊint�ͣ� 0 �����з���֯����[Ĭ��]��1 ����֯��������������ƵԴ�Ǹ���ɨ��Դ��������źţ�ʱͨ������֯���������߻�������
#define BRAC_SO_LOCALVIDEO_WIDTHCTRL		38	///< ������Ƶ�ɼ��ֱ��ʿ�ȿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoWidth��
#define BRAC_SO_LOCALVIDEO_HEIGHTCTRL		39	///< ������Ƶ�ɼ��ֱ��ʸ߶ȿ��ƣ�����Ϊint�ͣ�ͬ���������ã�VideoHeight��
#define BRAC_SO_LOCALVIDEO_FOCUSCTRL		90	///< ������Ƶ����ͷ�Խ����ƣ�����Ϊint�ͣ�1��ʾ�Զ��Խ��� 0��ʾ�ֶ��Խ���
#define BRAC_SO_LOCALVIDEO_PIXFMTCTRL		91	///< ������Ƶ�ɼ����ȸ�ʽ���ƣ�����Ϊint�ͣ�-1��ʾ����ƥ�䣬�������Ȳ���ָ����ʽ���ο���BRAC_PixelFormat��
#define BRAC_SO_LOCALVIDEO_OVERLAY			92	///< ������Ƶ����Overlayģʽ������Ϊint�ͣ�1��ʾ����Overlayģʽ�� 0��ʾ��ͨģʽ[Ĭ��]��
#define BRAC_SO_LOCALVIDEO_CODECID			93	///< ������Ƶ������ID���ã�����Ϊint�ͣ�-1��ʾĬ�ϣ�������õı�����ID�����ڣ����ں˻����Ĭ�ϵı�������

#define BRAC_SO_NETWORK_P2PPOLITIC			40	///< ��������P2P���Կ��ƣ�����Ϊ��int�ͣ�0 ��ֹ����P2P��1 ����������P2P[Ĭ��]��2 �ϲ�Ӧ�ÿ���P2P���ӣ�3 ���轨��P2P���ӣ�
#define BRAC_SO_NETWORK_P2PCONNECT			41	///< ������ָ���û�����P2P���ӣ�����Ϊint�ͣ���ʾĿ���û�ID�������ӽ����ɹ��󣬻�ͨ����Ϣ�������ϲ�Ӧ�ã�P2P���Ʋ���=2ʱ��Ч
#define BRAC_SO_NETWORK_P2PBREAK			42	///< �Ͽ���ָ���û���P2P���ӣ�����Ϊint�ͣ���ʾĿ���û�ID��[�ݲ�֧�֣�����]
#define BRAC_SO_NETWORK_TCPSERVICEPORT		43	///< ���ñ���TCP����˿ڣ�����Ϊint�ͣ������ӷ�����֮ǰ������Ч
#define BRAC_SO_NETWORK_UDPSERVICEPORT		44	///< ���ñ���UDP����˿ڣ�����Ϊint�ͣ������ӷ�����֮ǰ������Ч
#define BRAC_SO_NETWORK_MULTICASTPOLITIC	45	///< �鲥���Կ��ƣ�����Ϊint�ͣ�0 ִ�з�����·�ɲ��ԣ���ֹ�鲥����[Ĭ��]�� 1 ���Է�����·�ɲ��ԣ�ֻ���鲥��㲥ý������ 2 ִ�з�����·�ɲ��ԣ�ͬʱ�鲥��
#define BRAC_SO_NETWORK_TRANSBUFMAXBITRATE	46	///< ���仺�������ļ�������ʿ��ƣ�����Ϊint�ͣ�0 �����ƣ���������ʴ���[Ĭ��]�� �����ʾ�������ʣ���λΪ��bps��

#define BRAC_SO_PROXY_FUNCTIONCTRL			50	///< �����û������ܿ��ƣ�������Ϊ��int�ͣ�1��������0�رմ���[Ĭ��]��
#define BRAC_SO_PROXY_VIDEOCTRL				51	///< �����û�������Ƶ���ƣ���������Ƶ��Ϊָ���û�����Ƶ���ⷢ��������Ϊint�ͣ���ʾ�����û���userid��
#define BRAC_SO_PROXY_AUDIOCTRL				52	///< �����û�������Ƶ���ƣ���������Ƶ��Ϊָ���û�����Ƶ���ⷢ��������ͬBRAC_SO_PROXY_VIDEOCTRL��

#define BRAC_SO_STREAM_BUFFERTIME			60	///< ������ʱ�䣨����Ϊint�ͣ���λ�����룬ȡֵ��Χ��500 ~ 5000��Ĭ�ϣ�800��

#define BRAC_SO_VIDEOSHOW_MODECTRL			80	///< ��Ƶ��ʾģʽ���ƣ�����Ϊ��int�ͣ�0 ��������ʾ��1 ��Ƶ������ʾ��
#define BRAC_SO_VIDEOSHOW_SETPRIMARYUSER	81	///< ��������ʾ�û���ţ�����Ϊ��int�ͣ��û�ID�ţ�
#define BRAC_SO_VIDEOSHOW_SETOVERLAYUSER	82	///< ���õ�����ʾ�û���ţ�����Ϊ��int�ͣ��û�ID�ţ�
#define BRAC_SO_VIDEOSHOW_DRIVERCTRL		83	///< ��Ƶ��ʾ�������ƣ�����Ϊ��int�ͣ�0 Ĭ�������� 1 Windows DirectShow��2 Windows GDI��3 SDL��


// ����������Ϣ��������
#define BRAC_TRANSTASK_PROGRESS				1	///< ����������Ȳ�ѯ������Ϊ��DOUBLE�ͣ�0.0 ~ 100.0����
#define BRAC_TRANSTASK_BITRATE				2	///< ��������ǰ�������ʣ�����Ϊ��int�ͣ���λ��bps��
#define BRAC_TRANSTASK_STATUS				3	///< ��������ǰ״̬������Ϊ��int�ͣ�


// ¼���ܱ�־����
#define BRAC_RECORD_FLAGS_VIDEO		0x00000001L	///< ¼����Ƶ
#define BRAC_RECORD_FLAGS_AUDIO		0x00000002L	///< ¼����Ƶ

// �鲥���ܱ�־����
#define BRAC_MCFLAGS_JOINGROUP		0x00000001L	///< ����ಥ��
#define BRAC_MCFLAGS_LEAVEGROUP		0x00000002L	///< �뿪�ಥ��
#define BRAC_MCFLAGS_SENDDATA		0x00000010L	///< ���ݷ��ͱ�־��ָʾ�öಥ�����ڷ�������
#define BRAC_MCFLAGS_RECVDATA		0x00000020L	///< ���ݽ��ձ�־��ָʾ�öಥ�����ڽ�������


// �û�״̬��־����
#define BRAC_USERSTATE_CAMERA				1	///< �û�����ͷ״̬������ΪDWORD�ͣ�
#define BRAC_USERSTATE_HOLDMIC				2	///< �û���Ƶ�豸״̬������ΪDWORD�ͣ�����ֵ��0 ��Ƶ�ɼ��رգ� 1 ��Ƶ�ɼ�������
#define BRAC_USERSTATE_SPEAKVOLUME			3	///< �û���ǰ˵������������ΪDOUBLE���ͣ�0.0 ~ 100.0����
#define BRAC_USERSTATE_RECORDING			4	///< �û�¼������״̬������ΪDWORD�ͣ�
#define	BRAC_USERSTATE_LEVEL				5	///< �û����𣨲���ΪDWORD�ͣ�
#define BRAC_USERSTATE_NICKNAME				6	///< �û��ǳƣ�����Ϊ�ַ���TCHAR���ͣ�
#define BRAC_USERSTATE_LOCALIP				7	///< �û�����IP��ַ������������Ϊ�ַ���TCHAR���ͣ�
#define BRAC_USERSTATE_INTERNETIP			8	///< �û�������IP��ַ������Ϊ�ַ���TCHAR���ͣ�
#define BRAC_USERSTATE_VIDEOBITRATE			9	///< �û���ǰ����Ƶ���ʣ�����ΪDWORD���ͣ�Bps��
#define BRAC_USERSTATE_AUDIOBITRATE			10	///< �û���ǰ����Ƶ���ʣ�����ΪDWORD���ͣ�Bps��
#define BRAC_USERSTATE_P2PCONNECT			11	///< ��ѯ�����û���ָ���û��ĵ�ǰP2P����״̬������ΪDWORD���ͣ�����ֵ��0 P2P��ͨ�� 1 P2P���ӳɹ�[TCP]��2 P2P���ӳɹ�[UDP]��3 P2P���ӳɹ�[TCP��UDP]��
#define BRAC_USERSTATE_NETWORKSTATUS		12	///< ��ѯָ���û�������״̬������ΪDWORD���ͣ�����ֵ��0 ������1 �Ϻã�2 һ�㣬3 �ϲ4 �ǳ����ע����ѯ�����Ҫ>1s
#define BRAC_USERSTATE_VIDEOSIZE			13	///< ��ѯָ���û�����Ƶ�ֱ��ʣ�����ΪDWORD���ͣ�����ֵ����16λ��ʾ��ȣ���16λ��ʾ�߶ȣ�

// ��Ƶ���ݻص���������
typedef void (CALLBACK * BRAC_VideoData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue);
// ��Ƶ������չ�ص��������壨����ʱ�����
typedef void (CALLBACK * BRAC_VideoDataEx_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, DWORD dwTimeStamp, LPVOID lpUserValue);
// ��Ƶ���ݻص���������
typedef void (CALLBACK * BRAC_AudioData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue);
// ��Ƶ������չ�ص��������壨����ʱ�����
typedef void (CALLBACK * BRAC_AudioDataEx_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, DWORD dwTimeStamp, LPVOID lpUserValue);
// ������Ϣ�ص���������
typedef void (CALLBACK * BRAC_TextMessage_CallBack)(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue);
// ͸��ͨ�����ݻص���������
typedef void (CALLBACK * BRAC_TransBuffer_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// ͸��ͨ��������չ�ص���������
typedef void (CALLBACK * BRAC_TransBufferEx_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// �ļ�����ص���������
typedef void (CALLBACK * BRAC_TransFile_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// �����仯�ص���������
typedef void (CALLBACK * BRAC_VolumeChange_CallBack)(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue);
// SDK Filter ͨ�����ݻص���������
typedef void (CALLBACK * BRAC_SDKFilterData_CallBack)(LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// ¼�񡢿���������ɻص���������
typedef void (CALLBACK * BRAC_RecordSnapShot_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType, LPVOID lpUserValue);
// �첽��Ϣ֪ͨ�ص���������
typedef void (CALLBACK* BRAC_NotifyMessage_CallBack)(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
// ��Ƶ��Ļ�¼��ص���������
typedef void (CALLBACK * BRAC_VideoScreenEvent_CallBack)(DWORD dwUserid, DWORD type, DWORD key, DWORD dwFlags, DWORD wParam, DWORD lParam, LPVOID lpUserValue);

/**
 *	API��������
 */

// ��ȡSDK�汾��Ϣ
BRAC_API DWORD BRAC_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, TCHAR* lpCompileTime, DWORD dwBufLen);
// ����رգ�SDK������־
BRAC_API DWORD BRAC_ActiveCallLog(BOOL bActive);

// ���÷�������֤���루��������ֹ�Ƿ��û���SDK���ӷ��������Ϸ��û����������ӣ�
BRAC_API DWORD BRAC_SetServerAuthPass(LPCTSTR lpPassword);
// ��ʼ��ϵͳ
BRAC_API DWORD BRAC_InitSDK(HWND hWnd, DWORD dwFuncMode);

// ������Ƶ���ݻص�����
BRAC_API DWORD BRAC_SetVideoDataCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶ������չ�ص�����������ʱ�����
BRAC_API DWORD BRAC_SetVideoDataExCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoDataEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶ���ݻص�����
BRAC_API DWORD BRAC_SetAudioDataCallBack(BRAC_AudioData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶ���ݻص���չ����������ʱ�����
BRAC_API DWORD BRAC_SetAudioDataExCallBack(BRAC_AudioDataEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����������Ϣ�ص�����
BRAC_API DWORD BRAC_SetTextMessageCallBack(BRAC_TextMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����͸��ͨ�����ݻص�����
BRAC_API DWORD BRAC_SetTransBufferCallBack(BRAC_TransBuffer_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����͸��ͨ��������չ�ص�����
BRAC_API DWORD BRAC_SetTransBufferExCallBack(BRAC_TransBufferEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// �����ļ�����ص�����
BRAC_API DWORD BRAC_SetTransFileCallBack(BRAC_TransFile_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ���������仯�ص�����
BRAC_API DWORD BRAC_SetVolumeChangeCallBack(BRAC_VolumeChange_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����SDK Filterͨ�����ݻص���������
BRAC_API DWORD BRAC_SetSDKFilterDataCallBack(BRAC_SDKFilterData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����¼������������֪ͨ�ص�����
BRAC_API DWORD BRAC_SetRecordSnapShotCallBack(BRAC_RecordSnapShot_CallBack lpFunction, LPVOID lpUserValue=NULL);
// �����첽��Ϣ֪ͨ�ص�����
BRAC_API DWORD BRAC_SetNotifyMessageCallBack(BRAC_NotifyMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶ��Ļ�¼��ص�����
BRAC_API DWORD BRAC_SetScreenEventCallBack(BRAC_VideoScreenEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);


// ���ӷ�����
BRAC_API DWORD BRAC_Connect(LPCTSTR lpServerAddr, DWORD dwPort);
// ��¼ϵͳ
BRAC_API DWORD BRAC_Login(LPCTSTR lpUserName, LPCTSTR lpPassword, DWORD dwPassEncType);
// ���뷿��
BRAC_API DWORD BRAC_EnterRoom(DWORD dwRoomid, LPCTSTR lpRoomPass, DWORD dwPassEncType);
// ���뷿��
BRAC_API DWORD BRAC_EnterRoomEx(LPCTSTR lpRoomName, LPCTSTR lpRoomPass);
// �뿪����
BRAC_API DWORD BRAC_LeaveRoom(DWORD dwRoomid);
// ע��ϵͳ
BRAC_API DWORD BRAC_Logout(VOID);

// �ͷ�������Դ
BRAC_API DWORD BRAC_Release(VOID);

// ��ȡ��ǰ���������û��б�
BRAC_API DWORD BRAC_GetOnlineUser(LPDWORD lpUserIDArray, DWORD& dwUserNum);
// ��ѯ�û�����ͷ��״̬
BRAC_API DWORD BRAC_GetCameraState(DWORD dwUserid, DWORD& dwState);
// ��ѯ�û�����״̬
BRAC_API DWORD BRAC_GetSpeakState(DWORD dwUserid, DWORD& dwState);
// ��ѯ�û�����
BRAC_API DWORD BRAC_GetUserLevel(DWORD dwUserid, DWORD& dwLevel);
// ��ѯ�û�����
BRAC_API DWORD BRAC_GetUserName(DWORD dwUserid, TCHAR* lpUserName, DWORD dwLen);
// ��ѯ��������
BRAC_API DWORD BRAC_GetRoomName(DWORD dwRoomId, TCHAR* lpRoomName, DWORD dwLen);
// ��ʾ������Ƶ������ڶԻ���
BRAC_API DWORD BRAC_ShowLVProperty(HWND hParent, LPCTSTR szCaption=NULL, DWORD dwX=0, DWORD dwY=0);

// ��ѯָ���û����״̬
BRAC_API DWORD BRAC_QueryUserState(DWORD dwUserId, int infoname, char FAR* infoval, int infolen);

// ö�ٱ�����Ƶ�ɼ��豸
BRAC_API DWORD BRAC_EnumVideoCapture(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// ѡ��ָ������Ƶ�ɼ��豸
BRAC_API DWORD BRAC_SelectVideoCapture(LPCTSTR szCaptureName);
// ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
BRAC_API DWORD BRAC_GetCurVideoCapture(TCHAR* lpDeviceName, DWORD dwLen);
// ö�ٱ�����Ƶ�ɼ��豸
BRAC_API DWORD BRAC_EnumAudioCapture(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// ѡ��ָ������Ƶ�ɼ��豸
BRAC_API DWORD BRAC_SelectAudioCapture(LPCTSTR szCaptureName);
// ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
BRAC_API DWORD BRAC_GetCurAudioCapture(TCHAR* lpDeviceName, DWORD dwLen);
// ö�ٱ�����Ƶ�����豸
BRAC_API DWORD BRAC_EnumAudioPlayback(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// ѡ��ָ������Ƶ�����豸
BRAC_API DWORD BRAC_SelectAudioPlayback(LPCTSTR szDeviceName);
// ��ȡ��ǰʹ�õ���Ƶ�����豸
BRAC_API DWORD BRAC_GetCurAudioPlayback(TCHAR* lpDeviceName, DWORD dwLen);

// �����û���Ƶ
BRAC_API DWORD BRAC_UserCameraControl(DWORD dwUserid, BOOL bOpen);
// �����û�����
BRAC_API DWORD BRAC_UserSpeakControl(DWORD dwUserid, BOOL bOpen);
// ������Ƶ��ʾλ��
BRAC_API DWORD BRAC_SetVideoPos(DWORD dwUserid, HWND hWnd, DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom);
// �ػ�ָ���û�����Ƶ
BRAC_API DWORD BRAC_RepaintVideo(DWORD dwUserId, HDC hDC);

// ��ȡָ����Ƶ�豸�ĵ�ǰ����
BRAC_API DWORD BRAC_AudioGetVolume(BRAC_AudioDevice device, DWORD& dwVolume);
// ����ָ����Ƶ�豸������
BRAC_API DWORD BRAC_AudioSetVolume(BRAC_AudioDevice device, DWORD dwVolume);

// �û�������Ƶ¼��
BRAC_API DWORD BRAC_StreamRecordCtrl(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam);
// ���û�����Ƶ����ץ�ģ����գ�
BRAC_API DWORD BRAC_SnapShot(DWORD dwUserId, DWORD dwFlags, DWORD dwParam);

// ͸��ͨ�����ͻ�����
BRAC_API DWORD BRAC_TransBuffer(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
// ͸��ͨ�����ͻ�������չ
BRAC_API DWORD BRAC_TransBufferEx(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// �����ļ�
BRAC_API DWORD BRAC_TransFile(DWORD dwUserid, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// ��ѯ�������������Ϣ
BRAC_API DWORD BRAC_QueryTransTaskInfo(DWORD dwUserid, DWORD dwTaskId, int infoname, char FAR* infoval, int infolen);
// ȡ����������
BRAC_API DWORD BRAC_CancelTransTask(DWORD dwUserid, DWORD dwTaskId);
// �����ı���Ϣ
BRAC_API DWORD BRAC_SendTextMessage(DWORD dwUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);
// ����SDK Filter ͨ������
BRAC_API DWORD BRAC_SendSDKFilterData(LPBYTE lpBuf, DWORD dwLen);

// ���ĵ�ǰ������ģʽ
BRAC_API DWORD BRAC_ChangeChatMode(DWORD dwChatMode);
// ��ȡָ���û���ǰ������ģʽ
BRAC_API DWORD BRAC_GetUserChatMode(DWORD dwUserid, DWORD& dwChatMode);
// ������Է�˽�ģ���Է�����˽������
BRAC_API DWORD BRAC_PrivateChatRequest(DWORD dwUserid);
// �ظ��Է���˽������
BRAC_API DWORD BRAC_PrivateChatEcho(DWORD dwUserid, DWORD dwRequestid,BOOL bAccept);
// �ظ��Է���˽��������չ�����Ը���������룩
BRAC_API DWORD BRAC_PrivateChatEchoEx(DWORD dwUserid, DWORD dwRequestid,DWORD dwErrorCode);
// �˳���ĳ�û���˽�ģ����߽�ĳ�û����Լ���˽���б������
BRAC_API DWORD BRAC_PrivateChatExit(DWORD dwUserid);

// SDK�ں˲�������
BRAC_API DWORD BRAC_SetSDKOption(int optname, const char FAR* optval, int optlen);
// SDK�ں˲���״̬��ѯ
BRAC_API DWORD BRAC_GetSDKOption(int optname, char FAR* optval, int optlen);

// �鲥���ܿ���
BRAC_API DWORD BRAC_MultiCastControl(LPCTSTR lpMultiCastAddr, DWORD dwPort, LPCTSTR lpNicAddr, DWORD dwTTL, DWORD dwFlags);

// �����ⲿ������Ƶ��ʽ
BRAC_API DWORD BRAC_SetInputVideoFormat(BRAC_PixelFormat pixFmt, DWORD dwWidth, DWORD dwHeight, DWORD dwFps, DWORD dwFlags);
// �ⲿ��Ƶ��������
BRAC_API DWORD BRAC_InputVideoData(LPBYTE lpVideoFrame, DWORD dwSize, DWORD dwTimeStamp);
// �����ⲿ������Ƶ��ʽ
BRAC_API DWORD BRAC_SetInputAudioFormat(DWORD dwChannels, DWORD dwSamplesPerSec, DWORD dwBitsPerSample, DWORD dwFlags);
// �ⲿ��Ƶ��������
BRAC_API DWORD BRAC_InputAudioData(LPBYTE lpSamples, DWORD dwSize, DWORD dwTimeStamp);


#endif //BR_ANYCHAT_CORE_SDK_H__INCLUDED_
