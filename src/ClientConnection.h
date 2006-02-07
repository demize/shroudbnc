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

class CTimer;
class CClientDnsEvents;
class CAssocArray;

class CClientConnection : public CConnection, public COwnedObject<CUser> {
	char *m_Nick;
	char *m_Password;
	char *m_Username;
	sockaddr_in m_Peer;
	char *m_PeerName;

	CClientDnsEvents *m_DnsEvents;

	commandlist_t m_CommandList;

#ifndef SWIG
	adns_query m_PeerA;
#endif

	bool ValidateUser();
public:
#ifndef SWIG
	CClientConnection(SOCKET Socket, sockaddr_in Peer, bool SSL = false);
	CClientConnection(SOCKET Client, CAssocArray *Box, CUser *Owning);
#endif
	virtual ~CClientConnection(void);

	virtual bool ParseLineArgV(int argc, const char** argv);
	virtual void ParseLine(const char* Line);
	virtual bool ProcessBncCommand(const char* Subcommand, int argc, const char** argv, bool NoticeUser);

	virtual const char* GetNick(void);

	virtual void SetOwner(CUser* Owner);

	virtual void AsyncDnsFinishedClient(hostent* response);
	virtual void SetPeerName(const char* PeerName, bool LookupFailure);
	virtual adns_query GetPeerDNSQuery(void);

	virtual const char* GetPeerName(void);
	virtual sockaddr_in GetPeer(void);

	virtual bool Read(bool DontProcess = false);
	virtual void Destroy(void);
	virtual const char* GetClassName(void);
	virtual void WriteUnformattedLine(const char* In);

	virtual bool Freeze(CAssocArray *Box);

	virtual void Kill(const char *Error);

	virtual commandlist_t *GetCommandList(void);
};
