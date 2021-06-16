// Created by amoylel on 09/08/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TRAYBASE_H__
#define AMO_TRAYBASE_H__




#include <amo/timer.hpp>

namespace amo {
    /*!
     * @class	TrayBase
     *
     * @brief	���̸������������ɼ��������Ϣ.
     *     * ���� http://www.codeguru.com/cpp/com-tech/activex/tutorials/article.php/c8115/How-to-Implement-a-Mouse-HoverLeave-Message-on-the-System-Tray.htm
     */
    class TrayBase {
    public:
        /*! @brief	The point mouse. */
        POINT m_ptMouse;
        /*! @brief	Handle of the thread. */
        HANDLE m_hThread;
        /*! @brief	Handle of the exit event. */
        HANDLE m_hExitEvent;
        /*! @brief	true to track mouse. */
        bool m_bTrackMouse;
        /*! @brief	true to mouse hover. */
        bool m_bMouseHover;
        /*! @brief	The create struct. */
        CRITICAL_SECTION	m_cs;
        /*! @brief	The mouse enter timer. */
        amo::timer m_MouseEnterTimer;
        
    public:
        TrayBase();
        virtual ~TrayBase();
        
        static UINT CALLBACK TrackMousePt(PVOID pvClass);
        void OnMouseMove();
        bool IsMouseHover();
        
    protected:
        /*!
         * @fn	virtual void TrayBase::OnMouseEnter() = 0;
         *
         * @brief	�����������¼�.
         */
        virtual void OnMouseEnter() = 0;
        /*!
         * @fn	virtual void TrayBase::OnMouseHover() = 0;
         *
         * @brief	���������ͣ�¼�.
         */
        virtual void OnMouseHover() = 0;
        /*!
         * @fn	virtual void TrayBase::OnMouseLeave() = 0;
         *
         * @brief	��������뿪�¼�.
         */
        virtual void OnMouseLeave() = 0;
    };
}



#endif // AMO_TRAYBASE_H__