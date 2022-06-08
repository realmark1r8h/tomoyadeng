// Created by amoylel on 08/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_ACTIONPREPROCESSOR_H__
#define AMO_ACTIONPREPROCESSOR_H__

#include <amo/stdint.hpp>

namespace amo {

    /*!
     * @class	Ԥ���¼�
     *
     * @id settingsActionPreprocessor
     *
     * @desc Ԥ���¼�
     *
     * @chapter settings
     *
     * @brief	Ԥ���¼�,���ڴ���˵�����ȫ�ֿ�ݼ���action���������¼������actionΪ�������������¼�����ô����ᴦ����Щ�¼�������ֹ�¼���ҳ�洫��.
     */
    
    class ActionPreprocessor {
    public:
        ActionPreprocessor(int32_t nBrowserID = -9999, int64_t nFrameID = -1);
        
        /*!
         * @fn	bool ActionPreprocessor::process(const std::string& action);
         * @ignore
         * @brief	Process the given action.
         *
         * @param	action	The action.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool process(const std::string& action);
        
        /*! @var	#String undo  ������������Frame*/
        /*! @var	#String redo  ������������Frame*/
        /*! @var	#String cut  ���У�������Frame*/
        /*! @var	#String copy  ���ƣ�������Frame*/
        /*! @var	#String paste  ճ����������Frame*/
        /*! @var	#String selectAll  ȫѡ��������Frame*/
        /*! @var	#String delete  ɾ����������Frame*/
        
        /*! @var	#String goBack  ���ˣ�������Browser*/
        /*! @var	#String goForward  ǰ����������Browser*/
        /*! @var	#String reload  �������¼��ص�ǰ���ڣ�������Browser*/
        /*! @var	#String forceReload  ���Ի��沢���¼��ص�ǰ���ڣ�������Browser*/
        /*! @var	#String stopLoad  ֹͣ���أ�������Browser*/
        
        
        /*! @var	#String print  ��ӡҳ�棬������HOST*/
        /*! @var	#String printToPDF  ��ӡҳ��ΪPDF��������HOST*/
        /*! @var	#String resetZoom  ����ҳ�����ŵȼ���������HOST*/
        /*! @var	#String zoomIn  ��Сҳ�棬������HOST*/
        /*! @var	#String zoomOut  �Ŵ�ҳ�棬������HOST*/
        
        /*! @var	#String show  ��ʾ����*/
        /*! @var	#String hide  ���ش���*/
        /*! @var	#String toggleVisible  ��ʾ/���ش���*/
        /*! @var	#String minimize  ��С������*/
        /*! @var	#String maximize  ��󻯴���*/
        /*! @var	#String close  �رմ���*/
        /*! @var	#String showDevtools  �򿪵��Դ���*/
        /*! @var	#String closeDevtools  �رյ��Դ���*/
        /*! @var	#String fullscreen  ȫ��*/
        /*! @var	#String nonFullscreen  �˳�ȫ��*/
        /*! @var	#String toggleFullScreen  ȫ��/�˳�ȫ��*/
        
        /*! @var	#String quit  �����˳�����*/
        /*! @var	#String exit  ǿ���˳�����*/
        
        
        
    private:
        /*! @brief	Identifier for the browser. */
        int32_t m_nBrowserID;
        /*! @brief	Identifier for the frame. */
        int64_t m_nFrameID;
    };
}

#endif // AMO_ACTIONPREPROCESSOR_H__

