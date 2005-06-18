/*******************************************************************************
 * shroudBNC - an object-oriented framework for IRC                            *
 * Copyright (C) 2005 Gunnar Beutner                                           *
 *                                                                             *
 * This program is free software; you can redistribute it and/or               *
 * modify it under the terms of the GNU General Public License                 *
 * as published by the Free Software Foundation; either version 2              *
 * of the License, or (at your option) any later version.                      *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with this program; if not, write to the Free Software                 *
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. *
 *******************************************************************************/

#if !defined(AFX_TCLCLIENTSOCKET_H__95D5FA95_A580_4446_89B8_C5F60A0F9A9F__INCLUDED_)
#define AFX_TCLCLIENTSOCKET_H__95D5FA95_A580_4446_89B8_C5F60A0F9A9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTclClientSocket : public CSocketEvents {
public:
	CTclClientSocket(SOCKET Socket, sockaddr_in Peer);
	virtual ~CTclClientSocket();

	virtual void Destroy(void);

	virtual bool Read(void);
	virtual void Write(void);
	virtual void Error(void);
	virtual bool HasQueuedData(void);
	virtual bool DoTimeout(void);

	virtual void SetControlProc(const char* Proc);
	virtual const char* GetControlProc(void);
	virtual void WriteLine(const char* Line);
private:
	SOCKET m_Socket;
	CConnection* m_Wrap;
	const char* m_Control;
};

#endif // !defined(AFX_TCLCLIENTSOCKET_H__95D5FA95_A580_4446_89B8_C5F60A0F9A9F__INCLUDED_)