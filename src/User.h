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

class CClientConnection;
class CIRCConnection;
class CConfig;
class CLog;
class CTrafficStats;
class CKeyring;
class CTimer;

/**
 * badlogin_t
 *
 * Describes a failed login attempt.
 */
typedef struct badlogin_s {
	sockaddr_in Address;
	unsigned int Count;
} badlogin_t;

#ifndef SWIG
bool BadLoginTimer(time_t Now, void *User);
bool UserReconnectTimer(time_t Now, void *User);
#endif

class CUser {
	friend class CCore;
#ifndef SWIG
	friend bool BadLoginTimer(time_t Now, void *User);
	friend bool UserReconnectTimer(time_t Now, void *User);
#endif

	char *m_Name; /**< the name of the user */

	CClientConnection *m_Client; /**< the user's client connection */
	CIRCConnection *m_IRC; /**< the user's irc connection */
	CConfig *m_Config; /**< the user's configuration object */
	CLog *m_Log; /**< the user's log file */

	time_t m_ReconnectTime;
	time_t m_LastReconnect;

	bool m_Locked; /**< determines whether the user is locked/suspended */

	CVector<badlogin_t> m_BadLogins; /**< a list of failed login attempts for this user */

	CVector<char *> m_HostAllows; /**< a list of hosts which are able to use this account */

	CTrafficStats *m_ClientStats; /**< traffic stats for the user's client connection(s) */
	CTrafficStats *m_IRCStats; /**< traffic stats for the user's irc connection(s) */

	CKeyring *m_Keys; /**< a list of channel keys */

	CTimer *m_BadLoginPulse;
	CTimer *m_ReconnectTimer;

	int m_IsAdminCache; /**< cached value which determines whether the user is an admin */

	CVector<X509 *> m_ClientCertificates;

	bool PersistCertificates(void);

	void UpdateHosts(void);
	void BadLoginPulse(void);
public:
#ifndef SWIG
	CUser(const char *Name);
#endif
	virtual ~CUser(void);

	virtual SOCKET GetIRCSocket(void);
	virtual CClientConnection *GetClientConnection(void);
	virtual CIRCConnection *GetIRCConnection(void);
	virtual bool IsConnectedToIRC(void);

	virtual bool Validate(const char *Password);
	virtual void Attach(CClientConnection *Client);

	virtual const char *GetNick(void);
	virtual void SetNick(const char *Nick);

	virtual const char *GetRealname(void);
	virtual void SetRealname(const char *Realname);

	virtual const char *GetUsername(void);
	virtual CConfig *GetConfig(void);

	virtual void Simulate(const char *Command, CClientConnection *FakeClient = NULL);

	virtual void Reconnect(void);

	virtual bool ShouldReconnect(void);
	virtual void ScheduleReconnect(int Delay = 10);

	virtual void Notice(const char *Text);
	virtual void RealNotice(const char *Text);

	virtual unsigned int GetIRCUptime(void);

	virtual CLog *GetLog(void);
	virtual void Log(const char *Format, ...);

	virtual void Lock(void);
	virtual void Unlock(void);
	virtual bool IsLocked(void);

	virtual void SetIRCConnection(CIRCConnection *IRC);
	virtual void SetClientConnection(CClientConnection *Client, bool DontSetAway = false);

	virtual void SetAdmin(bool Admin = true);
	virtual bool IsAdmin(void);

	virtual void SetPassword(const char *Password);

	virtual void SetServer(const char *Server);
	virtual const char *GetServer(void);

	virtual void SetPort(int Port);
	virtual int GetPort(void);

	virtual void MarkQuitted(void);

	virtual void LoadEvent(void);

	virtual void LogBadLogin(sockaddr_in Peer);
	virtual bool IsIpBlocked(sockaddr_in Peer);

	virtual void AddHostAllow(const char *Mask, bool UpdateConfig = true);
	virtual void RemoveHostAllow(const char *Mask, bool UpdateConfig = true);
	virtual CVector<char *> *GetHostAllows(void);
	virtual bool CanHostConnect(const char *Host);

	virtual CTrafficStats *GetClientStats(void);
	virtual CTrafficStats *GetIRCStats(void);

	virtual CKeyring *GetKeyring(void);

	virtual time_t GetLastSeen(void);

	virtual const char *GetAwayNick(void);
	virtual void SetAwayNick(const char *Nick);

	virtual const char *GetAwayText(void);
	virtual void SetAwayText(const char *Reason);

	virtual const char *GetVHost(void);
	virtual void SetVHost(const char *VHost);

	virtual int GetDelayJoin(void);
	virtual void SetDelayJoin(int DelayJoin);

	virtual const char *GetConfigChannels(void);
	virtual void SetConfigChannels(const char *Channels);

	virtual const char *GetSuspendReason(void);
	virtual void SetSuspendReason(const char *Reason);

	virtual const char *GetServerPassword(void);
	virtual void SetServerPassword(const char *Password);

	virtual const char *GetAutoModes(void);
	virtual void SetAutoModes(const char *AutoModes);

	virtual const char *GetDropModes(void);
	virtual void SetDropModes(const char *DropModes);

	virtual CVector<X509 *> *GetClientCertificates(void);
	virtual bool AddClientCertificate(X509 *Certificate);
	virtual bool RemoveClientCertificate(X509 *Certificate);
	virtual bool FindClientCertificate(X509 *Certificate);

	virtual void SetSSL(bool SSL);
	virtual bool GetSSL(void);

	virtual void SetIdent(const char *Ident);
	virtual const char *GetIdent(void);
};